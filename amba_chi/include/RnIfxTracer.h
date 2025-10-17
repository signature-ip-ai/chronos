#ifndef __RN_IFX_TRACER_H__
#define __RN_IFX_TRACER_H__

#include <systemc>


struct RnIfxAdapter;

class RnIfxTracer
{
public:
    explicit RnIfxTracer(RnIfxAdapter*, sc_core::sc_module_name);
    ~RnIfxTracer();
    void set_time_unit(double v, sc_core::sc_time_unit);

private:
    RnIfxAdapter* adapter_;
    sc_core::sc_trace_file* trace_file_;
};

#endif  // __RN_IFX_TRACER_H__
