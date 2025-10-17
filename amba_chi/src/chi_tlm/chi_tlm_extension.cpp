#include "chi_tlm/chi_tlm_extension.h"
auto
chi::ChiExtension::clone() const -> tlm_extension_base*
{
    return new ChiExtension(*this);
}
auto
chi::ChiExtension::copy_from(const tlm_extension_base& ext) -> void
{
    *this = static_cast<const ChiExtension&>(ext);
}
auto
chi::ChiExtension::populate_from_packet(const ChiPacket& packet) -> void
{
    // Copy basic fields
    channel    = packet.current_channel;
    chi_txn_id = packet.chi_txn_id;
    qos        = packet.qos;

    // Copy REQ fields
    req_fields.opcode             = packet.req_fields.opcode;
    req_fields.src_id             = packet.req_fields.src_id;
    req_fields.tgt_id             = packet.req_fields.tgt_id;
    req_fields.return_nid         = packet.req_fields.return_nid;
    req_fields.allow_retry        = packet.req_fields.allow_retry;
    req_fields.order              = packet.req_fields.order;
    req_fields.mem_attr.allocate  = packet.req_fields.mem_attr.allocate;
    req_fields.mem_attr.cacheable = packet.req_fields.mem_attr.cacheable;
    req_fields.mem_attr.device    = packet.req_fields.mem_attr.device;
    req_fields.mem_attr.ewa       = packet.req_fields.mem_attr.ewa;
    req_fields.do_dwt             = packet.req_fields.do_dwt;
    req_fields.exp_comp_ack       = packet.req_fields.exp_comp_ack;

    // Copy RSP fields
    rsp_fields.opcode    = packet.rsp_fields.opcode;
    rsp_fields.src_id    = packet.rsp_fields.src_id;
    rsp_fields.tgt_id    = packet.rsp_fields.tgt_id;
    rsp_fields.resp      = packet.rsp_fields.resp;
    rsp_fields.fwd_state = packet.rsp_fields.fwd_state;
    rsp_fields.pcrd_type = packet.rsp_fields.pcrd_type;
    rsp_fields.dbid      = packet.rsp_fields.dbid;

    // Copy SNP fields
    snp_fields.opcode          = packet.snp_fields.opcode;
    snp_fields.src_id          = packet.snp_fields.src_id;
    snp_fields.tgt_id          = packet.snp_fields.tgt_id;
    snp_fields.fwd_nid         = packet.snp_fields.fwd_nid;
    snp_fields.fwd_txn_id      = packet.snp_fields.fwd_txn_id;
    snp_fields.ret_to_src      = packet.snp_fields.ret_to_src;
    snp_fields.do_not_go_to_sd = packet.snp_fields.do_not_go_to_sd;

    // Copy DAT fields
    dat_fields.opcode    = packet.dat_fields.opcode;
    dat_fields.src_id    = packet.dat_fields.src_id;
    dat_fields.tgt_id    = packet.dat_fields.tgt_id;
    dat_fields.home_n_id = packet.dat_fields.home_n_id;
    dat_fields.resp      = packet.dat_fields.resp;
    dat_fields.fwd_state = packet.dat_fields.fwd_state;
    dat_fields.dbid      = packet.dat_fields.dbid;
}
auto
chi::ChiExtension::populate_new_packet(tlm::tlm_generic_payload& payload, tlm::tlm_phase& phase)
    -> ChiPacket
{
    ChiPacket packet;

    // Copy basic fields
    packet.current_channel = channel;
    packet.chi_txn_id      = chi_txn_id;
    packet.qos             = qos;
    packet.address         = payload.get_address();

    // Copy REQ fields
    packet.req_fields.opcode             = req_fields.opcode;
    packet.req_fields.src_id             = req_fields.src_id;
    packet.req_fields.tgt_id             = req_fields.tgt_id;
    packet.req_fields.return_nid         = req_fields.return_nid;
    packet.req_fields.allow_retry        = req_fields.allow_retry;
    packet.req_fields.order              = req_fields.order;
    packet.req_fields.mem_attr.allocate  = req_fields.mem_attr.allocate;
    packet.req_fields.mem_attr.cacheable = req_fields.mem_attr.cacheable;
    packet.req_fields.mem_attr.device    = req_fields.mem_attr.device;
    packet.req_fields.mem_attr.ewa       = req_fields.mem_attr.ewa;
    packet.req_fields.do_dwt             = req_fields.do_dwt;
    packet.req_fields.exp_comp_ack       = req_fields.exp_comp_ack;

    // Copy RSP fields
    packet.rsp_fields.opcode    = rsp_fields.opcode;
    packet.rsp_fields.src_id    = rsp_fields.src_id;
    packet.rsp_fields.tgt_id    = rsp_fields.tgt_id;
    packet.rsp_fields.resp      = rsp_fields.resp;
    packet.rsp_fields.fwd_state = rsp_fields.fwd_state;
    packet.rsp_fields.pcrd_type = rsp_fields.pcrd_type;
    packet.rsp_fields.dbid      = rsp_fields.dbid;

    // Copy SNP fields
    packet.snp_fields.opcode          = snp_fields.opcode;
    packet.snp_fields.src_id          = snp_fields.src_id;
    packet.snp_fields.tgt_id          = snp_fields.tgt_id;
    packet.snp_fields.fwd_nid         = snp_fields.fwd_nid;
    packet.snp_fields.fwd_txn_id      = snp_fields.fwd_txn_id;
    packet.snp_fields.ret_to_src      = snp_fields.ret_to_src;
    packet.snp_fields.do_not_go_to_sd = snp_fields.do_not_go_to_sd;

    // Copy DAT fields
    packet.dat_fields.opcode    = dat_fields.opcode;
    packet.dat_fields.src_id    = dat_fields.src_id;
    packet.dat_fields.tgt_id    = dat_fields.tgt_id;
    packet.dat_fields.home_n_id = dat_fields.home_n_id;
    packet.dat_fields.resp      = dat_fields.resp;
    packet.dat_fields.fwd_state = dat_fields.fwd_state;
    packet.dat_fields.dbid      = dat_fields.dbid;

    return packet;
}