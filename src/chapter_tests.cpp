#include <iostream>
#include "chapter_tests.hpp"

void BookTest::ChapterOne () {
    // Testing translation
	p = Point(-3, 4, 5);
	Matrix4f trans = translation(5, -3, 2);
	std::cout << trans * p << std::endl;
	p_output = Point(2, 1, 7);
	assert(trans * p == p_output);

	Matrix4f trans_inv = trans.inverse();
	std::cout << trans_inv * p << std::endl;
	p_output = Point(-8, 7, 3);
	assert(trans_inv * p == p_output);

	v = Vector(-3, 4, 5);
	std::cout << trans * v << std::endl;
	assert(v == trans_inv * v);

	// Testing scaling
	Matrix4f scal = scaling(2, 3, 4);
	p = Point(-4, 6, 8);
	p_output = Point(-8, 18, 32);
	std::cout << scal * p << std::endl;
	assert(scal * p == p_output);
}