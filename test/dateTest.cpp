//
// Created by edoardo on 28/05/19.
//

#include "gtest/gtest.h"
#include "../Date.h"

TEST(dateTest, ConstructorTest){
    Date d1(2, 3, 1990, true);
    EXPECT_EQ(d1.getGiorno(), 2);
    EXPECT_EQ(d1.getMese(), 3);
    EXPECT_NE(d1.getAnno(), 2010);
    EXPECT_TRUE(d1.IsValid());
}

TEST(dateTest, equalAndValidTest){
    Date d1(2, 3, 1990, true);;
    EXPECT_TRUE(d1.IsValid());
    Date d2(2, 3, 1990, false);
    EXPECT_TRUE(d2.IsValid());
    Date d3(29, 2, 1990, true);
    EXPECT_TRUE(d3.IsValid());
    Date d4(29, 2, 1990, false);
    EXPECT_FALSE(d4.IsValid());
    EXPECT_TRUE(d1 == d2);
    EXPECT_FALSE(d1 == d3);
    EXPECT_TRUE(d2 != d3);
    EXPECT_FALSE(d3 == d4);
}

TEST(dateTest, setTest){
    Date d1(2, 3, 1990, true);
    EXPECT_TRUE(d1.IsValid());
    d1.setGiorno(5, true);
    EXPECT_EQ(d1.getGiorno(), 5);
    EXPECT_TRUE(d1.IsValid());
    d1.setMese(13, true);
    EXPECT_NE(d1.getMese(), 13);
    EXPECT_TRUE(d1.IsValid());
}

TEST(dateTest, opAssignamentANDcopyConstructorTest){
    Date d1(2, 3, 1990, true);
    Date d2;
    d2 = d1;
    EXPECT_TRUE(d1 == d2);
    Date d3(d2);
    EXPECT_TRUE(d1 == d3);
}


