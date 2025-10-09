#ifndef __CHI_DAT_FLIT_H__
#define __CHI_DAT_FLIT_H__

#include <systemc>

namespace flits
{

struct ChiDatFlit
{
private:
    static constexpr auto DATA_WIDTH = 512;
    static constexpr auto NODEID_WIDTH = 11;

    // Calculate total flit width
    // data[511:0] + be[63:0] + tracetag[0:0] + tu[3:0] + tag[15:0] + tagop[1:0] + dataid[1:0] + ccid[1:0] +
    // dbid[11:0] + cbusy[2:0] + datasource[3:0] + resp[2:0] + resperr[1:0] + opcode[3:0] + homenid[10:0] +
    // txnid[11:0] + srcid[10:0] + tgtid[10:0] + qos[3:0]
    static constexpr auto FLIT_WIDTH = 680;

    // Field bit positions (from LSB)
    // field 0: qos[3:0]
    static constexpr auto QOS_MSB = 3, QOS_LSB = 0;

    // field 1: tgtid[10:0]
    static constexpr auto TGTID_MSB = 14, TGTID_LSB = 4;

    // field 2: srcid[10:0]
    static constexpr auto SRCID_MSB = 25, SRCID_LSB = 15;

    // field 3: txnid[11:0]
    static constexpr auto TXNID_MSB = 37, TXNID_LSB = 26;

    // field 4: homenid[10:0]
    static constexpr auto HOMENID_MSB = 48, HOMENID_LSB = 38;

    // field 5: opcode[3:0]
    static constexpr auto OPCODE_MSB = 52, OPCODE_LSB = 49;

    // field 6: resperr[1:0]
    static constexpr auto RESPERR_MSB = 54, RESPERR_LSB = 53;

    // field 7: resp[2:0]
    static constexpr auto RESP_MSB = 57, RESP_LSB = 55;

    // field 8: datasource[3:0] (union field)
    static constexpr auto DATASOURCE_MSB = 61, DATASOURCE_LSB = 58;
    static constexpr auto DATAPULL_MSB = 60, DATAPULL_LSB = 58;
    static constexpr auto FWDSTATE_MSB = 60, FWDSTATE_LSB = 58;

    // field 9: cbusy[2:0]
    static constexpr auto CBUSY_MSB = 64, CBUSY_LSB = 62;

    // field 10: dbid[11:0]
    static constexpr auto DBID_MSB = 76, DBID_LSB = 65;

    // field 11: ccid[1:0]
    static constexpr auto CCID_MSB = 78, CCID_LSB = 77;

    // field 12: dataid[1:0]
    static constexpr auto DATAID_MSB = 80, DATAID_LSB = 79;

    // field 13: tagop[1:0]
    static constexpr auto TAGOP_MSB = 82, TAGOP_LSB = 81;

    // field 14: tag[15:0]
    static constexpr auto TAG_MSB = 98, TAG_LSB = 83;

    // field 15: tu[3:0]
    static constexpr auto TU_MSB = 102, TU_LSB = 99;

    // field 16: tracetag[0:0]
    static constexpr auto TRACETAG_MSB = 103, TRACETAG_LSB = 103;

    // field 17: be[63:0]
    static constexpr auto BE_MSB = 167, BE_LSB = 104;

    // field 18: data[511:0]
    static constexpr auto DATA_MSB = 679, DATA_LSB = 168;

    sc_dt::sc_bv<FLIT_WIDTH> data;

public:
    ChiDatFlit() : data(0) {}
    ChiDatFlit(const sc_dt::sc_bv<FLIT_WIDTH> &bits) : data(bits) {}

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

    void set_homenid(sc_dt::sc_uint<NODEID_WIDTH> val)
    {
        data.range(HOMENID_MSB, HOMENID_LSB) = val;
    }

    void set_opcode(sc_dt::sc_uint<7> val)
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

