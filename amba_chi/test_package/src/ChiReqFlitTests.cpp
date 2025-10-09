#include <gtest/gtest.h>
#include <spdlog/spdlog.h>
#include <systemc>

#include <flits/ChiReqFlit.h>


TEST(ChiReqFlitTests, Test_qos)
{
    flits::ChiReqFlit req_flit;
    req_flit.set_qos(4);
    EXPECT_EQ(4, req_flit.get_qos());
}

TEST(ChiReqFlitTests, Test_tgtid)
{
    flits::ChiReqFlit req_flit;
    req_flit.set_tgtid(1024);
    EXPECT_EQ(1024, req_flit.get_tgtid());
}

TEST(ChiReqFlitTests, Test_srcid)
{
    flits::ChiReqFlit req_flit;
    req_flit.set_srcid(512);
    EXPECT_EQ(512, req_flit.get_srcid());
}

TEST(ChiReqFlitTests, Test_txnid)
{
    flits::ChiReqFlit req_flit;
    req_flit.set_txnid(2048);
    EXPECT_EQ(2048, req_flit.get_txnid());
}

TEST(ChiReqFlitTests, Test_stashnid)
{
    flits::ChiReqFlit req_flit;
    req_flit.set_stashnid(256);
    EXPECT_EQ(256, req_flit.get_stashnid());
}

TEST(ChiReqFlitTests, Test_returnnid)
{
    flits::ChiReqFlit req_flit;
    req_flit.set_returnnid(128);
    EXPECT_EQ(128, req_flit.get_returnnid());
}

TEST(ChiReqFlitTests, Test_slcrephint)
{
    flits::ChiReqFlit req_flit;
    req_flit.set_slcrephint(64);
    EXPECT_EQ(64, req_flit.get_slcrephint());
}

TEST(ChiReqFlitTests, Test_deep)
{
    flits::ChiReqFlit req_flit;
    req_flit.set_deep(1);
    EXPECT_EQ(1, req_flit.get_deep());
}

TEST(ChiReqFlitTests, Test_endian)
{
    flits::ChiReqFlit req_flit;
    req_flit.set_endian(1);
    EXPECT_EQ(1, req_flit.get_endian());
}

TEST(ChiReqFlitTests, Test_stashnidvalid)
{
    flits::ChiReqFlit req_flit;
    req_flit.set_stashnidvalid(1);
    EXPECT_EQ(1, req_flit.get_stashnidvalid());
}

TEST(ChiReqFlitTests, Test_returntxnid)
{
    flits::ChiReqFlit req_flit;
    req_flit.set_returntxnid(1536);
    EXPECT_EQ(1536, req_flit.get_returntxnid());
}

TEST(ChiReqFlitTests, Test_stashlpidvalid)
{
    flits::ChiReqFlit req_flit;
    req_flit.set_stashlpidvalid(1);
    EXPECT_EQ(1, req_flit.get_stashlpidvalid());
}

TEST(ChiReqFlitTests, Test_stashlpid)
{
    flits::ChiReqFlit req_flit;
    req_flit.set_stashlpid(16);
    EXPECT_EQ(16, req_flit.get_stashlpid());
}

TEST(ChiReqFlitTests, Test_opcode)
{
    flits::ChiReqFlit req_flit;
    req_flit.set_opcode(32);
    EXPECT_EQ(32, req_flit.get_opcode());
}

TEST(ChiReqFlitTests, Test_size)
{
    flits::ChiReqFlit req_flit;
    req_flit.set_size(4);
    EXPECT_EQ(4, req_flit.get_size());
}

TEST(ChiReqFlitTests, Test_addr)
{
    flits::ChiReqFlit req_flit;
    sc_dt::sc_uint<52> test_addr = 0x123456789ABC;
    req_flit.set_addr(test_addr);
    EXPECT_EQ(test_addr, req_flit.get_addr());
}

TEST(ChiReqFlitTests, Test_ns)
{
    flits::ChiReqFlit req_flit;
    req_flit.set_ns(1);
    EXPECT_EQ(1, req_flit.get_ns());
}

TEST(ChiReqFlitTests, Test_likelyshared)
{
    flits::ChiReqFlit req_flit;
    req_flit.set_likelyshared(1);
    EXPECT_EQ(1, req_flit.get_likelyshared());
}

TEST(ChiReqFlitTests, Test_allowretry)
{
    flits::ChiReqFlit req_flit;
    req_flit.set_allowretry(1);
    EXPECT_EQ(1, req_flit.get_allowretry());
}

TEST(ChiReqFlitTests, Test_order)
{
    flits::ChiReqFlit req_flit;
    req_flit.set_order(2);
    EXPECT_EQ(2, req_flit.get_order());
}

TEST(ChiReqFlitTests, Test_pcrdtype)
{
    flits::ChiReqFlit req_flit;
    req_flit.set_pcrdtype(8);
    EXPECT_EQ(8, req_flit.get_pcrdtype());
}

TEST(ChiReqFlitTests, Test_memattr)
{
    flits::ChiReqFlit req_flit;
    req_flit.set_memattr(12);
    EXPECT_EQ(12, req_flit.get_memattr());
}

TEST(ChiReqFlitTests, Test_dodwt)
{
    flits::ChiReqFlit req_flit;
    req_flit.set_dodwt(1);
    EXPECT_EQ(1, req_flit.get_dodwt());
}

TEST(ChiReqFlitTests, Test_snpattr)
{
    flits::ChiReqFlit req_flit;
    req_flit.set_snpattr(1);
    EXPECT_EQ(1, req_flit.get_snpattr());
}

TEST(ChiReqFlitTests, Test_taggroupid)
{
    flits::ChiReqFlit req_flit;
    req_flit.set_taggroupid(200);
    EXPECT_EQ(200, req_flit.get_taggroupid());
}

