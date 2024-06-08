#include "Matrix.h"
#include "Simplex.cpp"
#include "IOHelper.h"

int main(int argc, char* argv[]) {
	IOHelper helper = IOHelper();
	double** data = new double*[2];
	for (int i = 0; i < 2; i++) {
		data[i] = new double[2];
		for (int j = 0; j < 2; j++)
		{
			data[i][j] = 1;
		}
	}
	Matrix A(data, 2, 2);
	helper.print(A);
	return 0;
}
