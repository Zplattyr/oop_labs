#include <gtest/gtest.h>
#include "box_capacity.h"
#include <iostream>

TEST(zero, test01)
{
    ASSERT_TRUE(box_capacity(32, 0, 16)==0);
}

TEST(zero, test02)
{
    ASSERT_TRUE(box_capacity(0, 64, 16)==0);
}

TEST(zero, test03)
{
    ASSERT_TRUE(box_capacity(32, 64, 0)==0);
}

TEST(zero, test04)
{
    ASSERT_TRUE(box_capacity(0, 64, 0)==0);
}

TEST(zero, test05)
{
    ASSERT_TRUE(box_capacity(0, 0, 0)==0);
}

TEST(negative, test01)
{
    ASSERT_TRUE(box_capacity(-10, 0, 0)==0);
}

TEST(negative, test02)
{
    ASSERT_TRUE(box_capacity(0, -10, 0)==0);
}

TEST(negative, test03)
{
    ASSERT_TRUE(box_capacity(0, 0, -10)==0);
}

TEST(negative, test04)
{
    ASSERT_TRUE(box_capacity(0, -10, -10)==0);
}

TEST(basic, test01)
{
    ASSERT_TRUE(box_capacity(32, 64, 16)==13824);
}

TEST(basic, test02)
{
    ASSERT_TRUE(box_capacity(50, 40, 30)==24420);
}

TEST(basic, test03)
{
    ASSERT_TRUE(box_capacity(1, 5, 100)==0);
}

TEST(doub, test04)
{
    ASSERT_TRUE(box_capacity(15.84, 5.361, 8.48)==264);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}