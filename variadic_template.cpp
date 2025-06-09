#include <iostream>

void Print() { std::cout << std::endl; } // end of recursive calls. Should be declared BEFORE template :)

// Non move semantic:
// template <class T, class... Args>
// void Print(const T &v, const Args &...args)
// {
//     std::cout << v;
//     if (sizeof...(args))
//         std::cout << " ";
//     Print(args...);
// }

// MOVE semantic:
template <class T, class... Args>
void Print(T &&v, Args &&...args)
{
    std::cout << v;
    if (sizeof...(args))
        std::cout << " ";
    Print(std::forward<Args>(args)...); // USE forwarding and note syntax!!!
}

// Explanation of the recursion on parameters during calls:
// Print(1,  2,3);
//     Print(2,  3);
//         Print(3);
//             Print();

auto Sum() { return 0; }
template <class T, class... Args>
auto Sum(T &&v, Args... args)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return v + Sum(args...);
}

// C++ FOLF is a better alternative:

// Unary Folds (require parameters to be provided):
template <class... Args>
auto SumRFold(Args... args)
{
    return (args + ...); // SumRFold(1,2,3,4) = (1+(2+(3+4)))
}

template <class... Args>
auto SumLFold(Args... args)
{
    return (... + args); // SumLFold(1,2,3,4) = (((1+2)+3)+4)
}

// Binary Folds:
template <class... Args>
auto SumRFoldBin(Args... args)
{
    return (args + ... + 0); // SumRFold(1,2,3,4) = (1+(2+(3+(4+0))))
}

template <class... Args>
auto SumLFoldBin(Args... args)
{
    return (0 + ... + args); // SumLFold(1,2,3,4) = ((((0+1)+2)+3)+4)
}

// is any of provided even?
template <class... Args>
bool IsAnyEven(Args... args)
{
    return (... || (args % 2 == 0));
}

// is all even?
template <class... Args>
bool IsAllEven(Args... args)
{
    return (... && (args % 2 == 0));
}

template <class... Args, typename Predicate>
bool AnyOf(Predicate p, Args... args)
{
    return (... || p(args));
}

int variadic_template(void)
{
    Print("simple", "printing function", "for", "c++", 11, "\n");

    auto s = Sum(1, 2, 3, 4, 5);
    std::cout << "Sum(1,2,3,4,5) = " << s << std::endl;

    std::cout << "SumRFold(1,2,3,4,5) = " << SumRFold(1, 2, 3, 4, 5) << std::endl;

    std::cout << "SumLFold(1,2,3,4,5) = " << SumLFold(1, 2, 3, 4, 5) << std::endl;

    std::cout << "SumRFoldBin() = " << SumRFoldBin() << std::endl;

    std::cout << "IsAnyEven(1,3,5) = " << IsAnyEven(1, 3, 5) << std::endl;
    std::cout << "IsAnyEven(1,3,5,6) = " << IsAnyEven(1, 3, 5, 6) << std::endl;

    std::cout << "IsAllEven(1,3,5) = " << IsAllEven(1, 3, 5) << std::endl;
    std::cout << "IsAllEven(10,30,50) = " << IsAllEven(10, 30, 50) << std::endl;

    std::cout << "AnyOf(1,2,3, [](int i){return i%2 == 0}) = " << AnyOf([](int i)
                                                                        { return i % 2 == 0; }, 1, 2, 3)
              << std::endl;
    return 0;
}