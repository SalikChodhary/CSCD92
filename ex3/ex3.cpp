#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int* array = new int[100000];

    for (int i = 0; i < 100000; i++) {
        array[i] = int(9 * sin(i)) ;
        if (array[i] == 8) cout << "here " << endl;
    }

    int counts[19] = {0};

    for (int i = 0; i < 100000; i++) {
        int value = array[i];
        counts[value + 9]++; 
    }

    for (int i = -9; i <= 9; i++) {
        std::cout << "Value " << i << ": Count " << counts[i + 9] << std::endl;
    }

    delete[] array;

    return 0;
}