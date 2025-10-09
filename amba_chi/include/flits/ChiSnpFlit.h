/*
 * CHI SNP Flit
 *
 * Field Enumeration and Widths:
 * ============================
 * | Field Name        | Width (bits) | Range   | Description                           |
 * |-------------------|--------------|---------|---------------------------------------|
 * | qos               | 4            | 3:0     | Quality of Service                    |
 * | srcid             | 11           | 14:4    | Source Node ID                        |
 * | txnid             | 12           | 26:15   | Transaction ID                        |
 * | fwdnid            | 11           | 37:27   | Forward Node ID                       |
 * | field_4 (union)   | 12           | 49:38   | Union field with multiple views:      |
 * |   - fwdtxnid      | 12           | 49:38   |   Forward Transaction ID              |
 * |   - vmidext       | 8            | 45:38   |   VM ID Extension (with 4-bit pad)    |
 * |   - stashlpid     | 5            | 42:38   |   Stash LPID (with 6-bit pad)         |
 * |   - stashlpidvalid| 1            | 43:43   |   Stash LPID Valid                    |
 * | opcode            | 5            | 54:50   | SNP Operation Code                    |
 * | addr              | 49           | 103:55  | Address (REQ_ADDR_WIDTH-3 = 52-3)     |
 * | ns                | 1            | 104:104 | Non-Secure                            |
 * | donotgotosd       | 1            | 105:105 | Do Not Go To SD                       |
 * | rettosrc          | 1            | 106:106 | Return To Source                      |
 * | tracetag          | 1            | 107:107 | Trace Tag                             |
 * |-------------------|--------------|---------|---------------------------------------|
 * | Total Flit Width: | 108 bits     |         |                                       |
 *
 * Field Breakdown by Size:
 * - 1-bit fields:  ns, donotgotosd, rettosrc, tracetag, stashlpidvalid (5 fields)
 * - 4-bit fields:  qos (1 field)
 * - 5-bit fields:  opcode, stashlpid (2 fields)
 * - 8-bit fields:  vmidext (1 field)
 * - 11-bit fields: srcid, fwdnid (2 fields)
 * - 12-bit fields: txnid, fwdtxnid, field_4 union (3 fields)
 * - 49-bit fields: addr (1 field)
 *
 * Note: The union field_4 allows the same 12 bits to be interpreted in three
 *       different ways depending on the context of the SNP transaction.
 */

#ifndef __CHI_SNP_FLIT_H__
#define __CHI_SNP_FLIT_H__

#include <systemc>

namespace flits
{

struct ChiSnpFlit
{
private:
    static constexpr auto REQ_ADDR_WIDTH = 52;
    static constexpr auto NODEID_WIDTH = 11;
    static constexpr auto OPCODE_WIDTH = 5;

    static constexpr auto FLIT_WIDTH = 108;

    // field 0 - qos
    static constexpr auto QOS_MSB = 3, QOS_LSB = 0;

    // field 1 - srcid
    static constexpr auto SRCID_MSB = 14, SRCID_LSB = 4;

    // field 2 - txnid
    static constexpr auto TXNID_MSB = 26, TXNID_LSB = 15;

    // field 3 - fwdnid
    static constexpr auto FWDNID_MSB = 37, FWDNID_LSB = 27;

    // field 4 - union field_4 (fwdtxnid/vmidext/stash fields)
    static constexpr auto FWDTXNID_MSB = 49, FWDTXNID_LSB = 38;
    static constexpr auto VMIDEXT_MSB = 45, VMIDEXT_LSB = 38;
    static constexpr auto STASHLPID_MSB = 42, STASHLPID_LSB = 38;
    static constexpr auto STASHLPIDVALID_MSB = 43, STASHLPIDVALID_LSB = 43;

    // field 5 - opcode
    static constexpr auto OPCODE_MSB = 54, OPCODE_LSB = 50;

    // field 6 - addr
    static constexpr auto ADDR_MSB = 103, ADDR_LSB = 55;

    // field 7 - ns
    static constexpr auto NS_MSB = 104, NS_LSB = 104;

    // field 8 - donotgotosd
    static constexpr auto DONOTGOTOSD_MSB = 105, DONOTGOTOSD_LSB = 105;

    // field 9 - rettosrc
    static constexpr auto RETTOSRC_MSB = 106, RETTOSRC_LSB = 106;

    // field 10 - tracetag
    static constexpr auto TRACETAG_MSB = 107, TRACETAG_LSB = 107;

    sc_dt::sc_bv<FLIT_WIDTH> data;

public:
    ChiSnpFlit() : data(0) {}
    ChiSnpFlit(const sc_dt::sc_bv<FLIT_WIDTH> &bits) : data(bits) {}

    void set_qos(sc_dt::sc_uint<4> val)
    {
        data.range(QOS_MSB, QOS_LSB) = val;
    }

