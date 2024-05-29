#pragma once
#include "MatrixException.h"
class Matrix
{
public:
	Matrix() = delete;
	Matrix(const int m_row, const int m_column)
	{
		row = m_row;
		column = m_column;
		data = new double* [row];
		for (int i = 0; i < row; i++)
		{
			data[i] = new double[column]();
		}
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
	* @brief		Override the operator +
	*/
	Matrix operator+(Matrix m_mat)
	{
		if (m_mat.get_row() == this->get_row() && m_mat.get_column() == this->get_column())
		{
			int row = this->get_row();
			int column = this->get_column();
			Matrix result = Matrix(row, column);
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < column; j++)
				{
					result[i][j] = *this[i][j] + m_mat[i][j];
				}
			}
			return result;
		}
		else
		{
			throw new MatrixException;
		}
	}

	/**
	* @brief		Override the operator -
	*/
	Matrix operator-(Matrix m_mat)
	{
		if (m_mat.get_row() == this->get_row() && m_mat.get_column() == this->get_column())
		{
			int row = this->get_row();
			int column = this->get_column();
			Matrix result = Matrix(row, column);
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < column; j++)
				{
					result[i][j] = *this[i][j] - m_mat[i][j];
				}
			}
			return result;
		}
		else
		{
			throw new MatrixException;
		}
	}

	/**
	* @brief		Override the operator *
	*/
	Matrix operator*(Matrix m_mat)
	{
		if (this->get_column() == m_mat.get_column())
		{
			int row = this->get_row();
			int column = m_mat.get_column();
			int num = this->get_column();
			Matrix result = Matrix(row, column);
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < column; j++)
				{
					for (int k = 0; k < num; k++)
					{
						result[i][j] += *this[i][k] * m_mat[k][j];
					}
				}
			}
			return result;
		}
		else
		{
			throw new MatrixException;
		}
	}

	/**
	* @brief		Override the operator =
	*/
	void operator=(Matrix m_mat)
	{
		
	}

	/**
	* @brief		Override the operator ==
	*/
	bool operator==(Matrix m_mat)
	{
		
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
	* @return		*this
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
	* @return			*this
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
	* @return			*this
	*/
	Matrix& primary_row_transform_2(int index, double k)
	{
		for (int i = 0; i < this->column; i++)
		{
			this->data[index][i] *= k;
		}
		return *this;
	}

	/**
	* @brief				Add row i to row j (column) k times:
	* @param augend_index	The index of the augend row
	* @param addend_index   The index of the addend row
	* @param k				The multiplier
	*
	* @return				this
	*/
	Matrix& primary_row_transform_3(int augend_index, int addend_index, double k)
	{
		for (int i = 0; i < this->column; i++)
		{
			this->data[augend_index][i] += (k * this->data[addend_index][i]);
		}
		return *this;
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
	bool double_check()
	{
		if (this->row == 1 && this->column == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

/**
* @brief				Combine the piecewise matrices
* @param matrix_group	The group of piecewise matrices
*
* @return				The combination of the group
* @todo
*/
Matrix combine(Matrix** matrix_group)
{
	
}

