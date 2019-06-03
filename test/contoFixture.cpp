
#include "gtest/gtest.h"
#include "../Conto.h"

class contoSuite : public ::testing::Test {
protected:
    virtual void setUp(){
        me = std::make_shared<Utenza>("Edoardo", "Bonanni", 'm', 2, 3, 1998, false, "Via Calcinaia", 59 , "FI");
        other = std::make_shared<Utenza>("Pinco", "Pallino", 'm', 15, 7, 1990, false, "Via Calamandrei", 89 , "MI");
        myBankAccount = std::make_shared<Conto>(me, "c1", 0, 0);
        otherBankAccount = std::make_shared<Conto>(other, "c2", 0, 0);
    }

    std::unique_ptr<FileMgr> meTransaction;
    std::unique_ptr<FileMgr> otherTransaction;
    std::unique_ptr<FileMgr> meInvestment;
    std::unique_ptr<FileMgr> otherInvestment;
    std::shared_ptr<Utenza> me;
    std::shared_ptr<Utenza> other;
    std::shared_ptr<Conto> myBankAccount;
    std::shared_ptr<Conto> otherBankAccount;
};

TEST_F(contoSuite, someTransaction){
    bool fatalerror = false;
    typeTransaction type;
    std::string filenameMyFileTransaction = me.operator*().getNome() + me.operator*().getCognome() + "Transaction.txt";

    /*
    std::string filenameOtherFileTransaction = other.operator->()->getNome() + other.operator->()->getCognome() +"Transaction.txt";
    float mySaldo = 0;
    float otherSaldo = 0;
    meTransaction = std::unique_ptr<FileMgr>(new FileMgr(filenameMyFileTransaction, true, fatalerror));
    ASSERT_EQ(fatalerror, true);
    otherTransaction = std::unique_ptr<FileMgr>(new FileMgr(filenameOtherFileTransaction, true, fatalerror));
    ASSERT_EQ(fatalerror, true);


    std::shared_ptr<DateTime> dt1 = std::make_shared<DateTime>(12, 3, 2018, 12, 2, 33, false);
    std::shared_ptr<DateTime> dt2 = std::make_shared<DateTime>(15, 3, 2018, 15, 24, 3, false);
    std::shared_ptr<DateTime> dt3 = std::make_shared<DateTime>(28, 3, 2018, 14, 12, 55, false);
    std::shared_ptr<DateTime> dt4 = std::make_shared<DateTime>(1, 4, 2018, 11, 18, 2, false);
    std::shared_ptr<DateTime> dt5 = std::make_shared<DateTime>(5, 4, 2018, 18, 18, 18, false);
    std::shared_ptr<DateTime> dt6 = std::make_shared<DateTime>(16, 4, 2018, 10, 1, 29, false);
    std::shared_ptr<DateTime> dt7 = std::make_shared<DateTime>(22, 4, 2018, 22, 45, 56, false);
    std::shared_ptr<DateTime> dt8 = std::make_shared<DateTime>(26, 4, 2018, 17, 22, 55, false);
    std::shared_ptr<DateTime> dt9 = std::make_shared<DateTime>(30, 4, 2018, 15, 3, 28, false);

    type = typeTransaction::Deposito;
    std::shared_ptr<Transazione> d1 = std::make_shared<Transazione>(type, 5000.50, myBankAccount, myBankAccount, dt1, false);
    std::shared_ptr<Transazione> d2 = std::make_shared<Transazione>(type, 120.50, myBankAccount, myBankAccount, dt2, false);
    std::shared_ptr<Transazione> d3 = std::make_shared<Transazione>(type, 400, otherBankAccount, myBankAccount, dt2, false);

    type = typeTransaction ::Prelievo;
    std::shared_ptr<Transazione> p1 = std::make_shared<Transazione>(type, 300, myBankAccount, myBankAccount,  dt3, false);
    std::shared_ptr<Transazione> p2 = std::make_shared<Transazione>(type, 10000, myBankAccount, myBankAccount,  dt4, false);
    std::shared_ptr<Transazione> p3 = std::make_shared<Transazione>(type, 100, otherBankAccount, myBankAccount, dt3, false);

    type = typeTransaction ::Bonifico;
    std::shared_ptr<Transazione> b1 = std::make_shared<Transazione>(type, 150, myBankAccount, otherBankAccount, dt5, false);
    std::shared_ptr<Transazione> b2 = std::make_shared<Transazione>(type, 20000, myBankAccount, otherBankAccount, dt6, false);
    std::shared_ptr<Transazione> b3 = std::make_shared<Transazione>(type, 200, otherBankAccount, myBankAccount, dt7, false);

    //add depositi
    myBankAccount->addTransazione(d1, meTransaction.get(), fatalerror);
    ASSERT_EQ(fatalerror, true);
    mySaldo += d1->getInvio();
    EXPECT_EQ(myBankAccount->getSaldo(), mySaldo);

    myBankAccount->addTransazione(d2, meTransaction.get(), fatalerror);
    ASSERT_EQ(fatalerror, true);
    mySaldo += d2->getInvio();
    EXPECT_EQ(myBankAccount->getSaldo(), mySaldo);

    //add prelievi
    myBankAccount->addTransazione(p1, meTransaction.get(), fatalerror);
    ASSERT_EQ(fatalerror, true);
    mySaldo -= - d3->getInvio();
    EXPECT_EQ(myBankAccount->getSaldo(), mySaldo);

    myBankAccount->addTransazione(p2, meTransaction.get(), fatalerror);
    EXPECT_EQ(myBankAccount->getSaldo(), mySaldo);

    //add another prelievo
    otherBankAccount->addTransazione(d3, otherTransaction.get(), fatalerror);
    ASSERT_EQ(fatalerror, true);
    otherSaldo += d3->getInvio();
    EXPECT_EQ(otherBankAccount->getSaldo(), otherSaldo);

    otherBankAccount->addTransazione(p3, otherTransaction.get(), fatalerror);
    ASSERT_EQ(fatalerror, true);
    otherSaldo -= p3->getInvio();
    EXPECT_EQ(otherBankAccount->getSaldo(), otherSaldo);

    //add bonifici
    myBankAccount->addTransazione(b1, meTransaction.get(), fatalerror);
    ASSERT_EQ(fatalerror, true);
    otherBankAccount->addTransazione(b1, otherTransaction.get(), fatalerror);
    ASSERT_EQ(fatalerror, true);
    mySaldo -= b1->getInvio();
    otherSaldo += b1->getInvio();
    EXPECT_EQ(myBankAccount->getSaldo(), mySaldo);
    EXPECT_EQ(otherBankAccount->getSaldo(), otherSaldo);

    myBankAccount->addTransazione(b2, meTransaction.get(), fatalerror);
    ASSERT_EQ(fatalerror, true);
    otherBankAccount->addTransazione(b2, otherTransaction.get(), fatalerror);
    ASSERT_EQ(fatalerror, true);
    EXPECT_EQ(myBankAccount->getSaldo(), mySaldo);
    EXPECT_EQ(otherBankAccount->getSaldo(), otherSaldo);

    myBankAccount->addTransazione(b3, meTransaction.get(), fatalerror);
    ASSERT_EQ(fatalerror, true);
    otherBankAccount->addTransazione(b3, otherTransaction.get(), fatalerror);
    ASSERT_EQ(fatalerror, true);
    otherSaldo -= b1->getInvio();
    mySaldo += b1->getInvio();
    EXPECT_EQ(myBankAccount->getSaldo(), mySaldo);
    EXPECT_EQ(otherBankAccount->getSaldo(), otherSaldo);*/
}