    void set_datasource(sc_dt::sc_uint<4> val)
    {
        data.range(DATASOURCE_MSB, DATASOURCE_LSB) = val;
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

    void set_ccid(sc_dt::sc_uint<2> val)
    {
        data.range(CCID_MSB, CCID_LSB) = val;
    }

    void set_dataid(sc_dt::sc_uint<2> val)
    {
        data.range(DATAID_MSB, DATAID_LSB) = val;
    }

    void set_tagop(sc_dt::sc_uint<2> val)
    {
        data.range(TAGOP_MSB, TAGOP_LSB) = val;
    }

    void set_tag(sc_dt::sc_uint<16> val)
    {
        data.range(TAG_MSB, TAG_LSB) = val;
    }

    void set_tu(sc_dt::sc_uint<4> val)
    {
        data.range(TU_MSB, TU_LSB) = val;
    }

    void set_tracetag(sc_dt::sc_uint<1> val)
    {
        data.range(TRACETAG_MSB, TRACETAG_LSB) = val;
    }

    void set_be(sc_dt::sc_uint<64> val)
    {
        data.range(BE_MSB, BE_LSB) = val;
    }

    void set_data_field(sc_dt::sc_bv<DATA_WIDTH> val)
    {
        data.range(DATA_MSB, DATA_LSB) = val;
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

    auto get_homenid() const
    {
        return data.range(HOMENID_MSB, HOMENID_LSB);
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

    auto get_datasource() const
    {
        return data.range(DATASOURCE_MSB, DATASOURCE_LSB);
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

    auto get_ccid() const
    {
        return data.range(CCID_MSB, CCID_LSB);
    }

    auto get_dataid() const
    {
        return data.range(DATAID_MSB, DATAID_LSB);
    }

    auto get_tagop() const
    {
        return data.range(TAGOP_MSB, TAGOP_LSB);
    }

    auto get_tag() const
    {
        return data.range(TAG_MSB, TAG_LSB);
    }

    auto get_tu() const
    {
        return data.range(TU_MSB, TU_LSB);
    }

    auto get_tracetag() const
    {
        return data.range(TRACETAG_MSB, TRACETAG_LSB);
    }

    auto get_be() const
    {
        return data.range(BE_MSB, BE_LSB);
    }

    auto get_data_field() const
    {
        return data.range(DATA_MSB, DATA_LSB);
    }

    sc_dt::sc_bv<FLIT_WIDTH> get_raw() const
    {
        return data;
    }

    void set_raw(const sc_dt::sc_bv<FLIT_WIDTH> &bits)
    {
        data = bits;
    }

    void pack_flit(sc_dt::sc_bv<DATA_WIDTH> data_field, sc_dt::sc_uint<64> be, sc_dt::sc_uint<1> tracetag,
                   sc_dt::sc_uint<4> tu, sc_dt::sc_uint<16> tag, sc_dt::sc_uint<2> tagop,
                   sc_dt::sc_uint<2> dataid, sc_dt::sc_uint<2> ccid, sc_dt::sc_uint<12> dbid,
                   sc_dt::sc_uint<3> cbusy, sc_dt::sc_uint<4> datasource, sc_dt::sc_uint<3> resp,
                   sc_dt::sc_uint<2> resperr, sc_dt::sc_uint<7> opcode, sc_dt::sc_uint<NODEID_WIDTH> homenid,
                   sc_dt::sc_uint<12> txnid, sc_dt::sc_uint<NODEID_WIDTH> srcid,
                   sc_dt::sc_uint<NODEID_WIDTH> tgtid, sc_dt::sc_uint<4> qos)
    {
        set_data_field(data_field);
        set_be(be);
        set_tracetag(tracetag);
        set_tu(tu);
        set_tag(tag);
        set_tagop(tagop);
        set_dataid(dataid);
        set_ccid(ccid);
        set_dbid(dbid);
        set_cbusy(cbusy);
        set_datasource(datasource);
        set_resp(resp);
        set_resperr(resperr);
        set_opcode(opcode);
        set_homenid(homenid);
        set_txnid(txnid);
        set_srcid(srcid);
        set_tgtid(tgtid);
        set_qos(qos);
    }
};

}  // namespace flits

#endif // __CHI_DAT_FLIT_H__
