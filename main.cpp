#include "Matrix.h"
#include "Simplex.cpp"
#include "MPI_Simplex.cpp"
#include "IOHelper.h"
#include <chrono>

int main(int argc, char* argv[]) {
	IOHelper helper = IOHelper();
	double** lhs = new double* [3];
	for (int i = 0; i < 3; i++)
	{
		lhs[i] = new double[5];
	}
	lhs[0][0] = 0;
	lhs[0][1] = 5;
	lhs[0][2] = 1;
	lhs[0][3] = 0;
	lhs[0][4] = 0;
	lhs[1][0] = 6;
	lhs[1][1] = 2;
	lhs[1][2] = 0;
	lhs[1][3] = 1;
	lhs[1][4] = 0;
	lhs[2][0] = 1;
	lhs[2][1] = 1;
	lhs[2][2] = 0;
	lhs[2][3] = 0;
	lhs[2][4] = 1;
	Matrix A(lhs, 3, 5);

	double* rhs = new double[3];
	rhs[0] = 15;
	rhs[1] = 24;
	rhs[2] = 5;
	Vector b(rhs, 3);

	double* cost = new double[5];
	cost[0] = -2;
	cost[1] = -1;
	cost[2] = 0;
	cost[3] = 0;
	cost[4] = 0;
	Vector c(cost, 5);

	MPI_Simplex mpi_smp(A, b, c);

	auto start = std::chrono::system_clock::now();
	Vector mpi_solution = mpi_smp.MPI_solve(argc, argv);
	auto end = std::chrono::system_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	std::cout << "»¨·ÑÁË"
		<< double(duration.count()) * std::chrono::microseconds::period::num / std::chrono::microseconds::period::den
		<< "Ãë" << std::endl;

	helper.print(mpi_solution);

	return 0;
}
