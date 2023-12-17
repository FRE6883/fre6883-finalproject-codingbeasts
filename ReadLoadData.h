#pragma once

#include <stdio.h>
#include <cstring>
#include <string> 
#include <iostream>
#include <sstream>  
#include <vector>
#include <locale>
#include <iomanip>
#include <fstream>
#include <curl/curl.h>
#include <map>
#include "Stock_indv.h"

namespace fre
{
    struct MemoryStruct 
    {
    	char* memory;
    	size_t size;
    };
    
    string FormatDate(string Date);
    
    void plotResults(Vector Beat, Vector Meet, Vector Miss, int N);
    
    void LoadEarnings(map<string, Stock_indv> &data);
    
    int write_data(void* ptr, int size, int nmemb, void* data);
    
    void FetchData(map<string, Stock_indv> &stock_map, String group_tickers);
}