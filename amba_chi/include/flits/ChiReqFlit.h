/*
 * CHI REQ Flit
 *
 * Field Enumeration and Widths:
 * ============================
 * | Field Name        | Width (bits) | Range     | Description                           |
 * |-------------------|--------------|-----------|---------------------------------------|
 * | qos               | 4            | 3:0       | Quality of Service                    |
 * | tgtid             | 11           | 14:4      | Target Node ID                        |
 * | srcid             | 11           | 25:15     | Source Node ID                        |
 * | txnid             | 12           | 37:26     | Transaction ID                        |
 * | field_4 (union)   | 11           | 48:38     | Union field with multiple views:      |
 * |   - returnnid     | 11           | 48:38     |   Return Node ID (DMT)                |
 * |   - stashnid      | 11           | 48:38     |   Stash Node ID (Stash transactions)  |
 * |   - slcrephint    | 7            | 44:38     |   SLC Replacement Hint (padded)       |
 * | field_5 (union)   | 1            | 49:49     | Union field with multiple views:      |
 * |   - stashnidvalid | 1            | 49:49     |   Stash Node ID Valid (Stash)         |
 * |   - endian        | 1            | 49:49     |   Endian (Atomic transactions)        |
 * |   - deep          | 1            | 49:49     |   Deep (CleanSharedPersist*)          |
 * | field_6 (union)   | 12           | 61:50     | Union field with multiple views:      |
 * |   - returntxnid   | 12           | 61:50     |   Return Transaction ID (DMT)         |
 * |   - stashlpid     | 5            | 54:50     |   Stash LPID (with valid bit)         |
 * |   - stashlpidvalid| 1            | 55:55     |   Stash LPID Valid                    |
 * | opcode            | 7            | 68:62     | REQ Operation Code                    |
 * | size              | 3            | 71:69     | Transfer Size                         |
 * | addr              | 52           | 123:72    | Address (REQ_ADDR_WIDTH)              |
 * | ns                | 1            | 124:124   | Non-Secure                            |
 * | likelyshared      | 1            | 125:125   | Likely Shared                         |
 * | allowretry        | 1            | 126:126   | Allow Retry                           |
 * | order             | 2            | 128:127   | Ordering Requirements                 |
 * | pcrdtype          | 4            | 132:129   | Protocol Credit Type                  |
 * | memattr           | 4            | 136:133   | Memory Attributes                     |
 * | field_16 (union)  | 1            | 137:137   | Union field with multiple views:      |
 * |   - snpattr       | 1            | 137:137   |   Snoop Attribute                     |
 * |   - dodwt         | 1            | 137:137   |   Do DWT                              |
 * | field_17 (union)  | 8            | 145:138   | Union field with multiple views:      |
 * |   - lpid          | 5            | 142:138   |   LPID (with 3-bit pad)               |
 * |   - pgroupid      | 8            | 145:138   |   P Group ID (Persistent CMO)         |
 * |   - stashgroupid  | 8            | 145:138   |   Stash Group ID (StashOnceSep)       |
 * |   - taggroupid    | 8            | 145:138   |   Tag Group ID (Memory Tagging)       |
 * | field_18 (union)  | 1            | 146:146   | Union field with multiple views:      |
 * |   - excl          | 1            | 146:146   |   Exclusive (Exclusive transactions)  |
 * |   - snoopme       | 1            | 146:146   |   Snoop Me (Atomic transactions)      |
 * | expcompack        | 1            | 147:147   | Expect Completion Acknowledge         |
 * | tagop             | 2            | 149:148   | Tag Operation                         |
 * | tracetag          | 1            | 150:150   | Trace Tag                             |
 * |-------------------|--------------|-----------|---------------------------------------|
 * | Total Flit Width: | 151 bits     |           |                                       |
 *
 * Field Breakdown by Size:
 * - 1-bit fields:  ns, likelyshared, allowretry, snpattr, dodwt, excl, snoopme,
 *                   expcompack, tracetag, stashnidvalid, endian, deep, stashlpidvalid (13 fields)
 * - 2-bit fields:  order, tagop (2 fields)
 * - 3-bit fields:  size (1 field)
 * - 4-bit fields:  qos, pcrdtype, memattr (3 fields)
 * - 5-bit fields:  stashlpid, lpid (2 fields)
 * - 7-bit fields:  opcode, slcrephint (2 fields)
 * - 8-bit fields:  pgroupid, stashgroupid, taggroupid (3 fields)
 * - 11-bit fields: tgtid, srcid, returnnid, stashnid (4 fields)
 * - 12-bit fields: txnid, returntxnid (2 fields)
 * - 52-bit fields: addr (1 field)
 *
 * Note: The union fields allow the same bits to be interpreted in different
 *       ways depending on the context of the REQ transaction:
 *       - field_4: returnnid for DMT, stashnid for Stash, slcrephint for cache replacement
 *       - field_5: stashnidvalid for Stash, endian for Atomic, deep for CleanSharedPersist*
 *       - field_6: returntxnid for DMT, stashlpid/stashlpidvalid for Stash
 *       - field_16: snpattr for general use, dodwt for DWT
 *       - field_17: lpid for general use, *groupid for specific contexts
 *       - field_18: excl for Exclusive, snoopme for Atomic transactions
 */

