#include <gtest/gtest.h>
#include <spdlog/spdlog.h>
#include <systemc>

#include <flits/ChiRspFlit.h>


TEST(ChiRspFlitTests, Test_qos)
{
    flits::ChiRspFlit rsp_flit;
    rsp_flit.set_qos(4);
    EXPECT_EQ(4, rsp_flit.get_qos());
}

TEST(ChiRspFlitTests, Test_tgtid)
{
    flits::ChiRspFlit rsp_flit;
    rsp_flit.set_tgtid(1024);
    EXPECT_EQ(1024, rsp_flit.get_tgtid());
}

TEST(ChiRspFlitTests, Test_srcid)
{
    flits::ChiRspFlit rsp_flit;
    rsp_flit.set_srcid(512);
    EXPECT_EQ(512, rsp_flit.get_srcid());
}

TEST(ChiRspFlitTests, Test_txnid)
{
    flits::ChiRspFlit rsp_flit;
    rsp_flit.set_txnid(2048);
    EXPECT_EQ(2048, rsp_flit.get_txnid());
}

TEST(ChiRspFlitTests, Test_opcode)
{
    flits::ChiRspFlit rsp_flit;
    rsp_flit.set_opcode(16);
    EXPECT_EQ(16, rsp_flit.get_opcode());
}

TEST(ChiRspFlitTests, Test_resperr)
{
    flits::ChiRspFlit rsp_flit;
    rsp_flit.set_resperr(2);
    EXPECT_EQ(2, rsp_flit.get_resperr());
}

TEST(ChiRspFlitTests, Test_resp)
{
    flits::ChiRspFlit rsp_flit;
    rsp_flit.set_resp(4);
    EXPECT_EQ(4, rsp_flit.get_resp());
}

TEST(ChiRspFlitTests, Test_datapull)
{
    flits::ChiRspFlit rsp_flit;
    rsp_flit.set_datapull(3);
    EXPECT_EQ(3, rsp_flit.get_datapull());
}

TEST(ChiRspFlitTests, Test_fwdstate)
{
    flits::ChiRspFlit rsp_flit;
    rsp_flit.set_fwdstate(5);
    EXPECT_EQ(5, rsp_flit.get_fwdstate());
}

TEST(ChiRspFlitTests, Test_cbusy)
{
    flits::ChiRspFlit rsp_flit;
    rsp_flit.set_cbusy(6);
    EXPECT_EQ(6, rsp_flit.get_cbusy());
}

TEST(ChiRspFlitTests, Test_dbid)
{
    flits::ChiRspFlit rsp_flit;
    rsp_flit.set_dbid(1500);
    EXPECT_EQ(1500, rsp_flit.get_dbid());
}

TEST(ChiRspFlitTests, Test_taggroupid)
{
    flits::ChiRspFlit rsp_flit;
    rsp_flit.set_taggroupid(200);
    EXPECT_EQ(200, rsp_flit.get_taggroupid());
}

TEST(ChiRspFlitTests, Test_stashgroupid)
{
    flits::ChiRspFlit rsp_flit;
    rsp_flit.set_stashgroupid(150);
    EXPECT_EQ(150, rsp_flit.get_stashgroupid());
}

TEST(ChiRspFlitTests, Test_pgroupid)
{
    flits::ChiRspFlit rsp_flit;
    rsp_flit.set_pgroupid(100);
    EXPECT_EQ(100, rsp_flit.get_pgroupid());
}

TEST(ChiRspFlitTests, Test_pcrdtype)
{
    flits::ChiRspFlit rsp_flit;
    rsp_flit.set_pcrdtype(8);
    EXPECT_EQ(8, rsp_flit.get_pcrdtype());
}

TEST(ChiRspFlitTests, Test_tagop)
{
    flits::ChiRspFlit rsp_flit;
    rsp_flit.set_tagop(3);
    EXPECT_EQ(3, rsp_flit.get_tagop());
}

TEST(ChiRspFlitTests, Test_tracetag)
{
    flits::ChiRspFlit rsp_flit;
    rsp_flit.set_tracetag(1);
    EXPECT_EQ(1, rsp_flit.get_tracetag());
}

TEST(ChiRspFlitTests, Test_all_setters_with_get_raw)
{
    flits::ChiRspFlit rsp_flit;

    rsp_flit.set_qos(0xF);
    rsp_flit.set_tgtid(0x7FF);
    rsp_flit.set_srcid(0x400);
    rsp_flit.set_txnid(0xFFF);
    rsp_flit.set_opcode(0x1F);
    rsp_flit.set_resperr(0x3);
    rsp_flit.set_resp(0x7);
    rsp_flit.set_datapull(0x7);
    rsp_flit.set_cbusy(0x7);
    rsp_flit.set_dbid(0xFFF);
    rsp_flit.set_pcrdtype(0xF);
    rsp_flit.set_tagop(0x3);
    rsp_flit.set_tracetag(1);

    sc_dt::sc_bv<73> expected_raw("0x1FFFFFFFFFFFE007FFF");
    EXPECT_EQ(expected_raw, rsp_flit.get_raw());
}

