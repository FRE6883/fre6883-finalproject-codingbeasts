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
    const std::string apiKey = "656a2b0c7c23c6.26415138";
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

void HistoricalPricesRetriever :: setDate(string ead){
    string cur_date = convertDateFormat(ead);
    cout<<cur_date;
    // start_date = subtractFinancialDays(cur_date);
    // end_date = addFinancialDays(cur_date);
    // cout<<start_date<<endl<<end_date;
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
    
int main() {
    // Create an instance of HistoricalPricesRetriever
    int N = 15; // Replace 5 with the desired value of N
    HistoricalPricesRetriever pricesRetriever(N);

    // Set a date using the setDate function
    std::string dateToSet = "05-Dec-23"; // Replace with the desired date
    pricesRetriever.setDate(dateToSet);

    return 0;
}