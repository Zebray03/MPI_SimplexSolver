#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Vector.h"

class IOHelper
{
public:
	IOHelper(){}

	~IOHelper(){}

	/**
	* @brief			Input the matrix from a file
	* @param filepath	The filepath
	*
	* @return			Matrix
	*/
	Matrix matrix_input(std::string& filepath)
	{
		std::ifstream inputfile(filepath);
		std::string eachrow;
		std::vector<std::vector<char>> input_vector;
		while (std::getline(inputfile, eachrow)) {
			std::vector<char> row;
			for (char& x : eachrow) {
				if (x != ' ')
				{
					row.push_back(x);
				}
			}
			input_vector.push_back(row);
		}
	}

	/**
	* @brief			Input the matrix from a file
	* @param filepath	The filepath
	*
	* @return			Vector
	*/
	Vector vector_input(std::string& filepath)
	{
		std::ifstream inputfile(filepath);
	}

	/**
	* @brief	Print the matrix
	*/
	void print(Matrix& matrix)
	{
		int row = matrix.get_size()[0];
		int column = matrix.get_size()[1];
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
			{
				std::cout << matrix[i][j] << (j != column - 1 ? ' ' : '\n') << std::endl;
			}
		}
	}

	/**
	* @brief	Print the vector
	*/
	void print(Vector& vector)
	{
		int row = vector.get_size();
		for (int i = 0; i < row; i++)
		{
			std::cout << vector[i] << std::endl;
		}
	}
};