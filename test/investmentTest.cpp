
#include "gtest/gtest.h"
#include "../Investimento.h"

TEST(investmentTest, ConstructorAndEqualTest){
    Utenza* u1 = new Utenza("Edoardo", "Bonanni", 'm', 2, 3, 1998, false, "Via calcinaia", 59, "FI");
    Utenza* u2 = new Utenza("Poste", "Via Togliatti", 2, "FI");
    DateTime* d1 = new DateTime(2, 2, 2019, 22, 12, 3, true);
    DateTime* d2 = new DateTime(2, 2, 2019, 22, 12, 3, true);
    Investimento i1("Azioni ferrari", 2000, u1, d1, false);
    EXPECT_EQ(i1.getInvestimento(), 2000);
    EXPECT_EQ(i1.getCausale(), "Azioni ferrari");
    EXPECT_EQ(i1.getUtenza()->getNome(), "Edoardo");
    EXPECT_EQ(i1.getDataora()->getMinuto(), 12);
    EXPECT_EQ(i1.getDataora()->getSecondo(), 5);
    Investimento i2("Azioni fiat", 1000, u1, d1, false);
    Investimento i3("Azioni fiat", 1000, u1, d2, false);
    Investimento i4("Azioni fiat", 1000, u2, d1, false);
    Investimento i5("Azioni ferrari", 2000, u1, d1, false);
    EXPECT_FALSE(i1==i2);
    EXPECT_FALSE(i2==i3);
    EXPECT_FALSE(i2==i4);
    EXPECT_TRUE(i1==i5);
    i5.setDataora(d2);
    EXPECT_FALSE(i1==i5);
    delete d1;
    delete d2;
    delete u1;
    delete u2;
}

TEST(investmentTest, opAssignamentANDcopyConstructorTest){
    Utenza* u1 = new Utenza("Edoardo", "Bonanni", 'm', 2, 3, 1998, false, "Via calcinaia", 59, "FI");
    Utenza* u2 = new Utenza("Poste", "Via Togliatti", 2, "FI");
    DateTime* d1 = new DateTime(2, 2, 2019, 22, 12, 3, true);
    Investimento i1("Azioni ferrari", 2000, u1, d1, false);
    Investimento i2("Azioni fiat", 1000, u2, d1, false);
    Investimento i3(i1);
    Investimento i4(i2);
    EXPECT_TRUE(i1==i3);
    EXPECT_TRUE(i2==i4);
    i3 = i4;
    EXPECT_TRUE(i2==i3);
    delete d1;
    delete u1;
    delete u2;
}

TEST(investmentTest, simulateInvestmentTest){
    Utenza* u1 = new Utenza("Edoardo", "Bonanni", 'm', 2, 3, 1998, false, "Via calcinaia", 59, "FI");
    DateTime* d1 = new DateTime(2, 2, 2019, 22, 12, 3, true);
    DateTime* d2 = new DateTime(2, 2, 2019, 22, 12, 5, true);
    Investimento i1("Azioni ferrari", 2000, u1, d1, false);
    EXPECT_EQ(i1.getGuadagno(), 0);
    ASSERT_FALSE(d2 > d1);
    i1.simulateInvestment(d2);
    EXPECT_EQ(i1.getGuadagno(), 0);
    i1.setCompleted(true);
    EXPECT_EQ(i1.isCompleted(), true);
    i1.simulateInvestment(d2);
    EXPECT_TRUE(i1.getGuadagno() != 0);
    delete d1;
    delete d2;
    delete u1;
}