//Markus Buchholz

#include <iostream>
#include <thread>
#include <cmath>
#include <Eigen/Dense>
#include <chrono>
#include <vector>
#include <atomic>

int nr_threads = 8;
std::atomic<double> M;

auto work_fast = []()
{
    double desired;
    // https://cplusplus.com/reference/atomic/atomic/load/
    // current value of M is loaded to expected from atomic

    double expected = M.load();

    Eigen::Matrix<double, 10, 1> R = Eigen::Matrix<double, 10, 1>::Random();

    do
    {
        desired = expected + R.dot(R);
    } while (!M.compare_exchange_strong(expected, desired));

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
};

auto work_slow = []()
{
    double desired;

    double expected = M.load();

    Eigen::Matrix<double, 10, 1> R = Eigen::Matrix<double, 10, 1>::Random();

    do
    {
        desired = expected + R.dot(R);
    } while (!M.compare_exchange_strong(expected, desired));

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
