#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class IWV{
    private:
        vector<double> idxLevel;
        
        // delete this later; not being used
        vector<double> idxReturn;
        vector<string> dates;
        
        // key-> date
        // value-> idx return
        map<string,double> idxMap;
        
        string startDate = "2022-12-21";
        string endDate = "2023-12-15";
    
    public:
        IWV(){};
        // will give 0 if it ran correctly and will give -1 if it did not run correctly
        
        void populate_idxMap();
        int populate_idxReturn();
        int populate_idxLevel();
        // int returnIWV(string ipstart, string ipend, vector<double> & IWVsubset);
        //vector<double> returnIWV(string ipstart, string ipend) ;
        void displayIWV();
        
        vector<double> returnIWV(string ipstart, string ipend);
};