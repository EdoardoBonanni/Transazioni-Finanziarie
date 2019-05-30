
#include "gtest/gtest.h"
#include "../Transazione.h"

TEST(transactionTest, ConstructorAndEqualTest){
    typeTransaction type;
    Utenza* u1 = new Utenza("Edoardo", "Bonanni", 'm', 2, 3, 1998, false, "Via calcinaia", 59, "FI");
    Utenza* u2 = new Utenza("Poste", "Via Togliatti", 2, "FI");
    Conto* c1 = new Conto(u1, "c1", 0, 0);
    Conto* c2 = new Conto(u2, "c2", 0, 0);
    DateTime* d1 = new DateTime(2, 2, 2019, 22, 12, 3, true);
    DateTime* d2 = new DateTime(2, 2, 2019, 22, 12, 7, true);
    DateTime* d3 = new DateTime(2, 2, 2019, 22, 12, 18, true);

    type = typeTransaction::Deposito;
    Transazione t1(type, 100.50, c1, NULL, d1, false);
    Transazione t2(type, 500.50, c1, NULL, d2, false);
    Transazione t3(type, 133.50, c2, NULL, d1, false);

    type = typeTransaction::Prelievo;
    Transazione t4(type, 100.50, c1, NULL, d2, false);
    Transazione t5(type, 30, c1, NULL, d2, false);

    type = typeTransaction::Bonifico;
    Transazione t6(type, 30, c1, c2, d2, false);
    Transazione t7(type, 30, c2, c1, d3, false);

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

    delete d1;
    delete d2;
    delete d3;
    delete u1;
    delete u2;
}

TEST(transactionTest, opAssignamentANDcopyConstructorTest){
    Utenza* u1 = new Utenza("Edoardo", "Bonanni", 'm', 2, 3, 1998, false, "Via calcinaia", 59, "FI");
    Utenza* u2 = new Utenza("Poste", "Via Togliatti", 2, "FI");
    DateTime* d1 = new DateTime(2, 2, 2019, 22, 12, 3, true);
    Conto* c1 = new Conto(u1, "c1", 0, 0);
    Conto* c2 = new Conto(u2, "c2", 0, 0);

    Transazione t1(typeTransaction::Deposito, 100.50, c1, NULL, d1, false);
    Transazione t2(typeTransaction::Prelievo, 100.50, c2, NULL, d1, false);
    Transazione t3(typeTransaction::Bonifico, 30, c2, c1, d1, false);

    Transazione t4(t1);
    Transazione t5(t2);
    Transazione t6(t3);

    EXPECT_TRUE(t1==t4);
    EXPECT_TRUE(t2==t5);
    EXPECT_TRUE(t3==t6);
    t5=t6;
    EXPECT_TRUE(t3==t5);

    delete d1;
    delete u1;
    delete u2;
}