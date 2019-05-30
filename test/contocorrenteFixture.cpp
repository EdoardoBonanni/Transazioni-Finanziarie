
#include "gtest/gtest.h"
#include "../ContoCorrente.h"

class contocorrenteSuite : public ::testing::Test {
protected:
    virtual void setUp(){
        Utenza* me = new Utenza("Edoardo", "Bonanni", 'm', 2, 3, 1998, false, "Via Calcinaia", 59 , "FI");
        Utenza* other = new Utenza("Pinco", "Pallino", 'm', 15, 7, 1990, false, "Via Calamandrei", 89 , "MI");
    }

    virtual void deleteList(){
        delete myBankAccount;
        delete otherBankAccount;
        delete me;
        delete other;
        delete meTransaction;
        delete otherTransaction;
        delete meInvestment;
        delete otherInvestment;
    }

    FileMgr* meTransaction;
    FileMgr* otherTransaction;
    FileMgr* meInvestment;
    FileMgr* otherInvestment;
    Utenza* me;
    Utenza* other;
    ContoCorrente* myBankAccount;
    ContoCorrente* otherBankAccount;
};

TEST_F(contocorrenteSuite, someTransaction){
    bool fatalerror = false;
    std::string filenameMyFileTransaction = me->getNome() + me->getCognome() + "Transaction.txt";
    std::string filenameOtherFileTransaction = other->getNome() + other->getCognome() +"Transaction.txt";
    float mySaldo = 0;
    float otherSaldo = 0;
    meTransaction = new FileMgr(filenameMyFileTransaction, true, fatalerror);
    ASSERT_EQ(fatalerror, true);
    otherTransaction = new FileMgr(filenameOtherFileTransaction, true, fatalerror);
    ASSERT_EQ(fatalerror, true);

    DateTime* dt1 = new DateTime(12, 3, 2018, 12, 2, 33, false);
    DateTime* dt2 = new DateTime(15, 3, 2018, 15, 24, 3, false);
    DateTime* dt3 = new DateTime(28, 3, 2018, 14, 12, 55, false);
    DateTime* dt4 = new DateTime(1, 4, 2018, 11, 18, 2, false);
    DateTime* dt5 = new DateTime(5, 4, 2018, 18, 18, 18, false);
    DateTime* dt6 = new DateTime(16, 4, 2018, 10, 1, 29, false);
    DateTime* dt7 = new DateTime(22, 4, 2018, 22, 45, 56, false);
    DateTime* dt8 = new DateTime(26, 4, 2018, 17, 22, 55, false);
    DateTime* dt9 = new DateTime(30, 4, 2018, 15, 3, 28, false);

    Transazione* d1= new Transazione("Deposito", 5000.50, me, dt1, false);
    Transazione* d2= new Transazione("Deposito", 120.50, me, dt2, false);
    Transazione* d3= new Transazione("Deposito", 400, other, dt2, false);

    Transazione* p1 = new Transazione("Prelievo", 300, me, dt3, false);
    Transazione* p2 = new Transazione("Prelievo", 10000, me, dt4, false);
    Transazione* p3 = new Transazione("Prelievo", 100, other, dt3, false);

    Transazione* b1 = new Transazione("Bonifico", 150, me, other, dt5, false);
    Transazione* b2 = new Transazione("Bonifico", 20000, me, other, dt6, false);
    Transazione* b3 = new Transazione("Bonifico", 200, other, me, dt7, false);

    //add depositi
    myBankAccount->addTransazione(d1, meTransaction, fatalerror);
    ASSERT_EQ(fatalerror, true);
    mySaldo += d1->getInvio();
    EXPECT_EQ(myBankAccount->getSaldo(), mySaldo);

    myBankAccount->addTransazione(d2, meTransaction, fatalerror);
    ASSERT_EQ(fatalerror, true);
    mySaldo += d2->getInvio();
    EXPECT_EQ(myBankAccount->getSaldo(), mySaldo);

    //add prelievi
    myBankAccount->addTransazione(p1, meTransaction, fatalerror);
    ASSERT_EQ(fatalerror, true);
    mySaldo -= - d3->getInvio();
    EXPECT_EQ(myBankAccount->getSaldo(), mySaldo);

    myBankAccount->addTransazione(p2, meTransaction, fatalerror);
    EXPECT_EQ(myBankAccount->getSaldo(), mySaldo);

    //add another prelievo
    otherBankAccount->addTransazione(d3, otherTransaction, fatalerror);
    ASSERT_EQ(fatalerror, true);
    otherSaldo += d3->getInvio();
    EXPECT_EQ(otherBankAccount->getSaldo(), otherSaldo);

    otherBankAccount->addTransazione(p3, otherTransaction, fatalerror);
    ASSERT_EQ(fatalerror, true);
    otherSaldo -= p3->getInvio();
    EXPECT_EQ(otherBankAccount->getSaldo(), otherSaldo);

    //add bonifici
    myBankAccount->addTransazione(b1, otherTransaction, fatalerror);
    ASSERT_EQ(fatalerror, true);
    otherBankAccount->addTransazione(b1, otherTransaction, fatalerror);
    ASSERT_EQ(fatalerror, true);
    mySaldo -= b1->getInvio();
    otherSaldo += b1->getInvio();
    EXPECT_EQ(myBankAccount->getSaldo(), mySaldo);
    EXPECT_EQ(otherBankAccount->getSaldo(), otherSaldo);

    myBankAccount->addTransazione(b2, otherTransaction, fatalerror);
    ASSERT_EQ(fatalerror, true);
    otherBankAccount->addTransazione(b2, otherTransaction, fatalerror);
    ASSERT_EQ(fatalerror, true);
    EXPECT_EQ(myBankAccount->getSaldo(), mySaldo);
    EXPECT_EQ(otherBankAccount->getSaldo(), otherSaldo);

    myBankAccount->addTransazione(b3, otherTransaction, fatalerror);
    ASSERT_EQ(fatalerror, true);
    otherBankAccount->addTransazione(b3, otherTransaction, fatalerror);
    ASSERT_EQ(fatalerror, true);
    otherSaldo -= b1->getInvio();
    mySaldo += b1->getInvio();
    EXPECT_EQ(myBankAccount->getSaldo(), mySaldo);
    EXPECT_EQ(otherBankAccount->getSaldo(), otherSaldo);

    delete dt1;
    delete dt2;
    delete dt3;
    delete dt4;
    delete dt5;
    delete dt6;
    delete dt7;
    delete dt8;
    delete dt9;
    delete d1;
    delete d2;
    delete d3;
    delete p1;
    delete p2;
    delete p3;
    delete b1;
    delete b2;
    delete b3;
}

