#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

vector<double> generateVector(int numPoints) {
    vector<double> x(numPoints);
    vector<double> y(numPoints);

    double step = 10.0 / (numPoints - 1);
    double value = -5.0;

    for (int i = 0; i < numPoints; i++) {
        x[i] = value;
        y[i] = cos(value);
        value += step;
    }

    return y;
}

vector<double> movingAverage(const vector<double>& y, int windowSize) {
    vector<double> averages(y.size());

    for (int i = 0; i < y.size(); i++) {

        int windowStart = i;
        int windowEnd = min(int(y.size()), i + windowSize);

        double sum = 0.0;
        for (int j = windowStart; j < windowEnd; j++)
            sum += y[j];

        averages[i] = sum / windowSize;
    }

    return averages;
}

void printTable(const vector<double>& y, const vector<double>& avg5, const vector<double>& avg10) {
    cout << "    y    |  Avg (5) | Avg (10)" << endl;
    cout << "------------------------------" << endl;

    for (int i = 0; i < y.size(); i++) {
        cout << y[i] << " | " << avg5[i] << " | " << avg10[i] << endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: ./moving_average <numPoints>" << endl;
        return 1;
    }

    int numPoints = atoi(argv[1]);

    if (numPoints < 1)
        cout << "Error: numPoints must be atleast 1" << endl;

    vector<double> y = generateVector(numPoints);
    vector<double> avg5 = movingAverage(y, 5);
    vector<double> avg10 = movingAverage(y, 10);

    printTable(y, avg5, avg10);

    return 0;
}
