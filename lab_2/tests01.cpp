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

TEST(neg_equal, test01) {
    Money num1("-34"), num2("-34");
    ASSERT_TRUE(num1 == num2);
}

TEST(neg_equal, test02) {
    Money num1("-343"), num2("-343");
    ASSERT_TRUE(num1 == num2);
}

TEST(neg_equal, test03) {
    Money num1("-00000000034"), num2("-34");
    ASSERT_TRUE(num1 == num2);
}

TEST(neg_equal, test04) {
    Money num1("-34"), num2("34");
    ASSERT_FALSE(num1 == num2);
}

TEST(neg_equal, test05) {
    Money num1("-344"), num2("-34");
    ASSERT_FALSE(num1 == num2);
}

TEST(neg_equal, test06) {
    Money num1("-34"), num2("-344");
    ASSERT_FALSE(num1 == num2);
}

TEST(neg_equal, test07) {
    Money num1("34"), num2("-34");
    ASSERT_FALSE(num1 == num2);
}

TEST(not_equal, test01) {
    Money num1("10823"), num2("10823");
    ASSERT_FALSE(num1 != num2);
}

TEST(not_equal, test02) {
    Money num1("853"), num2("1000");
    ASSERT_TRUE(num1 != num2);
}

TEST(neg_not_equal, test01) {
    Money num1("-322");
    ASSERT_TRUE(num1 != Money());
}

TEST(neg_not_equal, test02) {
    Money num1("-10823"), num2("-10823");
    ASSERT_FALSE(num1 != num2);
}

TEST(neg_not_equal, test03) {
    Money num1("-853"), num2("-1000");
    ASSERT_TRUE(num1 != num2);
}

TEST(neg_not_equal, test04) {
    Money num1("-53"), num2("53");
    ASSERT_TRUE(num1 != num2);
}

