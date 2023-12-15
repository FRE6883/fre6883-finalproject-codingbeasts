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

using namespace std;

class HistoricalPricesRetriever {
private:
    const std::string apiKey = "656b5c5e9982a8.16874092";
    std::string urlCommon = "https://eodhistoricaldata.com/api/eod/";
    int N;
    FILE* fp;
    std::string start_date;
	std::string end_date;

public:
    HistoricalPricesRetriever(int& N_) : N(N_) {}
    
    void setDate(std::string ead);
    
    void retrieveHistoricalPrices();
    
    void Filewriter();
    
    std::string convertDateFormat(const std::string& inputDate);
    
    std::tm subtractFinancialDays(const std::tm& currentDate);
    
    std::tm addFinancialDays(const std::tm& currentDate);
    
};
// unordered_map<string,string> sample_list, unordered_map<string,string> ticker_list
// int write_data(void* ptr, int size, int nmemb, FILE* stream)
// {
// 	size_t written;
// 	written = fwrite(ptr, size, nmemb, stream);
// 	return written;
// }
void HistoricalPricesRetriever::Filewrite(){
    vector<string> symbolList;
	populateSymbolVector(symbolList);
    fp = fopen(resultfilename, "wb");
    if (handle)
	{
		string url_common = "https://eodhistoricaldata.com/api/eod/";
		string start_date = "2023-11-01";
		string end_date = "2023-11-30";
		string api_token = "656cb6bd815a15.50045816";  // You must replace this API token with yours

		vector<string>::iterator itr = symbolList.begin();
		for (; itr != symbolList.end(); itr++)
		{
			struct MemoryStruct data;
			data.memory = NULL;
			data.size = 0;

			string symbol = *itr;
			string url_request = url_common + symbol + ".US?" + "from=" + start_date + "&to=" + end_date + "&api_token=" + api_token + "&period=d";
			curl_easy_setopt(handle, CURLOPT_URL, url_request.c_str());

			//adding a user agent
			curl_easy_setopt(handle, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:74.0) Gecko/20100101 Firefox/74.0");
			curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0);
			curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0);
			fprintf(fp, "Symbol = %s\n", symbol.c_str());

			curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data);
			curl_easy_setopt(handle, CURLOPT_WRITEDATA, fp);
			result = curl_easy_perform(handle);
			fclose(fp);

			//fprintf(fp, "%c", '\n');
			double lret=0.0;

			// check for errors 
			if (result != CURLE_OK) {
				fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
				return -1;
			}

			curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data2);
			curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void*)&data);

			// perform, then store the expected code in result
			result = curl_easy_perform(handle);

			if (result != CURLE_OK)
			{
				// if errors have occured, tell us what is wrong with result
				fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
				return 1;
			}
			fp = fopen(resultfilename, "wb");
			fprintf(fp, "Symbol = %s\n", symbol.c_str());
			fclose(fp);
			
			stringstream sData;
			sData.str(data.memory);
			string sValue, sDate;
			double dValue = 0;
			string line;
			int c=0;
			double prev=0.0;
			double curr=0.0;
			string adj_str;
			cout << symbol << endl;;
			fp = fopen(resultfilename, "ab");
			while (getline(sData, line)) {
				size_t found = line.find('-');
				if (found != std::string::npos)
				{
					fp = fopen(resultfilename, "ab");
					cout << line << endl;
					sDate = line.substr(0, line.find_first_of(','));
					line.erase(line.find_last_of(','));
					sValue = line.substr(line.find_last_of(',') + 1);
					line.erase(line.find_last_of(','));
					adj_str=line.substr(line.find_last_of(',')+1);


					dValue = strtod(sValue.c_str(), NULL);
					if(c==0){
						prev=dValue;
						lret=0.000000;
						fprintf(fp, "sDate= %s, ", sDate.c_str());
						fprintf(fp, "dDailyReturn=%f\n",lret);

						
					}
					else{
						curr=dValue;
						lret=log(curr/prev);
						fprintf(fp, "sDate= %s, ", sDate.c_str());
						fprintf(fp, "dDailyReturn= %f\n",lret);
						prev=curr;
					

						
					}
					c++;
					fclose(fp);
					cout << sDate << " " << std::fixed << ::setprecision(2) << dValue << endl;
				}
			}
			
			free(data.memory);
			data.size = 0;
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
void HistoricalPricesRetriever :: retrieveHistoricalPrices(){
    const char resultfilename[FILENAME_MAX] = "results.txt";
    CURL* handle;
	CURLcode result;
	// set up the program environment that libcurl needs 
	curl_global_init(CURL_GLOBAL_ALL);
	// curl_easy_init() returns a CURL easy handle 
	handle = curl_easy_init();
	vector<string> symbolList;
	//populateSymbolVector(symbolList);
	string thisTicker = "MSFT";
	symbolList.push_back(thisTicker);
	if (handle)
	{
		string url_common = "https://eodhistoricaldata.com/api/eod/";
// 		string start_date = "2023-11-01";
// 		string end_date = "2023-11-30";
		string api_token = "656b5c5e9982a8.16874092";  // You must replace this API token with yours
// 		vector<string>::iterator itr = symbolList.begin();
// 		for (; itr != symbolList.end(); itr++)
// 		{
// 			struct MemoryStruct data;
// 			data.memory = NULL;
// 			data.size = 0;

// 			string symbol = *itr;
// 			string url_request = url_common + symbol + ".US?" + "from=" + start_date + "&to=" + end_date + "&api_token=" + api_token + "&period=d";
// 			curl_easy_setopt(handle, CURLOPT_URL, url_request.c_str());

// 			//adding a user agent
// 			curl_easy_setopt(handle, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:74.0) Gecko/20100101 Firefox/74.0");
// 			curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0);
// 			curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0);
// 			fp = fopen(resultfilename, "ab");
// 			fprintf(fp, "%s\n", symbol.c_str());
// 			curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data);
// 			curl_easy_setopt(handle, CURLOPT_WRITEDATA, fp);
// 			result = curl_easy_perform(handle);
// 			fprintf(fp, "%c", '\n');
// 			fclose(fp);

// 			// check for errors 
// 			if (result != CURLE_OK) {
// 				fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
// 				return -1;
// 			}

// 			// perform, then store the expected code in result
// 			result = curl_easy_perform(handle);

// 			if (result != CURLE_OK)
// 			{
// 				// if errors have occured, tell us what is wrong with result
// 				fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
// 				return 1;
// 			}
	}

}

