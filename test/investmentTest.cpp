
#include "gtest/gtest.h"
#include "../Investimento.h"

TEST(investmentTest, ConstructorAndEqualTest){
    std::shared_ptr<Utenza> u1 = std::make_shared<Utenza>("Edoardo", "Bonanni", 'm', 2, 3, 1998, false, "Via calcinaia", 59, "FI");
    std::shared_ptr<Utenza> u2 = std::make_shared<Utenza>("Poste", "Via Togliatti", 2, "FI");
    std::shared_ptr<Conto> c1 = std::make_shared<Conto>(u1, "c1", 0, 0);
    std::shared_ptr<Conto> c2 = std::make_shared<Conto>(u2, "c2", 0, 0);
    DateTime dt1 (2, 4, 2019, 22, 12, 3, true);
    DateTime dt2 (2, 4, 2019, 22, 12, 7, true);

    Investimento i1("Azioni ferrari", 2000, c1, &dt1, false);
    EXPECT_EQ(i1.getInvestimento(), 2000);
    EXPECT_EQ(i1.getCausale(), "Azioni ferrari");
    EXPECT_EQ(i1.getConto()->getNome(), "c1");
    EXPECT_EQ(i1.getConto()->getUtenza()->getNome(), "Edoardo");
    EXPECT_EQ(i1.getDataora()->getMinuto(), 12);
    EXPECT_NE(i1.getDataora()->getSecondo(), 5);

    Investimento i2("Azioni fiat", 1000, c1, &dt1, false);
    Investimento i3("Azioni fiat", 1000, c1, &dt2, false);
    Investimento i4("Azioni fiat", 1000, c2, &dt1, false);
    Investimento i5("Azioni ferrari", 2000, c1, &dt1, false);

    EXPECT_FALSE(i1==i2);
    EXPECT_FALSE(i2==i3);
    EXPECT_FALSE(i2==i4);
    EXPECT_TRUE(i1==i5);
    i5.setDataora(&dt2);
    EXPECT_FALSE(i1==i5);
}

TEST(investmentTest, opAssignamentANDcopyConstructorTest){
    std::shared_ptr<Utenza> u1 = std::make_shared<Utenza>("Edoardo", "Bonanni", 'm', 2, 3, 1998, false, "Via calcinaia", 59, "FI");
    std::shared_ptr<Utenza> u2 = std::make_shared<Utenza>("Poste", "Via Togliatti", 2, "FI");
    std::shared_ptr<Conto> c1 = std::make_shared<Conto>(u1, "c1", 0, 0);
    std::shared_ptr<Conto> c2 = std::make_shared<Conto>(u2, "c2", 0, 0);
    DateTime dt1 (2, 4, 2019, 22, 12, 3, true);

    Investimento i1("Azioni ferrari", 2000, c1, &dt1, false);
    Investimento i2("Azioni fiat", 1000, c2, &dt1, false);

    Investimento i3(i1);
    Investimento i4(i2);

    EXPECT_TRUE(i1==i3);
    EXPECT_TRUE(i2==i4);
    i3 = i4;
    EXPECT_TRUE(i2==i3);
}

TEST(investmentTest, simulateInvestmentTest){
    std::shared_ptr<Utenza> u1 = std::make_shared<Utenza>("Edoardo", "Bonanni", 'm', 2, 3, 1998, false, "Via calcinaia", 59, "FI");
    std::shared_ptr<Conto> c1 = std::make_shared<Conto>(u1, "c1", 0, 0);
    DateTime dt1 (2, 4, 2019, 22, 12, 3, true);
    DateTime dt2 (2, 4, 2019, 22, 12, 7, true);

    Investimento i1("Azioni ferrari", 2000, c1, &dt1, false);
    EXPECT_EQ(i1.getGuadagno(), 0);
    EXPECT_TRUE(dt2.operator>(dt1));
    i1.simulateInvestment(&dt2);
    EXPECT_EQ(i1.getGuadagno(), 0);
    i1.setCompleted(true);
    EXPECT_EQ(i1.isCompleted(), true);
    i1.simulateInvestment(&dt2);
    EXPECT_TRUE(i1.getGuadagno() != 0);
}