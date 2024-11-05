//data as text file parsed to object file here

#include<iostream>
//#include"flightData.h"  //including this file will cause redeifinition error as its already declared in flightdatastructure module
#include<string.h>
#include<stdlib.h>
#include<fstream>
#include<vector>
#include<sstream>

int stringToInt(string stringValue){
  //this function converts the string to int
  int number;

  stringstream converter(stringValue);
  converter>>number;
  
  return number;
}

string intToString(int number){
  string str;
  stringstream converter;
  converter<<number;
  converter>>str;

  return str;

}

class parser{
    public:
    vector<flightDataNode> loadData()
    {
        
        vector<flightDataNode> flightData;
        //this reads the meta file that has the list of all the flights data
        vector<string> flightFileName;
        flightFileName = getFlightFileName();
        flightDataNode flightNode;

        vector<string>::iterator it=flightFileName.begin();
        /* test successfull flightFile name is there
        do{
            cout<<*it<<"\n";
            it++;
        }while(it!=flightFileName.end());
        */
        string flightName;
        do{
            flightName = *it;
            flightName = "./flightDetails/" + flightName + ".txt";
            flightNode = getFlightData(flightName); 
            flightData.push_back(flightNode);
            it++;
        }while(it!=flightFileName.end());
        return flightData;
    }

    vector<string> getFlightFileName()
    {   //reads the data from meta file and gets the all the flight names
        vector<string> flightFileName;
        ifstream MyReadFile("flightNames.txt");
        string myText;
        cout<<"\navailable flights:";
        while (getline (MyReadFile, myText)) {
            // Output the text from the file
            // cout << myText<<"\n";
            flightFileName.push_back(myText);
            cout<<myText<<" ";
            }
        MyReadFile.close();

        return flightFileName;
    }

    flightDataNode getFlightData(string flightName){
        string myText;
        vector<string> line;

        flightDataNode node;

        // Read from the text file
        ifstream MyReadFile(flightName);

        // Use a while loop together with the getline() function to read the file line by line
        while (getline (MyReadFile, myText)) {
        // Output the text from the file
        // cout << myText<<"\n";
            line.push_back(myText);
        }
        MyReadFile.close();
        //vector<string>::iterator it=line.begin();
        //cout<<*(it+16)<<"\n\n";


        node = DataCollector(line);
        //dataPrinter(node);
        //passengerDataPrinter(node.passengerDataEconomy);
        //passengerDataPrinter(node.passengerDataBusiness);
        return node;
    }

