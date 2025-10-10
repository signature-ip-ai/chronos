#include <QpIfxAdapter.h>

QpIfxAdapter::QpIfxAdapter(sc_core::sc_module_name name)
    : sc_core::sc_module(name)
{
    qp_rstb_out.write(true);
    qreqn_out.write(false);
    pstate_out.write(false);
    preq_out.write(false);

    SC_METHOD(forward_clock);
    sensitive << qp_clk_in;
    dont_initialize();

    SC_METHOD(forward_reset);
    sensitive << qp_rstb_in;
    dont_initialize();
}

void QpIfxAdapter::forward_clock()
{
    qp_clk_out.write(qp_clk_in.read());
}

void QpIfxAdapter::forward_reset()
{
    qp_rstb_out.write(qp_rstb_in.read());
}
