#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include "Vector.h"

int main() {
    std::vector<int> dydziai = {10000, 100000, 1000000, 10000000, 100000000};

    std::cout << "\n--- Spartos analize: std::vector vs Vector ---" << std::endl;
    std::cout << std::left << std::setw(15) << "Dydis"
              << std::setw(20) << "std::vector (s)"
              << std::setw(20) << "Vector (s)" << std::endl;
    std::cout << std::string(55, '-') << std::endl;

    for (int sz : dydziai) {
        auto t1 = std::chrono::high_resolution_clock::now();
        std::vector<int> v1;
        for (int i = 1; i <= sz; ++i) v1.push_back(i);
        auto t2 = std::chrono::high_resolution_clock::now();
        double laikas1 = std::chrono::duration<double>(t2 - t1).count();

        auto t3 = std::chrono::high_resolution_clock::now();
        Vector<int> v2;
        for (int i = 1; i <= sz; ++i) v2.push_back(i);
        auto t4 = std::chrono::high_resolution_clock::now();
        double laikas2 = std::chrono::duration<double>(t4 - t3).count();

        std::cout << std::left << std::setw(15) << sz
                  << std::setw(20) << std::fixed << std::setprecision(6) << laikas1
                  << std::setw(20) << laikas2 << std::endl;
    }

    return 0;
}