void HistoricalPricesRetriever :: setDate(string ead){
    string cur_date = convertDateFormat(ead);
    start_date = subtractFinancialDays(cur_date);
    end_date = addFinancialDays(cur_date);
}

string HistoricalPricesRetriever :: convertDateFormat(const std::string& inputDate) {
    std::istringstream iss(inputDate);
    std::ostringstream oss;

    // Input and output date structures
    struct tm inputTime = {};
    std::tm outputTime = {};

    // Define the format of the input date
    iss >> std::get_time(&inputTime, "%d-%b-%y");

    // Check if parsing was successful
    if (iss.fail()) {
        std::cerr << "Error parsing date." << std::endl;
        return "";
    }

    // Set the output date format
    outputTime.tm_year = inputTime.tm_year + 100;  
    outputTime.tm_mon = inputTime.tm_mon;
    outputTime.tm_mday = inputTime.tm_mday;

    // Format the output date
    oss << std::put_time(&outputTime, "%Y-%m-%d");

    return oss.str();
}

std::tm HistoricalPricesRetriever :: subtractFinancialDays(const std::tm& currentDate) {
    std::tm result = currentDate;
    int n = N;

    while (n > 0) {
        // Subtract one day
        std::mktime(&result);
        result.tm_sec -= 24 * 60 * 60;
        std::mktime(&result);

        // Check if the current day is not a weekend (Saturday or Sunday)
        if (result.tm_wday != 0 && result.tm_wday != 6) {
            --n;  // Decrease the count only on non-weekend days
        }
    }

    return result;
}


std::tm HistoricalPricesRetriever :: addFinancialDays(const std::tm& currentDate) {
    std::tm result = currentDate;
    int n = N;

    while (N > 0) {
        // Subtract one day
        std::mktime(&result);
        result.tm_sec += 24 * 60 * 60;
        std::mktime(&result);

        // Check if the current day is not a weekend (Saturday or Sunday)
        if (result.tm_wday != 0 && result.tm_wday != 6) {
            --n;  // Decrease the count only on non-weekend days
        }
    }
}
    
// int main() {
//     // Example usage
//     std::tm currentDate = {};
//     std::istringstream ss("2023-01-01");
//     ss >> std::get_time(&currentDate, "%Y-%m-%d");

//     int N = 60;
//     std::tm resultDate = subtractFinancialDays(currentDate, N);

//     std::cout << "Current Date: " << std::put_time(&currentDate, "%Y-%m-%d") << std::endl;
//     std::cout << N << " Financial Days Before: " << std::put_time(&resultDate, "%Y-%m-%d") << std::endl;

//     return 0;
// }