
#include "gtest/gtest.h"
#include "../Utenza.h"

TEST(UtenzaTest, ConstructorTest){
    Utenza u1("Edoardo", "Bonanni", 'm', 2, 3, 1998, false, "Via calcinaia", 59, "FI");
    EXPECT_EQ(u1.getNome(), "Edoardo");
    EXPECT_NE(u1.getCognome(), "BONANNI");
    EXPECT_EQ(u1.getDataNascita()->getGiorno(), 2);
    EXPECT_EQ(u1.getDataNascita()->getMese(), 3);
    EXPECT_NE(u1.getDataNascita()->getAnno(), 2010);
    EXPECT_NE(u1.getIndirizzo(), "VIA CALCINAIA");
}

TEST(UtenzaTest, equalTest){
    Utenza u1("Edoardo", "Bonanni", 'm', 2, 3, 1998, false, "Via calcinaia", 59, "FI");
    Utenza u2("EDOARDO", "BONANNI", 'm', 2, 3, 1998, false);
    Utenza u3("EDOARDO", "BONANNI", 'm', 2, 3, 1998, false);
    Utenza u4("EDOARDO", "BONANNI", 'f', 2, 3, 1998, true);
    EXPECT_FALSE(u1 == u2);
    EXPECT_TRUE(u2 == u3);
    EXPECT_TRUE(u3 != u4);
    Utenza u5("Poste", "Via Togliatti", 2, "FI");
    Utenza u6("Poste", "Via Togliatti", 2, "FI");
    EXPECT_FALSE(u1 == u5);
    EXPECT_FALSE(u5 != u6);
    Utenza u7("Edoardo", "Bonanni", true);
    EXPECT_TRUE(u1 != u7);

}

TEST(UtenzaTest, setTest){
    Utenza u1("Edoardo", "Bonanni", 'm', 2, 3, 1998, false, "Via calcinaia", 59, "FI");
    Utenza u2("Poste", "Via Togliatti", 2, "FI");
    Utenza u3("Edoardo", "Bonanni", true);
    Utenza u4("Poste", "", false);
    EXPECT_TRUE(u1 != u3);
    EXPECT_TRUE(u2 != u4);
    u3.setSesso('m');
    u3.setDataNascita(new Date(2, 3, 1998, false));
    EXPECT_EQ(u1.getDataNascita()->getGiorno(), u3.getDataNascita()->getGiorno());
    EXPECT_TRUE(u1 == u3);
    u4.setIndirizzo("Via Togliatti");
    u4.setNumeroCivico(2);
    u4.setProvincia("FI");
    EXPECT_TRUE(u2 == u4);

}

TEST(UtenzaTest, opAssignamentANDcopyConstructorTest){
    Utenza u1("Edoardo", "Bonanni", 'm', 2, 3, 1998, false, "Via calcinaia", 59, "FI");
    Utenza u2;
    u2 = u1;
    EXPECT_TRUE(u1 == u2);
    Utenza u3(u2);
    EXPECT_TRUE(u2 == u3);
    Utenza u4("Poste", "Via Togliatti", 2, "FI");
    u2 = u4;
    EXPECT_TRUE(u2 == u4);
    Utenza u5(u4);
    EXPECT_TRUE(u2 == u5);
}
