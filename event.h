#ifndef EVENT_H
#define EVENT_H
#include <vector>

class ActivityEngine
{
    public:
        ActivityEngine() : dayCount(0) {}
        ActivityEngine(std::vector<Vehicle> &v): vehicles(v), dayCount(0) {}
        void simulateDay(std::vector<Stats> &stats, std::vector<Vehicle> &vehicles, StatsInfo si);
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
