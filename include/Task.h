#pragma once

#include <string>

struct Task
{
    int id;
    std::string name;
    int priority;
    int duration;

    bool operator<(const Task &other) const;
};
