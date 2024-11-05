#include<iostream>
#include<vector>
#include"flightData.h"
#include"parser.h"
using namespace std;



class flightDataStructure{
    private:
    int x;
    vector<flightDataNode> flightData;   //this the data of all the flight records in the flight
    public:
    void test_printer(){
        parser parsingObj;
        flightDataNode node;
        vector<flightDataNode>::iterator it = flightData.begin();
        do
        {
            node = *it;
            parsingObj.dataPrinter(node);
            parsingObj.passengerDataPrinter(node.passengerDataEconomy);
            parsingObj.passengerDataPrinter(node.passengerDataBusiness);
            it++;
        } while (it!=flightData.end());
        

    }
    flightDataStructure(){
        //we load the txt database to object here
        //we shall make a class and use it here
        parser parsingObj;
        flightData = parsingObj.loadData();
        //test_printer();
    }
    /*********************************************************************
     * functions used for ticket booking
     *********************************************************************/

    string getFlightName(){ //gets flight number from user we should also check the validity as well as availability
        string flightName;
        cout<<"\nenter flight number:";
        cin>>flightName;
        return flightName;
    }

    string getFlightClass(){
        string flightClass;
        int choice;
        cout<<"\nSelect the flight class, select a choice\n1.Economy class 2.Business class:";
        while(true){
            cin>>choice;
            if(choice==1){
                flightClass = "Economy";
                break;
            }
            else if(choice==2){
                flightClass = "Business";
                break;
            }
            else{
                cout<<"\ninvalid entry enter again\n";
            }

        }
        return flightClass;
    }

    int getNumberOfTickets(){//check validity and availability
        int numberOfTickets;
        cout<<"\nenter number of tickets to purchased:";
        cin>>numberOfTickets;
        return numberOfTickets;
    }

    string getBookingID(string flightName,string flightClass,int numberOfTickets){
        string BookingID;
        BookingID= flightName;

        BookingID = BookingID + intToString(numberOfTickets);

        flightDataNode node;
        vector<flightDataNode>::iterator it = flightData.begin();
        do
        {
            node = *it;
            if(flightName==node.flightName){
                if(flightClass=="Economy"){
                    BookingID = BookingID + "eco"+ intToString(node.Economy.SeatsRemain);
                    BookingID = BookingID + intToString(node.Economy.Rate);
                    }
                else{
                    BookingID = BookingID + "bus" + intToString(node.Business.SeatsRemain);
                    BookingID = BookingID + intToString(node.Business.Rate);
                }

            }
            it++;
        } while (it!=flightData.end());

        return BookingID;

    }

    string getSeatNumber(string flightName,string flightClass){
        //get flight node ... flightData
        passengerDataNode passdata;
        //flightDataNode node;
        string seatNumber;
        flightDataNode node;


        int flag = 0;
        while(flag == 0){
        flag =1;
    
        //node = getFlightNode(flightName);
        cout<<"\nenter seat number:";
        cin>>seatNumber;
        vector<flightDataNode>::iterator it = flightData.begin();
        do
        {
            node = *it;
            if(node.flightName==flightName){
                if(flightClass == "Economy"){
                    vector<passengerDataNode>::iterator it2 = node.passengerDataEconomy.begin();
                    do{
                        passdata = *it2;
                        if(passdata.seatNumber == seatNumber){
                            cout<<"\nseat number already taken enter again:";
                            flag =0;
                            break;
                        }
                        it2++;
                    }while(it2 != node.passengerDataEconomy.end());
                    
                }

                if(flightClass == "Business"){

                }
            }
            it++;
        } while (it!=flightData.end());

        }
        return seatNumber;

    }

    void addPassenger(string flightName,passengerDataNode passNode){
        //bookingid is generated
        cout<<"\nticket booking successfull!";

        flightDataNode node;
        vector<flightDataNode>::iterator it = flightData.begin();
        if(passNode.mealPreference=="yes"){
            passNode.ticketRate=200;
        }
        else{
            passNode.ticketRate=0;
        }
        do
        {
            node = *it;
            if(node.flightName == flightName){
                if(passNode.flightClass=="Economy"){
                    passNode.ticketRate = passNode.ticketRate + node.Economy.Rate;
                    node.Economy.SeatsRemain = node.Economy.SeatsRemain - 1;
                    node.passengerDataEconomy.push_back(passNode);
                }
                else{
                    passNode.ticketRate = passNode.ticketRate + node.Business.Rate;
                    node.Business.SeatsRemain =node.Business.SeatsRemain- 1;
                    node.passengerDataBusiness.push_back(passNode);
                }
            }
            *it=node;
            it++;
        } while (it!=flightData.end());
        //cout<<"heloooo";

        //show ticket status
        
    }

