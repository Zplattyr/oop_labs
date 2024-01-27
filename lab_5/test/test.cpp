#include <gtest/gtest.h>
#include <list>
#include "stack.h"


TEST(AllocatorTest, TEST_01) {
    PoolAllocator<int> allocator;
    ASSERT_NO_THROW(allocator.allocate(1));
}

TEST(AllocatorTest, TEST_02) {
    PoolAllocator<int> allocator;
    int *tmp = allocator.allocate(1);
    ASSERT_NO_THROW(allocator.deallocate(tmp, 1));
}

TEST(AllocatorTest, TEST_03) {
    PoolAllocator<int> allocator;
    for (size_t i = 0; i < 30000; i++) {
        allocator.allocate();
    }
    ASSERT_ANY_THROW(allocator.allocate());
}

TEST(AllocatorTest, TEST_04) {
    PoolAllocator<int> allocator;
    int *tmp1 = allocator.allocate(1) + sizeof(int) * 2048;
    ASSERT_ANY_THROW(allocator.deallocate(tmp1, 1));
}

TEST(AllocatorTest, TEST_05) {
    PoolAllocator<int> allocator;
    int *tmp;
    for (size_t i = 0; i < 100; i++) {
        tmp = allocator.allocate(1);
    }
    ASSERT_NO_THROW(allocator.destroy(tmp));
}

TEST(STACK, Stack_Constructor) {
    ASSERT_NO_THROW(Stack<int> l;);
}

TEST(STACK, Stack_push_1) {
    Stack<int> l;
    l.push(1);
    ASSERT_TRUE(*l.cbegin() == 1);
}

TEST(STACK, Stack_push_2) {
    Stack<int> l;
    std::vector<int> m;
    bool flag = true;
    for (size_t i = 0; i < 10; i++)
    {
        m.push_back(i);
        l.push(i);
        if(m[i] != l.top()){flag = false; break;}
    }
    
    ASSERT_TRUE(flag);
}

TEST(STACK, Stack_get_size_1) {
    Stack<int> v;
    v.push(1);
    v.push(2);
    v.push(3);
    v.push(4);
    ASSERT_TRUE(v.get_size() == 4);
}

TEST(STACK, Stack_get_size_2) {
    Stack<double> v;
    ASSERT_TRUE(v.get_size() == 0);
}

TEST(STACK, Stack_get_capacity_1) {
    Stack<double> v;
    ASSERT_TRUE(v.get_capacity() == 0);
}

TEST(STACK, Stack_get_capacity_2) {
    Stack<double> v;
    v.push(123);
    ASSERT_TRUE(v.get_capacity() == 1);
}

TEST(STACK, Stack_get_capacity_3) {
    Stack<double> v;
    v.push(123);
    v.push(12);
    v.push(1);
    ASSERT_TRUE(v.get_capacity() == 4);
}

TEST(STACK, Stack_clear) {
    Stack<double> v;
    v.push(123);
    v.push(12);
    v.push(1);
    v.clear();
    ASSERT_TRUE(v.get_size() == 0);
}

// TEST(STACK, Stack_IndexOperator_1) {
//     Stack<float> v;
//     v.push(1);
//     v.push(3);
//     v.push(2);
//     v.push(0);
//     v.push(-9);
//     ASSERT_TRUE(v[3] == 0);
// }

// TEST(STACK, Stack_IndexOperator_2) {
//     Stack<float> v;
//     v.push(1);
//     ASSERT_TRUE(v[0] == 1);
// }

// TEST(STACK, Stack_IndexOperator_3) {
//     Stack<float> v;
//     for (size_t i = 0; i < 10; i++)
//     {
//         v.push(i);
//     }
//     ASSERT_TRUE(v[v.get_size() - 1] == 9);
// }

TEST(STACK, Stack_pop_1) {
    Stack<float> v;
    v.push(1);
    v.pop();
    ASSERT_TRUE(v.get_size() == 0);
}

