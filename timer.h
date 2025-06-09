#pragma once
#include <chrono>
#include <iostream>
#include <string_view>

class Timer
{
    std::chrono::steady_clock::time_point m_start;

public:
    Timer() : m_start{std::chrono::steady_clock::now()} {};
    void Show(std::string_view message = "")
    {
        auto end = std::chrono::steady_clock::now();
        auto difference = end - m_start;
        std::cout << message << std::chrono::duration_cast<std::chrono::microseconds>(difference).count() << "us" << std::endl;
    }
};
