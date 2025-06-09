#include <iostream>
#include <string>

template <class Container>
std::ostream &PrintContainer(std::ostream &out, const Container &c)
{
    std::cout << "[";
    for (auto &e : c)
        out << e << " ";
    std::cout << "]";
    return out;
}

// necessary typename word usage! We get type which is stored inside container (typename T::value_type):
template <typename T, typename Compare = std::less<typename T::value_type>>
void Sort(T &cont, Compare function = Compare())
{
    if (std::begin(cont) == std::end(cont))
        return;
    for (auto itI = std::begin(cont); itI != std::end(cont) - 1; ++itI)
    {
        for (auto itJ = std::begin(cont); itJ != std::end(cont) - 1; ++itJ)
        {
            if (function(*itJ, *(itJ + 1)))
            {
                // auto tempValue = std::move(*itJ);
                // *itJ = std::move(*(itJ + 1));
                // *(itJ + 1) = std::move(tempValue);
                std::swap(*itJ, *(itJ + 1));
            }
        }
    }
}

// above comparison can be replaces by functor:
template <class T>
struct Comparator
{
    bool operator()(const T &a, const T &b) { return a > b; }
};

int sort_template()
{
    int arr[]{1, 6, 8, 4, 0};
    std::string s{"Hren'"};

    PrintContainer(std::cout, s);
    std::cout << std::endl;

    PrintContainer(std::cout, arr);
    std::cout << std::endl;

    // c style array has difficulty to deduce element type (!)
    Sort(arr, std::less<int>());
    PrintContainer(std::cout, arr);
    std::cout << std::endl;

    Sort(arr, std::greater<int>());
    PrintContainer(std::cout, arr);
    std::cout << std::endl;

    // stl has no problem to use default comparators
    Sort(s);
    PrintContainer(std::cout, s);
    std::cout << std::endl;

    // lambda will work the same...
    Comparator<char> comp;
    Sort(s, comp);
    PrintContainer(std::cout, s);
    std::cout << std::endl;
    return 0;
}