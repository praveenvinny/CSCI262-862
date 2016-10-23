#ifndef STRUCTURES_H
#define STRUCUTRES_H
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

static void replaceStr(std::string &input, char value)
{
    char startVal;
    int offset;
    if(value == 'L')
    {
        startVal = 'A';
        offset = 26;
    }
    else
    {
        startVal = '0';
        offset = 9;
    }
    char replace;
    for(unsigned int i = 0; i < input.size(); i++)
    {
        replace = startVal + rand() % offset;
        if(input[i] == value)
            input[i] = replace;
    }
}

class Vehicle
{
    public:
        Vehicle() : vehicleName(""), parkingFlag(0), registration(""), volumeWeight(0), speedWeight(0) {}
        friend std::ostream &operator <<(std::ostream &out, Vehicle v)
        {
            out << v.vehicleName;
            if(v.vehicleName.size()<8)
                out<< "\t\t";
            else
                out<<"\t";
            if( v.parkingFlag == 1)
                out<<"True"<< "\t\t";
            else
                out<<"False"<<"\t\t";
            out << v.registration << "\t\t";
            out << v.volumeWeight << "\t\t";
            out << v.speedWeight << "\n";
            return out;
        }
        void setName(std::string name)   { vehicleName = name; }
        void setFlag(int flag)          { parkingFlag = flag; }
        void setRego(std::string rego)   { registration = rego; }
        void setVolumeWeight(int weight) { volumeWeight = weight; }
        void setSpeedWeight(int speed)   { speedWeight = speed; }
        void setSpeed(int speed)         { this->speed = speed; }
        void setBeginningTime(int time)  { beginningTime = time; }
        void setParked(bool val)         { isParked = val; }
        void generateRego()
        {
            replaceStr(registration, 'L');
            replaceStr(registration, 'D');
        }

        std::string getName() { return vehicleName; }
        int getParkingFlag() { return parkingFlag; }
        std::string getRego() { return registration; }
        int getVolumeWeight() { return volumeWeight; }
        int getSpeedWeight()  { return speedWeight; }
        int getSpeed()        { return speed; }
        int getBegTime()      { return beginningTime; }
        bool isVehicleParked()       { return isParked; }
    private:
        std::string vehicleName;
        int parkingFlag;
        std::string registration;
        int volumeWeight;
        int speedWeight;
        int speed;
        int beginningTime;
        bool isParked;
};

class Stats
{
    public:
        Stats() : vehicleType(""), numberMean(0), numberStdDev(0), speedMean(0), speedStdDev(0){};
        friend std::ostream &operator <<(std::ostream &out, Stats s)
        {
            out << s.vehicleType;
            if(s.vehicleType.size()<8)
                out<< "\t\t";
            else
                out<<"\t";
            out << s.numberMean << "\t\t";
            out << s.numberStdDev << "\t\t\t";
            out << s.speedMean << "\t\t";
            out << s.speedStdDev << std::endl;
            return out;
        }
        void setType(std::string type)  { vehicleType = type; }
        void setNumMean(int mean)       { numberMean = mean; }
        void setNumStdDev(int nsd)      { numberStdDev = nsd; }
        void setSpeedMean(int mean)     { speedMean = mean; }
        void setSpeedStdDev(int speed)  { speedStdDev = speed; }

        std::string getType()       { return vehicleType; }
        int getNumMean()    { return numberMean; }
        int getNumStdDev()  { return numberStdDev; }
        int getSpeedMean()  { return speedMean; }
        int getSpeedStdDev(){ return speedStdDev; }
    private:
        std::string vehicleType;
        int numberMean;
        int numberStdDev;
        int speedMean;
        int speedStdDev;
};

struct StatsInfo
{
    int noOfVehicleType;
    int lengthOfRoad;
    int speedLimit;
    int noOfParkingSpaces;
};


#endif /* STRUCTURES_H */
