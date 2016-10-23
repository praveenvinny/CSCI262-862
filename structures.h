#ifndef STRUCTURES_H
#define STRUCUTRES_H
#include <string>
#include <iostream>

class Vehicle
{
    public:
        Vehicle() : vehicleName(""), parkingFlag(0), registrationFormat(""), volumeWeight(0), speed(0) {}
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
            out << v.speed << "\n";
            return out;
        }
        void setName(std::string name)  { vehicleName = name; }
        void setFlag(char flag)          { parkingFlag = flag; }
        void setRego(std::string rego)  { registrationFormat = rego; }
        void setWeight(int weight)      { volumeWeight = weight; }
        void setSpeed(int speed)        { this->speed = speed; }
    private:
        std::string vehicleName;
        char parkingFlag;
        std::string registrationFormat;
        int volumeWeight;
        int speed;
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
