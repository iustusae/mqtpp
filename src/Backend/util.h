//
// Created by Ayman Ougri on 5/1/23.
//

#ifndef MQT_UTIL_H
#define MQT_UTIL_H

#include <map>
#include <string>
#include <chrono>

std::map<std::string, std::string> load_env(const std::string& path);
std::string formatDate(std::chrono::system_clock::time_point tp);
#endif //MQT_UTIL_H
