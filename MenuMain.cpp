#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <stdexcept> 
#include <iomanip>
#include <vector>
#include <map>
#include <chrono>
#include <sstream> 
#include <typeinfo>
#include "ReadLoadData.h"
#include "Stock_indv.h"
#include "Group.h"
#include "bootstrap.h"
#include "Matrix.h"
#include <thread>

using namespace std;
using namespace std::chrono;
using namespace fre;

String SetN(int N, map<string, Stock_indv> &s_map_)
{

    auto ITR = s_map_.begin();
    
    String skipped_tickers;
    
    for(;ITR != s_map_.end(); ITR++)
    {
        int flag = (ITR->second).SetN(N);
        if(flag == -1)
        {
            skipped_tickers.push_back(ITR->first);
            
        }
        
    }
    
    cout<<"\nNo. of stocks with no data for given n (will be skipped): "<<skipped_tickers.size()<<endl;
    cout<<"Tickers for these stocks: "<<endl;
    for(int i = 0; i < (int)skipped_tickers.size(); i++)
    {
        cout<<setw(10)<<setfill(' ')<<skipped_tickers[i]<<" ";
        if((i+1)%10 == 0)
            cout<<endl;
        
    }
    return skipped_tickers;
}

void CalAbnormalReturns(map<string, Stock_indv> &stock_map)
{
    auto itr = stock_map.begin();
    for(; itr != stock_map.end(); itr++)
    {
        (itr->second).CalculateAbnormalReturns(stock_map);
    }
}
void print1dvec(const vector<string> & vect){
    for(int i=0;i<vect.size();i++){
        cout << vect[i] << " ";
    }
}


void print1dvec(const vector<double> & vect){
    for(int i=0;i<vect.size();i++){
        cout << vect[i] << " ";
    }
}

void print2dvector(const vector<vector<string>> & vect){
    for (int i = 0; i < vect.size(); i++) {
        for (int j = 0; j < vect[i].size(); j++){
            
            cout << vect[i][j] << " ";
        }
        cout << endl;
        cout << endl;
    }
}




