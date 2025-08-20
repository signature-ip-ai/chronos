#include <SnIfxAdapter.hpp>

#include <memory>
#include <systemc>
#include <SnDeviceIf.hxx>
#include <SnNocTlmIf.hxx>

SnIfxAdapter::SnIfxAdapter(sc_core::sc_module_name name)
    : sc_core::sc_module(name)
    , sn_dev_if(std::make_shared<SnDeviceIf<SnIfxAdapter>>("SnDeviceIf0"))
    , sn_tlm_if(std::make_shared<SnNocTlmIf<SnIfxAdapter>>("SnNocTlmIf0"))
    , initiator_socket(sn_tlm_if->initiator_socket)
    , intfrx_clk(sn_dev_if->intfrx_clk)
    , rstb_intfrx_clk(sn_dev_if->rstb_intfrx_clk)
    , RX_LINKACTIVEREQ(sn_dev_if->RX_LINKACTIVEREQ)
    , RX_LINKACTIVEACK(sn_dev_if->RX_LINKACTIVEACK)
    , RX_RSPFLITPEND(sn_dev_if->RX_RSPFLITPEND)
    , RX_RSPFLITV(sn_dev_if->RX_RSPFLITV)
    , RX_RSPLCRDV(sn_dev_if->RX_RSPLCRDV)
    , RX_DATFLITPEND(sn_dev_if->RX_DATFLITPEND)
    , RX_DATFLITV(sn_dev_if->RX_DATFLITV)
    , RX_DATLCRDV(sn_dev_if->RX_DATLCRDV)
    , TX_LINKACTIVEREQ(sn_dev_if->TX_LINKACTIVEREQ)
    , TX_LINKACTIVEACK(sn_dev_if->TX_LINKACTIVEACK)
    , TX_REQFLITPEND(sn_dev_if->TX_REQFLITPEND)
    , TX_REQFLITV(sn_dev_if->TX_REQFLITV)
    , TX_REQLCRDV(sn_dev_if->TX_REQLCRDV)
    , TX_DATFLITPEND(sn_dev_if->TX_DATFLITPEND)
    , TX_DATFLITV(sn_dev_if->TX_DATFLITV)
    , TX_DATLCRDV(sn_dev_if->TX_DATLCRDV)
    , TXSACTIVE(sn_dev_if->TXSACTIVE)
    , RXSACTIVE(sn_dev_if->RXSACTIVE)
    , RX_RSPFLIT(sn_dev_if->RX_RSPFLIT)
    , RX_DATFLIT(sn_dev_if->RX_DATFLIT)
    , TX_REQFLIT(sn_dev_if->TX_REQFLIT)
    , TX_DATFLIT(sn_dev_if->TX_DATFLIT)
{}
