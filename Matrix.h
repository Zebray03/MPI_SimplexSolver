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
	int get_size(int dim)
	{
		switch (dim)
		{
		case 1:
			return this->get_row();
		case 2:
			return this->get_column();
		default:
			cerr << "The input ONLY can be 1 or 2." << endl;
			break;
		}
	}
	Matrix operator+(Matrix m_mat)
	{
		try
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
				MatrixException matrix_err = MatrixException();
				throw(matrix_err);
			}
		}
		catch (const MatrixException&)
		{
			cerr << "The sizes of the two matrices do not coincide." << endl;
			exit(1);
		}
	}
	Matrix operator-(Matrix m_mat)
	{
		try
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
				MatrixException matrix_err = MatrixException();
				throw(matrix_err);
			}
		}
		catch (const MatrixException&)
		{
			cerr << "The sizes of the two matrices do not coincide." << endl;
			exit(1);
		}
	}
	Matrix operator*(Matrix m_mat)
	{
		try
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
				MatrixException matrix_err = MatrixException();
				throw(matrix_err);
			}
		}
		catch (const MatrixException&)
		{
			cerr << "The sizes of the two matrices do not coincide." << endl;
			exit(1);
		}
	}
	void operator=(Matrix m_mat)
	{
		
	}
	bool operator==(Matrix m_mat)
	{
		
	}
	double* operator[](int index)
	{
		return this->get_data()[index];
	}
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

