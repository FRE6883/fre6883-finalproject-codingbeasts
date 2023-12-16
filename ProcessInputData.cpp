#include "ProcessInputData.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

// we are sorting the data table using the last column of surprize% as the basis
bool sortcol(const vector<string>& v1, const vector<string>& v2){
    double val1 = stod(v1[v1.size()-1]);
    double val2 = stod(v2[v2.size()-1]);
    
    return val1>val2;
}

void ProcessInputData::print1dvec(const vector<string> & vect){
    for(int i=0;i<vect.size();i++){
        cout << vect[i] << " ";
    }
}

void ProcessInputData::print2dvector(const vector<vector<string>> & vect){
    for (int i = 0; i < vect.size(); i++) {
        for (int j = 0; j < vect[i].size(); j++)
            cout << vect[i][j] << " ";
        cout << endl;
    }
}

void printMap(map<string,string> earningsmap){
    map<string,string>::iterator itr;
    
    cout << "the earnings map is:";
    
    for(itr=earningsmap.begin();itr!=earningsmap.end();itr++){
        cout << itr->first << " " << itr->second << endl;
    }
}

void inputData(const vector<vector<string>> data, vector<string> & beats, vector<string> & meets, vector<string> & misses){
    for(int i=0;i<data.size();i++){
        if(i>=0 && i<=786){
            beats.push_back(data[i][0]);
        } 
        else if(i>=787 && i<=1659){
            meets.push_back(data[i][0]);
        } 
        else{
            misses.push_back(data[i][0]);
        }
    }
    
    // this for loop is for the test input size of 30
    // for(int i=0;i<data.size();i++){
    //     if(i>=0 && i<=9){
    //         beats.push_back(data[i][0]);
    //     } 
    //     else if(i>= && i<=19){
    //         meets.push_back(data[i][0]);
    //     } 
    //     else{
    //         misses.push_back(data[i][0]);
    //     }
    // }
}

// string convertMonth(string inputmo){
//     if(inpoutmo=="May"){
//         return "05";
//     }
//     if(inpoutmo=="Jun"){
//         return "06";
//     }
//     if(inpoutmo=="Jul"){
//         return "07";
//     }
//     if(inpoutmo=="Aug"){
//         return "08";
//     }
//     if(inpoutmo=="Sep"){
//         return "09";
//     }
//     if(inpoutmo=="Oct"){
//         return "10";
//     }
// }

// string ProcessInputData::modifyInputDate(string ipdate){
//     string date;
//     string month;
//     string year;
            
//             int first = ipdate.find_first_of('-');
//             int second = ipdate.find_last_of('-');
            
//             datex = ipdate.substr(0,first);
            
//             month = ipdate.substr(first+1,second-first-1);
            
//             year = ipdate.substr(second+1);
            
//             //year = ipdate.substr(second+1,second+3);
            
//             cout << "date: " << date << " month: " << month << " year:" << year << endl;
            
//             year = "20" + year;
            
//             return "";
// }


void ProcessInputData::loadData(){
    ifstream inputFile;
    inputFile.open(dataFilePath);
    
    string line = "";
    
    //int counter = 0;
    
    while(getline(inputFile, line)){
        vector<string> input;
        vector<string> tickerVal;
        
        // ticker,date,period_ending,estimate,reported,surprise,surprise%
        string ticker,date,period_ending,estimate,reported,surprise,surpriseptage;
        
        stringstream inputString(line);
        getline(inputString, ticker, ',');
        input.push_back(ticker);
        
        //cout << "ticker is: " << ticker << endl;
        
        getline(inputString, date, ',');
        
        if(date.size()==8){
            date= "0" + date;
            //cout << date << endl;
        }
        
        input.push_back(date);
        tickerVal.push_back(date);
        
        getline(inputString, period_ending, ',');
        input.push_back(period_ending);
        tickerVal.push_back(period_ending);
        
        getline(inputString, estimate, ',');
        input.push_back(estimate);
        tickerVal.push_back(estimate);
        
        getline(inputString, reported, ',');
        input.push_back(reported);
        tickerVal.push_back(reported);
        
        getline(inputString, surprise, ',');
        input.push_back(surprise);
        tickerVal.push_back(surprise);
        
        getline(inputString, surpriseptage, ',');
        input.push_back(surpriseptage);
        tickerVal.push_back(surpriseptage);
        
        //cout << ticker << " " << surpriseptage << endl; 
        
        data.push_back(input);
        
        tickerAccess[ticker] = tickerVal;
        
        earningsmap[ticker] = date;
        

        line = "";
    }
    
    // removing the column headers
    //data.erase(data.begin());
    
    cout << "data acquired:" << endl;
    
    cout << "mapotained" << endl;
    
    //printMap(earningsmap);
}

void ProcessInputData::sortData_fillTickerGroups(){
    // cout << "before sort:" << endl;
    // print2dvector(data);
    
    sort(data.begin(), data.end(), sortcol);
    // cout << "after sort:" << endl;
    // print2dvector(data);
    
    inputData(data, beatsgroup, meetsgroup, missesgroup);
    
    // cout << "\nbeats vector:" << endl;
    
    // print1dvec(beatsgroup);
    
    // cout << "\nmeets vector:" << endl;
    
    // print1dvec(meetsgroup);
    
    // cout << "\nmisses vector:" << endl;
    
    // print1dvec(missesgroup);
}