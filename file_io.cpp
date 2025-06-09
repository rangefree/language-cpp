#include <iostream>
#include <fstream>
#include <string>

template <class T>
bool WriteToFile(const std::string &filename, const T &data)
{
    std::ofstream s;
    s.open(filename);
    if (!s.is_open())
        return false;
    s << data;
    return true;
}

bool FileToString(const std::string &filename, std::string &target)
{
    std::ifstream s;
    s.open(filename);
    if (!s.is_open())
        return false;
    std::string str;
    while (s.good())
    {
        std::getline(s, str);
        target += "\n" + str;
    }

    return true;
}

int file_io(void)
{
    std::string name{"data.txt"};
    std::string textToWrite{"(C++11) Raw String"}, text;

    WriteToFile(name, textToWrite + "\n10");

    FileToString(name, text);
    std::cout << text << "\n";
    return 0;
}

#include <vector>
#include <filesystem>
// reading file into vector's "buffer"
int read_into_buffer()
{
    std::string name{"file_io.h"};
    size_t size{std::filesystem::file_size(name)};
    std::vector<char> v(size, 0);
    std::string s; //(size,0);
    s.resize(size);
    if (auto file = std::ifstream(name))
    {
        file.read(v.data(), size); // bring us to end

        file.clear();                 // 1(!) reset flags
        file.seekg(0, std::ios::beg); // 2(!) go back to beginning of the file
        file.read(s.data(), size);    // 3(!) read data
    }
    else
        std::cout << "failed to open file (" << name << ")\n";

    std::cout << "----------------------\n";
    std::cout << v.data() << std::endl;
    std::cout << "----------------------\n";
    std::cout << s.data() << std::endl;
    std::cout << "----------------------\n";
    return 0;
}
