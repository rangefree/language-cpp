#include <iostream>
#include <fstream>
#include <string>
// #include <experimental/filesystem>
#include <filesystem>

// NOTE: stream::seekp() or stream::seekg() can be used to set put or get position

//WARNING: binary files do not have eof marker to check. you need to know file content structure!

int copy_text_file(void)
{
    // using namespace std::experimental::filesystem;
    using namespace std::filesystem;
    path src(current_path());
    src /= "source.txt";

    path dst(current_path());
    dst /= "destination.txt";

    std::ifstream sIn(src);
    if (sIn.is_open())
    {
        std::ofstream sOut(dst);
        std::string buffer;
        while (std::getline(sIn, buffer).good())
            sOut << buffer << "\n";
    }
    else
        std::cerr << "Failed to open file (" << src << ")" << std::endl;

    return 0;
}