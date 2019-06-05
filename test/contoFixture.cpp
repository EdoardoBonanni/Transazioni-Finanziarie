
#include "gtest/gtest.h"
#include "../Conto.h"

class contoSuite : public ::testing::Test {
protected:
    virtual void SetUp() override{
        me = std::make_shared<Utenza>("Edoardo", "Bonanni", 'm', 2, 3, 1998, false, "Via Calcinaia", 59 , "FI");
        other = std::make_shared<Utenza>("Pinco", "Pallino", 'm', 15, 7, 1990, false, "Via Calamandrei", 89 , "MI");
        myBankAccount = std::make_shared<Conto>(me, "c1", 0, 0);
        otherBankAccount = std::make_shared<Conto>(other, "c2", 0, 0);
    }


    std::shared_ptr<Utenza> me;
    std::shared_ptr<Utenza> other;
    std::shared_ptr<Conto> myBankAccount;
    std::shared_ptr<Conto> otherBankAccount;
};

TEST_F(contoSuite, someTransaction){
    bool fatalerror = false;
    typeTransaction type;
    std::string filenameMyFileTransaction = me->getNome() + me->getCognome() + myBankAccount->getNome() + "TransactionTest1.txt";
    std::string filenameOtherFileTransaction = other->getNome() + other->getCognome() + otherBankAccount->getNome() + "TransactionTest1.txt";
    float mySaldo = 0;
    float otherSaldo = 0;
    FileMgr meTransaction(filenameMyFileTransaction, true, fatalerror);
    FileMgr otherTransaction (filenameOtherFileTransaction, true, fatalerror);

    DateTime dt1(12, 3, 2018, 12, 2, 33, false);
    DateTime dt2(15, 3, 2018, 15, 24, 3, false);
    DateTime dt3(28, 3, 2018, 14, 12, 55, false);
    DateTime dt4(1, 4, 2018, 11, 18, 2, false);
    DateTime dt5(5, 4, 2018, 18, 18, 18, false);
    DateTime dt6(16, 4, 2018, 10, 1, 29, false);
    DateTime dt7(22, 4, 2018, 22, 45, 56, false);
    DateTime dt8(26, 4, 2018, 17, 22, 55, false);
    DateTime dt9(30, 4, 2018, 15, 3, 28, false);


    type = typeTransaction::Deposito;
    std::shared_ptr<Transazione> d1 = std::make_shared<Transazione>(type, 5000.50, myBankAccount, myBankAccount, &dt1, false);
    std::shared_ptr<Transazione> d2 = std::make_shared<Transazione>(type, 120.50, myBankAccount, myBankAccount, &dt2, false);
    std::shared_ptr<Transazione> d3 = std::make_shared<Transazione>(type, 400, otherBankAccount, otherBankAccount, &dt2, false);

    type = typeTransaction ::Prelievo;
    std::shared_ptr<Transazione> p1 = std::make_shared<Transazione>(type, 300, myBankAccount, myBankAccount,  &dt3, false);
    std::shared_ptr<Transazione> p2 = std::make_shared<Transazione>(type, 10000, myBankAccount, myBankAccount,  &dt4, false);
    std::shared_ptr<Transazione> p3 = std::make_shared<Transazione>(type, 100, otherBankAccount, otherBankAccount, &dt3, false);

    type = typeTransaction ::Bonifico;
    std::shared_ptr<Transazione> b1 = std::make_shared<Transazione>(type, 150, myBankAccount, otherBankAccount, &dt5, false);
    std::shared_ptr<Transazione> b2 = std::make_shared<Transazione>(type, 50000, myBankAccount, otherBankAccount, &dt6, false);
    std::shared_ptr<Transazione> b3 = std::make_shared<Transazione>(type, 200, otherBankAccount, myBankAccount, &dt7, false);


    //add depositi
    myBankAccount->addTransazione(d1, &meTransaction, fatalerror);
    mySaldo += d1->getInvio();
    EXPECT_EQ(myBankAccount->getSaldo(), mySaldo);

    myBankAccount->addTransazione(d2, &meTransaction, fatalerror);
    mySaldo += d2->getInvio();
    EXPECT_EQ(myBankAccount->getSaldo(), mySaldo);


    //add prelievi
    myBankAccount->addTransazione(p1, &meTransaction, fatalerror);
    mySaldo -= p1->getInvio();
    EXPECT_EQ(myBankAccount->getSaldo(), mySaldo);

    myBankAccount->addTransazione(p2, &meTransaction, fatalerror);
    EXPECT_EQ(myBankAccount->getSaldo(), mySaldo);


    //add another prelievo
    otherBankAccount->addTransazione(d3, &otherTransaction, fatalerror);
    otherSaldo += d3->getInvio();
    EXPECT_EQ(otherBankAccount->getSaldo(), otherSaldo);

    otherBankAccount->addTransazione(p3, &otherTransaction, fatalerror);
    otherSaldo -= p3->getInvio();
    EXPECT_EQ(otherBankAccount->getSaldo(), otherSaldo);


    //add bonifici
    otherBankAccount->addTransazione(b1, &otherTransaction, fatalerror);
    myBankAccount->addTransazione(b1, &meTransaction, fatalerror);
    mySaldo -= b1->getInvio();
    otherSaldo += b1->getInvio();
    EXPECT_EQ(myBankAccount->getSaldo(), mySaldo);
    EXPECT_EQ(otherBankAccount->getSaldo(), otherSaldo);

    otherBankAccount->addTransazione(b2, &otherTransaction, fatalerror);
    myBankAccount->addTransazione(b2, &meTransaction, fatalerror);
    EXPECT_EQ(myBankAccount->getSaldo(), mySaldo);
    EXPECT_EQ(otherBankAccount->getSaldo(), otherSaldo);

    myBankAccount->addTransazione(b3, &meTransaction, fatalerror);
    otherBankAccount->addTransazione(b3, &otherTransaction, fatalerror);
    otherSaldo -= b3->getInvio();
    mySaldo += b3->getInvio();
    EXPECT_EQ(myBankAccount->getSaldo(), mySaldo);
    EXPECT_EQ(otherBankAccount->getSaldo(), otherSaldo);
}


