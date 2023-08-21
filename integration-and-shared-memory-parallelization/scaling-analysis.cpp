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
    int num_threads[] = {1, 2, 4, 8}; // Number of threads to test

    for (int N = 10; N <= max_N; N *= 10) {
        std::cout << "N = " << N << std::endl;
        
        for (int num_thread : num_threads) {
            double total_runtime = 0.0;
            int num_runs = 5; // Number of runs for averaging

            for (int run = 0; run < num_runs; ++run) {
                omp_set_num_threads(num_thread);
                double start_time = omp_get_wtime();
                double result = left_riemann_sum(N);
                double end_time = omp_get_wtime();
                
                total_runtime += end_time - start_time;
            }
            
            double average_runtime = total_runtime / num_runs;
            std::cout << "  Threads = " << num_thread << ", Avg. Runtime: " << average_runtime << " seconds" << std::endl;
        }
    }

    return 0;
}



