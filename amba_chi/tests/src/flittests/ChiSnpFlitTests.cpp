#include <gtest/gtest.h>
#include <spdlog/spdlog.h>
#include <systemc>

#include <flits/ChiSnpFlit.h>


TEST(ChiSnpFlitTests, Test_qos)
{
    flits::ChiSnpFlit snp_flit;
    snp_flit.set_qos(8);
    EXPECT_EQ(8, snp_flit.get_qos());
}

TEST(ChiSnpFlitTests, Test_srcid)
{
    flits::ChiSnpFlit snp_flit;
    snp_flit.set_srcid(512);
    EXPECT_EQ(512, snp_flit.get_srcid());
}

TEST(ChiSnpFlitTests, Test_txnid)
{
    flits::ChiSnpFlit snp_flit;
    snp_flit.set_txnid(2048);
    EXPECT_EQ(2048, snp_flit.get_txnid());
}

TEST(ChiSnpFlitTests, Test_fwdnid)
{
    flits::ChiSnpFlit snp_flit;
    snp_flit.set_fwdnid(256);
    EXPECT_EQ(256, snp_flit.get_fwdnid());
}

TEST(ChiSnpFlitTests, Test_fwdtxnid)
{
    flits::ChiSnpFlit snp_flit;
    snp_flit.set_fwdtxnid(1024);
    EXPECT_EQ(1024, snp_flit.get_fwdtxnid());
}

TEST(ChiSnpFlitTests, Test_vmidext)
{
    flits::ChiSnpFlit snp_flit;
    snp_flit.set_vmidext(128);
    EXPECT_EQ(128, snp_flit.get_vmidext());
}

TEST(ChiSnpFlitTests, Test_stashlpid)
{
    flits::ChiSnpFlit snp_flit;
    snp_flit.set_stashlpid(16);
    EXPECT_EQ(16, snp_flit.get_stashlpid());
}

TEST(ChiSnpFlitTests, Test_stashlpidvalid)
{
    flits::ChiSnpFlit snp_flit;
    snp_flit.set_stashlpidvalid(1);
    EXPECT_EQ(1, snp_flit.get_stashlpidvalid());
}

TEST(ChiSnpFlitTests, Test_opcode)
{
    flits::ChiSnpFlit snp_flit;
    snp_flit.set_opcode(16);
    EXPECT_EQ(16, snp_flit.get_opcode());
}

TEST(ChiSnpFlitTests, Test_addr)
{
    flits::ChiSnpFlit snp_flit;
    sc_dt::sc_uint<49> test_addr = 0x123456789ABC;
    snp_flit.set_addr(test_addr);
    EXPECT_EQ(test_addr, snp_flit.get_addr());
}

TEST(ChiSnpFlitTests, Test_ns)
{
    flits::ChiSnpFlit snp_flit;
    snp_flit.set_ns(1);
    EXPECT_EQ(1, snp_flit.get_ns());
}

TEST(ChiSnpFlitTests, Test_donotgotosd)
{
    flits::ChiSnpFlit snp_flit;
    snp_flit.set_donotgotosd(1);
    EXPECT_EQ(1, snp_flit.get_donotgotosd());
}

TEST(ChiSnpFlitTests, Test_rettosrc)
{
    flits::ChiSnpFlit snp_flit;
    snp_flit.set_rettosrc(1);
    EXPECT_EQ(1, snp_flit.get_rettosrc());
}

TEST(ChiSnpFlitTests, Test_tracetag)
{
    flits::ChiSnpFlit snp_flit;
    snp_flit.set_tracetag(1);
    EXPECT_EQ(1, snp_flit.get_tracetag());
}

TEST(ChiSnpFlitTests, Test_all_setters_with_get_raw)
{
    flits::ChiSnpFlit snp_flit;

    snp_flit.set_qos(0xF);
    snp_flit.set_srcid(0x400);
    snp_flit.set_txnid(0xFFF);
    snp_flit.set_fwdnid(0x200);
    snp_flit.set_fwdtxnid(0x800);
    snp_flit.set_opcode(0x1F);
    snp_flit.set_addr(0x1FFFFFFFFFFFF);
    snp_flit.set_ns(1);
    snp_flit.set_donotgotosd(1);
    snp_flit.set_rettosrc(1);
    snp_flit.set_tracetag(1);

    sc_dt::sc_bv<108> expected_raw("0xFFFFFFFFFFFFFFE001007FFC00F");
    EXPECT_EQ(expected_raw, snp_flit.get_raw());
}

