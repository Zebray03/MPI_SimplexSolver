#pragma once
#include "../../include/Matrix.h"
#include "../../include/IOHelper.h"
#include "../../src/MPI_SimplexSolver.cpp"
#include <cassert>
#include <chrono>

static void mpi_simplex_dir_search_test1(int argc, char* argv[])
{
	IOHelper ioHelper;
	std::string filepath;

	filepath = "./data/A.txt";
	Matrix A;
	assert(ioHelper.matrix_input(filepath, A));

	filepath = "./data/b.txt";
	Vector b;
	assert(ioHelper.matrix_input(filepath, b));

	filepath = "./data/c.txt";
	Vector c;
	assert(ioHelper.matrix_input(filepath, c));

	MPI_SimplexSolver mpi_smp(A, b, c);

	auto start = std::chrono::system_clock::now();
	Vector mpi_solution = mpi_smp.MPI_solve_parallel_trans(argc, argv);
	auto end = std::chrono::system_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	std::cout << "mpi_simplex_dir_search»¨·ÑÁË"
		<< double(duration.count()) * std::chrono::microseconds::period::num / std::chrono::microseconds::period::den
		<< "Ãë" << std::endl;

	ioHelper.print(mpi_solution);
}