TEST_F(contoSuite, someInvestment) {
    bool fatalerror = false;
    std::string filenameMyFileTransaction = me->getNome() + me->getCognome() + myBankAccount->getNome() + "TransactionTest2.txt";
    std::string filenameOtherFileTransaction = other->getNome() + other->getCognome() + otherBankAccount->getNome() + "TransactionTest2.txt";
    std::string filenameMyFileInvestment = me->getNome() + me->getCognome() + myBankAccount->getNome() + "InvestmentTest2.txt";
    std::string filenameOtherFileInvestment = other->getNome() + other->getCognome() + otherBankAccount->getNome() + "InvestmentTest2.txt";
    float mySaldo = 0;
    float otherSaldo = 0;
    float myMoneyInvested=0;
    float otherMoneyInvested=0;

    FileMgr meTransaction(filenameMyFileTransaction, true, fatalerror);
    FileMgr otherTransaction(filenameOtherFileTransaction, true, fatalerror);
    FileMgr meInvestment(filenameMyFileInvestment, true, fatalerror);
    FileMgr otherInvestment(filenameOtherFileInvestment, true, fatalerror);

    DateTime dt1(12, 3, 2018, 12, 2, 33, false);
    DateTime dt2(15, 3, 2018, 15, 24, 3, false);
    DateTime dt3(28, 3, 2018, 14, 12, 55, false);
    DateTime dt4(1, 4, 2018, 11, 18, 2, false);

    std::shared_ptr<Transazione> d1 = std::make_shared<Transazione>(typeTransaction::Deposito, 5000.50, myBankAccount, myBankAccount, &dt1, false);
    std::shared_ptr<Transazione> d2 = std::make_shared<Transazione>(typeTransaction::Deposito, 400, otherBankAccount, otherBankAccount, &dt1, false);

    Investimento i1 ("Azioni ferrari", 330, myBankAccount, &dt2, false);
    Investimento i2 ("Azioni mercedes", 150, myBankAccount, &dt2, false);
    Investimento i3 ("Azioni audi", 150, otherBankAccount, &dt3, false);


    //Prova investimento
    myBankAccount->addInvestimento(&i1, &meInvestment, fatalerror);
    EXPECT_EQ(myBankAccount->getSaldo(), mySaldo);
    EXPECT_EQ(myBankAccount->getSoldiInvestiti(), myMoneyInvested);


    //Depositi
    myBankAccount->addTransazione(d1, &meTransaction, fatalerror);
    mySaldo += d1->getInvio();
    EXPECT_EQ(myBankAccount->getSaldo(), mySaldo);

    otherBankAccount->addTransazione(d2, &otherTransaction, fatalerror);
    otherSaldo += d2->getInvio();
    EXPECT_EQ(otherBankAccount->getSaldo(), otherSaldo);


    //insert investimenti
    myBankAccount->addInvestimento(&i1, &meInvestment, fatalerror);
    mySaldo -= i1.getInvestimento();
    myMoneyInvested += i1.getInvestimento();
    EXPECT_EQ(myBankAccount->getSaldo(), mySaldo);
    EXPECT_EQ(myBankAccount->getSoldiInvestiti(), myMoneyInvested);

    otherBankAccount->addInvestimento(&i2, &otherInvestment, fatalerror);
    otherSaldo -= i2.getInvestimento();
    otherMoneyInvested += i2.getInvestimento();
    EXPECT_EQ(otherBankAccount->getSaldo(), otherSaldo);
    EXPECT_EQ(otherBankAccount->getSoldiInvestiti(), otherMoneyInvested);

    myBankAccount->addInvestimento(&i3, &meInvestment, fatalerror);
    mySaldo -= i3.getInvestimento();
    myMoneyInvested += i3.getInvestimento();
    EXPECT_EQ(myBankAccount->getSaldo(), mySaldo);
    EXPECT_EQ(myBankAccount->getSoldiInvestiti(), myMoneyInvested);


    //remove investimenti
    myBankAccount->removeInvestimento(&i1, &dt4, &meInvestment, fatalerror);
    mySaldo += i1.getGuadagno();
    myMoneyInvested -= i1.getInvestimento();
    EXPECT_EQ(myBankAccount->getSaldo(), mySaldo);
    EXPECT_EQ(myBankAccount->getSoldiInvestiti(), myMoneyInvested);

    otherBankAccount->removeInvestimento(&i2, &dt4, &otherInvestment, fatalerror);
    otherSaldo += i2.getGuadagno();
    otherMoneyInvested -= i2.getInvestimento();
    EXPECT_EQ(otherBankAccount->getSaldo(), otherSaldo);
    EXPECT_EQ(otherBankAccount->getSoldiInvestiti(), otherMoneyInvested);
}

