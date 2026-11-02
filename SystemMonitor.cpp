#include "SystemMonitor.h"

#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <sstream>
#include <ctime>
#include <algorithm>

SystemMonitor::SystemMonitor()
{
    std::random_device rd;
    generator.seed(rd());

    statistics["tasks_completed"] = 0;
    statistics["tasks_failed"] = 0;
    statistics["warnings"] = 0;
}

double SystemMonitor::randomValue(double min, double max)
{
    std::uniform_real_distribution<double> distribution(min, max);
    return distribution(generator);
}

void SystemMonitor::addServer(
    int id,
    const std::string &name)
{
    Server server;

    server.id = id;
    server.name = name;
    server.status = "ONLINE";

    server.cpu = randomValue(10, 80);
    server.memory = randomValue(20, 90);
    server.temperature = randomValue(35, 70);

    servers.push_back(server);

    log("Server " + name + " initialized.");
}

void SystemMonitor::addTask(
    int id,
    const std::string &name,
    int priority,
    int duration)
{
    Task task;

    task.id = id;
    task.name = name;
    task.priority = priority;
    task.duration = duration;

    taskQueue.push(task);

    log(
        "Task #" +
        std::to_string(id) +
        " added to processing queue.");
}

void SystemMonitor::updateServers()
{
    for (auto &server : servers)
    {

        server.cpu += randomValue(-10, 10);
        server.memory += randomValue(-5, 5);
        server.temperature += randomValue(-2, 3);

        server.cpu = std::clamp(server.cpu, 0.0, 100.0);
        server.memory = std::clamp(server.memory, 0.0, 100.0);

        if (server.temperature > 80)
        {

            server.status = "WARNING";
            statistics["warnings"]++;

            log(
                "WARNING: " +
                server.name +
                " temperature exceeded threshold.");
        }
        else if (server.cpu > 95)
        {

            server.status = "OVERLOAD";
            statistics["warnings"]++;

            log(
                "WARNING: " +
                server.name +
                " CPU overload detected.");
        }
        else
        {
            server.status = "ONLINE";
        }
    }
}

void SystemMonitor::processTasks()
{

    while (!taskQueue.empty())
    {

        Task current = taskQueue.top();
        taskQueue.pop();

        std::cout
            << "\n[PROCESSING] "
            << current.name
            << " | Priority: "
            << current.priority
            << std::endl;

        for (int i = 0; i <= 100; i += 10)
        {

            std::cout
                << "\r["
                << std::string(i / 10, '#')
                << std::string(10 - i / 10, ' ')
                << "] "
                << std::setw(3)
                << i
                << "%";

            std::cout.flush();

            std::this_thread::sleep_for(
                std::chrono::milliseconds(40));
        }

        std::cout << std::endl;
        statistics["tasks_completed"]++;

        log(
            "Task #" +
            std::to_string(current.id) +
            " completed successfully.");
    }
}

void SystemMonitor::displayServers()
{

    std::cout << "\n";
    std::cout
        << "================ SERVER STATUS ================\n";

    std::cout
        << std::left
        << std::setw(8) << "ID"
        << std::setw(18) << "NAME"
        << std::setw(12) << "STATUS"
        << std::setw(10) << "CPU"
        << std::setw(10) << "MEM"
        << std::setw(10) << "TEMP"
        << std::endl;

    std::cout
        << "------------------------------------------------\n";

    for (const auto &server : servers)
    {

        std::cout
            << std::left
            << std::setw(8)
            << server.id

            << std::setw(18)
            << server.name

            << std::setw(12)
            << server.status

            << std::setw(10)
            << std::fixed
            << std::setprecision(1)
            << server.cpu

            << std::setw(10)
            << server.memory

            << std::setw(10)
            << server.temperature

            << std::endl;
    }
}

void SystemMonitor::displayStatistics()
{

    std::cout << "\n";
    std::cout
        << "================ STATISTICS ===================\n";

    for (const auto &item : statistics)
    {

        std::cout
            << std::left
            << std::setw(20)
            << item.first
            << ": "
            << item.second
            << std::endl;
    }
}

void SystemMonitor::log(
    const std::string &message)
{
    auto now = std::chrono::system_clock::now();

    std::time_t currentTime =
        std::chrono::system_clock::to_time_t(now);

    std::stringstream stream;

    stream << std::put_time(
        std::localtime(&currentTime),
        "%H:%M:%S");

    std::string entry =
        "[" + stream.str() + "] " + message;

    logs.push_back(entry);

    std::cout
        << "\n"
        << entry
        << std::endl;
}

void SystemMonitor::displayLogs()
{

    std::cout << "\n";
    std::cout
        << "================ SYSTEM LOG ==================\n";

    for (const auto &entry : logs)
    {
        std::cout << entry << std::endl;
    }
}