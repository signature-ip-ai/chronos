/*
 * CHI RSP Flit
 *
 * Field Enumeration and Widths:
 * ============================
 * | Field Name        | Width (bits) | Range   | Description                           |
 * |-------------------|--------------|---------|---------------------------------------|
 * | qos               | 4            | 3:0     | Quality of Service                    |
 * | tgtid             | 11           | 14:4    | Target Node ID                        |
 * | srcid             | 11           | 25:15   | Source Node ID                        |
 * | txnid             | 12           | 37:26   | Transaction ID                        |
 * | opcode            | 5            | 42:38   | RSP Operation Code                    |
 * | resperr           | 2            | 44:43   | Response Error                        |
 * | resp              | 3            | 47:45   | Response                              |
 * | field_7 (union)   | 3            | 50:48   | Union field with multiple views:      |
 * |   - datapull      | 3            | 50:48   |   Data Pull (Stash transactions)      |
 * |   - fwdstate      | 3            | 50:48   |   Forward State (DCT)                 |
 * | cbusy             | 3            | 53:51   | Completer Busy                        |
 * | field_9 (union)   | 12           | 65:54   | Union field with multiple views:      |
 * |   - dbid          | 12           | 65:54   |   Data Buffer ID                      |
 * |   - taggroupid    | 8            | 61:54   |   Tag Group ID (Memory Tagging)       |
 * |   - stashgroupid  | 8            | 61:54   |   Stash Group ID (Stash transactions) |
 * |   - pgroupid      | 8            | 61:54   |   P Group ID (Persistent CMO)         |
 * | pcrdtype          | 4            | 69:66   | Protocol Credit Type                  |
 * | tagop             | 2            | 71:70   | Tag Operation                         |
 * | tracetag          | 1            | 72:72   | Trace Tag                             |
 * |-------------------|--------------|---------|---------------------------------------|
 * | Total Flit Width: | 73 bits      |         |                                       |
 *
 * Field Breakdown by Size:
 * - 1-bit fields:  tracetag (1 field)
 * - 2-bit fields:  resperr, tagop (2 fields)
 * - 3-bit fields:  resp, datapull, fwdstate, cbusy (4 fields)
 * - 4-bit fields:  qos, pcrdtype (2 fields)
 * - 5-bit fields:  opcode (1 field)
 * - 8-bit fields:  taggroupid, stashgroupid, pgroupid (3 fields)
 * - 11-bit fields: tgtid, srcid (2 fields)
 * - 12-bit fields: txnid, dbid, field_9 union (3 fields)
 *
 * Note: The union fields allow the same bits to be interpreted in different
 *       ways depending on the context of the RSP transaction:
 *       - field_7: datapull for Stash, fwdstate for DCT
 *       - field_9: dbid for general use, *groupid for specific contexts
 */

#ifndef __CHI_RSP_FLIT_H__
#define __CHI_RSP_FLIT_H__

#include <systemc>

namespace flits
{

struct ChiRspFlit
{
private:
    static constexpr auto NODEID_WIDTH = 11;
    static constexpr auto OPCODE_WIDTH = 5;
    static constexpr auto FLIT_WIDTH = 73;

    // field 0
    static constexpr auto QOS_MSB = 3, QOS_LSB = 0;

    // field 1
    static constexpr auto TGTID_MSB = 14, TGTID_LSB = 4;

    // field 2
    static constexpr auto SRCID_MSB = 25, SRCID_LSB = 15;

    // field 3
    static constexpr auto TXNID_MSB = 37, TXNID_LSB = 26;

    // field 4
    static constexpr auto OPCODE_MSB = 42, OPCODE_LSB = 38;

    // field 5
    static constexpr auto RESPERR_MSB = 44, RESPERR_LSB = 43;

    // field 6
    static constexpr auto RESP_MSB = 47, RESP_LSB = 45;

    // field 7
    static constexpr auto DATAPULL_MSB = 50, DATAPULL_LSB = 48;
    static constexpr auto FWDSTATE_MSB = 50, FWDSTATE_LSB = 48;

    // field 8
    static constexpr auto CBUSY_MSB = 53, CBUSY_LSB = 51;

    // field 9
    static constexpr auto DBID_MSB = 65, DBID_LSB = 54;
    static constexpr auto TAGGROUPID_MSB = 61, TAGGROUPID_LSB = 54;
    static constexpr auto STASHGROUPID_MSB = 61, STASHGROUPID_LSB = 54;
    static constexpr auto PGROUPID_MSB = 61, PGROUPID_LSB = 54;

    // field 10
    static constexpr auto PCRDTYPE_MSB = 69, PCRDTYPE_LSB = 66;

    // field 11
    static constexpr auto TAGOP_MSB = 71, TAGOP_LSB = 70;

    // field 12
    static constexpr auto TRACETAG_MSB = 72, TRACETAG_LSB = 72;

    sc_dt::sc_bv<FLIT_WIDTH> data;

public:
    ChiRspFlit() : data(0) {}
    ChiRspFlit(const sc_dt::sc_bv<FLIT_WIDTH> &bits) : data(bits) {}

    void set_qos(sc_dt::sc_uint<4> val)
    {
        data.range(QOS_MSB, QOS_LSB) = val;
    }

    void set_tgtid(sc_dt::sc_uint<NODEID_WIDTH> val)
    {
        data.range(TGTID_MSB, TGTID_LSB) = val;
    }

    void set_srcid(sc_dt::sc_uint<NODEID_WIDTH> val)
    {
        data.range(SRCID_MSB, SRCID_LSB) = val;
    }

