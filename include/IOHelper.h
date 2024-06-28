#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <sstream>  
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
	* @param matrix		The target
	*
	* @return			bool
	*/
	bool matrix_input(std::string& filepath, Matrix& matrix)
	{
		std::ifstream inputfile(filepath);
		if (!inputfile.is_open())
		{
			std::cerr << "Failed to open file: " << filepath << std::endl;
			return false;
		}
		std::string eachrow;
		std::vector<double> row;
		std::vector<std::vector<double>> input_data;
		bool firstLine = true;
		while (std::getline(inputfile, eachrow))
		{
			std::istringstream iss(eachrow);
			double value;
			eachrow.clear();
			while (iss >> value)
			{
				eachrow.push_back(value);
				if (iss.peek() != EOF && iss.peek() != '\n' && iss.peek() != '\r')
				{
					iss.ignore();
				}
			}
			if (firstLine)
			{
				firstLine = false;
			}
			else if (eachrow.size() != input_data[0].size())
			{
				std::cerr << "Error: Inconsistent number of columns in the file." << std::endl;
				inputfile.close();
				return false;
			}
			input_data.push_back(row);
		}
		inputfile.close();
		Matrix temp = Matrix(input_data);
		matrix = temp;
		return true;
	}

	/**
	* @brief			Input the matrix from a file
	* @param filepath	The filepath
	*
	* @return			bool
	*/
	bool vector_input(std::string& filepath, Vector& vector)
	{
		std::ifstream inputfile(filepath);
		if (!inputfile.is_open())
		{
			std::cerr << "Failed to open file: " << filepath << std::endl;
			return false;
		}
		std::string eachrow;
		std::vector<double> input_data;
		std::getline(inputfile, eachrow);
		std::istringstream iss(eachrow);
		double value;
		eachrow.clear();
		while (iss >> value)
		{
			eachrow.push_back(value);
			if (iss.peek() != EOF && iss.peek() != '\n' && iss.peek() != '\r')
			{
				iss.ignore();
			}
		}
		inputfile.close();
		Vector temp = Vector(input_data);
		vector = temp;
		return true;
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
				std::cout << matrix[i][j];
				//std::cout << matrix[i][j] << (j != column - 1 ? ' ' : '\n');
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