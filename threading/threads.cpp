#include <cstdint>
#include <thread>
#include <iostream>
#include <vector>

#include <future>

#include <mutex>

class Str
{

public:
    std::string m_s{"not set"};

    Str() { std::cout << "Str::Str()" << std::endl; };
    ;
    Str(const Str &s) { std::cout << "Str::Str(const Str&)" << std::endl; };
    ;
    Str(Str &&s) { std::cout << "Str(Str &&s)" << std::endl; };
    ;
    ~Str() { std::cout << "~Str::Str()" << std::endl; };

    void Set(const std::string &s)
    {
        m_s = s;
        std::cout << "Str::Set(" << s << ") invoked! " << std::endl;
    };
};

void thFunc(uint32_t num, Str &s)
{
    std::cout << std::this_thread::get_id() << " " << "Begin execution for " << num << " elements" << std::endl;
    s.Set("VALUE");
    std::vector<uint32_t> v;
    for (uint32_t i = 0; i < num; ++i)
    {
        //        std::cout << std::this_thread::get_id() << " " << "inserting element (" << i << ")" << std::endl;
        v.push_back(std::move(i));
    }
    std::cout << std::this_thread::get_id() << " " << "Exiting thread function." << std::endl;
}

void threads()
{
    Str s;
    std::cout << "main Starting thread (";
    //(!!!) thread constructor REQUIRES use of std:ref()/cref() to pass it by reference to the thread function!
    std::thread th(thFunc, 10000000, std::ref(s));
    std::cout << th.get_id() << ")\n";
    std::cout << "main waiting thread to finish... " << std::endl;
    if (th.joinable())
        th.join();
    std::cout << "main Thread set value to [" << s.m_s << "]" << std::endl;
    std::cout << "main Exiting... " << std::endl;
}

void future()
{
    std::cout << "---- std::future: " << std::endl;
    auto Add = [](int a, int b) -> int
    {
        // std::this_thread::sleep_for(std::chrono::milliseconds(10));
        std::cout << std::this_thread::get_id() << " " << "Calculated result = " << (a + b) << "\n";
        return a + b;
    };

    std::packaged_task<int(int, int)> task(Add);
    std::future<int> res = task.get_future();

    // same thread execution:
    task(2, 3);
    std::cout << std::this_thread::get_id() << " " << "Result is of task(2,3) = " << res.get() << std::endl;

    // other thread execution:
    auto delay{std::chrono::milliseconds(1000)};
    auto Operation = [&delay](const std::vector<int> &v) -> int
    {
        int res{0};
        std::cout << std::this_thread::get_id() << " " << "Begin execution\n";
        for (auto i : v)
        {
            res += i;
            std::cout << std::this_thread::get_id() << " " << res << std::endl;
            std::this_thread::sleep_for(delay);
        };

        std::cout << std::this_thread::get_id() << " " << "Exiting." << std::endl;
        return res;
    };

    std::packaged_task<int(const std::vector<int>)> Oper(Operation);
    std::future<int> res2 = Oper.get_future();
    std::vector<int> v{1, 2, 3, 4, 5};
    std::thread thOper(std::move(Oper), std::cref(v));
    while (res2.wait_for(delay) == std::future_status::timeout)
    {
        std::cout << std::this_thread::get_id() << " " << "waiting for result..." << std::endl;
    }

    std::cout << std::this_thread::get_id() << " " << "Result of Operation = " << res2.get() << std::endl;
    thOper.join();
}

void syncronization()
{
    std::mutex m;
    uint32_t halfSize{10000};
    std::vector<uint32_t> v;
    std::cout << "Cores: " << std::thread::hardware_concurrency() << std::endl;

    // uint32_t prefix = (uint32_t)(std::this_thread::get_id()) * 10000;
    auto filler = [&](uint32_t size)
    {
        // uint32_t prefix = std::this_thread::get_id() * 10000;
        for (uint32_t i = 0; i < size; ++i)
        {
            std::lock_guard lock(m);
            v.push_back(i);
        }
    };

    std::thread th1(std::move(filler), halfSize);
    std::thread th2(std::move(filler), halfSize);

    th1.join();
    th2.join();
    std::cout << "vector size after fill: " << v.size() << std::endl;
}
