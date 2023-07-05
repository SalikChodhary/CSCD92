#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

double f(double x) {
    return sin(2 * x);
}

double g(double x) {
    return cos(3 * x);
}

int main() {
    ofstream outputFile("lissajous.txt");
    if (!outputFile) {
        cerr << "err: failed to create file" << endl;
        return 1;
    }

    double startX = -5.0;
    double endX = 5.0;
    int numPoints = 101;
    double stepSize = (endX - startX) / (numPoints - 1);

    for (int i = 0; i < numPoints; ++i) {
        double x = startX + i * stepSize;
        double y = f(x);
        double z = g(x);
        outputFile << x << " " << y << " " << z << "\n";
    }

    outputFile.close();

    cout << "table data written to lisajous.txt" << endl;

    return 0;
}