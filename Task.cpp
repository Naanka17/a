#include "Task.h"

bool Task::operator<(const Task &other) const
{
    return priority < other.priority;
}