int main() 
{
    
    int group,test =0;  
    string x;
    string tick;
    int N=0;
    int integer1;

    map<string, Stock_indv> GlobalStockMap;
    Stock_indv Russel;
    
    LoadEarnings(GlobalStockMap);
    
    String ticker_skip;
    string etf="IWV";    
    GlobalStockMap[etf] = Russel;
    
    Groupby_S_ gobj(&GlobalStockMap);
    gobj.CGroup(ticker_skip);
    
    Table groupTable = gobj.Get_Group_Mapping_();
    
    Bootstrap GlobalBoot_;
    Matrix AAR;
    
    int gott = 0;
    
    while(true)
    {
        cout<<"\n\nMenu: ";
        cout<<endl;
        cout<<"1) Enter N to retrieve 2N+1 historical prices for all stocks (Please allow around 2 mins to fetch)"<<endl;
        cout<<"2) Pull information for one stock from one group. ";
        cout<<endl;
        cout<<"3) Display AAR, AAR-std, CAAR, CAAR-std for one group. ";
        cout<<endl;
        cout<<"4) Display gnuplot plot for CAAR of all 3 groups.  ";
        cout<<endl;
        cout<<"5) Exit program ";
        cout<<endl;
        cout<<endl;
        cout<<"Please select appropriate option number:  ";
        cout<<endl;
        cin>>x;
        cout<<endl;
        switch(stoi(x))
        {
            case 1:
                while(test==0)
                {
                    
                    cout<<"Enter N value between 60 and 90: "<<endl;
                    cin>>N;
                    integer1 = (int) N;
                    
                    
                    if (integer1 != N)
                    {
                        cout<<"Error, please enter an integer value error"<<endl;
                        cin.clear();
                    }
                    else if(N>=60 && N<=90 && !cin.fail())  
                    {
                        
                        if (gott == 0)
                        {
                            cout<<"Loading data, please allow around 2 mins to load...\n";
                            auto start = high_resolution_clock::now();
                            //Multi threading
                            thread t1(FetchData,std::ref(GlobalStockMap),groupTable[0]);
                            thread t2(FetchData,std::ref(GlobalStockMap),groupTable[1]);
                            thread t3(FetchData,std::ref(GlobalStockMap),groupTable[2]);
                            t1.join();
                            t2.join();
                            t3.join();
                            
                            String Index;
                            
                            Index.push_back("IWV");
                            FetchData(GlobalStockMap,Index);
                            
                            auto stop = high_resolution_clock::now();
                            auto duration = duration_cast<seconds>(stop - start);
                            cout<<"Fetched data in seconds: "<<duration.count()<<endl;
                            gott  = 1;
                            CalAbnormalReturns(GlobalStockMap);
                        }
                        
                        AAR = GlobalBoot_.GetAAR();
                        if(AAR.size() != 0)
                            AAR.clear();
                            
                        ticker_skip = SetN(N, GlobalStockMap);
                        gobj.CGroup(ticker_skip);
                        test = 1;
                    }
                    else
                    {
                        cout<<"Error, Enough data points not found. Please select N above 60 and below 90 "<<endl;
                        cin.clear();
                    }
                }
                
            
                break;
            
            case 2:              
                if (N>=60 && N<=90)
                {
                    while(test==0)
                    {
                        cout<<"Please provide ticker of stock: "<<endl;
                        cin>> tick;
                        
                        if(GlobalStockMap.find(tick) != GlobalStockMap.end())
                        {
                            GlobalStockMap[tick].DisplayDetails();
                            test = 1;
                        }
                        else
                        {
                            cout<<"Error, Please enter a valid ticker. Example: Try 'MSFT'\n";
                            //break;
                        }
                        
                        
                        if(!cin.fail())
                        {
                            test = 1;
                        }
                        else 
                        { 
                            cout<<"Error, Invalid Input field. Example: Try GOOG ";   // try and error c++ 
                        }
                    }
                }
                else
                {
                    cout<<"Data has not yet been retrieved! Try retrieving data first using Option 1 in Main Menu!"<<endl;
                }
                
            
                break;
            
            case 3:
                
                if(N>=60 && N<=90)
                {   
                    Bootstrap boot(&gobj, &GlobalStockMap, N);
                    boot.RunBS();
                    cout << "\nBootstrap object created" << endl;
                    while(test==0)
                    {
                        cout<<"1) Beat \t 2) Meet \t 3) Miss"<<endl;
                        cout<< "Please select appropriate group number: "<<endl; 
                        cin>>group;
                        int integer2 = (int) group;
                        
                        if(integer2 != group)
                        {
                            cout<<"Invalid Input field"<<endl;
                            cin.clear();
                            
                        }
                        else if(group == 1)   //switch?
                        {
                            cout<<" Beat Estimate Group summary "<<endl;
                            boot.ResultsDisp(group-1);

                            test = 1;
                        }
                        else if(group == 2)
                        {
                            cout<<"\n Meet Estimate Group summary "<<endl;
                            boot.ResultsDisp(group-1);
                            test = 1;
                        }
                        else if(group == 3)
                        {
                            
                            cout<<" Miss Estimate Group summary "<<endl;
                            boot.ResultsDisp(group-1);
                            test = 1;
                        }
                        else 
                        {
                            cout<<"Error, Please select valid option number"<<endl;
                        }
                    
                    }
                    GlobalBoot_ = boot;
                    AAR = GlobalBoot_.GetAAR();
                    
                }
                
                else
                {
                    cout<<"Data has not yet been retrieved! Try retrieving data first using Option 1 in Main Menu!"<<endl;
                }
                
            
                break;
            
            case 4:
                
                if(N>=60 && N<=90)
                {   
                    
                    if(AAR.size() == 0)
                    {
                        cout<<"Error, Please run Bootstrap in Option 3 first";
                
                    }
                    else
                    {
                        Vector g1 = GlobalBoot_.GetCAAR(0);
                        Vector g2 = GlobalBoot_.GetCAAR(1);
                        Vector g3 = GlobalBoot_.GetCAAR(2);
                        
                        plotResults(100*g1, 100*g2, 100*g3, N);
                        
                        GlobalBoot_.plott(100*g1, 100*g2, 100*g3, N);    
                    }
                    
                    
                }
                else
                {
                    cout<<"Data has not yet been retrieved! Try retrieving data first using Option 1 in Main Menu!"<<endl;
                }
                
            
                break;
            
            case 5:
                exit(0);
                break;
            
            
            default:
                cout<<"Error, Please select valid option "<< endl;
                cin.clear();
                test = 1;
                break;
                //break;
        }

            
        
         
        test = 0;
        
    }
    
    return 0;
     
}
