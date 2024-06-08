#pragma once
#include "Vector.h"
#include <mpi.h>

class MPI_Simplex
{
public:
	MPI_Simplex(Matrix& A, Vector& b, Vector& c)
	{
		int* A_size = A.get_size();
		int b_size = b.get_size();
		int c_size = c.get_size();
		if (A_size[0] != b_size || A_size[1] != c_size)
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
				tab_data[i][var_num] = b[i];
			}
			Matrix temp1 = Matrix(base_num, var_num);
			tabular = temp1;

			double* cost_data = new double[var_num];
			for (int j = 0; j < var_num; j++)
			{
				cost_data[j] = c[j];
			}
			Vector temp2 = Vector(cost_data, var_num);
			cost = temp2;
		}
	}

	~MPI_Simplex(){}

	/**
	* @brief	Solve the simplex using the MPI interface
	*/
	Matrix MPI_solve()
	{

	}
private:
	Matrix tabular;
	Vector cost;
};