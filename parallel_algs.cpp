#include "parallel_algs.h"
#include "timer.h"
#include <vector>
#include <random>
#include <algorithm>
#include <execution>

constexpr uint32_t vSize{1000000};
using Vector = std::vector<long>;

void FillVector(Vector &v)
{
    v.reserve(vSize);
    std::default_random_engine engine{std::random_device{}()};
    std::uniform_int_distribution<long> distribution{0, vSize};
    for (uint32_t i = 0; i < vSize; ++i)
        v.push_back(distribution(engine));
}

void ParAlgs()
{
    {
        Vector v;
        FillVector(v);
        Timer timer;
        std::sort(v.begin(), v.end());
        timer.Show("std::sort(v.begin(), v.end()) time: ");
    }

    {
        Vector v;
        FillVector(v);
        Timer timer;
        std::sort(std::execution::seq, v.begin(), v.end());
        timer.Show("std::sort(std::execution::seq, v.begin(), v.end()) time: ");
    }

    Vector v;
    FillVector(v);
    Timer timer;
    std::sort(std::execution::par, v.begin(), v.end());
    timer.Show("std::sort(std::execution::par, v.begin(), v.end()) time: ");
}
