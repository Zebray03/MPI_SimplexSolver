#pragma once
#include "Vector.h"
#include <mpi.h>

class MPI_SimplexSolver
{
public:
	MPI_SimplexSolver(Matrix& A, Vector& b, Vector& c)
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
			this->tabular = new Matrix(tab_data, base_num, var_num + 1);

			double* cost_data = new double[var_num];
			for (int j = 0; j < var_num; j++)
			{
				cost_data[j] = c[j];
			}
			this->cost = new Vector(cost_data, var_num);
		}
	}

	~MPI_SimplexSolver(){}

	/**
	* @brief	Solve the simplex using the MPI interface
	*/
	Vector MPI_solve(int argc, char* argv[])
	{
		// Get the number of the bases and variables
		int base_num = this->tabular->get_size()[0];
		int var_num = this->tabular->get_size()[1] - 1;
		// Initial the indexes of the bases
		int* bases_index = new int[base_num];
		for (int i = 0; i < base_num; i++)
		{
			if ((*tabular)[i][i] == 0)
			{
				for (int j = 0; j < base_num; j++)
				{
					if ((*tabular)[j][i] != 0)
					{
						tabular->primary_row_transform_3(i, j, 1);
					}
				}
			}
			bases_index[i] = i;
		}
		// Allocate the reduced costs
		double* reduced_cost = new double[var_num];
		bool not_completed = true;
		bool is_bounded;
		// MPI
		MPI_Init(&argc, &argv);
		int world_size;
		MPI_Comm_size(MPI_COMM_WORLD, &world_size);
		int world_rank;
		MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
		int start_row = (base_num * world_rank) / world_size;
		int end_row = (base_num * (world_rank + 1)) / world_size;
		MPI_Barrier(MPI_COMM_WORLD);
		// Execute the loop of solving
		do
		{
			// Renew the tabular
			if (world_rank == 0)
			{
				for (int i = 0; i < base_num; ++i)
				{
					tabular->row_unitization(i, bases_index[i]);
				}
				int unitization_done = 1;
				MPI_Bcast(&unitization_done, 1, MPI_INT, 0, MPI_COMM_WORLD);
			}
			else {
				int unitization_done;
				MPI_Bcast(&unitization_done, 1, MPI_INT, 0, MPI_COMM_WORLD);

				for (int i = world_rank; i < base_num; i += world_size)
				{
					for (int j = 0; j < base_num; ++j)
					{
						if (j != i) {
							tabular->primary_row_transform_3(j, i, -(*tabular)[j][bases_index[i]]);
						}
					}
				}
			}
			if (world_rank == 0)
			{
				// Calculate the reduced costs
				for (int j = 0; j < var_num; j++)
				{
					double sum = 0;
					for (int i = 0; i < base_num; i++)
					{
						sum += (*cost)[bases_index[i]] * (*tabular)[i][j];
					}
					reduced_cost[j] = (*cost)[j] - sum;
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
					standard = DBL_MAX;
					for (int i = 0; i < base_num; i++)
					{
						if ((*tabular)[i][in_index] > 0 && (*tabular)[i][var_num] / (*tabular)[i][in_index] < standard)
						{
							standard = (*tabular)[i][var_num] / (*tabular)[i][in_index];
							out_index = bases_index[i];
						}
					}
					// Resolve the condition and renew the flag
					if (out_index == -1)
					{
						not_completed = false;
						is_bounded = false;
					}
					else
					{
						for (int index = 0; index < base_num; index++)
						{
							if (bases_index[index] == out_index)
							{
								bases_index[index] = in_index;
								break;
							}
						}
					}
				}
			}
			MPI_Barrier(MPI_COMM_WORLD);
		} while (not_completed);
		MPI_Barrier(MPI_COMM_WORLD);
		MPI_Finalize();

		// Build up the solution
		if (is_bounded)
		{
			double* solution_data = new double[var_num];
			for (int i = 0; i < var_num; i++)
			{
				solution_data[i] = 0;
			}
			for (int j = 0; j < base_num; j++)
			{
				solution_data[bases_index[j]] = (*tabular)[j][var_num];
			}
			return Vector(solution_data, var_num);
		}
		else
		{
			return Vector();
		}
	}

private:
	Matrix* tabular;
	Vector* cost;
};