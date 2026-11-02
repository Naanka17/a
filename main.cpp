#include "SystemMonitor.h"
#include <string>

int main()
{
    SystemMonitor monitor;

    // Create 10 servers
    for (int i = 1; i <= 10; ++i)
    {
        monitor.addServer(i, std::string("Server-") + (i < 10 ? "0" : "") + std::to_string(i));
    }

    monitor.addTask(1, "Database backup", 3, 5);
    monitor.addTask(2, "Log processing", 1, 3);
    monitor.addTask(3, "User request", 5, 2);

    monitor.displayServers();

    monitor.updateServers();
    monitor.displayServers();

    monitor.processTasks();

    monitor.displayStatistics();
    monitor.displayLogs();

    return 0;
}