TEST_F(contocorrenteSuite, someInvestment) {
    bool fatalerror = false;
    std::string filenameMyFileTransaction = me->getNome() + me->getCognome() + "Transaction.txt";
    std::string filenameOtherFileTransaction = other->getNome() + other->getCognome() +"Transaction.txt";
    std::string filenameMyFileInvestment = me->getNome() + me->getCognome() + "Investment.txt";
    std::string filenameOtherFileInvestment = other->getNome() + other->getCognome() +"Investment.txt";
    float mySaldo = 0;
    float otherSaldo = 0;
    float myMoneyInvested=0;
    float otherMoneyInvested=0;
    meTransaction = new FileMgr(filenameMyFileTransaction, true, fatalerror);
    ASSERT_EQ(fatalerror, true);
    otherTransaction = new FileMgr(filenameOtherFileTransaction, true, fatalerror);
    ASSERT_EQ(fatalerror, true);
    meInvestment = new FileMgr(filenameMyFileInvestment, true, fatalerror);
    ASSERT_EQ(fatalerror, true);
    otherInvestment = new FileMgr(filenameOtherFileInvestment, true, fatalerror);
    ASSERT_EQ(fatalerror, true);

    DateTime* dt1 = new DateTime(12, 3, 2018, 12, 2, 33, false);
    DateTime* dt2 = new DateTime(15, 3, 2018, 15, 24, 3, false);
    DateTime* dt3 = new DateTime(28, 3, 2018, 14, 12, 55, false);
    DateTime* dt4 = new DateTime(1, 4, 2018, 11, 18, 2, false);

    Transazione* d1= new Transazione("Deposito", 5000.50, me, dt1, false);
    Transazione* d2= new Transazione("Deposito", 400, other, dt1, false);

    Investimento* i1 = new Investimento("Azioni ferrari", 330, me, dt2, false);
    Investimento* i2 = new Investimento("Azioni mercedes", 150, me, dt2, false);
    Investimento* i3 = new Investimento("Azioni audi", 150, other, dt3, false);

    //Prova investimento
    myBankAccount->addInvestimento(i1, meTransaction, fatalerror);
    ASSERT_EQ(fatalerror, true);
    EXPECT_EQ(myBankAccount->getSaldo(), mySaldo);
    EXPECT_EQ(myBankAccount->getSoldiInvestiti(), myMoneyInvested);

    //Depositi
    myBankAccount->addTransazione(d1, meTransaction, fatalerror);
    ASSERT_EQ(fatalerror, true);
    mySaldo += d1->getInvio();
    EXPECT_EQ(myBankAccount->getSaldo(), mySaldo);

    otherBankAccount->addTransazione(d2, otherTransaction, fatalerror);
    ASSERT_EQ(fatalerror, true);
    otherSaldo += d2->getInvio();
    EXPECT_EQ(otherBankAccount->getSaldo(), mySaldo);

    //insert investimenti
    myBankAccount->addInvestimento(i1, meTransaction, fatalerror);
    ASSERT_EQ(fatalerror, true);
    mySaldo -= i1->getInvestimento();
    myMoneyInvested += i1->getInvestimento();
    EXPECT_EQ(myBankAccount->getSaldo(), mySaldo);
    EXPECT_EQ(myBankAccount->getSoldiInvestiti(), myMoneyInvested);

    otherBankAccount->addInvestimento(i2, otherTransaction, fatalerror);
    ASSERT_EQ(fatalerror, true);
    otherSaldo -= i2->getInvestimento();
    otherMoneyInvested += i2->getInvestimento();
    EXPECT_EQ(otherBankAccount->getSaldo(), otherSaldo);
    EXPECT_EQ(otherBankAccount->getSoldiInvestiti(), otherMoneyInvested);

    myBankAccount->addInvestimento(i3, meTransaction, fatalerror);
    ASSERT_EQ(fatalerror, true);
    mySaldo -= i3->getInvestimento();
    myMoneyInvested += i3->getInvestimento();
    EXPECT_EQ(myBankAccount->getSaldo(), mySaldo);
    EXPECT_EQ(myBankAccount->getSoldiInvestiti(), myMoneyInvested);

    //remove investimenti
    myBankAccount->removeInvestimento(i1, dt4, meTransaction, fatalerror);
    ASSERT_EQ(fatalerror, true);
    mySaldo += i1->getGuadagno();
    myMoneyInvested -= i1->getInvestimento();
    EXPECT_EQ(myBankAccount->getSaldo(), mySaldo);
    EXPECT_EQ(myBankAccount->getSoldiInvestiti(), myMoneyInvested);

    otherBankAccount->removeInvestimento(i2, dt4, otherTransaction, fatalerror);
    ASSERT_EQ(fatalerror, true);
    otherSaldo += i2->getGuadagno();
    otherMoneyInvested -= i2->getInvestimento();
    EXPECT_EQ(otherBankAccount->getSaldo(), otherSaldo);
    EXPECT_EQ(otherBankAccount->getSoldiInvestiti(), otherMoneyInvested);

    delete dt1;
    delete dt2;
    delete dt3;
    delete d1;
    delete d2;
    delete i1;
    delete i2;
    delete i3;
}