#ifndef __CHI_REQ_FLIT_H__
#define __CHI_REQ_FLIT_H__

#include <systemc>

namespace flits
{

struct ChiReqFlit
{
private:
    static constexpr auto REQ_ADDR_WIDTH = 52;
    static constexpr auto NODEID_WIDTH = 11;
    static constexpr auto OPCODE_WIDTH = 7;

    static constexpr auto FLIT_WIDTH = 151;

    // field 0
    static constexpr auto QOS_MSB = 3, QOS_LSB = 0;

    // field 1
    static constexpr auto TGTID_MSB = 14, TGTID_LSB = 4;

    // field 2
    static constexpr auto SRCID_MSB = 25, SRCID_LSB = 15;

    // field 3
    static constexpr auto TXNID_MSB = 37, TXNID_LSB = 26;

    // field 4
    static constexpr auto RETURNNID_MSB = 48, RETURNNID_LSB = 38;
    static constexpr auto STASHNID_MSB = 48, STASHNID_LSB = 38;
    static constexpr auto SLCREPHINT_MSB = 44, SLCREPHINT_LSB = 38;

    // field 5
    static constexpr auto STASHNIDVALID_MSB = 49, STASHNIDVALID_LSB = 49;
    static constexpr auto ENDIAN_MSB = 49, ENDIAN_LSB = 49;
    static constexpr auto DEEP_MSB = 49, DEEP_LSB = 49;

    // field 6
    static constexpr auto RETURNTXNID_MSB = 61, RETURNTXNID_LSB = 50;
    static constexpr auto STASHLPID_MSB = 54, STASHLPID_LSB = 50;
    static constexpr auto STASHLPIDVALID_MSB = 55, STASHLPIDVALID_LSB = 55;

    // field 7
    static constexpr auto OPCODE_MSB = 68, OPCODE_LSB = 62;

    // field 8
    static constexpr auto SIZE_MSB = 71, SIZE_LSB = 69;

    // field 9
    static constexpr auto ADDR_MSB = 123, ADDR_LSB = 72;

    // field 10
    static constexpr auto NS_MSB = 124, NS_LSB = 124;

    // field 11
    static constexpr auto LIKELYSHARED_MSB = 125, LIKELYSHARED_LSB = 125;

    // field 12
    static constexpr auto ALLOWRETRY_MSB = 126, ALLOWRETRY_LSB = 126;

    // field 13
    static constexpr auto ORDER_MSB = 128, ORDER_LSB = 127;

    // field 14
    static constexpr auto PCRDTYPE_MSB = 132, PCRDTYPE_LSB = 129;

    // field 15
    static constexpr auto MEMATTR_MSB = 136, MEMATTR_LSB = 133;

    // field 16
    static constexpr auto SNPATTR_MSB = 137, SNPATTR_LSB = 137;
    static constexpr auto DODWT_MSB = 137, DODWT_LSB = 137;

    // field 17
    static constexpr auto LPID_MSB = 142, LPID_LSB = 138;
    static constexpr auto PGROUPID_MSB = 145, PGROUPID_LSB = 138;
    static constexpr auto STASHGROUPID_MSB = 145, STASHGROUPID_LSB = 138;
    static constexpr auto TAGGROUPID_MSB = 145, TAGGROUPID_LSB = 138;

    // field 18
    static constexpr auto EXCL_MSB = 146, EXCL_LSB = 146;
    static constexpr auto SNOOPME_MSB = 146, SNOOPME_LSB = 146;

    // field 19
    static constexpr auto EXPCOMPACK_MSB = 147, EXPCOMPACK_LSB = 147;

    // field 20
    static constexpr auto TAGOP_MSB = 149, TAGOP_LSB = 148;

    // field 21
    static constexpr auto TRACETAG_MSB = 150, TRACETAG_LSB = 150;

    sc_dt::sc_bv<FLIT_WIDTH> data;

public:
    ChiReqFlit() : data(0) {}
    ChiReqFlit(const sc_dt::sc_bv<FLIT_WIDTH> &bits) : data(bits) {}

