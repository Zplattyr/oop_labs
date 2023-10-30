#include <gtest/gtest.h>
#include "money.h"

TEST(equal, test01) {
    Money num1("0"), num2("0");
    ASSERT_TRUE(num1 == num2);
}

TEST(equal, test02) {
    Money num1("00000000000000"), num2("0");
    ASSERT_TRUE(num1 == num2);
}

TEST(equal, test03) {
    Money num1("152"), num2("151");
    ASSERT_FALSE(num1 == num2);
}

TEST(equal, test04) {
    Money num1("311");
    ASSERT_TRUE(num1 == Money("311"));
}

TEST(equal, test05) {
    Money num1("888");
    ASSERT_FALSE(num1 == Money("886"));
}

TEST(equal, test06) {
    Money num1("00000000000000555"), num2("555");
    ASSERT_TRUE(num1 == num2);
}

TEST(not_equal, test01) {
    Money num1("10823"), num2("10823");
    ASSERT_FALSE(num1 != num2);
}

TEST(not_equal, test02) {
    Money num1("853"), num2("1000");
    ASSERT_TRUE(num1 != num2);
}

TEST(not_eq, test03) {
    Money num1("322");
    ASSERT_TRUE(num1 != Money());
}

TEST (greater, test01) {
    Money num1("1053"), num2("223");
    ASSERT_TRUE(num1 > num2);
}

TEST(greater, test02) {
    Money num1("153");
    ASSERT_FALSE(num1 > num1);
}

TEST(greater, test03) {
    Money num1("10105"), num2("10010");
    ASSERT_TRUE(num1 > num2);
}

TEST(greater, test04) {
    Money num1("105"), num2("223");
    ASSERT_FALSE(num1 > num2);
}


TEST(greater_or_eq, test01) {
    Money num1("1053"), num2("223");
    ASSERT_TRUE(num1 >= num2);
}

TEST(greater_or_eq, test02) {
    Money num1("1053");
    ASSERT_TRUE(num1 >= num1);
}


TEST(greater_or_eq, test03) {
    Money num1("0"), num2("1220");
    ASSERT_FALSE(num1 >= num2);
}

TEST(less, test01) {
    Money num1("1053"), num2("223");
    ASSERT_FALSE(num1 < num2);
}

TEST(less, test02) {
    Money num1("1453");
    ASSERT_FALSE(num1 < num1);
}

TEST(less, test03) {
    Money num1("10100"), num2("10010");
    ASSERT_FALSE(num1 < num2);
}

TEST(less, test04) {
    Money num1("10"), num2("1220");
    ASSERT_TRUE(num1 < num2);
}

TEST(less_or_eq, test01) {
    Money num1("34"), num2("15");
    ASSERT_FALSE(num1 <= num2);
}

TEST(less_or_eq, test02) {
    Money num1("145");
    ASSERT_TRUE(num1 <= num1);
}

TEST(less_or_eq, test03) {
    Money num1("22"), num2("12");
    ASSERT_FALSE(num1 <= num2);
}

TEST(less_or_eq, test04) {
    Money num1("10"), num2("1220");
    ASSERT_TRUE(num1 <= num2);
}

TEST(add, test01) {
    Money num1("0"), num2("1053");
    ASSERT_TRUE(num1 + num2 == Money("1053"));
}

TEST(add, test02) {
    Money num1("103"), num2("0");
    ASSERT_TRUE(num1 + num2 == Money("103"));
}

TEST(add, test03) {
    Money num1("43"), num2("1");
    ASSERT_TRUE(num1 + num2 == Money("44"));
}

TEST(add, test04) {
    Money num1("4035"), num2("10890");
    ASSERT_TRUE(num1 + num2 == Money("14925"));
}

TEST(add, test05) {
    Money num1("545"), num2("223");
    ASSERT_TRUE(num1 + num2 == Money("768"));
}

TEST(add, test06) {
    Money num1("4"), num2("1532222");
    ASSERT_TRUE(num1 + num2 == Money("1532226"));
}

TEST(add, test07) {
    Money num1("00000000000004"), num2("1532222");
    ASSERT_TRUE(num1 + num2 == Money("1532226"));
}

TEST(add_n_ravno, test01) {
    Money num1("0"), num2("435");
    num1 += num2;
    ASSERT_TRUE (num1 == num2);
}

TEST(add_n_ravno, test02) {
    Money num1("435"), num2("0");
    num1 += num2;
    ASSERT_TRUE (num1 == Money("435"));
}

TEST(add_n_ravno, test03) {
    Money num1("435"), num2("435");
    num1 += num2;
    ASSERT_TRUE (num1 == Money("870"));
}

TEST(add_n_ravno, test04) {
    Money num1("435"), num2("10890");
    num1 += num2;
    ASSERT_TRUE (num1 == Money("11325"));
}

TEST(sub, test01) {
    Money num1("105310403253"), num2("223");
    Money res(num1 - num2);
    ASSERT_TRUE(num1 - num2 == res);
}

TEST(sub, test02) {
    Money num1("43510101"), num2("43510100");
    Money res = num1 - num2;
    ASSERT_TRUE(num1 - num2 == Money("1"));
}

TEST(sub, test03) {
    Money num1("43510101"), num2("43510100");
    Money res = num1 - num2;
    ASSERT_TRUE(num1 - num2 == Money("0001"));
}

TEST(sub, test04) {
    Money num1("1053"), num2("0");
    Money res(num1 - num2);
    ASSERT_TRUE(num1 - num2 == num1);
}

TEST(sub, test05) {
    Money num1("223"), num2("1053");
    ASSERT_TRUE(num1 - num2 == Money("-830"));
}

TEST(sub_n_ravno, test01) {
    Money num1("0"), num2("435");
    ASSERT_TRUE(num1 - num2 == Money("-435"));
}

TEST(sub_n_ravno, test02) {
    Money num1("435"), num2("0");
    num1 -= num2;
    ASSERT_TRUE (num1 == Money("435"));
}

TEST(sub_n_ravno, test03) {
    Money num1("435"), num2("435");
    num1 -= num2;
    ASSERT_TRUE (num1 == Money("0"));
}

TEST(sub_n_ravno, test04) {
    Money num1("4035"), num2("1089");
    num1 -= num2;
    ASSERT_TRUE (num1 == Money("2946"));
}

TEST(sub_n_ravno, test05) {
    Money num1("43510101"), num2("43510100");
    num1 -= num2;
    ASSERT_TRUE(num1 == Money("1"));
}

TEST(sub_n_ravno, test06) {
    Money num1("435"), num2("43510100");
    num1 -= num2;
    ASSERT_TRUE(num1 == Money("-43509665"));
}

TEST(negative, test01) {
    Money num1("435"), num2("43510100");
    num1 -= num2;
    ASSERT_TRUE(num1 == Money("-43509665"));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}