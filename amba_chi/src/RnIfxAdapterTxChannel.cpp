#include <RnIfxAdapterTxChannel.h>
#include <ELinkState.h>
#include <flits/ChiReqFlit.h>
#include <flits/ChiDatFlit.h>
#include <flits/ChiRspFlit.h>

RnIfxAdapterTxChannel::RnIfxAdapterTxChannel(sc_core::sc_module_name module_name)
    : sc_core::sc_module(module_name)
    , module_initialized_(false)
    , req_credit_counter_(0)
    , dat_credit_counter_(0)
    , rsp_credit_counter_(0)
    , link_state_current_(ELinkState::STOP)
    , link_state_next_(ELinkState::STOP)
{
    SC_METHOD(main_process);
    sensitive << intfrx_clk_in.pos() << rstb_intfrx_clk_in.neg();
    dont_initialize();

    std::cout << name() << " elaborated\n";
}

void RnIfxAdapterTxChannel::initialize()
{
    assert(!module_initialized_ && "Module must only be initialized once");
    reset();
    module_initialized_ = true;
}

void RnIfxAdapterTxChannel::send_chi_req(const chi::ChiExtension* message)
{
    flits::ChiReqFlit req_flit;
    req_flit.set_qos(message->qos);
    req_flit.set_opcode(static_cast<uint8_t>(message->req_fields.opcode));
    req_flit.set_srcid(message->req_fields.src_id);
    req_flit.set_tgtid(message->req_fields.tgt_id);
    req_flit.set_returnnid(message->req_fields.return_nid);
    req_flit.set_allowretry(message->req_fields.allow_retry);
    req_flit.set_order(message->req_fields.order);

    sc_dt::sc_uint<4> mem_attr;
    mem_attr.set(0, message->req_fields.mem_attr.allocate);
    mem_attr.set(1, message->req_fields.mem_attr.cacheable);
    mem_attr.set(2, message->req_fields.mem_attr.device);
    mem_attr.set(3, message->req_fields.mem_attr.ewa);
    req_flit.set_memattr(mem_attr);

    req_flit.set_dodwt(message->req_fields.do_dwt);
    req_flit.set_expcompack(message->req_fields.exp_comp_ack);
}

void RnIfxAdapterTxChannel::send_chi_wdat(const chi::ChiExtension* message)
{
    flits::ChiDatFlit wdat_flit;
    wdat_flit.set_qos(message->qos);
    wdat_flit.set_opcode(static_cast<uint8_t>(message->dat_fields.opcode));
    wdat_flit.set_srcid(message->dat_fields.src_id);
    wdat_flit.set_tgtid(message->dat_fields.tgt_id);
    wdat_flit.set_homenid(message->dat_fields.home_n_id);
    wdat_flit.set_resp(static_cast<uint8_t>(message->dat_fields.resp));
    wdat_flit.set_fwdstate(static_cast<uint8_t>(message->dat_fields.fwd_state));
    wdat_flit.set_dbid(message->dat_fields.dbid);
}

void RnIfxAdapterTxChannel::send_chi_srsp(const chi::ChiExtension* message)
{
    flits::ChiRspFlit srsp_flit;
    srsp_flit.set_qos(message->qos);
    srsp_flit.set_opcode(static_cast<uint8_t>(message->rsp_fields.opcode));
    srsp_flit.set_srcid(message->rsp_fields.src_id);
    srsp_flit.set_tgtid(message->rsp_fields.tgt_id);
    srsp_flit.set_resp(static_cast<uint8_t>(message->rsp_fields.resp));
    srsp_flit.set_fwdstate(static_cast<uint8_t>(message->rsp_fields.fwd_state));
    srsp_flit.set_pcrdtype(message->rsp_fields.pcrd_type);
    srsp_flit.set_dbid(message->rsp_fields.dbid);
}

void RnIfxAdapterTxChannel::main_process()
{
    if (!rstb_intfrx_clk_in.read())
    {
        reset();
        return;
    }

    link_handshake();

    if (ELinkState::ACTIVATE == link_state_current_ || ELinkState::RUN == link_state_current_)
    {
        credit_check();
    }

    update_link_state();
}

void RnIfxAdapterTxChannel::reset()
{
    std::cout << name() << ": reset\n";

    // Required from CHI Rev E.b 14.1.3
    TX_LINKACTIVEREQ_out.write(false);

    TX_REQFLITV_out.write(false);
    TX_DATFLITV_out.write(false);
    TX_RSPFLITV_out.write(false);

    // all other signals
    TX_REQFLITPEND_out.write(false);
    TX_RSPFLITPEND_out.write(false);
    TX_DATFLITPEND_out.write(false);
    TXSACTIVE_out.write(false);

    req_credit_counter_ = 0;
    dat_credit_counter_ = 0;
    rsp_credit_counter_ = 0;

    link_state_current_ = ELinkState::STOP;
    link_state_next_ = ELinkState::STOP;
}

void RnIfxAdapterTxChannel::link_handshake()
{
    if (!TXSACTIVE_out.read())
    {
        TXSACTIVE_out.write(true);
    }

    if (!TX_LINKACTIVEREQ_out.read())
    {
        TX_LINKACTIVEREQ_out.write(true);
        std::cout << "tx_link_handshake (ELinkState::ACTIVATE)\n";
        link_state_next_ = ELinkState::ACTIVATE;
    }

    if (ELinkState::ACTIVATE == link_state_current_ && TX_LINKACTIVEACK_in.read())
    {
        if (TX_LINKACTIVEREQ_out.read())
        {
            std::cout << "tx_link_handshake (ELinkState::RUN)\n";
            link_state_next_ = ELinkState::RUN;
        }
        else
        {
            std::cout << "tx_link_handshake (ELinkState::DEACTIVATE)\n";
            link_state_next_ = ELinkState::DEACTIVATE;
        }
    }
}

void RnIfxAdapterTxChannel::credit_check()
{
    if ((MAX_CREDITS > req_credit_counter_) && TX_REQLCRDV_in.read())
    {
        ++req_credit_counter_;
        std::cout << "Increment REQ credit counter: " << static_cast<unsigned>(req_credit_counter_) << "\n";
    }

    if ((MAX_CREDITS > dat_credit_counter_) && TX_DATLCRDV_in.read())
    {
        ++dat_credit_counter_;
        std::cout << "Increment WDAT credit counter: " << static_cast<unsigned>(dat_credit_counter_) << "\n";
    }

    if ((MAX_CREDITS > rsp_credit_counter_) && TX_RSPLCRDV_in.read())
    {
        ++rsp_credit_counter_;
        std::cout << "Increment SRSP credit counter: " << static_cast<unsigned>(rsp_credit_counter_) << "\n";
    }
}

void RnIfxAdapterTxChannel::update_link_state()
{
    link_state_current_ = link_state_next_;
}
