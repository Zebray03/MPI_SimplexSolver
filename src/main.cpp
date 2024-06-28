#include "../test/iotest.cpp"
#include "../test/test1/mpi_simplex_par_trans_test1.cpp"
#include "../test/test1/mpi_simplex_dir_search_test1.cpp"
#include "../test/test2/mpi_simplex_par_trans_test2.cpp"
#include "../test/test2/mpi_simplex_dir_search_test2.cpp"
#include "../test/test3/mpi_simplex_par_trans_test3.cpp"
#include "../test/test3/mpi_simplex_dir_search_test3.cpp"

int main(int argc, char* argv[]) {
	iotest();
	mpi_simplex_par_trans_test1(argc, argv);
	mpi_simplex_dir_search_test1(argc, argv);

	return 0;
}
