// Copyright 2025 NNTU-CS
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include "alg.h"

int main() {
    std::ofstream csv("result/data.csv");
    csv << "size,time1,time2,time3\n";

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 100);

    std::vector<int> sizes = {100, 500, 1000, 2000, 3000, 4000, 5000,
                               6000, 7000, 8000, 9000, 10000, 12000,
                               14000, 16000, 18000, 20000, 25000,
                               30000, 35000, 40000};

    for (int n : sizes) {
        int *data = new int[n];
        for (int i = 0; i < n; ++i) {
            data[i] = dist(gen);
        }
        std::sort(data, data + n);

        auto start = std::chrono::high_resolution_clock::now();
        countPairs1(data, n, 50);
        auto end = std::chrono::high_resolution_clock::now();
        double t1 = std::chrono::duration<double, std::milli>(end - start).count();

        start = std::chrono::high_resolution_clock::now();
        countPairs2(data, n, 50);
        end = std::chrono::high_resolution_clock::now();
        double t2 = std::chrono::duration<double, std::milli>(end - start).count();

        start = std::chrono::high_resolution_clock::now();
        countPairs3(data, n, 50);
        end = std::chrono::high_resolution_clock::now();
        double t3 = std::chrono::duration<double, std::milli>(end - start).count();

        csv << n << "," << t1 << "," << t2 << "," << t3 << "\n";
        std::cout << "n=" << n << " done: t1=" << t1 << " t2=" << t2 << " t3=" << t3 << "\n";

        delete[] data;
    }

    csv.close();
    return 0;
}
