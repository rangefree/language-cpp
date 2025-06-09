#include <iostream>
#include <filesystem>
#include <vector>
#include <algorithm>

namespace fs = std::filesystem;

std::string GetPermissons(const fs::path &path)
{
    std::string s;
    auto p = fs::status(path).permissions();
    s += (p & fs::perms::owner_read) != fs::perms::none ? "r" : "_";
    s += (p & fs::perms::owner_write) != fs::perms::none ? "w" : "_";
    s += (p & fs::perms::owner_exec) != fs::perms::none ? "x" : "_";
    s += (p & fs::perms::group_read) != fs::perms::none ? "r" : "_";
    s += (p & fs::perms::group_write) != fs::perms::none ? "w" : "_";
    s += (p & fs::perms::group_exec) != fs::perms::none ? "x" : "_";
    s += (p & fs::perms::others_read) != fs::perms::none ? "r" : "_";
    s += (p & fs::perms::others_write) != fs::perms::none ? "w" : "_";
    s += (p & fs::perms::others_exec) != fs::perms::none ? "x" : "_";
    return s;
}

void ListDir()
{
    auto curPath{fs::current_path()};
    std::cout << "Current path:" << curPath << std::endl;
    std::cout << "Current path:" << curPath.string() << std::endl;

    std::vector<fs::directory_entry> entries;
    for (const auto &dirEntry : fs::directory_iterator{curPath})
    {
        entries.push_back(dirEntry);
    }

    std::partition(entries.begin(), entries.end(), [](const fs::directory_entry &e)
                   { return e.is_directory(); });

    for (const auto &dirEntry : entries)
    {
        switch (const auto &p = dirEntry.path(); dirEntry.status().type())
        {
        case fs::file_type::directory:
            std::cout << "[DIR]\t" << GetPermissons(p) << "\t\t" << p.filename() << std::endl;
            break;

        case fs::file_type::regular:
            std::cout << "\t" << GetPermissons(p) << "\t" << dirEntry.file_size() << "\t" << p.filename() << std::endl;
            break;

        default:
            break;
        }
    }
}