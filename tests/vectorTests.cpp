#include <gtest/gtest.h>
#include "Vector.h"

TEST(VectorTest, DefaultConstructor) {
    Vector<int> v;
    EXPECT_EQ(v.size(), 0);
    EXPECT_TRUE(v.empty());
}

TEST(VectorTest, PushBack) {
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[2], 3);
}

TEST(VectorTest, At) {
    Vector<int> v;
    v.push_back(10);
    EXPECT_EQ(v.at(0), 10);
    EXPECT_THROW(v.at(5), std::out_of_range);
}

TEST(VectorTest, FrontBack) {
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    EXPECT_EQ(v.front(), 1);
    EXPECT_EQ(v.back(), 3);
}

TEST(VectorTest, PopBack) {
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.pop_back();
    EXPECT_EQ(v.size(), 1);
    EXPECT_EQ(v.back(), 1);
}

TEST(VectorTest, CopyConstructor) {
    Vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    Vector<int> v2(v1);
    EXPECT_EQ(v2.size(), 2);
    EXPECT_EQ(v2[0], 1);
}

TEST(VectorTest, CopyAssignment) {
    Vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);

    Vector<int> v2;
    v2.push_back(9);
    v2 = v1;

    EXPECT_EQ(v2.size(), 2);
    EXPECT_EQ(v2[0], 1);
    EXPECT_EQ(v2[1], 2);
}

TEST(VectorTest, MoveConstructor) {
    Vector<int> v1;
    v1.push_back(5);
    Vector<int> v2(std::move(v1));
    EXPECT_EQ(v2[0], 5);
    EXPECT_EQ(v1.size(), 0);
}

TEST(VectorTest, EqualityOperator) {
    Vector<int> v1, v2;
    v1.push_back(1); v2.push_back(1);
    EXPECT_TRUE(v1 == v2);
    v2.push_back(2);
    EXPECT_TRUE(v1 != v2);
}

TEST(VectorTest, Reserve) {
    Vector<int> v;
    v.reserve(100);
    EXPECT_GE(v.capacity(), 100);
    EXPECT_EQ(v.size(), 0);
}

TEST(VectorTest, Resize) {
    Vector<int> v;
    v.resize(5);
    EXPECT_EQ(v.size(), 5);
}

TEST(VectorTest, Erase) {
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.erase(v.begin());
    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v[0], 2);
}

TEST(VectorTest, Insert) {
    Vector<int> v;
    v.push_back(1);
    v.push_back(3);
    v.insert(v.begin() + 1, 2);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v.size(), 3);
}
