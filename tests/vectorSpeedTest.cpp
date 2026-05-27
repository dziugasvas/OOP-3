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

    volatile long long kontrolinis = 0;

    for (int sz : dydziai) {
        auto t1 = std::chrono::high_resolution_clock::now();
        std::vector<int> v1;
        for (int i = 1; i <= sz; ++i) v1.push_back(i);
        long long suma1 = 0;
        for (int x : v1) suma1 += x;
        kontrolinis += suma1;
        auto t2 = std::chrono::high_resolution_clock::now();
        double laikas1 = std::chrono::duration<double>(t2 - t1).count();

        auto t3 = std::chrono::high_resolution_clock::now();
        Vector<int> v2;
        for (int i = 1; i <= sz; ++i) v2.push_back(i);
        long long suma2 = 0;
        for (int x : v2) suma2 += x;
        kontrolinis += suma2;
        auto t4 = std::chrono::high_resolution_clock::now();
        double laikas2 = std::chrono::duration<double>(t4 - t3).count();

        if (suma1 != suma2) {
            std::cout << "Klaida: konteineriu sumos nesutampa!" << std::endl;
        }

        std::cout << std::left << std::setw(15) << sz
                  << std::setw(20) << std::fixed << std::setprecision(6) << laikas1
                  << std::setw(20) << laikas2 << std::endl;
    }

    std::cout << "\n--- Atminties perskirstymu palyginimas ---" << std::endl;

    int perskirsymai_std = 0;
    std::vector<int> v3;
    for (int i = 1; i <= 100000000; ++i) {
        if (v3.capacity() == v3.size()) perskirsymai_std++;
        v3.push_back(i);
    }

    int perskirsymai_vec = 0;
    Vector<int> v4;
    for (int i = 1; i <= 100000000; ++i) {
        if (v4.capacity() == v4.size()) perskirsymai_vec++;
        v4.push_back(i);
    }

    std::cout << "std::vector perskirstymai: " << perskirsymai_std << std::endl;
    std::cout << "Vector perskirstymai: " << perskirsymai_vec << std::endl;

    return 0;
}
