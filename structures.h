#ifndef STRUCTURES_H
#define STRUCUTRES_H
#include <string>
#include <iostream>
#include <vector>

class Vehicle
{
    public:
        Vehicle() : vehicleName(""), parkingFlag(0), registrationFormat(""), volumeWeight(0), speedWeight(0) {}
        friend std::ostream &operator <<(std::ostream &out, Vehicle v)
        {
            out << v.vehicleName;
            if(v.vehicleName.size()<8)
                out<< "\t\t";
            else
                out<<"\t";
            if( v.parkingFlag == true)
                out<<"True"<< "\t\t";
            else
                out<<"False"<<"\t\t";
            out << v.registrationFormat << "\t\t";
            out << v.volumeWeight << "\t\t";
            out << v.speedWeight << "\n";
            return out;
        }
        void setName(std::string name)   { vehicleName = name; }
        void setFlag(char flag)          { parkingFlag = flag; }
        void setRego(std::string rego)   { registrationFormat = rego; }
        void setVolumeWeight(int weight) { volumeWeight = weight; }
        void setSpeedWeight(int speed)   { speedWeight = speed; }
        void setSpeed(int speed)         { this->speed = speed; }
        void setBeginningTime(int time)  { beginningTime = time; }

        std::string getName() { return vehicleName; }
        char getParkingFlag() { return parkingFlag; }
        std::string getRego() { return registrationFormat; }
        int getVolumeWeight() { return volumeWeight; }
        int getSpeedWeight()  { return speedWeight; }
        int getSpeed()        { return speed; }
        int getBegTime()      { return beginningTime; }
    private:
        std::string vehicleName;
        char parkingFlag;
        std::string registrationFormat;
        int volumeWeight;
        int speedWeight;
        int speed;
        int beginningTime;
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

/*

*/

struct StatsInfo
{
    int noOfVehicleType;
    int lengthOfRoad;
    int speedLimit;
    int noOfParkingSpaces;
};


#endif /* STRUCTURES_H */
