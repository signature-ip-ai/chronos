#pragma once

#include "chi_enums.h"
#include <tlm>

namespace chi {
class ChiCreditExtension : public tlm::tlm_extension<ChiCreditExtension> {
public:
    ChiChannel channel;

    auto clone() const -> tlm_extension_base* override;
    auto copy_from(tlm_extension_base const& ext) -> void override;
};
} // namespace chi
