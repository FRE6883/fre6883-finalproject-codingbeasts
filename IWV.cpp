#include "IWV.h"

#pragma once

#include "Stock_indv.h"

// #include "GetHistoricalData.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>


#include <stdio.h>
#include <cstring>
#include <string> 
#include <iostream>
#include <sstream>  
#include <vector>
#include <locale>
#include <iomanip>
#include <fstream>
#include <cmath> 
#include "curl/curl.h"
#include <unordered_map> 

#include <stdio.h>
#include <cstring>
#include <string> 
#include <iostream>
#include <sstream>  
#include <vector>
#include <locale>
#include <iomanip>
#include <fstream>
#include "curl/curl.h"

#include <math.h>

#include <iterator>

using namespace std;

void printIdxMap(map<string,double> idxMap){
	
	cout << "PRINTING IDXMAP" << endl;
	map<string,double>::iterator itr;
	
	for(itr = idxMap.begin(); itr!=idxMap.end();itr++){
		cout << itr->first << " >> " << itr->second << endl;
	}
}

vector<double> IWV::returnIWV(string ipstart, string ipend) {
    cout << "\nidxMap.size() " << idxMap.size() << "\n" << endl;
    
    // Find the starting and ending iterators in the map
    auto startItr = idxMap.lower_bound(ipstart);
    auto endItr = idxMap.upper_bound(ipend);

    if (startItr == idxMap.end()) {
        cout << "Start date " << ipstart << " not found in IDX map." << endl;
        return vector<double>();
    }
    if (endItr == idxMap.end()) {
        cout << "End date " << ipend << " not found in IDX map." << endl;
        return vector<double>();
    }

    vector<double> IWVsubset;
    for (auto itr = startItr; itr != endItr; ++itr) {
        IWVsubset.push_back(itr->second);
    }

    return IWVsubset;
}

int IWV::populate_idxReturn(){
    
    // DELETING THE FIRST DATA POINT OF THE IDX LEVEL AND THE IDX DATES
    for(int i=1;i<idxLevel.size();i++){
        double todaysReturn = log(idxLevel[i]/idxLevel[i-1]);
        idxReturn.push_back(todaysReturn);
    }
    
    idxLevel.erase(idxLevel.begin());
    dates.erase(dates.begin());
}

void IWV::populate_idxMap(){
	cout << "return size: " << idxReturn.size() << " dates size:" << dates.size() << endl;
	
	vector<string>::iterator itrstr = dates.begin();
	vector<double>::iterator itrdoub = idxReturn.begin();
	
	for(;itrdoub!=idxReturn.end();itrdoub++,itrstr++){
		idxMap[*itrstr] = *itrdoub;
	}
}

void IWV::displayIWV(){
    vector<string>::iterator itrD= dates.begin();
    vector<double>::iterator itrR= idxReturn.begin();
    for(vector<double>::iterator itr= idxLevel.begin();itr!=idxLevel.end();itr++){
        cout << *itrD << " idxLevel>>" << *itr << " idxReturn>>" << *itrR << endl;
        itrD++;
        itrR++;
    }
}

int write_dataxx(void* ptr, int size, int nmemb, FILE* stream)
{
	size_t written;
	written = fwrite(ptr, size, nmemb, stream);
	return written;
}
struct MemoryStructxx {
	char* memory;
	size_t size;
};
void* myreallocxx(void* ptr, size_t size)
{
	if (ptr)
		return realloc(ptr, size);
	else
		return malloc(size);
}
int write_data2xx(void* ptr, size_t size, size_t nmemb, void* data)
{
	size_t realsize = size * nmemb;
	struct MemoryStructxx* mem = (struct MemoryStructxx*)data;
	mem->memory = (char*)myreallocxx(mem->memory, mem->size + realsize + 1);
	if (mem->memory) {
		memcpy(&(mem->memory[mem->size]), ptr, realsize);
		mem->size += realsize;
		mem->memory[mem->size] = 0;
	}
	return realsize;
}

