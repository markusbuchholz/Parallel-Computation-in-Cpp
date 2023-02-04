// Markus Buchholz

#include <atomic>
#include <thread>
#include <iostream>
#include <Eigen/Dense>

// https://en.cppreference.com/w/cpp/atomic/atomic

std::atomic<int> M;
Eigen::Matrix<int, 3, 1> M_1 = Eigen::Matrix<int, 3, 1>::Ones();
auto work = []()
{
    for (auto ii = 0; ii < 1000; ii++) // 10-OK //100-NO
    {
        M += M_1.dot(M_1);
    }
};

int main()
{

    std::thread t1(work);
    std::thread t2(work);

    t1.join();
    t2.join();

    std::cout << M << "\n";
    return 0;
}