    void set_qos(sc_dt::sc_uint<4> val)
    {
        data.range(QOS_MSB, QOS_LSB) = val;
    }

    void set_tgtid(sc_dt::sc_uint<11> val)
    {
        data.range(TGTID_MSB, TGTID_LSB) = val;
    }

    void set_srcid(sc_dt::sc_uint<11> val)
    {
        data.range(SRCID_MSB, SRCID_LSB) = val;
    }

    void set_txnid(sc_dt::sc_uint<12> val)
    {
        data.range(TXNID_MSB, TXNID_LSB) = val;
    }

    void set_stashnid(sc_dt::sc_uint<11> val)
    {
        data.range(STASHNID_MSB, STASHNID_LSB) = val;
    }

    void set_returnnid(sc_dt::sc_uint<11> val)
    {
        data.range(RETURNNID_MSB, RETURNNID_LSB) = val;
    }

    void set_slcrephint(sc_dt::sc_uint<7> val)
    {
        data.range(SLCREPHINT_MSB, SLCREPHINT_LSB) = val;
    }

    void set_deep(sc_dt::sc_uint<1> val)
    {
        data.range(DEEP_MSB, DEEP_LSB) = val;
    }

    void set_endian(sc_dt::sc_uint<1> val)
    {
        data.range(ENDIAN_MSB, ENDIAN_LSB) = val;
    }

    void set_stashnidvalid(sc_dt::sc_uint<1> val)
    {
        data.range(STASHNIDVALID_MSB, STASHNIDVALID_LSB) = val;
    }

    void set_returntxnid(sc_dt::sc_uint<12> val)
    {
        data.range(RETURNTXNID_MSB, RETURNTXNID_LSB) = val;
    }

    void set_stashlpidvalid(sc_dt::sc_uint<1> val)
    {
        data.range(STASHLPIDVALID_MSB, STASHLPIDVALID_LSB) = val;
    }

    void set_stashlpid(sc_dt::sc_uint<5> val)
    {
        data.range(STASHLPID_MSB, STASHLPID_LSB) = val;
    }

    void set_opcode(sc_dt::sc_uint<OPCODE_WIDTH> val)
    {
        data.range(OPCODE_MSB, OPCODE_LSB) = val;
    }

    void set_size(sc_dt::sc_uint<3> val)
    {
        data.range(SIZE_MSB, SIZE_LSB) = val;
    }

    void set_addr(sc_dt::sc_uint<REQ_ADDR_WIDTH> val)
    {
        data.range(ADDR_MSB, ADDR_LSB) = val;
    }

    void set_ns(sc_dt::sc_uint<1> val)
    {
        data.range(NS_MSB, NS_LSB) = val;
    }

    void set_likelyshared(sc_dt::sc_uint<1> val)
    {
        data.range(LIKELYSHARED_MSB, LIKELYSHARED_LSB) = val;
    }

    void set_allowretry(sc_dt::sc_uint<1> val)
    {
        data.range(ALLOWRETRY_MSB, ALLOWRETRY_LSB) = val;
    }

    void set_order(sc_dt::sc_uint<2> val)
    {
        data.range(ORDER_MSB, ORDER_LSB) = val;
    }

    void set_pcrdtype(sc_dt::sc_uint<4> val)
    {
        data.range(PCRDTYPE_MSB, PCRDTYPE_LSB) = val;
    }

    void set_memattr(sc_dt::sc_uint<4> val)
    {
        data.range(MEMATTR_MSB, MEMATTR_LSB) = val;
    }

    void set_dodwt(sc_dt::sc_uint<1> val)
    {
        data.range(DODWT_MSB, DODWT_LSB) = val;
    }

