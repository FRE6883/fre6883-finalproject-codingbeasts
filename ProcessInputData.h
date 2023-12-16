#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class ProcessInputData{
    private:
        string dataFilePath;
        vector<string> beatsgroup, meetsgroup, missesgroup;
        string earliestAnnc, latestAnnc;
        map<string,string> earningsmap;
        
        // this stores all of the data taken in from the csv file
        vector<vector<string>> data;
        
        // key: ticker
        // value: vector of the date,period_ending,estimate,reported,surprise,surpriseptage data
        map<string,vector<string>> tickerAccess;
        
    public:
        // constructor with parameters
        ProcessInputData(string dataFilePath_):dataFilePath(dataFilePath_){};
        
        // default constructor
        ProcessInputData():dataFilePath(""){};
        
        void setdataFilePath(string input){
            dataFilePath = input;
        }
        
        //string modifyInputDate(string ipdate);
        
        void loadData();
        
        void sortData_fillTickerGroups();
        
        void print1dvec(const vector<string> & vect);
        
        void print2dvector(const vector<vector<string>> & vect);
        
        vector<vector<string>> getDatabase(){
            return data;
        }
        
        vector<string> getBeatsGroup(){
            return beatsgroup;
        }
        
        vector<string> getMeetsGroup(){
            return meetsgroup;
        }
        
        vector<string> getMissessGroup(){
            return missesgroup;
        }
        
        map<string,string> getEarningsMap(){
            return earningsmap;
        }
        
        string earliestAnnouncement(){
            return earliestAnnc;
        }
        
        string latestAnnouncement(){
            return latestAnnc;
        }
        
        
};