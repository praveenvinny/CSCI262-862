#include <iostream>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <cstring>
#include "structures.h"

using namespace std;

const int MAXNO = 90;

// global variables definition
vector <Vehicle> vehicles;
vector <Stats> stats;

StatsInfo statsInfo;
int noOfVehicleType;
int days;

// functions definition
void readVehicleData(string);
void readStatsData(string);

void printVehicleInfo();
void printStatsInfo();



void activityEngine();
void analysisEngine();
void alertEngine();

int main(int argc, char *argv[]) {
    /*
        if(argc != 4)
        {
            cout << "Please check the arguments, the program will end" << endl;
            exit(-1);
        }

        string vehiclesFileName = string(argv[1]);
        string statsFileName = string(argv[2]);
        days = atoi(argv[3]);

        cout<<"argc = "<<argc<<endl;
        cout<<"argv[0] = "<<argv[0]<<endl;
        cout<<"argv[1] = "<<argv[1]<<endl;
        cout<<"argv[2] = "<<argv[2]<<endl;
        cout<<"argv[3] = "<<argv[3]<<endl;
     */

    string vehiclesFileName = "Vehicles.txt";
    string statsFileName = "Stats.txt";
    days = 3;


    cout << "vehiclesFileName = " << vehiclesFileName << endl;
    cout << "statsFileName = " << statsFileName << endl;
    cout << "days = " << days << endl << endl;

    // read in all data from text file
    readVehicleData(vehiclesFileName);
    readStatsData(statsFileName);

    // print info
    printVehicleInfo();
    printStatsInfo();


    cout << endl << "noOfVehicleType = " << statsInfo.noOfVehicleType << endl
            << "lengthOfRoad = " << statsInfo.lengthOfRoad << endl
            << "speedLimit = " << statsInfo.speedLimit << endl
            << "noOfParkingSpaces = " << statsInfo.noOfParkingSpaces << endl;

    cout << "numberOfVehicleType = " << noOfVehicleType << endl;

    return 0;
}

//------------------------
// read in data from Vehicles.txt file

void readVehicleData(string vehiclesFileName) {
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
        aVehicleItem.setFlag(*token[1]);
        aVehicleItem.setRego(string(token [2]));
        aVehicleItem.setWeight(atoi(token [3]));
        aVehicleItem.setSpeed(atoi(token [4]));

        vehicles.push_back(aVehicleItem);
        noOfVehicleItem++;
    }

    afile.close();
    cout << "Data has been read from file Vehicles.txt" << endl << endl;
}

//------------------------
// read in data from Stats.txt file

void readStatsData(string statsFileName) {
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
        aStatsItem.setNumMean(atoi(token [1]));
        aStatsItem.setNumStdDev(atoi(token [2]));
        aStatsItem.setSpeedMean(atoi(token [3]));
        aStatsItem.setSpeedStdDev(atoi(token [4]));

        stats.push_back(aStatsItem);
        noOfStatsItem++;
    }

    afile.close();
    cout << "Data has been read from file Stats.txt" << endl << endl;
}

void printStatsInfo() {
    cout << endl << "- - - - - - - printStatsInfo - - - - - - -" << endl << endl;

    cout<<"Vehicle Name\tMean Number\tStandard Deviation\tMean Speed\tSpeed SD"<<endl;

    for (vector<Stats>::iterator iter = stats.begin(); iter != stats.end(); ++iter) {
        cout << *iter;
    }
}

void printVehicleInfo() {
    cout << endl << "- - - - - - - printVehicleInfo - - - - - - -" << endl << endl;

    cout<<"Vehicle Name\tParking Flag\tReg. Format\tVol Weight\tSpeed Weight\n";

    for (vector<Vehicle>::iterator iter = vehicles.begin(); iter != vehicles.end(); ++iter) {
        cout <<  *iter;
    }
}

void activityEngine() {

}

void analysisEngine() {

}

void alertEngine() {

}
