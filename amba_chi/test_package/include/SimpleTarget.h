#ifndef __SIMPLE_TARGET_H__
#define __SIMPLE_TARGET_H__

#include <systemc>
#include <tlm>
#include <tlm_utils/simple_target_socket.h>


class SimpleTarget : public sc_core::sc_module
{
public:
    tlm_utils::simple_target_socket<SimpleTarget> target_socket;

    SC_CTOR(SimpleTarget) : target_socket("socket")
    {
        // Register callback - much simpler than manual interface binding!
        target_socket.register_b_transport(this, &SimpleTarget::b_transport);
        target_socket.register_nb_transport_fw(this, &SimpleTarget::nb_transport_fw);
        target_socket.register_get_direct_mem_ptr(this, &SimpleTarget::get_direct_mem_ptr);
        target_socket.register_transport_dbg(this, &SimpleTarget::transport_dbg);
    }

    void b_transport(tlm::tlm_generic_payload& trans, sc_core::sc_time& delay)
    {
        trans.set_response_status(tlm::TLM_OK_RESPONSE);
    }

    tlm::tlm_sync_enum nb_transport_fw(tlm::tlm_generic_payload& trans,
                                     tlm::tlm_phase& phase,
                                     sc_core::sc_time& delay)
    {
        trans.set_response_status(tlm::TLM_OK_RESPONSE);
        return tlm::TLM_COMPLETED;
    }

    bool get_direct_mem_ptr(tlm::tlm_generic_payload& trans, tlm::tlm_dmi& dmi_data)
    {
        return false;
    }

    unsigned int transport_dbg(tlm::tlm_generic_payload& trans)
    {
        return trans.get_data_length();
    }
};

#endif  // __SIMPLE_TARGET_H__