TEST(STACK, Stack_pop_2) {
    Stack<float> v;
    for (size_t i = 0; i < 10; i++)
    {
        v.push(i);
    }
    for (size_t i = 0; i < 9; i++)
    {
        v.pop();
    }
    ASSERT_TRUE(v.get_size() == 1);
}

TEST(STACK, Stack_pop_3) {
    Stack<float> v;
    v.push(1);
    v.push(2);
    v.push(3);
    v.pop();
    ASSERT_TRUE((v.get_size() == 2) and (v.top() == 2));
}


TEST(STACK, Stack_iterator_1) {
    Stack<int> v;
    std::vector<int> m;
    v.push(123);
    v.push(12);
    v.push(1);
    m.push_back(123);
    m.push_back(12);
    m.push_back(1);
    size_t j = 0;
    bool flag = true;
    for (auto i = v.begin(); i != v.end(); ++i) {
        if (*i != m[j]) {
            flag = false;
        }
        j++;
    }
    ASSERT_TRUE(flag);
}

TEST(STACK, Stack_iterator_2) {
    Stack<int> v;
    std::vector<int> m;
    const int a = 1;
    v.push(a);
    m.push_back(a);
    size_t j = 0;
    bool flag = true;
    for (auto i = v.cbegin(); i != v.cend(); i++) {
        if (*i != m[j]) {
            flag = false;
        }
        j++;
    }
    ASSERT_TRUE(flag);
}

TEST(STACK, Stack_iterator_3) {
    Stack<char> v;
    v.push('a');
    v.push('b');
    v.push('c');
    auto iter = v.begin();
    iter++;
    iter++;
    ASSERT_TRUE((*iter == 'c'));
}

TEST(STACK, Stack_iterator_4) {
    Stack<char> v;
    v.push('a');
    v.push('b');
    v.push('c');
    auto iter = v.begin();
    ASSERT_TRUE((*iter == 'a'));
}

TEST(STACK, Stack_iterator_5) {
    Stack<int> v;
    v.push(1);
    v.push(2);
    v.push(3);
    auto iter1 = v.begin();
    auto iter2 = v.begin();
    ASSERT_TRUE(iter1 == iter2);
}

TEST(STACK, Stack_iterator_6) {
    Stack<int> v;
    v.push(1);
    v.push(2);
    v.push(3);
    auto iter1 = v.begin();
    auto iter2 = v.begin();
    iter2++;
    ASSERT_TRUE(iter1 != iter2);
}

TEST(STACK, Stack_iterator_7) {
    Stack<int> v;
    v.push(1);
    v.push(2);
    v.push(3);
    auto iter = v.begin();
    auto iter2 = v.begin();
    iter2++;
    iter2 = iter;
    ASSERT_TRUE(iter == iter2);
}

TEST(STACK, Stack_iterator_8) {
    Stack<int> v;
    v.push(1);
    v.push(2);
    v.push(3);
    auto iter = v.begin();
    auto iter2 = v.begin();
    iter2++;
    ASSERT_TRUE(iter != iter2);
}

TEST(STACK, Stack_iterator_9) {
    Stack<int> v;
    v.push(1);
    v.push(2);
    v.push(3);
    auto iter = v.end();
    auto iter2 = v.end();
    ASSERT_TRUE(iter == iter2);
}


TEST(STACK, Stack_iterator_10) {
    Stack<int> v;
    v.push(1);
    auto iter1 = v.cend();
    auto iter2 = v.cend();
    ASSERT_TRUE(iter1 == iter2);
}

TEST(STACK, Stack_iterator_11) {
    Stack<int> v;
    v.push(1);
    v.push(2);
    auto iter1 = v.begin();
    auto iter2 = v.end();
    iter2 = iter1;
    ASSERT_TRUE(iter1 == iter2);
}

TEST(STACK, Stack_iterator_12) {
    Stack<int> v;
    v.push(1);
    v.push(2);
    v.push(3);
    auto iter = v.begin();
    auto iterTMP = iter;
    auto iter2 = v.begin();
    iter2++;
    iter2 = std::move(iterTMP);
    ASSERT_TRUE(iter == iter2);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}