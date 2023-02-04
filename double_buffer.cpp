//Markus Buchholz

#include <iostream>
#include <vector>
#include <cmath>
#include <Eigen/Dense>
#include <thread>
#include <semaphore>
#include <random>
//----------------------------------------------------------------------

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

//----------------------------------------------------------------------

void computeData(Eigen::Matrix<double, 100, 100> V)
{

    Eigen::Matrix<double, 100, 100> S = Eigen::Matrix<double, 100, 100>::Ones();

    for (auto ii = 0; ii < 1000; ii++)
    {

        S *= V.inverse() * V.transpose();
    }
}
//----------------------------------------------------------------------

int main()
{

    int N = 10;

    std::binary_semaphore signalCapture{1};
    std::binary_semaphore signalCompute{0};

    Eigen::Matrix<double, 100, 100> A;
    Eigen::Matrix<double, 100, 100> B; 

    //----------------------------------------------------------------------

    auto capture = [&]()
    {
        for (int ii = 0; ii < N; ii++)
        {

            captureData(A);
            signalCapture.acquire(); // capturing Blocked. A is Blocked
            A.swap(B);               //B->A
            signalCompute.release(); // computing Free. B
        }
    };

    //----------------------------------------------------------------------

    auto compute = [&]()
    {
        for (int ii = 0; ii < N; ii++)
        {

            signalCompute.acquire(); // computing Blocked. B is blocked
            computeData(B);          // Load B
            signalCapture.release(); // capturing Free. A is free
        }
    };

    //----------------------------------------------------------------------

    std::jthread captureImage(capture);
    std::jthread processImage(compute);

    return 0;
}
