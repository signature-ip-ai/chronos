#include <RnIfxAdapterTxChannel.h>
#include <ELinkState.h>


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
    req_buffer_.emplace_back(translate_chi_req(message));
}

void RnIfxAdapterTxChannel::send_chi_wdat(const chi::ChiExtension* message)
{
    dat_buffer_.emplace_back(translate_chi_wdat(message));
}

void RnIfxAdapterTxChannel::send_chi_srsp(const chi::ChiExtension* message)
{
    rsp_buffer_.emplace_back(translate_chi_srsp(message));
}

void RnIfxAdapterTxChannel::main_process()
{
    if (!rstb_intfrx_clk_in.read())
    {
        reset();
        return;
    }

    stage_flits();
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
    TX_REQFLITPEND_out.write(true);
    TX_RSPFLITPEND_out.write(true);
    TX_DATFLITPEND_out.write(true);
    TXSACTIVE_out.write(false);

    req_credit_counter_ = 0;
    dat_credit_counter_ = 0;
    rsp_credit_counter_ = 0;

    link_state_current_ = ELinkState::STOP;
    link_state_next_ = ELinkState::STOP;
}

void RnIfxAdapterTxChannel::link_handshake()
{
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

void RnIfxAdapterTxChannel::stage_flits()
{
    const auto req_buffer_empty = req_buffer_.empty();
    const auto dat_buffer_empty = dat_buffer_.empty();
    const auto rsp_buffer_empty = rsp_buffer_.empty();

    if (req_buffer_empty && dat_buffer_empty && rsp_buffer_empty)
    {
        TXSACTIVE_out.write(false);  // All buffers are empty
        TX_REQFLITV_out.write(false);
        TX_RSPFLITV_out.write(false);
        TX_DATFLITV_out.write(false);
        return;
    }

    TXSACTIVE_out.write(true);

    if (!req_buffer_empty)
    {
        stage_req_flit();
    }
    else
    {
        TX_REQFLITV_out.write(false);
    }

    if (!dat_buffer_empty)
    {
        stage_dat_flit();
    }
    else
    {
        TX_DATFLITV_out.write(false);
    }

    if (!rsp_buffer_empty)
    {
        stage_rsp_flit();
    }
    else
    {
        TX_RSPFLITV_out.write(false);
    }
}

void RnIfxAdapterTxChannel::stage_req_flit()
{
    if (!req_credit_counter_ || (ELinkState::RUN != link_state_current_))
    {
        TX_REQFLITV_out.write(false);
        return;
    }

    flits::reqflit_t req_flit = req_buffer_.front();
    TX_REQFLIT_out.write(req_flit);
    req_buffer_.pop_front();
    --req_credit_counter_;

    TX_REQFLITV_out.write(true);

    std::cout << "Sending REQ Flit: " << req_flit << "\n";
    std::cout << "Remaining REQ credits: " << static_cast<unsigned>(req_credit_counter_) << "\n";
}

void RnIfxAdapterTxChannel::stage_dat_flit()
{
    if (!dat_credit_counter_ || (ELinkState::RUN != link_state_current_))
    {
        TX_DATFLITV_out.write(false);
        return;
    }

    flits::datflit_t dat_flit = dat_buffer_.front();
    TX_DATFLIT_out.write(dat_flit);
    dat_buffer_.pop_front();
    --dat_credit_counter_;

    TX_DATFLITV_out.write(true);

    std::cout << "Sending WDAT Flit: " << dat_flit << "\n";
    std::cout << "Remaining WDAT credits: " << static_cast<unsigned>(dat_credit_counter_) << "\n";
}

void RnIfxAdapterTxChannel::stage_rsp_flit()
{
    if (!rsp_credit_counter_ || (ELinkState::RUN != link_state_current_))
    {
        TX_RSPFLITV_out.write(false);
        return;
    }

    flits::rspflit_t rsp_flit = rsp_buffer_.front();
    TX_RSPFLIT_out.write(rsp_flit);
    rsp_buffer_.pop_front();
    --rsp_credit_counter_;

    TX_RSPFLITV_out.write(true);

    std::cout << "Sending SRSP Flit: " << rsp_flit << "\n";
    std::cout << "Remaining SRSP credits: " << static_cast<unsigned>(rsp_credit_counter_) << "\n";
}

flits::reqflit_t RnIfxAdapterTxChannel::translate_chi_req(const chi::ChiExtension* message)
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

    return req_flit.get_raw();
}

flits::datflit_t RnIfxAdapterTxChannel::translate_chi_wdat(const chi::ChiExtension* message)
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

    return wdat_flit.get_raw();
}

flits::rspflit_t RnIfxAdapterTxChannel::translate_chi_srsp(const chi::ChiExtension* message)
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

    return srsp_flit.get_raw();
}
