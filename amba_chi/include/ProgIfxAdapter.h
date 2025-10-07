#ifndef __PROG_IFX_ADAPTER_H__
#define __PROG_IFX_ADAPTER_H__

#include <systemc>
#include <tlm>
#include <tlm_utils/simple_target_socket.h>


SC_MODULE(ProgIfxAdapter)
{
public:
    static constexpr auto BUS_WIDTH = 32u;
    using TYPES = tlm::tlm_base_protocol_types;

    SC_HAS_PROCESS(ProgIfxAdapter);
    ProgIfxAdapter(sc_core::sc_module_name name);

    tlm_utils::simple_target_socket<ProgIfxAdapter, BUS_WIDTH, TYPES> target_socket;

    sc_core::sc_signal<bool> PCLK_prog_out;
    sc_core::sc_signal<bool> PRESETn_prog_out;
    sc_core::sc_signal<bool> PSEL_prog_out;
    sc_core::sc_signal<bool> PENABLE_prog_out;
    sc_core::sc_signal<bool> PWRITE_prog_out;
    sc_core::sc_signal<uint32_t> PSTRB_prog_out;
    sc_core::sc_signal<bool> PREADY_prog_in;
    sc_core::sc_signal<bool> PSLVERR_prog_in;
    sc_core::sc_signal<uint32_t> PADDR_prog_out;
    sc_core::sc_signal<uint32_t> PWDATA_prog_out;
    sc_core::sc_signal<uint32_t> PRDATA_prog_in;

private:
    void b_transport(tlm::tlm_generic_payload&, sc_core::sc_time&);
    tlm::tlm_sync_enum nb_transport_fw(tlm::tlm_generic_payload&, tlm::tlm_phase&, sc_core::sc_time&);
    bool get_direct_mem_ptr(tlm::tlm_generic_payload&, tlm::tlm_dmi&);
    unsigned int transport_dbg(tlm::tlm_generic_payload&);
};

#endif  // __PROG_IFX_ADAPTER_H__