TEST(neg_not_equal, test05) {
    Money num1("53"), num2("-53");
    ASSERT_TRUE(num1 != num2);
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

TEST(neg_greater_or_eq, test01) {
    Money num1("-1053"), num2("-223");
    ASSERT_FALSE(num1 >= num2);
}

TEST(neg_greater_or_eq, test02) {
    Money num1("-1053");
    ASSERT_TRUE(num1 >= num1);
}

TEST(neg_greater_or_eq, test03) {
    Money num1("0"), num2("-1220");
    ASSERT_TRUE(num1 >= num2);
}

TEST(neg_greater_or_eq, test04) {
    Money num1("45"), num2("-45");
    ASSERT_TRUE(num1 >= num2);
}

TEST(neg_greater_or_eq, test05) {
    Money num1("-45"), num2("45");
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

TEST(neg_less_or_eq, test01) {
    Money num1("-34"), num2("-15");
    ASSERT_TRUE(num1 <= num2);
}

TEST(neg_less_or_eq, test02) {
    Money num1("-145");
    ASSERT_TRUE(num1 <= num1);
}

TEST(neg_less_or_eq, test03) {
    Money num1("-22"), num2("-12");
    ASSERT_TRUE(num1 <= num2);
}

TEST(neg_less_or_eq, test04) {
    Money num1("-10"), num2("-1220");
    ASSERT_FALSE(num1 <= num2);
}

TEST(neg_less_or_eq, test05) {
    Money num1("-10"), num2("10");
    ASSERT_TRUE(num1 <= num2);
}

TEST(neg_less_or_eq, test06) {
    Money num1("10"), num2("-10");
    ASSERT_FALSE(num1 <= num2);
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

TEST(sub, test06) {
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

TEST(neg_sub_n_ravno, test01) {
    Money num1("43510101"), num2("43510100");
    num1 -= num2;
    ASSERT_TRUE(num1 == Money("1"));
}

TEST(neg_sub_n_ravno, test02) {
    Money num1("-34"), num2("-48");
    num1 -= num2;
    ASSERT_TRUE(num1 == Money("14"));
}

TEST(neg_sub_n_ravno, test03) {
    Money num1("-4343"), num2("-34");
    num1 -= num2;
    ASSERT_TRUE(num1 == Money("-4309"));
}

TEST(neg_sub_n_ravno, test04) {
    Money num1("43510101"), num2("43510100");
    num1 -= num2;
    ASSERT_TRUE(num1 == Money("1"));
}

TEST(sub_n_ravno, test06) {
    Money num1("435"), num2("43510100");
    num1 -= num2;
    ASSERT_TRUE(num1 == Money("-43509665"));
}

TEST(sub_n_ravno, test07) {
    Money num1("435"), num2("43510100");
    num1 -= num2;
    ASSERT_TRUE(num1 == Money("-43509665"));
}

TEST(sub_n_ravno, test08) {
    Money num1("435"), num2("43510100");
    num1 -= num2;
    ASSERT_TRUE(num1 == Money("-43509665"));
}

TEST(negative_less, test01) {
    Money num1("-435"), num2("-43510100");
    ASSERT_FALSE(num1 < num2);
}

TEST(negative_less, test02) {
    Money num1("-55"), num2("-48");
    ASSERT_TRUE(num1 < num2);
}

TEST(negative_greater, test01) {
    Money num1("-55"), num2("-48");
    ASSERT_FALSE(num1 > num2);
}

TEST(negative_greater, test02) {
    Money num1("-5555"), num2("-48");
    ASSERT_FALSE(num1 > num2);
}

TEST(opposite_greater, test01) {
    Money num1("5555"), num2("-48");
    ASSERT_TRUE(num1 > num2);
}

TEST(opposite_greater, test02) {
    Money num1("55"), num2("-48");
    ASSERT_TRUE(num1 > num2);
}

TEST(opposite_less, test01) {
    Money num1("55"), num2("-48");
    ASSERT_FALSE(num1 < num2);
}

TEST(opposite_less, test02) {
    Money num1("55"), num2("-48555");
    ASSERT_FALSE(num1 < num2);
}

TEST(opposite_less, test03) {
    Money num1("0"), num2("-1");
    ASSERT_TRUE(num2 < num1);
}

TEST(neg_add, test01) {
    Money num1("0"), num2("-1053");
    ASSERT_TRUE(num1 + num2 == Money("-1053"));
}

TEST(neg_add, test02) {
    Money num1("-103"), num2("0");
    ASSERT_TRUE(num1 + num2 == Money("-103"));
}

TEST(neg_add, test03) {
    Money num1("-43"), num2("-1");
    ASSERT_TRUE(num1 + num2 == Money("-44"));
}

TEST(neg_add, test04) {
    Money num1("-4035"), num2("-10890");
    ASSERT_TRUE(num1 + num2 == Money("-14925"));
}

TEST(neg_add, test05) {
    Money num1("-545"), num2("-223");
    ASSERT_TRUE(num1 + num2 == Money("-768"));
}

TEST(neg_add, test06) {
    Money num1("-4"), num2("-1532222");
    ASSERT_TRUE(num1 + num2 == Money("-1532226"));
}

TEST(neg_add, test07) {
    Money num1("-00000000000004"), num2("-1532222");
    ASSERT_TRUE(num1 + num2 == Money("-1532226"));
}

TEST(neg_add, test08) {
    Money num1("-4"), num2("1532222");
    ASSERT_TRUE(num1 + num2 == Money("1532218"));
}

TEST(neg_add, test09) {
    Money num1("4"), num2("-1532222");
    ASSERT_TRUE(num1 + num2 == Money("-1532218"));
}

TEST(neg_add, test10) {
    Money num1("-4"), num2("3");
    ASSERT_TRUE(num1 + num2 == Money("-1"));
}

TEST(neg_add, test11) {
    Money num1("-4"), num2("100");
    ASSERT_TRUE(num1 + num2 == Money("96"));
}

TEST(neg_add, test12) {
    Money num1("-50"), num2("4");
    ASSERT_TRUE(num1 + num2 == Money("-46"));
}

TEST(neg_sub, test01) {
    Money num1("-105310403253"), num2("-223");
    Money res(num1 - num2);
    ASSERT_TRUE(num1 - num2 == res);
}

TEST(neg_sub, test02) {
    Money num1("-43510101"), num2("-43510100");
    Money res = num1 - num2;
    ASSERT_TRUE(num1 - num2 == Money("-1"));
}

TEST(neg_sub, test03) {
    Money num1("-43510101"), num2("-43510100");
    Money res = num1 - num2;
    ASSERT_TRUE(num1 - num2 == Money("-0001"));
}

TEST(neg_sub, test04) {
    Money num1("-1053"), num2("0");
    Money res(num1 - num2);
    ASSERT_TRUE(num1 - num2 == num1);
}

TEST(neg_sub, test05) {
    Money num1("-223"), num2("-1053");
    ASSERT_TRUE(num1 - num2 == Money("830"));
}

TEST(neg_sub, test06) {
    Money num1("0"), num2("-435");
    ASSERT_TRUE(num1 - num2 == Money("435"));
}

TEST(neg_sub, test07) {
    Money num1("11"), num2("105");
    ASSERT_TRUE(num1 - num2 == Money("-94"));
}

TEST(neg_sub, test08) {
    Money num1("-19"), num2("-145");
    ASSERT_TRUE(num1 - num2 == Money("126"));
}

TEST(neg_add_n_ravno, test01) {
    Money num1("0"), num2("-435");
    num1 += num2;
    ASSERT_TRUE (num1 == num2);
}

TEST(neg_add_n_ravno, test02) {
    Money num1("-435"), num2("0");
    num1 += num2;
    ASSERT_TRUE (num1 == Money("-435"));
}

TEST(neg_add_n_ravno, test03) {
    Money num1("-435"), num2("-435");
    num1 += num2;
    ASSERT_TRUE (num1 == Money("-870"));
}

TEST(neg_add_n_ravno, test04) {
    Money num1("435"), num2("-435");
    num1 += num2;
    ASSERT_TRUE (num1 == Money("0"));
}

TEST(neg_add_n_ravno, test05) {
    Money num1("-435"), num2("436");
    num1 += num2;
    ASSERT_TRUE (num1 == Money("1"));
}

TEST(neg_add_n_ravno, test06) {
    Money num1("-435"), num2("19458");
    num1 += num2;
    ASSERT_TRUE (num1 == Money("19023"));
}

TEST(throw_test, test01)
{
    EXPECT_THROW(Money num1("A35"), std::invalid_argument);
}

TEST(throw_test, test02)
{
    EXPECT_THROW(Money num1("-A35"), std::invalid_argument);
}

TEST(throw_test, test03)
{
    EXPECT_THROW(Money num1("4C"), std::invalid_argument);
}

TEST(throw_test, test04)
{
    EXPECT_THROW(Money num1(4,20), std::invalid_argument);
}

TEST(throw_test, test05)
{
    EXPECT_THROW(Money num1(std::initializer_list<unsigned char>({1,2,30})), std::invalid_argument);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}