TEST(ChiSnpFlitTests, Test_set_raw_with_all_getters)
{
    flits::ChiSnpFlit snp_flit;

    sc_dt::sc_bv<108> test_raw("0xFFFFFFFFFFFFFFE001007FFC00F");
    snp_flit.set_raw(test_raw);

    // Verify all getters return the expected values
    EXPECT_EQ(0xF, snp_flit.get_qos());
    EXPECT_EQ(0x400, snp_flit.get_srcid());
    EXPECT_EQ(0xFFF, snp_flit.get_txnid());
    EXPECT_EQ(0x200, snp_flit.get_fwdnid());
    EXPECT_EQ(0x800, snp_flit.get_fwdtxnid());
    EXPECT_EQ(0x1F, snp_flit.get_opcode());
    EXPECT_EQ(0x1FFFFFFFFFFFF, snp_flit.get_addr());
    EXPECT_EQ(1, snp_flit.get_ns());
    EXPECT_EQ(1, snp_flit.get_donotgotosd());
    EXPECT_EQ(1, snp_flit.get_rettosrc());
    EXPECT_EQ(1, snp_flit.get_tracetag());
}

TEST(ChiSnpFlitTests, Test_constructor_with_bits)
{
    sc_dt::sc_bv<108> test_bits;
    test_bits.range(3, 0) = 0x5;
    test_bits.range(14, 4) = 0x2AA;

    flits::ChiSnpFlit snp_flit(test_bits);

    EXPECT_EQ(0x5, snp_flit.get_qos());
    EXPECT_EQ(0x2AA, snp_flit.get_srcid());
}

TEST(ChiSnpFlitTests, Test_boundary_values)
{
    flits::ChiSnpFlit snp_flit;

    snp_flit.set_qos(0xF);
    snp_flit.set_srcid(0x7FF);
    snp_flit.set_txnid(0xFFF);
    snp_flit.set_fwdnid(0x7FF);
    snp_flit.set_fwdtxnid(0xFFF);
    snp_flit.set_vmidext(0xFF);
    snp_flit.set_stashlpid(0x1F);
    snp_flit.set_stashlpidvalid(0x1);
    snp_flit.set_opcode(0x1F);
    snp_flit.set_addr(0x1FFFFFFFFFFFF);
    snp_flit.set_ns(0x1);
    snp_flit.set_donotgotosd(0x1);
    snp_flit.set_rettosrc(0x1);
    snp_flit.set_tracetag(0x1);

    EXPECT_EQ(0xF, snp_flit.get_qos());
    EXPECT_EQ(0x7FF, snp_flit.get_srcid());
    EXPECT_EQ(0xFFF, snp_flit.get_txnid());
    EXPECT_EQ(0x7FF, snp_flit.get_fwdnid());
    EXPECT_EQ(0xFFF, snp_flit.get_fwdtxnid());
    EXPECT_EQ(0xFF, snp_flit.get_vmidext());
    EXPECT_EQ(0x1F, snp_flit.get_stashlpid());
    EXPECT_EQ(0x1, snp_flit.get_stashlpidvalid());
    EXPECT_EQ(0x1F, snp_flit.get_opcode());
    EXPECT_EQ(0x1FFFFFFFFFFFF, snp_flit.get_addr());
    EXPECT_EQ(0x1, snp_flit.get_ns());
    EXPECT_EQ(0x1, snp_flit.get_donotgotosd());
    EXPECT_EQ(0x1, snp_flit.get_rettosrc());
    EXPECT_EQ(0x1, snp_flit.get_tracetag());
}

TEST(ChiSnpFlitTests, Test_zero_initialization)
{
    flits::ChiSnpFlit snp_flit;

    snp_flit.set_qos(0);
    snp_flit.set_srcid(0);
    snp_flit.set_txnid(0);
    snp_flit.set_fwdnid(0);
    snp_flit.set_fwdtxnid(0);
    snp_flit.set_vmidext(0);
    snp_flit.set_stashlpid(0);
    snp_flit.set_stashlpidvalid(0);
    snp_flit.set_opcode(0);
    snp_flit.set_addr(0);
    snp_flit.set_ns(0);
    snp_flit.set_donotgotosd(0);
    snp_flit.set_rettosrc(0);
    snp_flit.set_tracetag(0);

    EXPECT_EQ(0, snp_flit.get_qos());
    EXPECT_EQ(0, snp_flit.get_srcid());
    EXPECT_EQ(0, snp_flit.get_txnid());
    EXPECT_EQ(0, snp_flit.get_fwdnid());
    EXPECT_EQ(0, snp_flit.get_fwdtxnid());
    EXPECT_EQ(0, snp_flit.get_vmidext());
    EXPECT_EQ(0, snp_flit.get_stashlpid());
    EXPECT_EQ(0, snp_flit.get_stashlpidvalid());
    EXPECT_EQ(0, snp_flit.get_opcode());
    EXPECT_EQ(0, snp_flit.get_addr());
    EXPECT_EQ(0, snp_flit.get_ns());
    EXPECT_EQ(0, snp_flit.get_donotgotosd());
    EXPECT_EQ(0, snp_flit.get_rettosrc());
    EXPECT_EQ(0, snp_flit.get_tracetag());

    sc_dt::sc_bv<108> expected_zero(0);
    EXPECT_EQ(expected_zero, snp_flit.get_raw());
}
