#include<iostream>
#include"flightDataStruct.h"
using namespace std;

string getMealPreference(){
    string choice;
    cout<<"\nDo want meals provided to you during your travel ,It costs additional 200 rs (y/n):";
    while(true){
            cin>>choice;
            if(choice=="y"){
                return "yes";
            }
            else if(choice=="n"){
                return "no";
            }
            else{
                cout<<"\ninvalid entry enter again\n";
            }

        }
}

class flightTicketSystem{
    private:
    flightDataStructure flightds;

    public:
    void bookTicket(){
        string flightName,seatNumber,passengerName,flightClass;
        int age,mealPreference;
        int numberOfTickets;
        passengerDataNode passNode;

        flightName = flightds.getFlightName();
        passNode.flightClass= flightds.getFlightClass();
        numberOfTickets = flightds.getNumberOfTickets();
        //generate booking id
        passNode.bookingID = flightds.getBookingID(flightName,passNode.flightClass,numberOfTickets);
        for(int i=1;i<=numberOfTickets;i++){//we might need to check validity here
            cout<<"\nenter the detals of the passenger "<<i;
            
            cout<<"\nenter the name:";
            cin>>passNode.passengerName;
            cout<<"\nenter the age:";
            cin>>passNode.age;

            passNode.mealPreference = getMealPreference();

            passNode.seatNumber = flightds.getSeatNumber(flightName,passNode.flightClass);
            //check with the booking id details because we need a collective booking id generation
            //the arguement below then can extend to booking id generation too
            flightds.addPassenger(flightName,passNode);

        }
        cout<<"\nyour booking id is:"<<passNode.bookingID;
        flightds.updateRate(flightName,passNode.flightClass );

        flightds.updateDataBase();



    }

    void cancelTicket(){
        int numberOfTickets;
        string seatNumber;
        string bookingID;
        string flightName;
        string flightClass;
        flightName = flightds.getFlightName();
        bookingID = flightds.getBookingID();
        flightClass = flightds.getFlightClass();
        //cout<<"\nenter the number of tickets to be cancelled:";
        numberOfTickets = flightds.getNumberOfTicketsCancellation(bookingID);

        for(int i=1; i <= numberOfTickets;i++){
            flightds.removePassenger(flightName,bookingID,flightClass);
        }
        cout<<"cancel process sucessfull";

        flightds.updateDataBase();
    }

    void checkSeatAvailability(){
        cout<<"\nseat availability under maintenance";
    }

    void getMealDetails(){
        cout<<"\nunder development";
    }

    void getFlightSummary(){
        cout<<"under development";
        
    }

    void initiateSystem(){
        int choice=0;
        while(choice!=6){
            cout<<"\nMAIN MENU:";
            cout<<"\n1.Book ticket\n2.Cancel ticket\n3.Check seat availability\n4.print meal details\n5.Flight summary\n6.Exit";
        
            cout<<"\n\nEnter a number and press enter:";
            cin>>choice;
            switch (choice)
            {
            case 1:
                bookTicket();
                break;
            case 2:
                cancelTicket();
                break;
            case 3:
                checkSeatAvailability();
                break;
            case 4:
                getMealDetails();
                break;
            case 5:
                getFlightSummary();
                break;
            case 6:
                cout<<"\nThank you!";
                break;
            default:
                cout<<"\nInvalid entry!";
                choice = 6;
                break;
            }
        }
    }

};