    flightDataNode DataCollector(vector<string> line){
        flightDataNode node;

        node.flightName = line[1];   

        //cout<<line[1];

        
        node.Economy.SeatStruct = line[3];
        node.Economy.Rate = stringToInt(line[4]);
        node.Economy.seatsTotal = stringToInt(line[5]);
        node.Economy.SeatsRemain = stringToInt(line[6]);

        node.Business.SeatStruct = line[9];
        node.Business.Rate = stringToInt(line[10]);
        node.Business.seatsTotal = stringToInt(line[11]);
        node.Business.SeatsRemain = stringToInt(line[12]);

        vector<string>::iterator it=line.begin();
        it=it+16;
        while(*it!="</data>"){
            passengerDataNode passengerNode;
            //cout<<"\n"<<*it;
            passengerNode.passengerName=*(it+1);
            passengerNode.age=stringToInt(*(it+2));
            passengerNode.ticketRate=stringToInt(*(it+3));
            passengerNode.mealPreference=*(it+4);
            passengerNode.seatNumber=*(it+5);
            passengerNode.flightClass=*(it+6);
            passengerNode.bookingID=*(it+7);

            //cout<<"\n tetstttetet: "<<passengerNode.passengerName;

        if(*(it+6)=="Economy"){
            node.passengerDataEconomy.push_back(passengerNode);
        }
        else{
            node.passengerDataBusiness.push_back(passengerNode);
        }
        it=it+9;
        }
  return node;
}

void dataPrinter(flightDataNode node){
  cout<<node.flightName<<"\n";
  cout<<node.Economy.SeatStruct<<"\n"; 
  cout<<node.Economy.Rate<<"\n";
  cout<<node.Economy.seatsTotal<<"\n";
  cout<<node.Economy.SeatsRemain<<"\n";

  cout<<node.Business.SeatStruct<<"\n";
  cout<<node.Business.Rate<<"\n";
  cout<<node.Business.seatsTotal<<"\n";
  cout<<node.Business.SeatsRemain<<"\n";


}

void passengerDataPrinter(vector<passengerDataNode> passengerData){
  cout<<"\npassenger detail printer:\n";
  passengerDataNode passNode;
  vector<passengerDataNode>::iterator it = passengerData.begin();
  if(!passengerData.empty())
  {
  do{
    passNode = *it;
    cout<<"\n\n"<<passNode.passengerName;
    cout<<"\n"<<passNode.age;
    cout<<"\n"<<passNode.seatNumber;
    cout<<"\n"<<passNode.mealPreference;
    cout<<"\n"<<passNode.ticketRate;
    cout<<"\n"<<passNode.flightClass;
    cout<<"\n"<<passNode.bookingID;
    it++;
  }while(it!=passengerData.end());
  }
  else{
    cout<<"\nempty data";
  }


}

void writeBack(flightDataNode node,string fileName){
  string myText;
  vector<string> line;
  //we gonna test write back
  ofstream myFile(fileName,ios::trunc);
  //myFile<<"hello"<<endl<<"there";

  myFile<<"<meta>"<<endl<<node.flightName<<endl;

  myFile<<"<economy>"<<endl;
  myFile<<node.Economy.SeatStruct<<endl<<intToString(node.Economy.Rate)<<endl;
  myFile<<intToString(node.Economy.seatsTotal)<<endl<<intToString(node.Economy.SeatsRemain)<<endl;
  myFile<<"</economy>"<<endl;

  myFile<<"<business>"<<endl;
  myFile<<node.Business.SeatStruct<<endl<<intToString(node.Business.Rate)<<endl;
  myFile<<intToString(node.Business.seatsTotal)<<endl<<intToString(node.Business.SeatsRemain)<<endl;
  myFile<<"</business>"<<endl;
  myFile<<"</meta>"<<endl;

  myFile<<"<data>"<<endl;
  passengerDataNode passNode;
  vector<passengerDataNode> passengerData;
  
  passengerData = node.passengerDataEconomy;
  vector<passengerDataNode>::iterator it = passengerData.begin() ;
  if(!passengerData.empty())
  {
    do{
      myFile<<"<entry>"<<endl;
      passNode = *it;
      myFile<<passNode.passengerName<<endl;
      myFile<<passNode.age<<endl;
      myFile<<passNode.ticketRate<<endl;
      myFile<<passNode.mealPreference<<endl;
      myFile<<passNode.seatNumber<<endl;
      myFile<<passNode.flightClass<<endl;
      myFile<<passNode.bookingID<<endl;
      myFile<<"</entry>"<<endl;
      it++;
    }while(it!=passengerData.end());
  }

  passengerData = node.passengerDataBusiness;
  it = passengerData.begin() ;
  if(!passengerData.empty())
  {
    do{
      myFile<<"<entry>"<<endl;
      passNode = *it;
      myFile<<passNode.passengerName<<endl;
      myFile<<passNode.age<<endl;
      myFile<<passNode.ticketRate<<endl;
      myFile<<passNode.mealPreference<<endl;
      myFile<<passNode.seatNumber<<endl;
      myFile<<passNode.flightClass<<endl;
      myFile<<passNode.bookingID<<endl;
      myFile<<"</entry>"<<endl;
      it++;
    }while(it!=passengerData.end());
  }
  myFile<<"</data>";
  myFile.close();
}


};