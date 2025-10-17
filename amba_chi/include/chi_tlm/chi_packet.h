#pragma once

#include "chi_enums.h"

namespace chi {
class ChiPacket {
public:
    ChiPacket() = default;

    uint64_t   address;
    uint32_t   chi_txn_id;
    uint8_t    qos = 0;
    ChiChannel current_channel;

    // REQ fields
    struct {
        ReqOpcode opcode = ReqOpcode::Uninitialized;
        uint32_t  src_id;
        uint32_t  tgt_id;
        uint32_t  return_nid;
        bool      allow_retry = true;
        uint8_t   order       = 0b00;
        struct {
            bool allocate  = false;
            bool cacheable = false;
            bool device    = false;
            bool ewa       = false;
        } mem_attr;
        bool do_dwt       = false;
        bool exp_comp_ack = false;
    } req_fields;

    // RSP fields
    struct {
        RspOpcode opcode = RspOpcode::Uninitialized;
        uint32_t  src_id;
        uint32_t  tgt_id;
        Resp      resp      = Resp::Uninitialized;
        Resp      fwd_state = Resp::Uninitialized;
        uint8_t   pcrd_type = 0;
        uint16_t  dbid      = 0;
    } rsp_fields;

    // SNP fields
    struct {
        SnpOpcode opcode = SnpOpcode::Uninitialized;
        uint32_t  src_id;
        uint32_t  tgt_id;
        uint32_t  fwd_nid;
        uint32_t  fwd_txn_id;
        bool      ret_to_src;
        bool      do_not_go_to_sd = false;
    } snp_fields;

    // DAT fields
    struct {
        DatOpcode opcode = DatOpcode::Uninitialized;
        uint32_t  src_id;
        uint32_t  tgt_id;
        uint32_t  home_n_id;
        Resp      resp      = Resp::Uninitialized;
        Resp      fwd_state = Resp::Uninitialized;
        uint16_t  dbid      = 0;
    } dat_fields;

    auto get_address() const -> uint64_t { return address; }
};
} // namespace chi