TEST(ChiRspFlitTests, Test_set_raw_with_all_getters)
{
    flits::ChiRspFlit rsp_flit;

    sc_dt::sc_bv<73> raw_data("0x1FFFFFFFFFFFE007FFF");
    rsp_flit.set_raw(raw_data);

    EXPECT_EQ(0xF, rsp_flit.get_qos());
    EXPECT_EQ(0x7FF, rsp_flit.get_tgtid());
    EXPECT_EQ(0x400, rsp_flit.get_srcid());
    EXPECT_EQ(0xFFF, rsp_flit.get_txnid());
    EXPECT_EQ(0x1F, rsp_flit.get_opcode());
    EXPECT_EQ(0x3, rsp_flit.get_resperr());
    EXPECT_EQ(0x7, rsp_flit.get_resp());
    EXPECT_EQ(0x7, rsp_flit.get_datapull());
    EXPECT_EQ(0x7, rsp_flit.get_fwdstate());
    EXPECT_EQ(0x7, rsp_flit.get_cbusy());
    EXPECT_EQ(0xFFF, rsp_flit.get_dbid());
    EXPECT_EQ(0xFF, rsp_flit.get_taggroupid());
    EXPECT_EQ(0xFF, rsp_flit.get_stashgroupid());
    EXPECT_EQ(0xFF, rsp_flit.get_pgroupid());
    EXPECT_EQ(0xF, rsp_flit.get_pcrdtype());
    EXPECT_EQ(0x3, rsp_flit.get_tagop());
    EXPECT_EQ(1, rsp_flit.get_tracetag());
}

TEST(ChiRspFlitTests, Test_constructor_with_bits)
{
    sc_dt::sc_bv<73> test_bits;
    test_bits.range(3, 0) = 0x5;
    test_bits.range(14, 4) = 0x2AA;

    flits::ChiRspFlit rsp_flit(test_bits);

    EXPECT_EQ(0x5, rsp_flit.get_qos());
    EXPECT_EQ(0x2AA, rsp_flit.get_tgtid());
}

TEST(ChiRspFlitTests, Test_boundary_values)
{
    flits::ChiRspFlit rsp_flit;

    rsp_flit.set_qos(0xF);
    rsp_flit.set_tgtid(0x7FF);
    rsp_flit.set_srcid(0x7FF);
    rsp_flit.set_txnid(0xFFF);
    rsp_flit.set_opcode(0x1F);
    rsp_flit.set_resperr(0x3);
    rsp_flit.set_resp(0x7);
    rsp_flit.set_datapull(0x7);
    rsp_flit.set_cbusy(0x7);
    rsp_flit.set_dbid(0xFFF);
    rsp_flit.set_pcrdtype(0xF);
    rsp_flit.set_tagop(0x3);
    rsp_flit.set_tracetag(0x1);

    sc_dt::sc_bv<73> raw_data = rsp_flit.get_raw();
    EXPECT_NE(0, raw_data.to_uint64());

    EXPECT_EQ(0xF, rsp_flit.get_qos());
    EXPECT_EQ(0x7FF, rsp_flit.get_tgtid());
    EXPECT_EQ(0x7FF, rsp_flit.get_srcid());
    EXPECT_EQ(0xFFF, rsp_flit.get_txnid());
    EXPECT_EQ(0x1F, rsp_flit.get_opcode());
    EXPECT_EQ(0x3, rsp_flit.get_resperr());
    EXPECT_EQ(0x7, rsp_flit.get_resp());
    EXPECT_EQ(0x7, rsp_flit.get_datapull());
    EXPECT_EQ(0x7, rsp_flit.get_cbusy());
    EXPECT_EQ(0xFFF, rsp_flit.get_dbid());
    EXPECT_EQ(0xF, rsp_flit.get_pcrdtype());
    EXPECT_EQ(0x3, rsp_flit.get_tagop());
    EXPECT_EQ(0x1, rsp_flit.get_tracetag());
}

TEST(ChiRspFlitTests, Test_zero_initialization)
{
    flits::ChiRspFlit rsp_flit;

    EXPECT_EQ(0, rsp_flit.get_qos());
    EXPECT_EQ(0, rsp_flit.get_tgtid());
    EXPECT_EQ(0, rsp_flit.get_srcid());
    EXPECT_EQ(0, rsp_flit.get_txnid());
    EXPECT_EQ(0, rsp_flit.get_opcode());
    EXPECT_EQ(0, rsp_flit.get_resperr());
    EXPECT_EQ(0, rsp_flit.get_resp());
    EXPECT_EQ(0, rsp_flit.get_datapull());
    EXPECT_EQ(0, rsp_flit.get_fwdstate());
    EXPECT_EQ(0, rsp_flit.get_cbusy());
    EXPECT_EQ(0, rsp_flit.get_dbid());
    EXPECT_EQ(0, rsp_flit.get_taggroupid());
    EXPECT_EQ(0, rsp_flit.get_stashgroupid());
    EXPECT_EQ(0, rsp_flit.get_pgroupid());
    EXPECT_EQ(0, rsp_flit.get_pcrdtype());
    EXPECT_EQ(0, rsp_flit.get_tagop());
    EXPECT_EQ(0, rsp_flit.get_tracetag());

    sc_dt::sc_bv<73> expected_zero(0);
    EXPECT_EQ(expected_zero, rsp_flit.get_raw());
}
