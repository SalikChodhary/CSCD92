#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>

class NagelSchreckenbergModel {
public:
    NagelSchreckenbergModel(int road_length, int num_cars, int max_speed, double p, int num_steps)
        : road_length(road_length), num_cars(num_cars), max_speed(max_speed), p(p), num_steps(num_steps) {
        positions.resize(num_cars);
        velocities.resize(num_cars);
        data.resize(num_steps, std::vector<int>(num_cars * 2));

        initialize();
    }

    void runSimulation() {
        for (int t = 0; t < num_steps; ++t) {
            for (int i = 0; i < num_cars; ++i) {
                accelerate(i);
                decelerateDueToOtherCars(i);
                randomDeceleration(i);
                updatePosition(i);
                storeData(t, i);
            }
        }

        writeDataToFile();
    }

private:
    int road_length;
    int num_cars;
    int max_speed;
    double p;
    int num_steps;

    std::vector<int> positions;
    std::vector<int> velocities;
    std::vector<std::vector<int>> data;

    void initialize() {
        for (int i = 0; i < num_cars; ++i) {
            positions[i] = i * (road_length / num_cars);
            velocities[i] = rand() % (max_speed + 1);
        }
    }

    void accelerate(int i) {
        velocities[i] = std::min(velocities[i] + 1, max_speed);
    }

    void decelerateDueToOtherCars(int i) {
        int d = (positions[(i + 1) % num_cars] - positions[i] + road_length) % road_length;
        velocities[i] = std::min(velocities[i], d - 1);
    }

    void randomDeceleration(int i) {
        if (velocities[i] > 0 && static_cast<double>(rand()) / RAND_MAX < p) {
            velocities[i] -= 1;
        }
    }

    void updatePosition(int i) {
        positions[i] = (positions[i] + velocities[i]) % road_length;
    }

    void storeData(int t, int i) {
        data[t][i * 2] = positions[i];
        data[t][i * 2 + 1] = t;
    }

    void writeDataToFile() {
        std::ofstream outFile("traffic_data.txt");
        for (int t = 0; t < num_steps; ++t) {
            for (int i = 0; i < num_cars * 2; ++i) {
                outFile << data[t][i] << " ";
            }
            outFile << std::endl;
        }
        outFile.close();
    }
};

int main() {
    const int road_length = 1000;
    const int num_cars = 200;
    const int max_speed = 5;
    const double p = 0.13;
    const int num_steps = 500;

    NagelSchreckenbergModel model(road_length, num_cars, max_speed, p, num_steps);
    model.runSimulation();

    return 0;
}
