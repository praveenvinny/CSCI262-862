#include <iostream>
#include <cstdlib>
#include <fstream>
#include "structures.h"
#include "event.h"
#define DEBUG
#define DAY_LENGTH_IN_MINUTES 1440

void ActivityEngine::simulateDay(std::vector<Stats> &stats, std::vector<Vehicle> &vehicles, StatsInfo si)
{
    ofile << "\nBeginning simulation of day " << dayCount + 1 << "..." << std::endl;
    ofile << "Road is " << si.lengthOfRoad << " kilometres long..." << std::endl;
    dayCount++;

    for(int minute = 0; minute < DAY_LENGTH_IN_MINUTES; minute++)
    {
        if(minute < DAY_LENGTH_IN_MINUTES-180) // we don't want cars rocking up late
            generateVehicle(rand()%si.noOfVehicleType, stats, vehicles, minute);
        handleDepartures(minute, si);
        handleParking();
    }

}

static int varySpeed(int mean, int stdDev)
{
    int val = rand()% 2 + 1;
    int retval = rand() % (mean+val*stdDev);
    return retval;
}


// Return the offset in the vector of vehicles with registration number
static int findOffset(std::vector<Vehicle> vehicles, std::string rego)
{
    for(std::vector<Vehicle>::iterator iter = vehicles.begin(); iter < vehicles.end(); ++iter)
    {
        if(iter->getRego() == rego)
            return std::distance(vehicles.begin(), iter);
    }
    return -1;
}

void ActivityEngine::generateVehicle(int offset, std::vector<Stats> stats, std::vector<Vehicle> vehicles, int time)
{
    // this method has a chance of generating vehicle in accordance with the statistics in stats vector
    int probability = rand() % 1401; // get a number between 1 and 1399 for each minute in the day
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
        logMessage("Vehicle arrived on road:\n");
        logMessage("Name\tParking Flag\tRego\t\tVw\t\tSw\t\tSpeed\n");
        logMessage(vehicle);
        logMessage("\n");
        logMessage(vehicle.getRego());
        logMessage(" arrived at time: ");
        logMessage(time);
        logMessage("\n\n");
        #ifdef DEBUG
        std::cout << vehicle << std::endl;
        #endif
    }
}

float computeTravelTime(Vehicle &vehicle, StatsInfo si)
{
    return si.lengthOfRoad / vehicle.getSpeed() * 60;
}

void ActivityEngine::handleDepartures(int minute, StatsInfo si)
{
    int randOffset = 0;
    float ttime;
    for(unsigned int i =0; i < vehicles.size(); i++)
    {
        randOffset = rand() % vehicles.size();
        if(rand()%120 < 5 && !vehicles[i].isVehicleParked())
        {
            logMessage(vehicles[randOffset].getName());
            logMessage(" with registration: ");
            logMessage(vehicles[randOffset].getRego());
            logMessage(" has departed off side road at time: ");
            logMessage(minute);
            logMessage(" after ");
            logMessage(minute-vehicles[randOffset].getBegTime());
            logMessage(" minutes on the road.\n\n");

            vehicles.erase(vehicles.begin()+randOffset);
        }
    }
    for(std::vector<Vehicle>::iterator it = vehicles.begin(); it < vehicles.end(); ++it)
    {
        ttime = computeTravelTime(*it, si);
        if(minute >= (ttime + it->getBegTime() + it->getParkedTime()) && !it->isVehicleParked())
        {
            logMessage(vehicles[randOffset].getName());
            logMessage(" with registration: ");
            logMessage(vehicles[randOffset].getRego());
            logMessage(" has departed off end of road at time: ");
            logMessage(minute);
            logMessage(" after ");
            logMessage(ttime);
            logMessage(" minutes on the road.\n\n");
            vehicles.erase(it);
        }
    }
}

template <class T>
void ActivityEngine::logMessage(T message)
{
    ofile << message;
}

void ActivityEngine::handleParking()
{
    static std::vector<std::string> parkedVehicles; // store the offset of parked vehicles
    for(std::vector<Vehicle>::iterator it = vehicles.begin(); it < vehicles.end(); ++it)
    {
        if(it->getParkingFlag() == 1)
        {
            if(it->isVehicleParked() == false)
            {
                if(rand()%40 < 2)
                {
                    logMessage("Vehicle ");
                    logMessage(it->getRego());
                    logMessage(" has parked.\n");
                    it->setParked(true);
                    parkedVehicles.push_back(it->getRego());
                }

            }
        }
    }
    for(std::vector<std::string>::iterator it = parkedVehicles.begin(); it < parkedVehicles.end(); ++it)
    {
        size_t offset = findOffset(vehicles, *it);
        vehicles[offset].incTimeParked();
        if(rand()%20 < 2)
        {
            logMessage("Vehicle ");
            logMessage(vehicles[offset].getRego());
            logMessage(" is no longer parked.\n");
            vehicles[offset].setParked(false);
            parkedVehicles.erase(it);
        }
    }
}

