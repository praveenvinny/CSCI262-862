/*
 * File: event.h
 * Author: Jarod
 */
#ifndef EVENT_H
#define EVENT_H
#include <iostream>
#include <vector>
#include <map>
#include "analysisEngine.h"
#include <string>
//#define DEBUG
class ActivityEngine
{
    public:
        ActivityEngine(int size) : dayCount(0)
        {
            speed = new std::vector<float>[size];
            this->size = size;
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
            delete [] speed;
        }
        void simulateDay(std::vector<Stats> &stats, std::vector<Vehicle> &vehicles, StatsInfo si);
        template <class T>
        void logMessage(T message);
        void setUpCarList(std::vector<Stats> &stats, std::vector<Vehicle> &vehicles);
        void computeFinalStats(AnalysisEngine *ae, int aeSize);
        vector<Vehicle> getVectorList();
    protected:
        void generateVehicle(int offset, std::vector<Stats> stats, std::vector<Vehicle> vehicles, int time);
        void handleParking(StatsInfo statsInfo);
        void handleDepartures(int time,  StatsInfo si);
        void handleMovement();
    private:
        std::vector<Vehicle> vehicles;
        std::vector<float> *speed;
        std::vector<int> numberOfVehicles;
        std::vector<Stats> finalStats;
        int size;
        std::map<std::string, int> carList;
        int dayCount;
        std::ofstream ofile;
};

#endif /* EVENT_H */
