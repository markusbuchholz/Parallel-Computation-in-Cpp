//Markus Buchholz

#include <iostream>
#include <vector>
#include <cmath>
#include <Eigen/Dense>
#include <random>

void captureData(Eigen::Matrix<double, 100, 100> V)
{

    std::random_device device;
    std::mt19937 mt(device());
    std::uniform_real_distribution<double> dist(0.0, 10.0);


    for (int ij = 0; ij < 1000; ij++)
    {
        for (int ii = 0; ii < V.rows(); ii++)
        {
            for (int jj = 0; jj < V.cols(); jj++)
            {

                V(ii, jj) = dist(mt);
            }
        }
    }
}

void computeData(Eigen::Matrix<double, 100, 100> V)
{

    Eigen::Matrix<double, 100, 100> S = Eigen::Matrix<double, 100, 100>::Ones();

    for (auto ii = 0; ii < 1000; ii++)
    {

        S *= V.inverse() * V.transpose();
    }
}

int main()
{
    int N = 10;

    Eigen::Matrix<double, 100, 100> A = Eigen::Matrix<double, 100, 100>::Zero();

    for (auto ii = 0; ii < N; ii++)
    {

        captureData(A);
        computeData(A);
    }
}