TEST_F(contoSuite, sameUserDifferentBankaccount) {
    bool fatalerror = false;
    std::shared_ptr<Conto> myBankAccount2 = std::make_shared<Conto>(me, "c2", 0, 0);

    std::string filenameMyFileTransaction1 =
            me->getNome() + me->getCognome() + myBankAccount->getNome() + "TransactionTest3.txt";
    std::string filenameMyFileTransaction2 =
            me->getNome() + me->getCognome() + myBankAccount2->getNome() + "TransactionTest3.txt";
    std::string filenameMyFileInvestment1 =
            me->getNome() + me->getCognome() + myBankAccount->getNome() + "InvestmentTest3.txt";
    std::string filenameMyFileInvestment2 =
            me->getNome() + me->getCognome() + myBankAccount2->getNome() + "InvestmentTest3.txt";
    float mySaldo = 0;
    float Saldo2 = 0;
    float myMoneyInvested = 0;
    float MoneyInvested2 = 0;

    FileMgr meTransaction1(filenameMyFileTransaction1, true, fatalerror);
    FileMgr meTransaction2(filenameMyFileTransaction2, true, fatalerror);
    FileMgr meInvestment1(filenameMyFileInvestment1, true, fatalerror);
    FileMgr meInvestment2(filenameMyFileInvestment2, true, fatalerror);

    DateTime dt1(12, 3, 2018, 12, 2, 33, false);
    DateTime dt2(15, 3, 2018, 15, 24, 3, false);
    DateTime dt3(28, 3, 2018, 14, 12, 55, false);
    DateTime dt4(1, 4, 2018, 11, 18, 2, false);
    DateTime dt5(5, 4, 2018, 18, 18, 18, false);
    DateTime dt6(16, 4, 2018, 10, 1, 29, false);

    std::shared_ptr<Transazione> d1 = std::make_shared<Transazione>(typeTransaction::Deposito, 5000.50, myBankAccount,
                                                                    myBankAccount, &dt1, false);
    std::shared_ptr<Transazione> d2 = std::make_shared<Transazione>(typeTransaction::Deposito, 400, myBankAccount2,
                                                                    myBankAccount2, &dt1, false);

    std::shared_ptr<Transazione> p1 = std::make_shared<Transazione>(typeTransaction::Prelievo, 800, myBankAccount, myBankAccount,  &dt2, false);
    std::shared_ptr<Transazione> p2 = std::make_shared<Transazione>(typeTransaction::Prelievo, 50, myBankAccount2, myBankAccount2, &dt2, false);

    std::shared_ptr<Transazione> b1 = std::make_shared<Transazione>(typeTransaction::Bonifico, 200, myBankAccount, myBankAccount2, &dt3, false);
    std::shared_ptr<Transazione> b2 = std::make_shared<Transazione>(typeTransaction::Bonifico, 200, myBankAccount2, myBankAccount, &dt4, false);

    Investimento i1("Azioni ferrari", 330, myBankAccount, &dt5, false);
    Investimento i2("Azioni mercedes", 150, myBankAccount2, &dt5, false);

    //Depositi
    myBankAccount->addTransazione(d1, &meTransaction1, fatalerror);
    mySaldo += d1->getInvio();
    EXPECT_EQ(myBankAccount->getSaldo(), mySaldo);

    myBankAccount2->addTransazione(d2, &meTransaction2, fatalerror);
    Saldo2 += d2->getInvio();
    EXPECT_EQ(myBankAccount2->getSaldo(), Saldo2);

    //Prelievi
    myBankAccount->addTransazione(p1, &meTransaction1, fatalerror);
    mySaldo -= p1->getInvio();
    EXPECT_EQ(myBankAccount->getSaldo(), mySaldo);

    myBankAccount2->addTransazione(p2, &meTransaction2, fatalerror);
    Saldo2 -= p2->getInvio();
    EXPECT_EQ(myBankAccount2->getSaldo(), Saldo2);

    //Bonifici
    myBankAccount2->addTransazione(b1, &meTransaction2, fatalerror);
    myBankAccount->addTransazione(b1, &meTransaction1, fatalerror);
    mySaldo -= b1->getInvio();
    Saldo2 += b1->getInvio();
    EXPECT_EQ(myBankAccount->getSaldo(), mySaldo);
    EXPECT_EQ(myBankAccount2->getSaldo(), Saldo2);

    myBankAccount->addTransazione(b2, &meTransaction1, fatalerror);
    myBankAccount2->addTransazione(b2, &meTransaction2, fatalerror);
    Saldo2 -= b2->getInvio();
    mySaldo += b2->getInvio();
    EXPECT_EQ(myBankAccount->getSaldo(), mySaldo);
    EXPECT_EQ(myBankAccount2->getSaldo(), Saldo2);

    //insert investimenti
    myBankAccount->addInvestimento(&i1, &meInvestment1, fatalerror);
    mySaldo -= i1.getInvestimento();
    myMoneyInvested += i1.getInvestimento();
    EXPECT_EQ(myBankAccount->getSaldo(), mySaldo);
    EXPECT_EQ(myBankAccount->getSoldiInvestiti(), myMoneyInvested);

    myBankAccount2->addInvestimento(&i2, &meInvestment2, fatalerror);
    Saldo2 -= i2.getInvestimento();
    MoneyInvested2 += i2.getInvestimento();
    EXPECT_EQ(myBankAccount2->getSaldo(), Saldo2);
    EXPECT_EQ(myBankAccount2->getSoldiInvestiti(), MoneyInvested2);

    //remove investimenti
    myBankAccount->removeInvestimento(&i1, &dt6, &meInvestment1, fatalerror);
    mySaldo += i1.getGuadagno();
    myMoneyInvested -= i1.getInvestimento();
    EXPECT_EQ(myBankAccount->getSaldo(), mySaldo);
    EXPECT_EQ(myBankAccount->getSoldiInvestiti(), myMoneyInvested);

    myBankAccount2->removeInvestimento(&i2, &dt6, &meInvestment2, fatalerror);
    Saldo2 += i2.getGuadagno();
    MoneyInvested2 -= i2.getInvestimento();
    EXPECT_EQ(myBankAccount2->getSaldo(), Saldo2);
    EXPECT_EQ(myBankAccount2->getSoldiInvestiti(), MoneyInvested2);

}