#ifndef __RN_IFX_ADAPTER__
#define __RN_IFX_ADAPTER__

#include <memory>
#include <systemc>
#include <tlm>
#include <tlm_utils/simple_target_socket.h>

struct RnDeviceIf;
struct RnNocTlmIf;

SC_MODULE(RnIfxAdapter)
{
public:
    static constexpr auto BUS_WIDTH = 32u;
    using TYPES = tlm::tlm_base_protocol_types;

    SC_HAS_PROCESS(RnIfxAdapter);
    RnIfxAdapter(sc_core::sc_module_name name);

private:
    std::shared_ptr<RnDeviceIf> rn_dev_if;
    std::shared_ptr<RnNocTlmIf> rn_tlm_if;

public:
    tlm_utils::simple_target_socket<RnNocTlmIf, BUS_WIDTH, TYPES>& target_socket;
};

#endif  // __RN_IFX_ADAPTER__
