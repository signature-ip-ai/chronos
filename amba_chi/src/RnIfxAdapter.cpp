#include <RnIfxAdapter.h>
#include <iostream>

#include <ELinkState.h>
#include <RnIfxTracer.h>
#include <RnIfxAdapterTxChannel.h>
#include <RnIfxAdapterRxChannel.h>

RnIfxAdapter::RnIfxAdapter(sc_core::sc_module_name module_name)
    : sc_core::sc_module(module_name)
    , target_socket()
    , tracer_(nullptr)
    , tx_channel_(std::make_shared<RnIfxAdapterTxChannel>("RnIfxAdapterTxChannel"))
    , rx_channel_(std::make_shared<RnIfxAdapterRxChannel>("RnIfxAdapterRxChannel"))
{
    bind_tx_channels();
    tx_channel_->initialize();

    bind_rx_channels();
    rx_channel_->initialize();

    target_socket.register_b_transport(this, &RnIfxAdapter::b_transport);
    target_socket.register_nb_transport_fw(this, &RnIfxAdapter::nb_transport_fw);
    target_socket.register_get_direct_mem_ptr(this, &RnIfxAdapter::get_direct_mem_ptr);
    target_socket.register_transport_dbg(this, &RnIfxAdapter::transport_dbg);

    SC_METHOD(forward_clock);
    sensitive << intfrx_clk_in;
    dont_initialize();

    SC_METHOD(forward_reset);
    sensitive << rstb_intfrx_clk_in;
    dont_initialize();

    std::cout << name() << " elaborated\n";
}

void RnIfxAdapter::enable_trace()
{
    tracer_ = std::make_shared<RnIfxTracer>(this, name());
}

void RnIfxAdapter::set_trace_time_unit(double value, sc_core::sc_time_unit time_unit)
{
    assert(tracer_ && "enable_trace must be called first before set_trace_time_unit(...)");
    tracer_->set_time_unit(value, time_unit);
}

void RnIfxAdapter::b_transport(tlm::tlm_generic_payload& trans, sc_core::sc_time& delay)
{
    trans.set_response_status(tlm::TLM_OK_RESPONSE);
}

tlm::tlm_sync_enum RnIfxAdapter::nb_transport_fw(
    tlm::tlm_generic_payload& trans, tlm::tlm_phase& phase, sc_core::sc_time& delay)
{
    trans.set_response_status(tlm::TLM_OK_RESPONSE);
    return tlm::tlm_sync_enum();
}

bool RnIfxAdapter::get_direct_mem_ptr(tlm::tlm_generic_payload& trans, tlm::tlm_dmi& dmi_data)
{
    return false;
}

unsigned int RnIfxAdapter::transport_dbg(tlm::tlm_generic_payload& trans)
{
    return 0;
}

void RnIfxAdapter::forward_clock()
{
    intfrx_clk_out.write(intfrx_clk_in.read());
}

void RnIfxAdapter::forward_reset()
{
    rstb_intfrx_clk_out.write(rstb_intfrx_clk_in.read());
}

void RnIfxAdapter::bind_tx_channels()
{
    tx_channel_->intfrx_clk_in(intfrx_clk_in);
    tx_channel_->rstb_intfrx_clk_in(rstb_intfrx_clk_in);

    tx_channel_->TXSACTIVE_out(TXSACTIVE_out);

    tx_channel_->TX_LINKACTIVEREQ_out(TX_LINKACTIVEREQ_out);
    tx_channel_->TX_LINKACTIVEACK_in(TX_LINKACTIVEACK_in);

    tx_channel_->TX_REQFLITPEND_out(TX_REQFLITPEND_out);
    tx_channel_->TX_REQFLITV_out(TX_REQFLITV_out);
    tx_channel_->TX_REQFLIT_out(TX_REQFLIT_out);
    tx_channel_->TX_REQLCRDV_in(TX_REQLCRDV_in);

    tx_channel_->TX_RSPFLITPEND_out(TX_RSPFLITPEND_out);
    tx_channel_->TX_RSPFLITV_out(TX_RSPFLITV_out);
    tx_channel_->TX_RSPFLIT_out(TX_RSPFLIT_out);
    tx_channel_->TX_RSPLCRDV_in(TX_RSPLCRDV_in);

    tx_channel_->TX_DATFLITPEND_out(TX_DATFLITPEND_out);
    tx_channel_->TX_DATFLITV_out(TX_DATFLITV_out);
    tx_channel_->TX_DATFLIT_out(TX_DATFLIT_out);
    tx_channel_->TX_DATLCRDV_in(TX_DATLCRDV_in);
}

void RnIfxAdapter::bind_rx_channels()
{
    rx_channel_->intfrx_clk_in(intfrx_clk_in);
    rx_channel_->rstb_intfrx_clk_in(rstb_intfrx_clk_in);

    rx_channel_->RXSACTIVE_in(RXSACTIVE_in);

    rx_channel_->RX_LINKACTIVEREQ_in(RX_LINKACTIVEREQ_in);
    rx_channel_->RX_LINKACTIVEACK_out(RX_LINKACTIVEACK_out);

    rx_channel_->RX_RSPFLITPEND_in(RX_RSPFLITPEND_in);
    rx_channel_->RX_RSPFLITV_in(RX_RSPFLITV_in);
    rx_channel_->RX_RSPFLIT_in(RX_RSPFLIT_in);
    rx_channel_->RX_RSPLCRDV_out(RX_RSPLCRDV_out);

    rx_channel_->RX_DATFLITPEND_in(RX_DATFLITPEND_in);
    rx_channel_->RX_DATFLITV_in(RX_DATFLITV_in);
    rx_channel_->RX_DATFLIT_in(RX_DATFLIT_in);
    rx_channel_->RX_DATLCRDV_out(RX_DATLCRDV_out);

    rx_channel_->RX_SNPFLITPEND_in(RX_SNPFLITPEND_in);
    rx_channel_->RX_SNPFLITV_in(RX_SNPFLITV_in);
    rx_channel_->RX_SNPFLIT_in(RX_SNPFLIT_in);
    rx_channel_->RX_SNPLCRDV_out(RX_SNPLCRDV_out);
}
