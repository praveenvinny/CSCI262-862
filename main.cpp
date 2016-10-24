#include <iostream>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <ctime>
#include <cstring>
#include "structures.h"
#include "event.h"
using namespace std;
#define MAXNO 90

// functions definition
void readVehicleData(string vehiclesFileName, vector<Vehicle> &vehicles, int &noOfVehicleType);
void readStatsData(string statsFileName, vector<Stats> &stats, StatsInfo &statsInfo);

void printVehicleInfo(vector<Vehicle> vehicles);
void printStatsInfo(vector<Stats> stats);

int main(int argc, char *argv[]) {
    if(argc != 4)
    {
        cerr << "Usage: "<< argv[0] << " Vehicles.txt Stats.txt NumOfDays" << endl;
            exit(-1);
    }

    srand(time(NULL));

    vector<Vehicle> vehicles;
    vector<Stats> stats;
    ActivityEngine activityEngine;

    StatsInfo statsInfo;
    int noOfVehicleType;
    int days;

    string vehiclesFileName = string(argv[1]);
    string statsFileName = string(argv[2]);
    days = atoi(argv[3]);

    cout << "vehiclesFileName = " << vehiclesFileName << endl;
    cout << "statsFileName = " << statsFileName << endl;
    cout << "days = " << days << endl << endl;

    // read in all data from text file
    readVehicleData(vehiclesFileName, vehicles, noOfVehicleType);
    readStatsData(statsFileName, stats, statsInfo);

    // print info
    printVehicleInfo(vehicles);
    printStatsInfo(stats);

    for(int i = 0; i < days; i++)
        activityEngine.simulateDay(stats, vehicles, statsInfo);

    cout << endl << "noOfVehicleType = " << statsInfo.noOfVehicleType << endl
            << "lengthOfRoad = " << statsInfo.lengthOfRoad << endl
            << "speedLimit = " << statsInfo.speedLimit << endl
            << "noOfParkingSpaces = " << statsInfo.noOfParkingSpaces << endl;

    cout << "numberOfVehicleType = " << noOfVehicleType << endl;

    return 0;
}

//------------------------
// read in data from Vehicles.txt file

void readVehicleData(string vehiclesFileName, std::vector<Vehicle> &vehicles, int &noOfVehicleType) {
    fstream afile;
    //string vehiclesFileName = "Vehicles.txt";

    afile.open(vehiclesFileName.c_str());
    if (!afile) {
        cout << "Cannot open" << vehiclesFileName << ", please cheke the file" << endl;
        exit(-1);
    }

    noOfVehicleType = 0;
    cout << "Read in data from file Vehicles.txt to program" << endl;

    afile>>noOfVehicleType;
    afile.ignore();

    int noOfVehicleItem = 0;
    string line;
    Vehicle aVehicleItem;

    while (!afile.eof()) {
        getline(afile, line);

        char tmp[MAXNO];
        char token [MAXNO][MAXNO];
        strcpy(tmp, line.c_str());

        int i = 0;
        char *p = strtok(tmp, ":");
        while (p != NULL) {
            strcpy(token [i], p);
            p = strtok(NULL, ":");
            ++i;
        }

        aVehicleItem.setName(string(token [0]));
        aVehicleItem.setFlag(atoi(token[1]));
        aVehicleItem.setRego(string(token [2]));
        aVehicleItem.setVolumeWeight(atof(token [3]));
        aVehicleItem.setSpeedWeight(atof(token [4]));

        vehicles.push_back(aVehicleItem);
        noOfVehicleItem++;
    }

    afile.close();
    cout << "Data has been read from file Vehicles.txt" << endl << endl;
}

//------------------------
// read in data from Stats.txt file

void readStatsData(string statsFileName, std::vector<Stats> &stats, StatsInfo &statsInfo) {
    fstream afile;
    //string statsFileName = "Stats.txt";

    afile.open(statsFileName.c_str());
    if (!afile) {
        cout << "Cannot open" << statsFileName << ", please cheke the file" << endl;
        exit(-1);
    }

    cout << "Read in data from file Stats.txt to program" << endl;

    afile >> statsInfo.noOfVehicleType >> statsInfo.lengthOfRoad
            >> statsInfo.speedLimit >> statsInfo.noOfParkingSpaces;
    afile.ignore();

    int noOfStatsItem = 0;
    Stats aStatsItem;
    string line;
    while (!afile.eof()) {
        getline(afile, line);
        char tmp[MAXNO];
        char token [MAXNO][MAXNO];
        strcpy(tmp, line.c_str());

        int i = 0;
        char *p = strtok(tmp, ":");
        while (p != NULL) {
            strcpy(token [i], p);
            p = strtok(NULL, ":");
            ++i;
        }

        aStatsItem.setType(string(token [0]));
        aStatsItem.setNumMean(atof(token [1]));
        aStatsItem.setNumStdDev(atof(token [2]));
        aStatsItem.setSpeedMean(atof(token [3]));
        aStatsItem.setSpeedStdDev(atof(token [4]));

        stats.push_back(aStatsItem);
        noOfStatsItem++;
    }

    afile.close();
    cout << "Data has been read from file Stats.txt" << endl << endl;
}

void printStatsInfo(vector<Stats> stats) {
    cout << endl << "- - - - - - - printStatsInfo - - - - - - -" << endl << endl;

    cout<<"Vehicle Name\tMean Number\tStandard Deviation\tMean Speed\tSpeed SD"<<endl;

    for (vector<Stats>::iterator iter = stats.begin(); iter < stats.end(); ++iter) {
        cout << *iter;
    }
}

void printVehicleInfo(vector<Vehicle> vehicles) {
    cout << endl << "- - - - - - - printVehicleInfo - - - - - - -" << endl << endl;

    cout<<"Vehicle Name\tParking Flag\tReg. Format\tVol Weight\tSpeed Weight\tSpeed\n";

    for (vector<Vehicle>::iterator iter = vehicles.begin(); iter < vehicles.end(); ++iter) {
        cout <<  *iter << std::endl;;
    }
}

void analysisEngine() {

}

void alertEngine() {

}
