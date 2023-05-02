//
// Created by Ayman Ougri on 5/1/23.
//

#include "util.h"

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <chrono>
#include <sstream>
#include <iomanip>


std::string formatDate(std::chrono::system_clock::time_point tp) {
    // Convert time_point to time_t
    std::time_t tt = std::chrono::system_clock::to_time_t(tp);

    // Convert time_t to tm struct in local timezone
    std::tm* t = std::localtime(&tt);

    // Format string as "mm/dd/yyyy"
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << t->tm_mon + 1 << "/"
        << std::setw(2) << std::setfill('0') << t->tm_mday << "/"
        << std::setw(4) << std::setfill('0') << t->tm_year + 1900;
    return oss.str();
}


std::map<std::string, std::string> load_env(const std::string& path)
{
    std::map<std::string, std::string> env;
    std::ifstream file(path);

    if (!file.is_open())
    {
        std::cerr << "Failed to open .env file\n";
        return env;
    }

    std::string line;
    while (std::getline(file, line))
    {
        size_t pos = line.find('=');
        if (pos != std::string::npos)
        {
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);
            env[key] = value;
        }
    }

    return env;
}
