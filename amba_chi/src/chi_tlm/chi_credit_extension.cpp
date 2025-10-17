#include "chi_tlm/chi_credit_extension.h"

using namespace chi;

auto
ChiCreditExtension::clone() const -> tlm::tlm_extension_base*

{
    auto* ext    = new ChiCreditExtension();
    ext->channel = channel;
    return ext;
}

auto
ChiCreditExtension::copy_from(tlm_extension_base const& ext) -> void
{
    channel = static_cast<ChiCreditExtension const&>(ext).channel;
}