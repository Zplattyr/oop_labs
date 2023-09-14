#include <gtest/gtest.h>
#include "closest_pair_tonum.h"

TEST(test_01, basic_test_set)
{
    ASSERT_TRUE(closest_pair_tonum(10)=="(5,4)");
}

TEST(test_02, basic_test_set)
{
    ASSERT_TRUE(closest_pair_tonum(50)=="(45,36)");
}

TEST(test_03, basic_test_set)
{
    ASSERT_TRUE(closest_pair_tonum(30)=="(29,20)");
}

TEST(test_04, basic_test_set)
{
    ASSERT_TRUE(closest_pair_tonum(1)=="Border is too low");
}

TEST(test_05, basic_test_set)
{
    ASSERT_TRUE(closest_pair_tonum(3)=="Don't exist");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}