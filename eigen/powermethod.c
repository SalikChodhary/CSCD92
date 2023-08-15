#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

const double tolerance = 1e-5;

int main() {
  double largestEigenvalue;
  std::ifstream eigenvaluesFile("eigenvaluesA.txt");

  if (eigenvaluesFile.is_open()) {
    eigenvaluesFile >> largestEigenvalue;
    eigenvaluesFile.close();
  } else {
    std::cerr << "Error: Unable to open eigenvaluesA.txt for reading." << std::endl;
    return 1;
  }

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

  std::vector<double> x(n, 1.0);
  int maxIterations = 105;
  int iteration = 0;
  double residual = 0.0;

  while (iteration < maxIterations) {
      std::vector<double> Ax(n, 0.0);
      for (int i = 0; i < n; ++i) {
          for (int j = 0; j < n; ++j) {
              Ax[i] += A[i * n + j] * x[j];
          }
      }

      double maxAx = Ax[0];

      for (int i = 1; i < n; ++i) {
          if (Ax[i] > maxAx) {
              maxAx = Ax[i];
          }
      }

      for (int i = 0; i < n; ++i) {
          x[i] = Ax[i] / maxAx;
      }

      double newEigenvalue = maxAx;
      residual = std::abs(newEigenvalue - largestEigenvalue);

      if (residual < tolerance) {
          break;
      }

      ++iteration;
  }

  std::cout << "Verified largest eigenvalue: " << largestEigenvalue << std::endl;
  std::cout << "Number of iterations: " << iteration << std::endl;
  std::cout << "Residual: " << residual << std::endl;

  return 0;
}