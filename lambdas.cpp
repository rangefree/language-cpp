
#include <iostream>
#include <vector>
#include <algorithm>

int Add(int a, int b)
{
    return a + b;
}


int lambda()
{
    int acc{0};
    auto accumulate = [&acc](auto &&i)
    {
        acc = Add(acc, std::forward<decltype(i)>(i));
    };

    std::vector<int> v{1, 2, 3, 4, 5};

    std::for_each(v.begin(), v.end(), accumulate);

    std::cout << "total of vector's values = " << acc << std::endl;

    return 0;
}
