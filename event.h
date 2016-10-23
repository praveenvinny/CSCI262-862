#ifndef EVENT_H
#define EVENT_H
#include <vector>
#include <string>
#define DEBUG
class ActivityEngine
{
    public:
        ActivityEngine() : dayCount(0) {}
        ActivityEngine(std::vector<Vehicle> &v): vehicles(v), dayCount(0) {}
        void simulateDay(std::vector<Stats> &stats, std::vector<Vehicle> &vehicles, StatsInfo si);
        void writeLogFile(std::string outputFileName = "ActivityLog.txt");
    protected:
        void generateVehicle(int offset, std::vector<Stats> stats, std::vector<Vehicle> vehicles, int time);
        void handleParking();
        void handleDepartures(int time);
        void handleMovement();
    private:
        std::vector<Vehicle> vehicles;
        int dayCount;
};

#endif /* EVENT_H */
