#include <RnIfxTracer.h>
#include <RnIfxAdapter.h>

RnIfxTracer::RnIfxTracer(RnIfxAdapter* adapter, sc_core::sc_module_name name)
    : adapter_(adapter)
    , trace_file_(sc_core::sc_create_vcd_trace_file((const char*) name))
{
    sc_core::sc_trace(trace_file_, adapter_->intfrx_clk_in, "intfrx_clk_in");
    sc_core::sc_trace(trace_file_, adapter_->rstb_intfrx_clk_in, "rstb_intfrx_clk_in");
    sc_core::sc_trace(trace_file_, adapter_->intfrx_clk_out, "intfrx_clk_out");
    sc_core::sc_trace(trace_file_, adapter_->rstb_intfrx_clk_out, "rstb_intfrx_clk_out");

    // System Control
    sc_core::sc_trace(trace_file_, adapter_->SYSCOREQ_out, "SYSCOREQ_out");
    sc_core::sc_trace(trace_file_, adapter_->SYSCOACK_in, "SYSCOACK_in");

    // Link Activity
    sc_core::sc_trace(trace_file_, adapter_->TXSACTIVE_out, "TXSACTIVE_out");
    sc_core::sc_trace(trace_file_, adapter_->RXSACTIVE_in, "RXSACTIVE_in");
    sc_core::sc_trace(trace_file_, adapter_->TX_LINKACTIVEREQ_out, "TX_LINKACTIVEREQ_out");
    sc_core::sc_trace(trace_file_, adapter_->TX_LINKACTIVEACK_in, "TX_LINKACTIVEACK_in");
    sc_core::sc_trace(trace_file_, adapter_->RX_LINKACTIVEREQ_in, "RX_LINKACTIVEREQ_in");
    sc_core::sc_trace(trace_file_, adapter_->RX_LINKACTIVEACK_out, "RX_LINKACTIVEACK_out");

    // TX REQ Channel
    sc_core::sc_trace(trace_file_, adapter_->TX_REQFLITPEND_out, "TX_REQFLITPEND_out");
    sc_core::sc_trace(trace_file_, adapter_->TX_REQFLITV_out, "TX_REQFLITV_out");
    sc_core::sc_trace(trace_file_, adapter_->TX_REQFLIT_out, "TX_REQFLIT_out");
    sc_core::sc_trace(trace_file_, adapter_->TX_REQLCRDV_in, "TX_REQLCRDV_in");

    // TX RSP Channel
    sc_core::sc_trace(trace_file_, adapter_->TX_RSPFLITPEND_out, "TX_RSPFLITPEND_out");
    sc_core::sc_trace(trace_file_, adapter_->TX_RSPFLITV_out, "TX_RSPFLITV_out");
    sc_core::sc_trace(trace_file_, adapter_->TX_RSPFLIT_out, "TX_RSPFLIT_out");
    sc_core::sc_trace(trace_file_, adapter_->TX_RSPLCRDV_in, "TX_RSPLCRDV_in");

    // TX DAT Channel
    sc_core::sc_trace(trace_file_, adapter_->TX_DATFLITPEND_out, "TX_DATFLITPEND_out");
    sc_core::sc_trace(trace_file_, adapter_->TX_DATFLITV_out, "TX_DATFLITV_out");
    sc_core::sc_trace(trace_file_, adapter_->TX_DATFLIT_out, "TX_DATFLIT_out");
    sc_core::sc_trace(trace_file_, adapter_->TX_DATLCRDV_in, "TX_DATLCRDV_in");

    // RX RSP Channel
    sc_core::sc_trace(trace_file_, adapter_->RX_RSPFLITPEND_in, "RX_RSPFLITPEND_in");
    sc_core::sc_trace(trace_file_, adapter_->RX_RSPFLITV_in, "RX_RSPFLITV_in");
    sc_core::sc_trace(trace_file_, adapter_->RX_RSPFLIT_in, "RX_RSPFLIT_in");
    sc_core::sc_trace(trace_file_, adapter_->RX_RSPLCRDV_out, "RX_RSPLCRDV_out");

    // RX DAT Channel
    sc_core::sc_trace(trace_file_, adapter_->RX_DATFLITPEND_in, "RX_DATFLITPEND_in");
    sc_core::sc_trace(trace_file_, adapter_->RX_DATFLITV_in, "RX_DATFLITV_in");
    sc_core::sc_trace(trace_file_, adapter_->RX_DATFLIT_in, "RX_DATFLIT_in");
    sc_core::sc_trace(trace_file_, adapter_->RX_DATLCRDV_out, "RX_DATLCRDV_out");

    // RX SNP Channel
    sc_core::sc_trace(trace_file_, adapter_->RX_SNPFLITPEND_in, "RX_SNPFLITPEND_in");
    sc_core::sc_trace(trace_file_, adapter_->RX_SNPFLITV_in, "RX_SNPFLITV_in");
    sc_core::sc_trace(trace_file_, adapter_->RX_SNPFLIT_in, "RX_SNPFLIT_in");
    sc_core::sc_trace(trace_file_, adapter_->RX_SNPLCRDV_out, "RX_SNPLCRDV_out");
}

RnIfxTracer::~RnIfxTracer()
{
    sc_core::sc_close_vcd_trace_file(trace_file_);
}

void RnIfxTracer::set_time_unit(double value, sc_core::sc_time_unit time_unit)
{
    trace_file_->set_time_unit(value, time_unit);
}