    void set_snpattr(sc_dt::sc_uint<1> val)
    {
        data.range(SNPATTR_MSB, SNPATTR_LSB) = val;
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

    void set_lpid(sc_dt::sc_uint<5> val)
    {
        data.range(LPID_MSB, LPID_LSB) = val;
    }

    void set_snoopme(sc_dt::sc_uint<1> val)
    {
        data.range(SNOOPME_MSB, SNOOPME_LSB) = val;
    }

    void set_excl(sc_dt::sc_uint<1> val)
    {
        data.range(EXCL_MSB, EXCL_LSB) = val;
    }

    void set_expcompack(sc_dt::sc_uint<1> val)
    {
        data.range(EXPCOMPACK_MSB, EXPCOMPACK_LSB) = val;
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

    auto get_stashnid() const
    {
        return data.range(STASHNID_MSB, STASHNID_LSB);
    }

    auto get_returnnid() const
    {
        return data.range(RETURNNID_MSB, RETURNNID_LSB);
    }

    auto get_slcrephint() const
    {
        return data.range(SLCREPHINT_MSB, SLCREPHINT_LSB);
    }

    auto get_deep() const
    {
        return data.range(DEEP_MSB, DEEP_LSB);
    }

    auto get_endian() const
    {
        return data.range(ENDIAN_MSB, ENDIAN_LSB);
    }

    auto get_stashnidvalid() const
    {
        return data.range(STASHNIDVALID_MSB, STASHNIDVALID_LSB);
    }

    auto get_returntxnid() const
    {
        return data.range(RETURNTXNID_MSB, RETURNTXNID_LSB);
    }

    auto get_stashlpidvalid() const
    {
        return data.range(STASHLPIDVALID_MSB, STASHLPIDVALID_LSB);
    }

    auto get_stashlpid() const
    {
        return data.range(STASHLPID_MSB, STASHLPID_LSB);
    }

    auto get_opcode() const
    {
        return data.range(OPCODE_MSB, OPCODE_LSB);
    }

    auto get_size() const
    {
        return data.range(SIZE_MSB, SIZE_LSB);
    }

    auto get_addr() const
    {
        return data.range(ADDR_MSB, ADDR_LSB);
    }

    auto get_ns() const
    {
        return data.range(NS_MSB, NS_LSB);
    }

    auto get_likelyshared() const
    {
        return data.range(LIKELYSHARED_MSB, LIKELYSHARED_LSB);
    }

    auto get_allowretry() const
    {
        return data.range(ALLOWRETRY_MSB, ALLOWRETRY_LSB);
    }

    auto get_order() const
    {
        return data.range(ORDER_MSB, ORDER_LSB);
    }

    auto get_pcrdtype() const
    {
        return data.range(PCRDTYPE_MSB, PCRDTYPE_LSB);
    }

    auto get_memattr() const
    {
        return data.range(MEMATTR_MSB, MEMATTR_LSB);
    }

    auto get_dodwt() const
    {
        return data.range(DODWT_MSB, DODWT_LSB);
    }

    auto get_snpattr() const
    {
        return data.range(SNPATTR_MSB, SNPATTR_LSB);
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

    auto get_lpid() const
    {
        return data.range(LPID_MSB, LPID_LSB);
    }

    auto get_snoopme() const
    {
        return data.range(SNOOPME_MSB, SNOOPME_LSB);
    }

    auto get_excl() const
    {
        return data.range(EXCL_MSB, EXCL_LSB);
    }

    auto get_expcompack() const
    {
        return data.range(EXPCOMPACK_MSB, EXPCOMPACK_LSB);
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

    void pack_flit(sc_dt::sc_uint<1> tracetag, sc_dt::sc_uint<2> tagop, sc_dt::sc_uint<1> expcompack,
                   sc_dt::sc_uint<1> field18, sc_dt::sc_uint<8> field17, sc_dt::sc_uint<1> field16,
                   sc_dt::sc_uint<4> memattr, sc_dt::sc_uint<4> pcrdtype, sc_dt::sc_uint<2> order,
                   sc_dt::sc_uint<1> allowretry, sc_dt::sc_uint<1> likelyshared, sc_dt::sc_uint<1> ns,
                   sc_dt::sc_uint<REQ_ADDR_WIDTH> addr, sc_dt::sc_uint<3> size,
                   sc_dt::sc_uint<OPCODE_WIDTH> opcode, sc_dt::sc_uint<12> field6_data,
                   sc_dt::sc_uint<1> field5_data, sc_dt::sc_uint<11> field4_data,
                   sc_dt::sc_uint<12> txnid, sc_dt::sc_uint<11> srcid,
                   sc_dt::sc_uint<11> tgtid, sc_dt::sc_uint<4> qos)
    {
        set_tracetag(tracetag);
        set_tagop(tagop);
        set_expcompack(expcompack);
        set_snoopme(field18);
        set_taggroupid(field17);
        set_dodwt(field16);
        set_memattr(memattr);
        set_pcrdtype(pcrdtype);
        set_order(order);
        set_allowretry(allowretry);
        set_likelyshared(likelyshared);
        set_ns(ns);
        set_addr(addr);
        set_size(size);
        set_opcode(opcode);
        set_returntxnid(field6_data);
        set_deep(field5_data);
        set_stashnid(field4_data);
        set_txnid(txnid);
        set_srcid(srcid);
        set_tgtid(tgtid);
        set_qos(qos);
    }
};

}  // namespace flits

#endif // __CHI_REQ_FLIT_H__
