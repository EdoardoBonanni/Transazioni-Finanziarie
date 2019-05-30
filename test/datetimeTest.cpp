
#include "gtest/gtest.h"
#include "../DateTime.h"

TEST(datetimeTest, ConstructorTest){
    DateTime d1(2, 3, 1990, 22, 12, 3, true);
    EXPECT_EQ(d1.getGiorno(), 2);
    EXPECT_EQ(d1.getMese(), 3);
    EXPECT_NE(d1.getAnno(), 2010);
    EXPECT_EQ(d1.getOra(), 22);
    EXPECT_EQ(d1.getMinuto(), 12);
    EXPECT_NE(d1.getSecondo(), 35);
    EXPECT_TRUE(d1.IsValid());
}

TEST(datetimeTest, equalAndValidTest){
    DateTime d1(2, 3, 1990, 22, 12, 3, true);
    EXPECT_TRUE(d1.IsValid());
    DateTime d2(2, 3, 1990, 22, 12, 3, false);
    EXPECT_TRUE(d2.IsValid());
    DateTime d3(29, 2, 1990, 22, 12, 3, true);
    EXPECT_TRUE(d3.IsValid());
    DateTime d4(29, 2, 1990, 22, 12, 3, false);
    EXPECT_FALSE(d4.IsValid());
    DateTime d5(29, 2, 1990, 25, 12, 3, true);
    EXPECT_FALSE(d5.IsValid());
    DateTime d6(29, 2, 1990, 22, 61, 3, true);
    EXPECT_FALSE(d6.IsValid());
    EXPECT_TRUE(d1 == d2);
    EXPECT_FALSE(d1 == d3);
    EXPECT_TRUE(d2 != d3);
    EXPECT_FALSE(d3 == d4);
    EXPECT_TRUE(d3 > d1);
    EXPECT_FALSE(d3 > d3);
}

TEST(datetimeTest, setTest){
    DateTime d1(2, 3, 1990, 22, 12, 3, true);
    d1.setGiorno(5, true);
    EXPECT_EQ(d1.getGiorno(), 5);
    EXPECT_TRUE(d1.IsValid());
    d1.setMese(13, true);
    EXPECT_NE(d1.getMese(), 13);
    EXPECT_TRUE(d1.IsValid());
    d1.setMese(2, true);
    d1.setGiorno(29, true);
    d1.setMinuto(60, true);
    EXPECT_TRUE(d1.IsValid());
    d1.setOra(25, true);
    EXPECT_NE(d1.getOra(), 25);
    EXPECT_TRUE(d1.IsValid());
}

TEST(datetimeTest, opAssignamentANDcopyConstructorTest){
    DateTime d1(2, 3, 1990, 22, 12, 3, true);
    DateTime d2;
    d2 = d1;
    EXPECT_TRUE(d1 == d2);
    DateTime d3(d2);
    EXPECT_TRUE(d1 == d3);
}