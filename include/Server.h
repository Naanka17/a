#pragma once

#include <string>

struct Server
{
    int id;
    std::string name;
    std::string status;
    double cpu;
    double memory;
    double temperature;
};