    void set_srcid(sc_dt::sc_uint<NODEID_WIDTH> val)
    {
        data.range(SRCID_MSB, SRCID_LSB) = val;
    }

    void set_txnid(sc_dt::sc_uint<12> val)
    {
        data.range(TXNID_MSB, TXNID_LSB) = val;
    }

    void set_fwdnid(sc_dt::sc_uint<NODEID_WIDTH> val)
    {
        data.range(FWDNID_MSB, FWDNID_LSB) = val;
    }

    void set_fwdtxnid(sc_dt::sc_uint<12> val)
    {
        data.range(FWDTXNID_MSB, FWDTXNID_LSB) = val;
    }

    void set_vmidext(sc_dt::sc_uint<8> val)
    {
        data.range(VMIDEXT_MSB, VMIDEXT_LSB) = val;
    }

    void set_stashlpid(sc_dt::sc_uint<5> val)
    {
        data.range(STASHLPID_MSB, STASHLPID_LSB) = val;
    }

    void set_stashlpidvalid(sc_dt::sc_uint<1> val)
    {
        data.range(STASHLPIDVALID_MSB, STASHLPIDVALID_LSB) = val;
    }

    void set_opcode(sc_dt::sc_uint<OPCODE_WIDTH> val)
    {
        data.range(OPCODE_MSB, OPCODE_LSB) = val;
    }

    void set_addr(sc_dt::sc_uint<REQ_ADDR_WIDTH - 3> val)
    {
        data.range(ADDR_MSB, ADDR_LSB) = val;
    }

    void set_ns(sc_dt::sc_uint<1> val)
    {
        data.range(NS_MSB, NS_LSB) = val;
    }

    void set_donotgotosd(sc_dt::sc_uint<1> val)
    {
        data.range(DONOTGOTOSD_MSB, DONOTGOTOSD_LSB) = val;
    }

    void set_rettosrc(sc_dt::sc_uint<1> val)
    {
        data.range(RETTOSRC_MSB, RETTOSRC_LSB) = val;
    }

    void set_tracetag(sc_dt::sc_uint<1> val)
    {
        data.range(TRACETAG_MSB, TRACETAG_LSB) = val;
    }

    auto get_qos() const
    {
        return data.range(QOS_MSB, QOS_LSB);
    }

    auto get_srcid() const
    {
        return data.range(SRCID_MSB, SRCID_LSB);
    }

    auto get_txnid() const
    {
        return data.range(TXNID_MSB, TXNID_LSB);
    }

    auto get_fwdnid() const
    {
        return data.range(FWDNID_MSB, FWDNID_LSB);
    }

    auto get_fwdtxnid() const
    {
        return data.range(FWDTXNID_MSB, FWDTXNID_LSB);
    }

    auto get_vmidext() const
    {
        return data.range(VMIDEXT_MSB, VMIDEXT_LSB);
    }

    auto get_stashlpid() const
    {
        return data.range(STASHLPID_MSB, STASHLPID_LSB);
    }

    auto get_stashlpidvalid() const
    {
        return data.range(STASHLPIDVALID_MSB, STASHLPIDVALID_LSB);
    }

    auto get_opcode() const
    {
        return data.range(OPCODE_MSB, OPCODE_LSB);
    }

    auto get_addr() const
    {
        return data.range(ADDR_MSB, ADDR_LSB);
    }

    auto get_ns() const
    {
        return data.range(NS_MSB, NS_LSB);
    }

    auto get_donotgotosd() const
    {
        return data.range(DONOTGOTOSD_MSB, DONOTGOTOSD_LSB);
    }

    auto get_rettosrc() const
    {
        return data.range(RETTOSRC_MSB, RETTOSRC_LSB);
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

    void pack_flit(sc_dt::sc_uint<1> tracetag, sc_dt::sc_uint<1> rettosrc,
                   sc_dt::sc_uint<1> donotgotosd, sc_dt::sc_uint<1> ns,
                   sc_dt::sc_uint<REQ_ADDR_WIDTH - 3> addr, sc_dt::sc_uint<OPCODE_WIDTH> opcode,
                   sc_dt::sc_uint<12> field_4_data, sc_dt::sc_uint<NODEID_WIDTH> fwdnid,
                   sc_dt::sc_uint<12> txnid, sc_dt::sc_uint<NODEID_WIDTH> srcid,
                   sc_dt::sc_uint<4> qos)
    {
        set_tracetag(tracetag);
        set_rettosrc(rettosrc);
        set_donotgotosd(donotgotosd);
        set_ns(ns);
        set_addr(addr);
        set_opcode(opcode);
        set_fwdtxnid(field_4_data);
        set_fwdnid(fwdnid);
        set_txnid(txnid);
        set_srcid(srcid);
        set_qos(qos);
    }
};

}  // namespace flits

#endif // __CHI_SNP_FLIT_H__
