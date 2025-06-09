
#include <iostream>
#include <vector>
#include <array>

template <class T, size_t size = 10>
class Stack
{
    T m_store[size];
    int m_top{-1};

public:
    void Push(const T &v)
    {
        m_store[++m_top] = v;
    }

    void Pop()
    {
        if (m_top < 0)
            return;
        --m_top;
    }

    int Top() { return m_top; }

    bool Empty() { return m_top < 0; }

    size_t Size() { return m_top + 1; }
};

// IMPORTANT benefit of the "using" keyword which typedef does not support:
template <typename T>
using MyStack = Stack<T>; 

template <typename T>
using MyStacks = std::vector<Stack<T, 10>>;

// Also function pointers ate more readable:
typedef const char *(*pFuncOld)(const std::string &);
using pFunc = const char *(*)(const std::string &);

const char *BustIt(const std::string &s)
{
    return s.c_str();
}

int stack_template(void)
{
    pFunc pCStr{&BustIt};
    std::string s{"BustIt!"};
    std::cout << "pCStr{\"BustIt!\"} = " << pCStr("BustIt!") << std::endl;

    Stack<int> stack;
    stack.Push(3);
    stack.Push(2);
    stack.Push(1);
    std::cout << "stack.Top=" << stack.Top() << std::endl;

    MyStacks<int> stacks;
    stacks.push_back(stack);

    std::cout << "Stacks count = " << stacks.size() << ", stacks[0].Top = " << stacks[0].Top() << std::endl;

    return 0;
}