int IWV::populate_idxLevel()
{
	vector<string> symbolList;
	//populateSymbolVector(symbolList);
	string thisTicker = "IWV";
	symbolList.push_back(thisTicker);
	
	// file pointer to create file that store the data  
	FILE* fp;

	const char resultfilename[FILENAME_MAX] = "Results.txt";

	// declaration of an object CURL 
	CURL* handle;

	CURLcode result;

	// set up the program environment that libcurl needs 
	curl_global_init(CURL_GLOBAL_ALL);

	// curl_easy_init() returns a CURL easy handle 
	handle = curl_easy_init();

	// if everything's all right with the easy handle... 
	if (handle)
	{
		string url_common = "https://eodhistoricaldata.com/api/eod/";
		string start_date = startDate;
		string end_date = endDate;
		//string api_token = "601390a0a753f2.12891709";  // You must replace this API token with yours
		string api_token = "656a2b0c7c23c6.26415138"; // MY FREE TIER TOKEN
		
		vector<string>::iterator itr = symbolList.begin();
		for (; itr != symbolList.end(); itr++)
		{
			struct MemoryStructxx data;
			data.memory = NULL;
			data.size = 0;

			string symbol = *itr;
			string url_request = url_common + symbol + ".US?" + "from=" + start_date + "&to=" + end_date + "&api_token=" + api_token + "&period=d";
			curl_easy_setopt(handle, CURLOPT_URL, url_request.c_str());

			//adding a user agent
			curl_easy_setopt(handle, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:74.0) Gecko/20100101 Firefox/74.0");
			curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0);
			curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0);
			fp = fopen(resultfilename, "ab");
			fprintf(fp, "%s\n", symbol.c_str());
			curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_dataxx);
			curl_easy_setopt(handle, CURLOPT_WRITEDATA, fp);
			result = curl_easy_perform(handle);
			fprintf(fp, "%c", '\n');
			fclose(fp);

			// check for errors 
			if (result != CURLE_OK) {
				fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
				return -1;
			}

			curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data2xx);
			curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void*)&data);

			// perform, then store the expected code in result
			result = curl_easy_perform(handle);

			if (result != CURLE_OK)
			{
				// if errors have occured, tell us what is wrong with result
				fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
				return 1;
			}
			
			stringstream sData;
			sData.str(data.memory);
			string sValue, sDate;
			double dValue = 0;
			double openValue = 0;
			int count = 0;
			string line;

			while (getline(sData, line)) {
				size_t found = line.find('-');
				if (found != std::string::npos)
				{
				    cout << line << endl;
                    sDate = line.substr(0, line.find_first_of(','));
                    line.erase(line.find_last_of(','));
                    sValue = line.substr(line.find_last_of(',') + 1);
                    dValue = strtod(sValue.c_str(), NULL);
                    //cout << sDate << " " << std::fixed << ::setprecision(6) << dValue << endl;
                    
                    
                    idxLevel.push_back(dValue);
                    dates.push_back(sDate);
				}
			}
			
			free(data.memory);
			data.size = 0;
			
			//average = sum/double(count);
			
			//cout <<" traditional average: "<< sum/(double(count)) << endl;
			
// 			cout << "\nFINAL OUTPUT:\n" << endl;
// 			cout << "Symbol=" << symbol << endl;
// 			cout << "sMinOpenDate=" << minOpenDate << std::fixed << ::setprecision(2) <<", sMinOpenDate=" << minOpen << endl;
// 			cout << "sMaxCloseDate=" << maxCloseDate << std::fixed << ::setprecision(2) <<", sMaxCloseDate=" << maxClose << endl;
		}

	}
	else
	{
		fprintf(stderr, "Curl init failed!\n");
		return -1;
	}

	// cleanup since you've used curl_easy_init  
	curl_easy_cleanup(handle);

	// release resources acquired by curl_global_init() 
	curl_global_cleanup();

	return 0;
}
