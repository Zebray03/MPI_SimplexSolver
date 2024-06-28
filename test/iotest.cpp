#pragma once
#include <string>
#include <cassert>
#include "../include/IOHelper.h"
#include "../include/Matrix.h"

static void iotest()
{
	IOHelper ioHelper;
	std::string filepath = "./test1/data/A.txt";
	Matrix result;
	assert(ioHelper.matrix_input(filepath, result));
}