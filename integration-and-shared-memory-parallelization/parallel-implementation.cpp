#include <iostream>
#include <cmath>
#include <omp.h>

double function(double x) {
    return 4 / (1 + x*x);
}

double left_riemann_sum(int N) {
    double h = 1.0 / N;
    double integral_sum = 0.0;

    #pragma omp parallel for reduction(+:integral_sum)
    for (int i = 1; i <= N; ++i) {
        double xi = i * h;
        integral_sum += function(xi);
    }

    double integral_approximation = h * integral_sum;
    return integral_approximation;
}

int main() {
    double true_value = M_PI;  // Actual value of π
    int max_N = 100000;        // Maximum number of subintervals

    for (int N = 10; N <= max_N; N *= 10) {
        double result = left_riemann_sum(N);
        double error = std::abs(result - true_value);
        std::cout << "N = " << N << ", Approximation: " << result << ", Error: " << error << std::endl;
    }

    return 0;
}