    void updateRate(string flightName,string flightClass){
        vector<flightDataNode>::iterator it = flightData.begin();
        flightDataNode node;
        do
        {
            node = *it;
            if(node.flightName == flightName){
                if(flightClass=="Economy"){
                    node.Economy.Rate = node.Economy.Rate + 100;
                }
                else{
                    node.Business.Rate = node.Business.Rate + 200;
                }
            }
            *it=node;
            it++;
        } while (it!=flightData.end());

    }
    /****************************************************************
    * functions containing ticket cancellation below
    ****************************************************************/
   
    string getBookingID(){
        string bookingID;
        int numberOfTickets;
        cout<<"\nenter the booking id:";
        cin>>bookingID;  //verificaaation need to be done
        cout<<"\npassengers details of tickets under the respective booking id are:"; //display the details
        return bookingID;
    }

    int getNumberOfTicketsCancellation(string BookingID){
        //checking validity
        int numberOfTickets;
        cout<<"\nenter number of tickets to cancelled:";
        cin>>numberOfTickets;
        return numberOfTickets;
    }

    string getSeatNumberCancellation(string bookingID){
        string SeatNumber;
        cout<<"\nenter the seat number";
        cin>>SeatNumber;
        return SeatNumber;
        //check validity
    }

    void removePassenger(string flightName,string bookingID,string flightClass){
        vector<flightDataNode>::iterator it = flightData.begin();
        flightDataNode node;
        string seatNumber;
        cout<<"\nenter seat number to be deleted:";
        cin>>seatNumber;
        do
        {
            node = *it;
            if(node.flightName == flightName){
                if(flightClass=="Economy"){
                    vector<passengerDataNode>::iterator itp = node.passengerDataEconomy.begin();
                    passengerDataNode nodep;
                    do
                    {
                        nodep = *itp;
                        if(nodep.bookingID==bookingID){

                            if(seatNumber==nodep.seatNumber){
                                node.passengerDataEconomy.erase(itp);
                                break;
                            }
                        }
                        itp++;
                    } while (itp!=node.passengerDataEconomy.end());
                    node.Economy.SeatsRemain = node.Economy.SeatsRemain + 1;


                }
                else{
                    vector<passengerDataNode>::iterator itp = node.passengerDataBusiness.begin();
                    passengerDataNode nodep;
                    do
                    {
                        nodep = *itp;
                        if(nodep.bookingID==bookingID){
                            if(seatNumber==nodep.seatNumber){
                                node.passengerDataBusiness.erase(itp);
                                break;
                            }
                        }
                        itp++;
                    } while (itp!=node.passengerDataBusiness.end());
                    node.Business.SeatsRemain = node.Business.SeatsRemain + 1;
                }
            }
            *it=node;
            it++;
        } while (it!=flightData.end());
        cout<<"\nticket cancelled";
    }
    /*
    this portion below contains other components of operations needed for the system
    */
    int seatFree(flightDataNode node,string SeatNumber,string flightClass){
        int status=1;
        if(flightClass == "Economy"){
            if(checkSeatEqual(SeatNumber,node.passengerDataEconomy)==1){
                cout<<"seat already exists\n";
                status = 0;
            }

        }
        else{
            if(checkSeatEqual(SeatNumber,node.passengerDataBusiness)==1){
                cout<<"seat already exists\n";
                status = 0;
            }

        }
        return status;
    }

    int checkSeatEqual(string SeatNumber,vector<passengerDataNode> passengerData){
        int status=0;
        passengerDataNode passNode;
        vector<passengerDataNode>:: iterator it = passengerData.begin();
        do{
            passNode=*it;
            if(passNode.seatNumber == SeatNumber){
                status = 1;
                break;
            }

        }while(it!=passengerData.end());
        return status;
    }

    void updateDataBase(){
        parser parsingObj;
        flightDataNode node;
        vector<flightDataNode>::iterator it = flightData.begin();
        string flightName;
        do
        {
            node = *it;
            flightName = node.flightName;
            flightName = "./flightDetails/" + flightName + ".txt";
            //cout<<"\nflight path"<<flightName;
            parsingObj.writeBack(node,flightName);
            it++;
        } while (it!=flightData.end());
   }

    flightDataNode getFlightNode(string flightName){

        flightDataNode node;
        vector<flightDataNode>::iterator it = flightData.begin();
        do
        {
            node = *it;
            if(node.flightName==flightName){
                return node;
            }
            it++;
        } while (it!=flightData.end());
        return node;
    }

   flightDataNode flightDataFinder(string flightName){
       flightDataNode node;
       vector<flightDataNode>::iterator it = flightData.begin();

        do
        {
            node = *it;
            if(node.flightName == flightName){
                return node;
            }
            *it=node;
            it++;
        } while (it!=flightData.end());

   }


};