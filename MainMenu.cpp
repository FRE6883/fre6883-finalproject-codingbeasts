#include <iostream>
#include <ctime>
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


int main() {

    int N = 60;
    
    cout << "\n\nMenu: " << endl;
    cout << "1) Enter N to retrieve 2N+1 historical prices for all stocks" << endl;
    cout << "2) Pull information for one stock from one group. " << endl;
    cout << "3) Display AAR, AAR-std, CAAR, CAAR-std for one group. " << endl;
    cout << "4) Display gnuplot plot for CAAR of all 3 groups.  " << endl;
    cout << "5) Exit program " << endl << endl;
    cout << "Please select appropriate option number:  " << endl;
    cin >> x;
    
    switch(x) {
        case 1: {
            // Your code for option 1
            break;
        }
        case 2: {
            // Your code for option 2
            break;
        }
        case 3: {
            // Your code for option 3
            break;
        }
        case 4: {
            // Your code for option 4
            break;
        }
        case 5: {
            exit(0);
            break;
        }
        default: {
            cout << "Error, Please select valid option " << endl;
            cin.clear();
            break;
        }
    }
    
    
        return 0;
    }