/*
TEST_F(contoSuite, someInvestment) {
    bool fatalerror = false;
    std::string filenameMyFileTransaction = me->getNome() + me->getCognome() + "Transaction.txt";
    std::string filenameOtherFileTransaction = other->getNome() + other->getCognome() +"Transaction.txt";
    std::string filenameMyFileInvestment = me->getNome() + me->getCognome() + "Investment.txt";
    std::string filenameOtherFileInvestment = other->getNome() + other->getCognome() +"Investment.txt";
    float mySaldo = 0;
    float otherSaldo = 0;
    float myMoneyInvested=0;
    float otherMoneyInvested=0;
    meTransaction = std::unique_ptr<FileMgr>(new FileMgr(filenameMyFileTransaction, true, fatalerror));
    ASSERT_EQ(fatalerror, true);
    otherTransaction = std::unique_ptr<FileMgr>(new FileMgr(filenameOtherFileTransaction, true, fatalerror));
    ASSERT_EQ(fatalerror, true);
    meInvestment = std::unique_ptr<FileMgr>(new FileMgr(filenameMyFileInvestment, true, fatalerror));
    ASSERT_EQ(fatalerror, true);
    otherInvestment = std::unique_ptr<FileMgr>(new FileMgr(filenameOtherFileInvestment, true, fatalerror));
    ASSERT_EQ(fatalerror, true);

    std::shared_ptr<DateTime> dt1 = std::make_shared<DateTime>(12, 3, 2018, 12, 2, 33, false);
    std::shared_ptr<DateTime> dt2 = std::make_shared<DateTime>(15, 3, 2018, 15, 24, 3, false);
    std::shared_ptr<DateTime> dt3 = std::make_shared<DateTime>(28, 3, 2018, 14, 12, 55, false);
    std::shared_ptr<DateTime> dt4 = std::make_shared<DateTime>(1, 4, 2018, 11, 18, 2, false);

    std::shared_ptr<Transazione> d1 = std::make_shared<Transazione>(typeTransaction::Deposito, 5000.50, myBankAccount, myBankAccount, dt1, false);
    std::shared_ptr<Transazione> d2 = std::make_shared<Transazione>(typeTransaction::Deposito, 400, otherBankAccount, myBankAccount, dt1, false);

    Investimento* i1 (new Investimento("Azioni ferrari", 330, myBankAccount, dt2, false));
    Investimento* i2 (new Investimento("Azioni mercedes", 150, myBankAccount, dt2, false));
    Investimento* i3 (new Investimento("Azioni audi", 150, otherBankAccount, dt3, false));

    //Prova investimento
    myBankAccount->addInvestimento(i1, meInvestment.get(), fatalerror);
    ASSERT_EQ(fatalerror, true);
    EXPECT_EQ(myBankAccount->getSaldo(), mySaldo);
    EXPECT_EQ(myBankAccount->getSoldiInvestiti(), myMoneyInvested);

    //Depositi
    myBankAccount->addTransazione(d1, meTransaction.get(), fatalerror);
    ASSERT_EQ(fatalerror, true);
    mySaldo += d1->getInvio();
    EXPECT_EQ(myBankAccount->getSaldo(), mySaldo);

    otherBankAccount->addTransazione(d2, otherTransaction.get(), fatalerror);
    ASSERT_EQ(fatalerror, true);
    otherSaldo += d2->getInvio();
    EXPECT_EQ(otherBankAccount->getSaldo(), mySaldo);

    //insert investimenti
    myBankAccount->addInvestimento(i1, meInvestment.get(), fatalerror);
    ASSERT_EQ(fatalerror, true);
    mySaldo -= i1->getInvestimento();
    myMoneyInvested += i1->getInvestimento();
    EXPECT_EQ(myBankAccount->getSaldo(), mySaldo);
    EXPECT_EQ(myBankAccount->getSoldiInvestiti(), myMoneyInvested);

    otherBankAccount->addInvestimento(i2, otherInvestment.get(), fatalerror);
    ASSERT_EQ(fatalerror, true);
    otherSaldo -= i2->getInvestimento();
    otherMoneyInvested += i2->getInvestimento();
    EXPECT_EQ(otherBankAccount->getSaldo(), otherSaldo);
    EXPECT_EQ(otherBankAccount->getSoldiInvestiti(), otherMoneyInvested);

    myBankAccount->addInvestimento(i3, meInvestment.get(), fatalerror);
    ASSERT_EQ(fatalerror, true);
    mySaldo -= i3->getInvestimento();
    myMoneyInvested += i3->getInvestimento();
    EXPECT_EQ(myBankAccount->getSaldo(), mySaldo);
    EXPECT_EQ(myBankAccount->getSoldiInvestiti(), myMoneyInvested);

    //remove investimenti
    myBankAccount->removeInvestimento(i1, dt4, meInvestment.get(), fatalerror);
    ASSERT_EQ(fatalerror, true);
    mySaldo += i1->getGuadagno();
    myMoneyInvested -= i1->getInvestimento();
    EXPECT_EQ(myBankAccount->getSaldo(), mySaldo);
    EXPECT_EQ(myBankAccount->getSoldiInvestiti(), myMoneyInvested);

    otherBankAccount->removeInvestimento(i2, dt4, otherInvestment.get(), fatalerror);
    ASSERT_EQ(fatalerror, true);
    otherSaldo += i2->getGuadagno();
    otherMoneyInvested -= i2->getInvestimento();
    EXPECT_EQ(otherBankAccount->getSaldo(), otherSaldo);
    EXPECT_EQ(otherBankAccount->getSoldiInvestiti(), otherMoneyInvested);
}*/
