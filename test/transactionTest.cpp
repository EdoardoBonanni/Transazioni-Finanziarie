
#include "gtest/gtest.h"
#include "../Transazione.h"

TEST(transactionTest, ConstructorAndEqualTest){
    Utenza* u1 = new Utenza("Edoardo", "Bonanni", 'm', 2, 3, 1998, false, "Via calcinaia", 59, "FI");
    Utenza* u2 = new Utenza("Poste", "Via Togliatti", 2, "FI");
    DateTime* d1 = new DateTime(2, 2, 2019, 22, 12, 3, true);
    DateTime* d2 = new DateTime(2, 2, 2019, 22, 12, 7, true);
    DateTime* d3 = new DateTime(2, 2, 2019, 22, 12, 18, true);
    Transazione t1("Deposito", 100.50, u1, d1, false);
    Transazione t2("Deposito", 500.50, u1, d2, false);
    Transazione t3("Deposito", 133.50, u2, d1, false);
    Transazione t4("Prelievo", 100.50, u1, d2, false);
    Transazione t5("Prelievo", 30, u1, d2, false);
    Transazione t6("Bonifico", 30, u1, u2, d2, false);
    Transazione t7("Bonifico", 30, u2, u1, d3, false);
    EXPECT_EQ(t1.getInvio(), 100.50);
    EXPECT_EQ(t2.getOperazione(), "Deposito");
    EXPECT_EQ(t3.getDataora()->getMinuto(), 12);
    EXPECT_NE(t5.getDataora()->getMinuto(), 12);
    EXPECT_EQ(t6.getMittente()->getNome(), "Edoardo");
    EXPECT_EQ(t6.getRicevitore()->getNome(), "Poste");
    EXPECT_NE(t7.getMittente()->getNome(), "Edoardo");
    EXPECT_NE(t7.getRicevitore()->getNome(), "Poste");
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
    Transazione t1("Deposito", 100.50, u1, d1, false);
    Transazione t2("Prelievo", 100.50, u2, d1, false);
    Transazione t3("Bonifico", 30, u2, u1, d1, false);
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