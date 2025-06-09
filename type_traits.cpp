#include <iostream>
#include <type_traits>

template <class T>
T Devide(const T &a, const T &b)
{
    static_assert(std::is_floating_point<T>::value, "Devide() supports only floating point operands");
    // if (std::is_floating_point<T>::value)
    return a / b;
}

template <class T>
void IsReference(T &&)
{
    std::cout << std::boolalpha;
    std::cout << "provided type " << typeid(T).name() << "is reference: " << std::is_reference<T>::value << std::endl;
}

void a(int &&i)
{
    std::cout << "a(rvalue {" << i << "})" << std::endl;
}

void a(int &i)
{
    std::cout << "a(lvalue {" << i << "})" << std::endl;
}

void b(int &&i)
{
    a(std::forward<int>(i));
    // a(i);
}

void b(int &i)
{
    // a(std::forward<int>(i));
    a(i);
}

template <class T>
void RemoveReference(T &&)
{
    // IsReference(std::forward<T>);
    // std::cout << std::boolalpha;

    std::cout << "provided type for reef removal " << typeid(T).name() << "is reference: " << std::is_reference<T>::value << std::endl;

    std::cout << "after remove reference: " << std::is_reference<typename std::remove_reference<T>::type>::value
              << std::endl;
}

// NOTE !!!: C++ 17 provides shortened aliases for value access:
//  std::is_integral<int>::value is same as std::is_integral_v<int>
//  std::remove_reference<T>::type is same as std::remove_reference_t<T>

// ATTANTION: compile tyme if   "if constexpr (...)" allows to skip code blocks during compile time!
// it is The Reason why next function compiles...

template <class T>
void PrintValue(const T &r)
{
    if constexpr (std::is_pointer_v<T>)
        std::cout << *r;
    else if constexpr (std::is_array_v<T>)
    {
        std::cout << "[";
        for (const auto &e : r)
            std::cout << " " << e;
        std::cout << "]";
    }
    else
        std::cout << r;

    std::cout << std::endl;
}

template <typename T>
std::string ToString(T &&rv)
{
    if constexpr (std::is_arithmetic_v<T>)
        return std::to_string(std::forward<T>(rv));
    else
        return std::string{std::forward<T>(rv)};
}

void CheckArchitecture()
{
    if (sizeof(void *) == 4)
        std::cout << "32-bit\n";
    else if (sizeof(void *) == 8)
        std::cout << "64-bit\n";
    else
        std::cout << "Unknown architecture\n";
}

int type_traits(void)
{
    std::cout << "is int? " << std::is_integral<int>::value << std::endl;

    std::cout << "Devide(1,2) = " << Devide(1.0, 2.) << std::endl;

    IsReference(5);

    std::string s{"hello"};
    IsReference(s);

    RemoveReference(s);

    b(5);

    int i{48};
    b(i);

    float f{2};
    std::cout << "PrintValue(f) = ";
    PrintValue(f);

    std::cout << "PrintValue(&f) = ";
    PrintValue(&f);

    std::cout << "PrintValue(1) = ";
    PrintValue(1);

    float arr[] = {1, 2, 3.3, 4, 5.3};

    std::cout << "PrintValue(arr) = ";
    PrintValue(arr);
    // PrintValue({1, 2, 3, 4});

    auto ss = ToString(5);
    auto sss = ToString(5.5);

    std::cout << "Results of ToString(): " << ss << " , " << sss << std::endl;

    CheckArchitecture();
    return 0;
}