TEST(ChiReqFlitTests, Test_stashgroupid)
{
    flits::ChiReqFlit req_flit;
    req_flit.set_stashgroupid(150);
    EXPECT_EQ(150, req_flit.get_stashgroupid());
}

TEST(ChiReqFlitTests, Test_pgroupid)
{
    flits::ChiReqFlit req_flit;
    req_flit.set_pgroupid(100);
    EXPECT_EQ(100, req_flit.get_pgroupid());
}

TEST(ChiReqFlitTests, Test_lpid)
{
    flits::ChiReqFlit req_flit;
    req_flit.set_lpid(20);
    EXPECT_EQ(20, req_flit.get_lpid());
}

TEST(ChiReqFlitTests, Test_snoopme)
{
    flits::ChiReqFlit req_flit;
    req_flit.set_snoopme(1);
    EXPECT_EQ(1, req_flit.get_snoopme());
}

TEST(ChiReqFlitTests, Test_excl)
{
    flits::ChiReqFlit req_flit;
    req_flit.set_excl(1);
    EXPECT_EQ(1, req_flit.get_excl());
}

TEST(ChiReqFlitTests, Test_expcompack)
{
    flits::ChiReqFlit req_flit;
    req_flit.set_expcompack(1);
    EXPECT_EQ(1, req_flit.get_expcompack());
}

TEST(ChiReqFlitTests, Test_tagop)
{
    flits::ChiReqFlit req_flit;
    req_flit.set_tagop(3);
    EXPECT_EQ(3, req_flit.get_tagop());
}

TEST(ChiReqFlitTests, Test_tracetag)
{
    flits::ChiReqFlit req_flit;
    req_flit.set_tracetag(1);
    EXPECT_EQ(1, req_flit.get_tracetag());
}

TEST(ChiReqFlitTests, Test_all_setters_with_get_raw)
{
    flits::ChiReqFlit req_flit;

    req_flit.set_qos(0xF);
    req_flit.set_tgtid(0x7FF);
    req_flit.set_srcid(0x400);
    req_flit.set_txnid(0xFFF);
    req_flit.set_returnnid(0x200);
    req_flit.set_deep(1);
    req_flit.set_returntxnid(0x800);
    req_flit.set_opcode(0x7F);
    req_flit.set_size(0x7);
    req_flit.set_addr(0xFFFFFFFFFFFFF);
    req_flit.set_ns(1);
    req_flit.set_likelyshared(1);
    req_flit.set_allowretry(1);
    req_flit.set_order(0x3);
    req_flit.set_pcrdtype(0xF);
    req_flit.set_memattr(0xF);
    req_flit.set_snpattr(1);
    req_flit.set_taggroupid(0xFF);
    req_flit.set_snoopme(1);
    req_flit.set_expcompack(1);
    req_flit.set_tagop(0x3);
    req_flit.set_tracetag(1);

    sc_dt::sc_bv<151> expected_raw("0x7FFFFFFFFFFFFFFFFFFFFFE002803FFE007FFF");

    EXPECT_EQ(expected_raw, req_flit.get_raw());
}

TEST(ChiReqFlitTests, Test_set_raw_with_all_getters)
{
    flits::ChiReqFlit req_flit;

    sc_dt::sc_bv<151> test_raw("0x7FFFFFFFFFFFFFFFFFFFFFE002803FFE007FFF");
    req_flit.set_raw(test_raw);

    EXPECT_EQ(0xF, req_flit.get_qos());
    EXPECT_EQ(0x7FF, req_flit.get_tgtid());
    EXPECT_EQ(0x400, req_flit.get_srcid());
    EXPECT_EQ(0xFFF, req_flit.get_txnid());
    EXPECT_EQ(0x200, req_flit.get_stashnid());
    EXPECT_EQ(0x200, req_flit.get_returnnid());
    EXPECT_EQ(0x0, req_flit.get_slcrephint());
    EXPECT_EQ(1, req_flit.get_deep());
    EXPECT_EQ(1, req_flit.get_endian());
    EXPECT_EQ(1, req_flit.get_stashnidvalid());
    EXPECT_EQ(0x800, req_flit.get_returntxnid());
    EXPECT_EQ(0, req_flit.get_stashlpidvalid());
    EXPECT_EQ(0, req_flit.get_stashlpid());
    EXPECT_EQ(0x7F, req_flit.get_opcode());
    EXPECT_EQ(0x7, req_flit.get_size());
    EXPECT_EQ(0xFFFFFFFFFFFFF, req_flit.get_addr());
    EXPECT_EQ(1, req_flit.get_ns());
    EXPECT_EQ(1, req_flit.get_likelyshared());
    EXPECT_EQ(1, req_flit.get_allowretry());
    EXPECT_EQ(0x3, req_flit.get_order());
    EXPECT_EQ(0xF, req_flit.get_pcrdtype());
    EXPECT_EQ(0xF, req_flit.get_memattr());
    EXPECT_EQ(1, req_flit.get_dodwt());
    EXPECT_EQ(1, req_flit.get_snpattr());
    EXPECT_EQ(0xFF, req_flit.get_taggroupid());
    EXPECT_EQ(0xFF, req_flit.get_stashgroupid());
    EXPECT_EQ(0xFF, req_flit.get_pgroupid());
    EXPECT_EQ(0x1F, req_flit.get_lpid());
    EXPECT_EQ(1, req_flit.get_snoopme());
    EXPECT_EQ(1, req_flit.get_excl());
    EXPECT_EQ(1, req_flit.get_expcompack());
    EXPECT_EQ(0x3, req_flit.get_tagop());
    EXPECT_EQ(1, req_flit.get_tracetag());
}
