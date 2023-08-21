#include <iostream>

double function(double x) {
    return 4 / (1 + x*x);
}

double left_riemann_sum(int N) {
    double h = 1.0 / N;
    double integral_sum = 0.0;
    
    for (int i = 1; i <= N; ++i) {
        double xi = i * h;
        integral_sum += function(xi);
    }
    
    double integral_approximation = h * integral_sum;
    return integral_approximation;
}

int main() {
    int N = 100000;  // Number of subintervals
    double result = left_riemann_sum(N);
    std::cout << "Approximated Integral: " << result << std::endl;
    
    return 0;
}
