#include <SnIfxAdapter.h>

#include <memory>
#include <systemc>

SnIfxAdapter::SnIfxAdapter(sc_core::sc_module_name name)
    : sc_core::sc_module(name)
    , initiator_socket()
{
    initiator_socket.register_nb_transport_bw(this, &SnIfxAdapter::nb_transport_bw);
    initiator_socket.register_invalidate_direct_mem_ptr(this, &SnIfxAdapter::invalidate_direct_mem_ptr);

    SC_METHOD(forward_clock);
    sensitive << intfrx_clk_in;
    dont_initialize();

    SC_METHOD(forward_reset);
    sensitive << rstb_intfrx_clk_in;
    dont_initialize();
}

tlm::tlm_sync_enum SnIfxAdapter::nb_transport_bw(
    tlm::tlm_generic_payload& trans, tlm::tlm_phase& phase, sc_core::sc_time& delay)
{
    trans.set_response_status(tlm::TLM_OK_RESPONSE);
    return tlm::tlm_sync_enum();
}

void SnIfxAdapter::invalidate_direct_mem_ptr(sc_dt::uint64 start_range, sc_dt::uint64 end_range)
{}

void SnIfxAdapter::forward_clock()
{
    intfrx_clk_out.write(intfrx_clk_in.read());
}

void SnIfxAdapter::forward_reset()
{
    rstb_intfrx_clk_out.write(rstb_intfrx_clk_in.read());
}
