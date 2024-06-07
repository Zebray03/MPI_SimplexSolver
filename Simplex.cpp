#pragma once
#include "Matrix.h"
#include <mpi.h>

class Simplex
{
public:
	Simplex(Matrix& A, Matrix& b, Matrix& c)
	{
		int* A_size = A.get_size();
		int* b_size = b.get_size();
		int* c_size = c.get_size();
		if (A_size[0] != b_size[0] || b_size[1] != 1 || A_size[1] != c_size[0])
		{
			// Exception
		}
		else
		{
			int base_num = A_size[0];
			int var_num = A_size[1];

			double** tab_data = new double* [base_num];
			for (int i = 0; i < base_num; i++)
			{
				tab_data[i] = new double[var_num + 1];
				for (int j = 0; j < var_num; j++)
				{
					tab_data[i][j] = A[i][j];
				}
				tab_data[i][var_num] = b[i][0];
			}
			Matrix temp1 = Matrix(base_num, var_num);
			tabular = temp1;

			double** cost_data = new double* [var_num];
			for (int j = 0; j < var_num; j++)
			{
				cost_data[j] = new double;
				cost_data[j][0] = c[j][0];
			}
			Matrix temp2 = Matrix(cost_data, var_num, 1);
			cost = temp2;
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
		bool is_bounded;
		
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
				double sum = 0;
				for (int i = 0; i < base_num; i++)
				{
					sum += cost[bases_index[i]][0] * tabular[i][j];
				}
				reduced_cost[j] = cost[j][0] - sum;
			}

			// Get the index of base_in variable
			int in_index = -1;
			int out_index = -1;
			double standard = 0;
			for (int j = 0; j < var_num; j++)
			{
				if (reduced_cost[j] < standard)
				{
					standard = reduced_cost[j];
					in_index = j;
				}
			}
			// Resolve the condition and renew the flag
			if (in_index == -1)
			{
				not_completed = false;
				is_bounded = true;
			}
			else
			{
				// Get the index of base_out variable
				standard = LLONG_MAX;
				for (int i = 0; i < base_num; i++)
				{
					if (tabular[i][in_index] > 0 && tabular[i][var_num] / tabular[i][in_index] < standard)
					{
						standard = tabular[i][var_num] / tabular[i][in_index];
						out_index = bases_index[i];
					}
				}
				// Resolve the condition and renew the flag
				if (out_index == -1)
				{
					not_completed = false;
					is_bounded = false;
				}
			}
		} while (not_completed);

		// Build up the solution
		if (is_bounded)
		{
			double** solution_data = new double* [var_num];
			for (int i = 0; i < var_num; i++)
			{
				solution_data[i] = new double[1];
				solution_data[i][0] = 0;
			}
			for (int j = 0; j < base_num; j++)
			{
				solution_data[bases_index[j]][0] = tabular[j][var_num];
			}
			return Matrix(solution_data, var_num, 1);
		}
		else
		{
			return Matrix();
		}
	}

	/**
	* @brief	Solve the simplex using the MPI interface
	*/
	Matrix MPI_solve()
	{

	}
private:
	Matrix tabular;
	Matrix cost;
};