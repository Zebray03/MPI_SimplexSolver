#pragma once
#include "MatrixException.h"
#include <vector>

class Matrix
{
public:
	Matrix() :row(0), column(0), data(nullptr) {}

	Matrix(int m_row, int m_column) :row(m_row), column(m_column)
	{
		data = new double* [row];
		for (int i = 0; i < row; i++)
		{
			data[i] = new double[column]();
		}
	}
	Matrix(double** data, int m_row, int m_column) :row(m_row), column(m_column)
	{
		this->data = new double* [row];
		for (int i = 0; i < row; i++)
		{
			this->data[i] = new double[column]();
			for (int j = 0; j < column; j++)
			{
				this->data[i][j] = data[i][j];
			}
		}
	}
	Matrix(std::vector<std::vector<char>> data)
	{
		//todo
	}

	~Matrix()
	{
		delete[] data;
	}

	int* get_size()
	{
		int size[] = { this->row,this->column };
		return size;
	}

	/**
	* @brief		Override the operator =
	*/
	Matrix& operator=(Matrix& para)
	{
		for (int i = 0; i < this->row; i++)
		{
			for (int j = 0; j < this->column; j++)
			{
				this->data[i][j] = para[i][j];
			}
		}
		return *this;
	}

	/**
	* @brief		Override the operator []
	*/
	double* operator[](int index)
	{
		return this->get_data()[index];
	}

	/**
	* @brief		Transpose the matrix
	*
	* @return		Matrix
	*/
	Matrix trans()
	{
		int row = this->get_column();
		int column = this->get_row();
		Matrix result = Matrix(row, column);
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
			{
				result[i][j] = *this[j][i];
			}
		}
		return result;
	}

	/**
	* @brief			Exchange the matrix's row i and j
	* @param index1		The index of the first row
	* @param index2		The index of the second row
	*
	* @return			void
	*/
	Matrix& primary_row_transform_1(int index1, int index2)
	{
		double* temp = new double[this->column];
		for (int i = 0; i < this->column; i++)
		{
			temp[i] = this->data[index2][i];
			this->data[index2][i] = this->data[index1][i];
			this->data[index1][i] = temp[i];
		}
		return *this;
	}

	/**
	* @brief			Multiply row i by a constant k
	* @param index		The index of the row
	* @param k			The constant
	*
	* @return			void
	*/
	void primary_row_transform_2(int index, double k)
	{
		for (int i = 0; i < this->column; i++)
		{
			this->data[index][i] *= k;
		}
	}

	/**
	* @brief				Add row i to row j (column) k times
	* @param augend_index	The index of the augend row
	* @param addend_index   The index of the addend row
	* @param k				The multiplier
	*
	* @return				void
	*/
	void primary_row_transform_3(int augend_index, int addend_index, double k)
	{
		for (int i = 0; i < this->column; i++)
		{
			this->data[augend_index][i] += (k * this->data[addend_index][i]);
		}
	}

	/**
	* @brief				Unitize row i
	* @param row_index		The index of the unitized row
	* @param column_index   The index of the unitizator in the row
	*
	* @return				void
	*/
	void row_unitization(int row_index, int column_index)
	{
		double divisor = 1 / data[row_index][column_index];
		this->primary_row_transform_2(row_index, divisor);
	}

	/**
	* @brief				Eliminate column j using row i (here Matrix[i,j] = 1)
	* @param row_index		The index of the eliminator row
	* @param column_index   The index of the eliminator in the row
	*
	* @return				void
	* @deprecated
	*/
	void column_elimination(int row_index, int column_index)
	{
		for (int i = 0; i < this->row; i++)
		{
			if (i == row_index)
			{
				continue;
			}
			else
			{
				this->primary_row_transform_3(i,row_index,data[i][column_index]);
			}
		}
	}

private:
	int row;
	int column;
	double** data;
	int get_row()
	{
		return this->row;
	}
	int get_column()
	{
		return this->column;
	}
	double** get_data()
	{
		return this->data;
	}
};