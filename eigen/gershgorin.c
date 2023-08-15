#include <iostream>
#include <fstream>
#include <vector>
#include <mkl_lapacke.h>



int main() {
    int n = 10;

    std::vector<double> A = {
        1, 11,  7,  9,  7, 11,  7,  9,  2, 11,
       11,  4, 10, 10,  6,  2,  9,  6, 10,  0,
        7, 10,  3,  5,  4,  4,  4,  4,  6, 10,
        9, 10,  5,  3,  8,  8,  3,  5,  1,  8,
        7,  6,  4,  8,  8, 10,  5,  6, 10,  0,
       11,  2,  4,  8, 10,  9,  4,  3,  5, 11,
        7,  9,  4,  3,  5,  4,  3, 10,  7,  2,
        9,  6,  4,  5,  6,  3, 10, 11,  1,  7,
        2, 10,  6,  1, 10,  5,  7,  1, 10,  5,
       11,  0, 10,  8,  0, 11,  2,  7,  5,  1
    };

    char jobz = 'N'; 
    char uplo = 'L'; 
    int lda = n;  
    std::vector<double> eigenvalues(n);
    int info;

    info = LAPACKE_dsyev(LAPACK_COL_MAJOR, jobz, uplo, n, A.data(), lda, eigenvalues.data());

    if (info == 0) {
        std::ofstream eigenvaluesFile("eigenvaluesA.txt");

        if (eigenvaluesFile.is_open()) {

            for (int i = 0; i < n; ++i) {
                eigenvaluesFile << eigenvalues[i] << std::endl;
            }
            eigenvaluesFile.close();
            std::cout << "Eigenvalues written to eigenvaluesA.txt" << std::endl;

            for (int i = 0; i < n; ++i) {
                double center = A[i * n + i];
                double radius = 0.0;
                for (int j = 0; j < n; ++j) {
                    if (j != i) {
                        radius += std::abs(A[i * n + j]);
                    }
                }

                double lowerBound = center - radius;
                double upperBound = center + radius;
                if (eigenvalues[i] < lowerBound || eigenvalues[i] > upperBound) {
                    std::cout << "Eigenvalue " << eigenvalues[i] << " is not within Gershgorin interval [" << lowerBound << ", " << upperBound << "]" << std::endl;
                }
            }
        } else {
            std::cerr << "Error: Unable to open eigenvaluesA.txt for writing." << std::endl;
        }
    } else {
        std::cerr << "Error: LAPACKE_dsyev returned info = " << info << std::endl;
    }

    return 0;
}