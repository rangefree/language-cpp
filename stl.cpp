#include <iostream>

#include <array>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>

#include <set>
#include <functional> // for greater<>()

template <class Cont>
void Print(const Cont &cont)
{
    std::cout << "[";
    for (auto it{std::begin(cont)}; it != std::end(cont); ++it)
    {
        if (it != cont.begin())
            std::cout << ", ";

        std::cout << *it;
    }
    std::cout << "]\n";
}

int sequential_containers()
{
    // C style array (constand size - static array)
    std::array<int, 6> arr{5, 3, 4, 7, 2, 1};
    std::cout << "std::array: ";
    Print(arr);

    // dynamic array, random access,
    std::vector<int> vect(arr.begin(), arr.end());
    vect.insert(vect.begin(), 10); // insert value at the beginning
    vect.insert(vect.end(), 100);  // insert at end
    vect.push_back(101);           // insert at end
    vect.erase(vect.begin() + 1);  // delete value at position 1 (5)
    std::cout << "std::vector: ";
    Print(vect);

    // deque, efficient for adding/removal of elements on both ends (!), random access,
    // not good for insertion/deletion between (begin, end) [in the middle].

    std::deque d(arr.begin(), arr.end());
    d.push_back(200);
    d.push_front(100);
    std::cout << "std::deque: ";
    Print(d);

    d.pop_front();
    d.pop_back();
    std::cout << "remove last and first element, std::deque: ";
    Print(d);

    d.erase(d.begin() + 2); // remove third (!) element
    std::cout << "remove third (!) element, std::deque: ";
    Print(d);

    // 2 way linked list, no random access
    std::list<int> l{arr.begin(), arr.end()};
    std::cout << "std::list: ";
    Print(l);

    // 1 way linked list, no random access, add always to the head. FILO
    std::forward_list<int> fl;
    for (int i{0}; i < 10; ++i)
        fl.push_front(i);
    std::cout << "std::forward_list: ";
    Print(fl);

    fl.insert_after(fl.begin(), 10);
    std::cout << "after fl.insert_after(fl.begin(), 10), std::forward_list: ";
    Print(fl);

    return 0;
}

int associative()
{
    // set efficient for lookups of the values
    // does not support duplications !
    std::set<int> s_assending;
    for (int i = 9; i >= 0; --i)
        s_assending.insert(i);
    std::cout << "std:set<int>: ";
    Print(s_assending);

    std::set<int, std::greater<int>> s_dessending(s_assending.begin(), s_assending.end());
    std::cout << "std::set<int, std::greater<int>>: ";
    Print(s_dessending);

    // multiset supports duplications:
    std::multiset<int> ms{s_assending.begin(), s_assending.end()};
    ms.insert(8);
    ms.insert(8);
    std::cout << "std::multiset<int>: ";
    Print(ms);

    auto it = ms.find(8);
    if (it != ms.end())
        std::cout << "found first element of value " << *it << std::endl;

    auto res = ms.equal_range(8);
    if (res.first != ms.end())
    {
        std::cout << "Found all occasions of 8: ";
        while (res.first != res.second)
            std::cout << *res.first++ << " ";
        std::cout << std::endl;
    }


    return 0;
}

int unordered()
{
    return 0;
}
