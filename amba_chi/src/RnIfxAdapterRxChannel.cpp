#include <RnIfxAdapterRxChannel.h>
#include <ELinkState.h>

RnIfxAdapterRxChannel::RnIfxAdapterRxChannel(sc_core::sc_module_name module_name)
    : sc_core::sc_module(module_name)
    , module_initialized_(false)
    , req_credit_available_(MAX_CREDITS)
    , dat_credit_available_(MAX_CREDITS)
    , rsp_credit_available_(MAX_CREDITS)
    , link_state_current_(ELinkState::STOP)
    , link_state_next_(ELinkState::STOP)
{
    SC_METHOD(main_process);
    sensitive << intfrx_clk_in.pos() << rstb_intfrx_clk_in.neg();
    dont_initialize();

    std::cout << name() << " elaborated\n";
}

void RnIfxAdapterRxChannel::initialize()
{
    assert(!module_initialized_ && "Module must only be initialized once");
    reset();
    module_initialized_ = true;
}

void RnIfxAdapterRxChannel::main_process()
{
    if (!rstb_intfrx_clk_in.read())
    {
        reset();
        return;
    }

    link_handshake();
    update_link_state();
}

void RnIfxAdapterRxChannel::reset()
{
    std::cout << name() << ": reset\n";

    // Required from CHI Rev E.b 14.1.3
    RX_LINKACTIVEACK_out.write(false);

    // All other states
    link_state_current_ = ELinkState::STOP;
    link_state_next_ = ELinkState::STOP;
}

void RnIfxAdapterRxChannel::link_handshake()
{
    if (RXSACTIVE_in.read() && RX_LINKACTIVEREQ_in.read())
    {
        link_state_next_ = ELinkState::ACTIVATE;
        std::cout << "rx_link_handshake (ELinkState::ACTIVATE)\n";
    }

    if (ELinkState::ACTIVATE == link_state_current_)
    {
        RX_LINKACTIVEACK_out.write(true);
        link_state_next_ = ELinkState::RUN;
        std::cout << "rx_link_handshake (ELinkState::RUN)\n";
    }
}

void RnIfxAdapterRxChannel::credit_send()
{

}

void RnIfxAdapterRxChannel::update_link_state()
{
    link_state_current_ = link_state_next_;
}
