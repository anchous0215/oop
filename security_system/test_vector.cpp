#include "pch.h"
#include "Vector.h"
#include <iostream>
#include <vector>



TEST(constructors, operators) {
	Vector<int> v1;
	Vector <double> v2(5);
	double d = 2.3;
	Vector <double> v3(3, d);
	ASSERT_ANY_THROW(Vector <double> v2(-5));
	ASSERT_ANY_THROW(v3[6]);
	for (int i = 0; i < 3; i++) {
		ASSERT_EQ(d, v3[i]);
	}
}

TEST(iterators, methods) {
	Vector<int> v1(5, 6);
	auto iter = v1.begin();
	ASSERT_EQ(6, *iter);
	iter = iter + 2;
	v1[2] = 3;
	ASSERT_EQ(3, *iter);
	v1[1] = 2;
	--iter;
	ASSERT_EQ(2, *iter);
	ASSERT_EQ(2, *(iter--));
	ASSERT_EQ(6, *iter);
	iter = v1.cbegin();
	auto it2 = v1.begin();
	ASSERT_EQ(iter, it2);
	it2 = v1.end();
	ASSERT_NE(iter, it2);
	for (auto i : v1) {
		std::cout << i;
	}
	std::vector<int> v2(5, 6);
	for (auto i : v2) {
		std::cout << i;
	}
}

TEST(methods, 1) {
	Vector<int> v1(3, 1);
	v1[0] = 4;
	ASSERT_EQ(v1[0], 4);
	Vector <int> v3;
	v3 = v1;
	for (int i = 0; i < v1.size(); i++) {
		ASSERT_EQ(v1[i], v3[i]);
	}
	Vector <int> v2;
}

TEST(methods, 2) {
	Vector<char> v1(3, 'c');
	for (int i = 0; i < 3; i++) {
		ASSERT_EQ('c', v1.at(i));
	}
	ASSERT_EQ(10, v1.capacity());
	v1.clear();
	ASSERT_EQ(v1.size(), 0);
	ASSERT_EQ(true, v1.empty());
	Vector <int> v2(7, 1);
	v2[3] = 8;
	v2.erase(2);
	v1.push_back('4');
	auto t = v1.erase(0);
	ASSERT_EQ(8, v2[2]);
	ASSERT_EQ(6, v2.size());
	v2[5] = 4;
	v2.erase(2, 3);
	ASSERT_EQ(4, v2[2]);
	ASSERT_EQ(3, v2.size());
	v2.insert(3, 4);
	ASSERT_EQ(4, v2[3]);
	v2.pop_back();
	ASSERT_EQ(3, v2.size());
	v1.reserve(32);
	ASSERT_EQ(40, v1.capacity());
}
