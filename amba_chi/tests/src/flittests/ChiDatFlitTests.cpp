#include <gtest/gtest.h>
#include <spdlog/spdlog.h>
#include <systemc>

#include <flits/ChiDatFlit.h>


TEST(ChiDatFlitTests, Test_qos)
{
    flits::ChiDatFlit dat_flit;
    dat_flit.set_qos(8);
    EXPECT_EQ(8, dat_flit.get_qos());
}

TEST(ChiDatFlitTests, Test_tgtid)
{
    flits::ChiDatFlit dat_flit;
    dat_flit.set_tgtid(1024);
    EXPECT_EQ(1024, dat_flit.get_tgtid());
}

TEST(ChiDatFlitTests, Test_srcid)
{
    flits::ChiDatFlit dat_flit;
    dat_flit.set_srcid(512);
    EXPECT_EQ(512, dat_flit.get_srcid());
}

TEST(ChiDatFlitTests, Test_txnid)
{
    flits::ChiDatFlit dat_flit;
    dat_flit.set_txnid(2048);
    EXPECT_EQ(2048, dat_flit.get_txnid());
}

TEST(ChiDatFlitTests, Test_homenid)
{
    flits::ChiDatFlit dat_flit;
    dat_flit.set_homenid(256);
    EXPECT_EQ(256, dat_flit.get_homenid());
}

TEST(ChiDatFlitTests, Test_opcode)
{
    flits::ChiDatFlit dat_flit;
    dat_flit.set_opcode(64);
    EXPECT_EQ(64, dat_flit.get_opcode());
}

TEST(ChiDatFlitTests, Test_resperr)
{
    flits::ChiDatFlit dat_flit;
    dat_flit.set_resperr(2);
    EXPECT_EQ(2, dat_flit.get_resperr());
}

TEST(ChiDatFlitTests, Test_resp)
{
    flits::ChiDatFlit dat_flit;
    dat_flit.set_resp(4);
    EXPECT_EQ(4, dat_flit.get_resp());
}

TEST(ChiDatFlitTests, Test_datasource)
{
    flits::ChiDatFlit dat_flit;
    dat_flit.set_datasource(8);
    EXPECT_EQ(8, dat_flit.get_datasource());
}

TEST(ChiDatFlitTests, Test_datapull)
{
    flits::ChiDatFlit dat_flit;
    dat_flit.set_datapull(3);
    EXPECT_EQ(3, dat_flit.get_datapull());
}

TEST(ChiDatFlitTests, Test_fwdstate)
{
    flits::ChiDatFlit dat_flit;
    dat_flit.set_fwdstate(5);
    EXPECT_EQ(5, dat_flit.get_fwdstate());
}

TEST(ChiDatFlitTests, Test_cbusy)
{
    flits::ChiDatFlit dat_flit;
    dat_flit.set_cbusy(6);
    EXPECT_EQ(6, dat_flit.get_cbusy());
}

TEST(ChiDatFlitTests, Test_dbid)
{
    flits::ChiDatFlit dat_flit;
    dat_flit.set_dbid(1500);
    EXPECT_EQ(1500, dat_flit.get_dbid());
}

TEST(ChiDatFlitTests, Test_ccid)
{
    flits::ChiDatFlit dat_flit;
    dat_flit.set_ccid(2);
    EXPECT_EQ(2, dat_flit.get_ccid());
}

TEST(ChiDatFlitTests, Test_dataid)
{
    flits::ChiDatFlit dat_flit;
    dat_flit.set_dataid(1);
    EXPECT_EQ(1, dat_flit.get_dataid());
}

TEST(ChiDatFlitTests, Test_tagop)
{
    flits::ChiDatFlit dat_flit;
    dat_flit.set_tagop(3);
    EXPECT_EQ(3, dat_flit.get_tagop());
}

TEST(ChiDatFlitTests, Test_tag)
{
    flits::ChiDatFlit dat_flit;
    dat_flit.set_tag(32768);
    EXPECT_EQ(32768, dat_flit.get_tag());
}

TEST(ChiDatFlitTests, Test_tu)
{
    flits::ChiDatFlit dat_flit;
    dat_flit.set_tu(10);
    EXPECT_EQ(10, dat_flit.get_tu());
}

TEST(ChiDatFlitTests, Test_tracetag)
{
    flits::ChiDatFlit dat_flit;
    dat_flit.set_tracetag(1);
    EXPECT_EQ(1, dat_flit.get_tracetag());
}

TEST(ChiDatFlitTests, Test_be)
{
    flits::ChiDatFlit dat_flit;
    sc_dt::sc_uint<64> test_be = 0xFFFFFFFFFFFFFFFF;
    dat_flit.set_be(test_be);
    EXPECT_EQ(test_be, dat_flit.get_be());
}

TEST(ChiDatFlitTests, Test_data_field)
{
    flits::ChiDatFlit dat_flit;
    sc_dt::sc_bv<512> test_data;
    test_data.range(511, 0) = "0x123456789ABCDEF0FEDCBA0987654321123456789ABCDEF0FEDCBA0987654321123456789ABCDEF0FEDCBA0987654321123456789ABCDEF0FEDCBA0987654321";
    dat_flit.set_data_field(test_data);
    EXPECT_EQ(test_data, dat_flit.get_data_field());
}

