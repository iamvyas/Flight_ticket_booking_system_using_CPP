/*
Contains all the datatype and structure used for the software
*/

#include<iostream>
#include<vector> 
using namespace std;

class flightClassNode{
    public:
    string SeatStruct;
    int Rate;
    int seatsTotal;
    int SeatsRemain;

};

struct passengerDataNode{
    string passengerName;
    int age;
    int ticketRate;
    string mealPreference;
    string seatNumber;
    string flightClass; //business or economic
    string bookingID;
};

class flightDataNode{
    public:
    string flightName;
    flightClassNode Business;
    flightClassNode Economy;
    vector<passengerDataNode> passengerDataEconomy;
    vector<passengerDataNode> passengerDataBusiness;  
    
};

/*
this bizzare tehe variable usage is gonna be

flightData.flightMetaData.economySeatStruct=25

flightData.passengerData.push_back(2)

maybe is should find a way to do every operations inside the flightDataNode itself
*/