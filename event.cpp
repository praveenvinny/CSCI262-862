#include <iostream>
#include <cstdlib>
#include "structures.h"
#include "event.h"

#define DAY_LENGTH_IN_MINUTES 1440

void ActivityEngine::simulateDay(std::vector<Stats> &stats, std::vector<Vehicle> &vehicles, StatsInfo si)
{

    std::cout << "Beginning simulation of day " << dayCount << "..." << std::endl;
    dayCount++;
    for(int minute = 0; minute < DAY_LENGTH_IN_MINUTES; minute++)
    {
        generateVehicle(rand()%si.noOfVehicleType, stats, vehicles, minute);

    }

}

static int varySpeed(int mean, int stdDev)
{
    int val = rand()% 2 + 1;
    int retval = rand() % (mean+val*stdDev);
    return retval;
}

// Return the offset in the vector of the Stats object of type vehicleType
int findOffset(std::vector<Stats> stats, std::string vehicleType)
{
    int i = 0;
    for(std::vector<Stats>::iterator iter = stats.begin(); iter < stats.end(); ++iter)
    {
        if(iter->getType() == vehicleType)
            return i;
        i++;
    }
    return -1;
}

void ActivityEngine::generateVehicle(int offset, std::vector<Stats> stats, std::vector<Vehicle> vehicles, int time)
{
    // this method has a chance of generating vehicle in accordance with the statistics in stats vector
    int probability = rand() % 1000; // get a number between 1 and 1399 for each minute in the day
    if(probability <= stats[offset].getNumMean())
    {
        Vehicle vehicle;
        vehicle.setName(vehicles[offset].getName());
        vehicle.setFlag(vehicles[offset].getParkingFlag());
        vehicle.setRego(vehicles[offset].getRego());
        vehicle.setVolumeWeight(vehicles[offset].getVolumeWeight());
        vehicle.setSpeedWeight(vehicles[offset].getSpeedWeight());
        vehicle.setSpeed(varySpeed(stats[offset].getSpeedMean(), stats[offset].getSpeedStdDev()));
        vehicle.setBeginningTime(time);
        vehicle.generateRego();
        this->vehicles.push_back(vehicle);
        #ifdef DEBUG
        std::cout << vehicle;
        #endif
    }
}

void ActivityEngine::handleDepartures(int time)
{
     for(std::vector<Vehicle>::iterator iter = vehicles.begin(); iter < vehicles.end(); ++iter)
     {
        // Check to see if they pull out on a side road
     }
}
