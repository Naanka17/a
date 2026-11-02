#pragma once

#include "Server.h"
#include "Task.h"

#include <vector>
#include <queue>
#include <map>
#include <string>
#include <random>

class SystemMonitor
{
private:
    std::vector<Server> servers;
    std::priority_queue<Task> taskQueue;
    std::vector<std::string> logs;
    std::map<std::string, int> statistics;

    std::mt19937 generator;

public:
    SystemMonitor();

    double randomValue(double min, double max);

    void addServer(int id, const std::string &name);
    void addTask(
        int id,
        const std::string &name,
        int priority,
        int duration);

    void updateServers();
    void processTasks();

    void displayServers();
    void displayStatistics();

    void log(const std::string &message);
    void displayLogs();
};