TEST(ChiDatFlitTests, Test_all_setters_with_get_raw)
{
    flits::ChiDatFlit dat_flit;

    dat_flit.set_qos(0xF);
    dat_flit.set_tgtid(0x7FF);
    dat_flit.set_srcid(0x400);
    dat_flit.set_txnid(0xFFF);
    dat_flit.set_homenid(0x200);
    dat_flit.set_opcode(0x7F);
    dat_flit.set_resperr(0x3);
    dat_flit.set_resp(0x7);
    dat_flit.set_datasource(0xF);
    dat_flit.set_cbusy(0x7);
    dat_flit.set_dbid(0xFFF);
    dat_flit.set_ccid(0x3);
    dat_flit.set_dataid(0x3);
    dat_flit.set_tagop(0x3);
    dat_flit.set_tag(0xFFFF);
    dat_flit.set_tu(0xF);
    dat_flit.set_tracetag(1);
    dat_flit.set_be(0xFFFFFFFFFFFFFFFF);

    sc_dt::sc_bv<680> expected_raw(0);
    expected_raw.range(167, 0) = "0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE803FFE007FFF";
    EXPECT_EQ(expected_raw, dat_flit.get_raw());
}

TEST(ChiDatFlitTests, Test_set_raw_with_all_getters)
{
    flits::ChiDatFlit dat_flit;

    sc_dt::sc_bv<680> test_raw(0);
    test_raw.range(167, 0) = "0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE803FFE007FFF";
    dat_flit.set_raw(test_raw);

    EXPECT_EQ(0xF, dat_flit.get_qos());
    EXPECT_EQ(0x7FF, dat_flit.get_tgtid());
    EXPECT_EQ(0x400, dat_flit.get_srcid());
    EXPECT_EQ(0xFFF, dat_flit.get_txnid());
    EXPECT_EQ(0x200, dat_flit.get_homenid());
    EXPECT_EQ(0x7F, dat_flit.get_opcode());
    EXPECT_EQ(0x3, dat_flit.get_resperr());
    EXPECT_EQ(0x7, dat_flit.get_resp());
    EXPECT_EQ(0xF, dat_flit.get_datasource());
    EXPECT_EQ(0x7, dat_flit.get_cbusy());
    EXPECT_EQ(0xFFF, dat_flit.get_dbid());
    EXPECT_EQ(0x3, dat_flit.get_ccid());
    EXPECT_EQ(0x3, dat_flit.get_dataid());
    EXPECT_EQ(0x3, dat_flit.get_tagop());
    EXPECT_EQ(0xFFFF, dat_flit.get_tag());
    EXPECT_EQ(0xF, dat_flit.get_tu());
    EXPECT_EQ(0x1, dat_flit.get_tracetag());
    EXPECT_EQ(0xFFFFFFFFFFFFFFFF, dat_flit.get_be());
}

TEST(ChiDatFlitTests, Test_constructor_with_bits)
{
    sc_dt::sc_bv<680> test_bits;
    test_bits.range(3, 0) = 0x5;
    test_bits.range(14, 4) = 0x2AA;

    flits::ChiDatFlit dat_flit(test_bits);

    EXPECT_EQ(0x5, dat_flit.get_qos());
    EXPECT_EQ(0x2AA, dat_flit.get_tgtid());
}

TEST(ChiDatFlitTests, Test_boundary_values)
{
    flits::ChiDatFlit dat_flit;

    dat_flit.set_qos(0xF);
    dat_flit.set_tgtid(0x7FF);
    dat_flit.set_srcid(0x7FF);
    dat_flit.set_txnid(0xFFF);
    dat_flit.set_homenid(0x7FF);
    dat_flit.set_opcode(0x7F);
    dat_flit.set_resperr(0x3);
    dat_flit.set_resp(0x7);
    dat_flit.set_datasource(0xF);
    dat_flit.set_cbusy(0x7);
    dat_flit.set_dbid(0xFFF);
    dat_flit.set_ccid(0x3);
    dat_flit.set_dataid(0x3);
    dat_flit.set_tagop(0x3);
    dat_flit.set_tag(0xFFFF);
    dat_flit.set_tu(0xF);
    dat_flit.set_tracetag(0x1);

    sc_dt::sc_bv<680> raw_data = dat_flit.get_raw();
    EXPECT_NE(0, raw_data.to_uint64());
}

TEST(ChiDatFlitTests, Test_zero_initialization)
{
    flits::ChiDatFlit dat_flit;

    EXPECT_EQ(0, dat_flit.get_qos());
    EXPECT_EQ(0, dat_flit.get_tgtid());
    EXPECT_EQ(0, dat_flit.get_srcid());
    EXPECT_EQ(0, dat_flit.get_txnid());
    EXPECT_EQ(0, dat_flit.get_homenid());
    EXPECT_EQ(0, dat_flit.get_opcode());
    EXPECT_EQ(0, dat_flit.get_resperr());
    EXPECT_EQ(0, dat_flit.get_resp());
    EXPECT_EQ(0, dat_flit.get_datasource());
    EXPECT_EQ(0, dat_flit.get_cbusy());
    EXPECT_EQ(0, dat_flit.get_dbid());
    EXPECT_EQ(0, dat_flit.get_ccid());
    EXPECT_EQ(0, dat_flit.get_dataid());
    EXPECT_EQ(0, dat_flit.get_tagop());
    EXPECT_EQ(0, dat_flit.get_tag());
    EXPECT_EQ(0, dat_flit.get_tu());
    EXPECT_EQ(0, dat_flit.get_tracetag());
    EXPECT_EQ(0, dat_flit.get_be());

    sc_dt::sc_bv<512> expected_zero_data(0);
    EXPECT_EQ(expected_zero_data, dat_flit.get_data_field());
}
