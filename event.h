#ifndef EVENT_H
#define EVENT_H
#include <vector>

class ActivityEngine
{
    public:
        ActivityEngine(std::vector<Vehicle> &v): vehicles(v) {}
        void simulateDay(std::vector<Stats> &s);

    private:
        std::vector<Vehicle> vehicles;
};

void activityEngine();

#endif /* EVENT_H */
