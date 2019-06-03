
#include "gtest/gtest.h"
#include "../Transazione.h"
#include "memory"

TEST(transactionTest, ConstructorAndEqualTest){
    typeTransaction type;
    std::shared_ptr<Utenza> u1 = std::make_shared<Utenza>("Edoardo", "Bonanni", 'm', 2, 3, 1998, false, "Via calcinaia", 59, "FI");
    std::shared_ptr<Utenza> u2 = std::make_shared<Utenza>("Poste", "Via Togliatti", 2, "FI");
    std::shared_ptr<Conto> c1 = std::make_shared<Conto>(u1, "c1", 0, 0);
    std::shared_ptr<Conto> c2 = std::make_shared<Conto>(u2, "c2", 0, 0);
    std::shared_ptr<DateTime> dt1 = std::make_shared<DateTime>(2, 2, 2019, 22, 12, 3, true);
    std::shared_ptr<DateTime> dt2 = std::make_shared<DateTime>(2, 2, 2019, 22, 13, 7, true);
    std::shared_ptr<DateTime> dt3 = std::make_shared<DateTime>(2, 2, 2019, 22, 13, 18, true);

    type = typeTransaction::Deposito;
    Transazione t1(type, 100.50, c1, c1, dt1, false);
    Transazione t2(type, 500.50, c1, c1, dt2, false);
    Transazione t3(type, 133.50, c2, c1, dt1, false);

    type = typeTransaction::Prelievo;
    Transazione t4(type, 100.50, c1, c1, dt2, false);
    Transazione t5(type, 30, c1, c1, dt2, false);

    type = typeTransaction::Bonifico;
    Transazione t6(type, 30, c1, c2, dt2, false);
    Transazione t7(type, 30, c2, c1, dt3, false);

    EXPECT_EQ(t1.getInvio(), 100.50);
    EXPECT_EQ(t3.getDataora()->getMinuto(), 12);
    EXPECT_NE(t5.getDataora()->getMinuto(), 12);

    EXPECT_EQ(t6.getMittente()->getUtenza()->getNome(), "Edoardo");
    EXPECT_EQ(t6.getMittente()->getNome(), "c1");
    EXPECT_EQ(t6.getRicevitore()->getUtenza()->getNome(), "Poste");
    EXPECT_EQ(t6.getRicevitore()->getNome(), "c2");
    EXPECT_NE(t7.getMittente()->getUtenza()->getNome(), "Edoardo");
    EXPECT_NE(t7.getRicevitore()->getUtenza()->getNome(), "Poste");

    EXPECT_FALSE(t1==t2);
    EXPECT_FALSE(t1==t4);
    EXPECT_FALSE(t6==t7);
}

TEST(transactionTest, opAssignamentANDcopyConstructorTest){
    std::shared_ptr<Utenza> u1 = std::make_shared<Utenza>("Edoardo", "Bonanni", 'm', 2, 3, 1998, false, "Via calcinaia", 59, "FI");
    std::shared_ptr<Utenza> u2 = std::make_shared<Utenza>("Poste", "Via Togliatti", 2, "FI");
    std::shared_ptr<Conto> c1 = std::make_shared<Conto>(u1, "c1", 0, 0);
    std::shared_ptr<Conto> c2 = std::make_shared<Conto>(u2, "c2", 0, 0);
    std::shared_ptr<DateTime> dt1 = std::make_shared<DateTime>(2, 2, 2019, 22, 12, 3, true);

    Transazione t1(typeTransaction::Deposito, 100.50, c1, c1, dt1, false);
    Transazione t2(typeTransaction::Prelievo, 100.50, c2, c1, dt1, false);
    Transazione t3(typeTransaction::Bonifico, 30, c2, c1, dt1, false);

    Transazione t4(t1);
    Transazione t5(t2);
    Transazione t6(t3);

    EXPECT_TRUE(t1==t4);
    EXPECT_TRUE(t2==t5);
    EXPECT_TRUE(t3==t6);
    t5=t6;
    EXPECT_TRUE(t3==t5);
}