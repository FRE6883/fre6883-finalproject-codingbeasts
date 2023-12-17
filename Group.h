#pragma once
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include <algorithm>
#include "Stock_indv.h"
#include <iostream>

using namespace std;
using namespace fre;

typedef vector<double> Vector;
typedef vector<vector<double>> Matrix;
typedef vector<vector<string>> Table;
typedef map<string,Stock_indv> Map;

class Group
{
    private:
        double check_var1;
    protected:
        //data members
        Table Group_Mapping; //table of tickers
        Map* stockMapPtr;
        int N_group;
        
        vector<string> Group_Names;
        
        bool (*cmp)(Stock_indv& a, Stock_indv& b);
        
        //constructor
        Group(Map* data_);
        
        //destructor
        virtual ~Group();
        
    public:
        //get, set number of groups
        void SetN(int n);
        int GetN() const;
        
        //get, set group names
        void SetGroupNames(vector<string>& names);
        vector<string> GetGroupNames() const;
        
        //get, set stock map
        Map GetStockMap_() const;
        void UpdateStockMap(Map* stockMapPtr_);
        
        //get Group Vector Pointer
        Table Get_Group_Mapping_();
        
        //create Groups
        virtual void CGroup(String skipped_tickers) = 0;
        virtual void CGroup(int n, String skipped_tickers) = 0;
        virtual void CGroup(Map* stockMapPtr_, int n, String skipped_tickers) = 0;
        
        //overloaded subscript operator to return by group name
        vector<string> operator[] (const string& groupname);
};

class Groupby_S_: public Group
{
    private:
        double check_var2_p;
    public:
        //constructor
        Groupby_S_(Map* stockMapPtr_);
        
        //destructor
        ~Groupby_S_();
        
        //create groups
        void CGroup(String skipped_tickers);
        void CGroup(int n, String skipped_tickers);
        void CGroup(Map* StockMapPtr_, int n,String skipped_tickers);
        
        //friend function
        friend bool compare(Stock_indv& a, Stock_indv& b);
};