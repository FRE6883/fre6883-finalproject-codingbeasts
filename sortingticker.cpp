#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;


bool sortcol(const vector<string>& v1, const vector<string>& v2){
    double val1 = stod(v1[1]);
    double val2 = stod(v2[1]);
    
    return val1>val2;
}

void print1dvec(const vector<string> & vect){
    for(int i=0;i<vect.size();i++){
        cout << vect[i] << " ";
    }
}

void printVector(const vector<vector<string>> & vect){
    for (int i = 0; i < vect.size(); i++) {
        for (int j = 0; j < vect[i].size(); j++)
            cout << vect[i][j] << " ";
        cout << endl;
    }
}

// WILL NEED TO CHANGE THIS INPUT TO PUSH 1000 INSTEAD OF 10 FOR EACH CLASS
void inputData(const vector<vector<string>> data, vector<string> & beats, vector<string> & meets, vector<string> & misses){
    
    int size = data.size();
    
    if(size!=3000){
        cout << size << endl;
        cout << "size not 3000";
        //return -1;
    }
    else{
        cout << "size correct";
    }
    
    // WILL NEED TO CHANGE THESE INDEXES
    //FOR rinput1.csv test file
    for(int i=0;i<data.size();i++){
        if(i>=0 && i<=9){
            beats.push_back(data[i][0]);
        } 
        else if(i>=10 && i<=19){
            meets.push_back(data[i][0]);
        } 
        else{
            misses.push_back(data[i][0]);
        }
    }
    
    // // for main rinput 3000 data points file
    // for(int i=0;i<data.size();i++){
    //     if(i>=0 && i<=999){
    //         beats.push_back(data[i][0]);
    //     } 
    //     else if(i>=1000 && i<=1999){
    //         meets.push_back(data[i][0]);
    //     } 
    //     else{
    //         misses.push_back(data[i][0]);
    //     }
    // }
}

int main(){
    // cout << "hello world" << endl;
    
    
    vector<string> beats;
    vector<string> meets;
    vector<string> misses;
    
    ifstream inputFile;
    
    inputFile.open("rinput1.csv");
    
    string line = "";
    
    vector<vector<string>> data;
    
    //cout << "running " << endl;
    
    while(getline(inputFile, line)){
        vector<string> input;
        
        string ticker,date,period_ending;
        string tempString;
        double estimate,reported,surprise,surpriseptage;
        
        stringstream inputString(line);
        
        getline(inputString, ticker, ',');
        input.push_back(ticker);
        
        getline(inputString, date, ',');
        getline(inputString, period_ending, ',');
        
        getline(inputString, tempString, ',');
        estimate = atof(tempString.c_str());
        
        getline(inputString, tempString, ',');
        reported = atof(tempString.c_str());
        
        getline(inputString, tempString, ',');
        surprise = atof(tempString.c_str());
        
        getline(inputString, tempString, ',');
        surpriseptage = atof(tempString.c_str());
        input.push_back(to_string(surpriseptage));
        
        
        
        cout << ticker << " " << surpriseptage << endl; 
        
        data.push_back(input);
        
        line = "";
    }
    
    data.erase(data.begin());
    
    cout << "data acquired:" << endl;
    
    
    cout << "before sort:" << endl;
    printVector(data);
    
    sort(data.begin(), data.end(), sortcol);
    cout << "after sort:" << endl;
    printVector(data);
    
    inputData(data, beats, meets, misses);
    
    
    cout << "\nbeats vector:" << endl;
    
    print1dvec(beats);
    
    cout << "\nmeets vector:" << endl;
    
    print1dvec(meets);
    
    cout << "\nmisses vector:" << endl;
    
    print1dvec(misses);
    
    return 0;
}