    void set_txnid(sc_dt::sc_uint<12> val)
    {
        data.range(TXNID_MSB, TXNID_LSB) = val;
    }

    void set_opcode(sc_dt::sc_uint<OPCODE_WIDTH> val)
    {
        data.range(OPCODE_MSB, OPCODE_LSB) = val;
    }

    void set_resperr(sc_dt::sc_uint<2> val)
    {
        data.range(RESPERR_MSB, RESPERR_LSB) = val;
    }

    void set_resp(sc_dt::sc_uint<3> val)
    {
        data.range(RESP_MSB, RESP_LSB) = val;
    }

    void set_datapull(sc_dt::sc_uint<3> val)
    {
        data.range(DATAPULL_MSB, DATAPULL_LSB) = val;
    }

    void set_fwdstate(sc_dt::sc_uint<3> val)
    {
        data.range(FWDSTATE_MSB, FWDSTATE_LSB) = val;
    }

    void set_cbusy(sc_dt::sc_uint<3> val)
    {
        data.range(CBUSY_MSB, CBUSY_LSB) = val;
    }

    void set_dbid(sc_dt::sc_uint<12> val)
    {
        data.range(DBID_MSB, DBID_LSB) = val;
    }

    void set_taggroupid(sc_dt::sc_uint<8> val)
    {
        data.range(TAGGROUPID_MSB, TAGGROUPID_LSB) = val;
    }

    void set_stashgroupid(sc_dt::sc_uint<8> val)
    {
        data.range(STASHGROUPID_MSB, STASHGROUPID_LSB) = val;
    }

    void set_pgroupid(sc_dt::sc_uint<8> val)
    {
        data.range(PGROUPID_MSB, PGROUPID_LSB) = val;
    }

    void set_pcrdtype(sc_dt::sc_uint<4> val)
    {
        data.range(PCRDTYPE_MSB, PCRDTYPE_LSB) = val;
    }

    void set_tagop(sc_dt::sc_uint<2> val)
    {
        data.range(TAGOP_MSB, TAGOP_LSB) = val;
    }

    void set_tracetag(sc_dt::sc_uint<1> val)
    {
        data.range(TRACETAG_MSB, TRACETAG_LSB) = val;
    }

    auto get_qos() const
    {
        return data.range(QOS_MSB, QOS_LSB);
    }

    auto get_tgtid() const
    {
        return data.range(TGTID_MSB, TGTID_LSB);
    }

    auto get_srcid() const
    {
        return data.range(SRCID_MSB, SRCID_LSB);
    }

    auto get_txnid() const
    {
        return data.range(TXNID_MSB, TXNID_LSB);
    }

    auto get_opcode() const
    {
        return data.range(OPCODE_MSB, OPCODE_LSB);
    }

    auto get_resperr() const
    {
        return data.range(RESPERR_MSB, RESPERR_LSB);
    }

    auto get_resp() const
    {
        return data.range(RESP_MSB, RESP_LSB);
    }

    auto get_datapull() const
    {
        return data.range(DATAPULL_MSB, DATAPULL_LSB);
    }

    auto get_fwdstate() const
    {
        return data.range(FWDSTATE_MSB, FWDSTATE_LSB);
    }

    auto get_cbusy() const
    {
        return data.range(CBUSY_MSB, CBUSY_LSB);
    }

    auto get_dbid() const
    {
        return data.range(DBID_MSB, DBID_LSB);
    }

    auto get_taggroupid() const
    {
        return data.range(TAGGROUPID_MSB, TAGGROUPID_LSB);
    }

    auto get_stashgroupid() const
    {
        return data.range(STASHGROUPID_MSB, STASHGROUPID_LSB);
    }

    auto get_pgroupid() const
    {
        return data.range(PGROUPID_MSB, PGROUPID_LSB);
    }

    auto get_pcrdtype() const
    {
        return data.range(PCRDTYPE_MSB, PCRDTYPE_LSB);
    }

    auto get_tagop() const
    {
        return data.range(TAGOP_MSB, TAGOP_LSB);
    }

    auto get_tracetag() const
    {
        return data.range(TRACETAG_MSB, TRACETAG_LSB);
    }

    sc_dt::sc_bv<FLIT_WIDTH> get_raw() const
    {
        return data;
    }

    void set_raw(const sc_dt::sc_bv<FLIT_WIDTH> &bits)
    {
        data = bits;
    }

    void pack_flit(sc_dt::sc_uint<1> tracetag, sc_dt::sc_uint<2> tagop, sc_dt::sc_uint<4> pcrdtype,
                   sc_dt::sc_uint<12> field_9_data, sc_dt::sc_uint<3> cbusy, sc_dt::sc_uint<3> field_7_data,
                   sc_dt::sc_uint<3> resp, sc_dt::sc_uint<2> resperr, sc_dt::sc_uint<OPCODE_WIDTH> opcode,
                   sc_dt::sc_uint<12> txnid, sc_dt::sc_uint<NODEID_WIDTH> srcid,
                   sc_dt::sc_uint<NODEID_WIDTH> tgtid, sc_dt::sc_uint<4> qos)
    {
        set_tracetag(tracetag);
        set_tagop(tagop);
        set_pcrdtype(pcrdtype);
        set_dbid(field_9_data);
        set_cbusy(cbusy);
        set_datapull(field_7_data);
        set_resp(resp);
        set_resperr(resperr);
        set_opcode(opcode);
        set_txnid(txnid);
        set_srcid(srcid);
        set_tgtid(tgtid);
        set_qos(qos);
    }
};

}  // namespace flits

#endif // __CHI_RSP_FLIT_H__
