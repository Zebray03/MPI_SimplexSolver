#pragma once
#include "Matrix.h"
#include <mpi.h>

class Simplex
{
public:
	Simplex(Matrix& A, Matrix& b)
	{
		int* A_size = A.get_size();
		int* b_size = b.get_size();
		if (A_size[0] != b_size[0] || b_size[1] != 1)
		{
			// Exception
		}
		else
		{
			int m_row = A_size[0];
			int m_column = A_size[1] + 1;
			Matrix temp = Matrix(m_row, m_column);
			tabular = temp;
		}
	}

	/**
	* @brief	Solve the simplex
	*/
	Matrix solve()
	{
		// Get the number of the bases and variables
		int base_num = this->tabular.get_size()[0];
		int var_num = this->tabular.get_size()[1] - 1;

		// Initial the indexes of the bases
		int* bases_index = new int[base_num];
		for (int i = 0; i < base_num; i++)
		{
			bases_index[i] = i;
		}

		// Allocate the reduced costs
		double* reduced_cost = new double[var_num];
		bool not_completed = true;
		
		// Execute the loop of solving
		do
		{
			// Renew the tabular
			for (int i = 0; i < base_num; i++)
			{
				tabular.row_unitization(i, bases_index[i]);
				for (int j = 0; j < base_num; j++)
				{
					if (i == j)
					{
						continue;
					}
					else
					{
						tabular.column_elimination(i, bases_index[i]);
					}
				}
			}

			// Calculate the reduced costs
			for (int j = 0; j < var_num; j++)
			{

			}

			// Get the index of base_in variable
			int in_index = -1;
			double standard = 0;
			for (int j = 0; j < var_num; j++)
			{

			}

			// Get the index of base_out variable
			int out_index = -1;
			for (int i = 0; i < base_num; i++)
			{

			}

			// Resolve the condition and renew the flag


		} while (not_completed);
	}

	/**
	* @brief	Solve the simplex using the MPI interface
	*/
	Matrix MPI_solve()
	{

	}
private:
	Matrix tabular;
};