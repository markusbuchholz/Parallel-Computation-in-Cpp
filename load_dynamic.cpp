//Markus Buchholz

#include <iostream>
#include <cmath>
#include <Eigen/Dense>
#include <vector>
#include <thread>
#include <atomic>

int main()
{

    Eigen::Matrix<double, 100, 100> M1 = Eigen::Matrix<double, 100, 100>::Random();
    std::vector<std::vector<Eigen::Matrix<double, 100, 100>>> V;

    std::vector<Eigen::Matrix<double, 100, 100>> vec0(2000, Eigen::Matrix<double, 100, 100>::Random());
    std::vector<Eigen::Matrix<double, 100, 100>> vec1(4, Eigen::Matrix<double, 100, 100>::Random());
    std::vector<Eigen::Matrix<double, 100, 100>> vec2(2, Eigen::Matrix<double, 100, 100>::Random());
    std::vector<Eigen::Matrix<double, 100, 100>> vec3(1, Eigen::Matrix<double, 100, 100>::Random());
    std::vector<Eigen::Matrix<double, 100, 100>> vec4(10000, Eigen::Matrix<double, 100, 100>::Random());
    std::vector<Eigen::Matrix<double, 100, 100>> vec5(3, Eigen::Matrix<double, 100, 100>::Random());
    std::vector<Eigen::Matrix<double, 100, 100>> vec6(2, Eigen::Matrix<double, 100, 100>::Random());
    std::vector<Eigen::Matrix<double, 100, 100>> vec7(10000, Eigen::Matrix<double, 100, 100>::Random());
    std::vector<Eigen::Matrix<double, 100, 100>> vec8(10000, Eigen::Matrix<double, 100, 100>::Random());
    std::vector<Eigen::Matrix<double, 100, 100>> vec9(5, Eigen::Matrix<double, 100, 100>::Random());

    V.push_back(vec0);
    V.push_back(vec1);
    V.push_back(vec2);
    V.push_back(vec3);
    V.push_back(vec4);
    V.push_back(vec5);
    V.push_back(vec6);
    V.push_back(vec7);
    V.push_back(vec8);
    V.push_back(vec9);

    std::atomic<int> index = 0;

    auto work = [&]()
    {
        Eigen::Matrix<double, 100, 100> S = Eigen::Matrix<double, 100, 100>::Ones();
        for (int ii = index.fetch_add(1); ii < V.size(); ii = index.fetch_add(1))
        {

            for (auto &jj : V[ii])
            {

                S *= jj;
            }
        }
    };

    std::vector<std::jthread> threads;

    for (int ii = 0; ii < V.size(); ii++)
    {
        threads.emplace_back(work);
    }
}
