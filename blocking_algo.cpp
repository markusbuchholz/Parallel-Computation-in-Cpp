//Markus Buchholz

#include <iostream>
#include <thread>
#include <mutex>
#include <cmath>
#include <Eigen/Dense>
#include <chrono>
#include <vector>

int nr_threads = 8;
double M;
std::mutex mtx;

auto work_fast = []()
{
    std::lock_guard<std::mutex> lock(mtx);

    Eigen::Matrix<double, 10, 1> R = Eigen::Matrix<double, 10, 1>::Random();
    M += R.dot(R);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
};

auto work_slow = []()
{
    std::lock_guard<std::mutex> lock(mtx);

    Eigen::Matrix<double, 10, 1> R = Eigen::Matrix<double, 10, 1>::Random();
    M += R.dot(R);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
};

int main()
{

    std::vector<std::thread> threads;

    for (int ii; ii < nr_threads - 1; ii++)
    {
        threads.emplace_back(work_fast);
    }
    threads.emplace_back(work_slow);

    // Wait for threads
    for (auto &thread : threads)
        thread.join();

    std::cout << "final dot product M = " << M << "\n";

    return 0;
}
