#ifndef EVENT_H
#define EVENT_H
#include <iostream>
#include <vector>
#include <map>
#include <string>
//#define DEBUG
class ActivityEngine
{
    public:
        ActivityEngine() : dayCount(0)
        {
            ofile.open("ActivityLog.txt");
            if (!ofile.is_open())
            {
                std::cerr << "Cannot open file ActivityLog.txt" <<std::endl;
                exit(-1);
            }
            ofile << "Opening log..." << std::endl;

        }
        ~ActivityEngine()
        {
            vehicles.clear();
            ofile << "Closing log..." << std::endl;
            ofile.close();
        }
        void simulateDay(std::vector<Stats> &stats, std::vector<Vehicle> &vehicles, StatsInfo si);
        template <class T>
        void logMessage(T message);
    protected:
        void generateVehicle(int offset, std::vector<Stats> stats, std::vector<Vehicle> vehicles, int time);
        void handleParking();
        void handleDepartures(int time,  StatsInfo si);
        void handleMovement();
    private:
        std::vector<Vehicle> vehicles;
        std::map<std::string, int> carList;
        int dayCount;
        std::ofstream ofile;
};

#endif /* EVENT_H */
