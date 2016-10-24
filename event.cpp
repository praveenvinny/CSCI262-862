#include <iostream>
#include <cstdlib>
#include <fstream>
#include "structures.h"
#include "event.h"
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
    this->vehicles.clear();
}

static int varySpeed(int mean, int stdDev)
{
    int val = rand()% 2 + 1;
    int retval = rand() % 10 + (mean+val*stdDev);
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
    int probability = 0;
    // this method has a chance of generating vehicle in accordance with the statistics in stats vector
    if(carList[vehicles[offset].getName()] - stats[offset].getNumMean() >= 20)
        probability = 30;
    else if(carList[vehicles[offset].getName()] - stats[offset].getNumMean() >= 10)
        probability = 35;
    else if(carList[vehicles[offset].getName()] - stats[offset].getNumMean() >= 5)
        probability = 40;
    else if(carList[vehicles[offset].getName()] - stats[offset].getNumMean() >= 0)
        probability = 100;
    else
        probability = 150;
    int rval = rand() % probability;
    if(rval <= 2)
    {
        Vehicle vehicle;
        carList[vehicles[offset].getName()] += 1;
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
        //logMessage("Name\tParking Flag\tRego\t\tVw\t\tSw\t\tSpeed\n");
        ofile << vehicle.getName() << " " << vehicle.getRego() << " Speed: "<< vehicle.getSpeed();
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
            logMessage(" with registration ");
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
            logMessage(it->getName());
            logMessage(" with registration ");
            logMessage(it->getRego());
            logMessage(" has departed off end of road at time: ");
            logMessage(minute);
            logMessage(" after ");
            logMessage(ttime+it->getParkedTime());
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
    static std::vector<std::string> parkedVehicles; // store the rego of parked vehicles
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
        int offset = findOffset(vehicles, *it);
        if(offset == -1)
            break;
        if((unsigned int) offset >= vehicles.size())
            offset = findOffset(vehicles, *it);
        vehicles[offset].incTimeParked();
        if(rand()%20 < 2)
        {
            logMessage(vehicles[offset].getName());
            logMessage(" ");
            logMessage(vehicles[offset].getRego());
            logMessage(" is no longer parked. ");
            vehicles[offset].setParked(false);
            logMessage("They have been parked for ");
            logMessage(vehicles[offset].getParkedTime());
            logMessage(" minutes total.\n");
            parkedVehicles.erase(it);
        }
    }
}

void ActivityEngine::setUpCarList(std::vector<Stats> &stats, std::vector<Vehicle> &vehicles)
{
    for(unsigned int i = 0; i < stats.size(); i++)
    {
        carList[vehicles[i].getName()] = stats[i].getNumMean();
    }
}
