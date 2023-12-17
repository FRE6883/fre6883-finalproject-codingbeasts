# pragma once
#include "Group.h"
#include "Matrix.h"
#include "Stock_indv.h"
#include "bootstrap.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;
namespace fre
{
    class Bootstrap
    {
        private:
            int MCN = 40;   // no. of bootstrap (monte carlo) iterations 
            int M = 30;     // size of each sample from a group 
            int T; //number of days (2N)
            double ttemp;
            Group* GroupPtr;
            map <string, Stock_indv>* MapPtr;
            
            //populated as part of output of Bootstrap  
            Matrix AAR_STD;  
            Matrix CAAR_STD;  
            Matrix Avg_AAR;   
            Matrix Avg_CAAR;
            vector<Matrix> Results; // group x output(AAR,AAR_STD,CAAR,CAAR_STD) x time 
    
        public:
            Bootstrap() {}
            Bootstrap(Group* GroupPtr_, map<string, Stock_indv>* myMap_, int n);
            ~Bootstrap(){}
            
            // Setter functions
            void SetMCN(int N_);
            void SetM(int M_);
            
            // Run bootstrap and populate Avg_AAR, AAR-STD, Avg_CAAR, CAAR_STD
            void RunBS(); 
            
            //Plot GNU Plot for Avg_CAAR for each group (Beat, Meet, Miss)
            void plott(Vector r1, Vector r2, Vector r3, int N);
            void ResultsDisp(int n);
            
            //Random sample generator
            String GenS(int gr_n);
            //Abnormal return calculation
            Vector AbnormRet(string ticker);
            // AAR calculation across sample stocks (of 1 sample) for 2N timesteps (2N x 1)
            Vector Cal_AAR(int gr_n); 
            // cumulative sum of input vectors
            Vector Cumulative_Sum_(const Vector& V);
            
            // Getter functions
            Matrix GetAAR() const {return Avg_AAR;}
            Matrix GetAAR_STD() const {return AAR_STD;}
            Matrix GetCAAR() const {return Avg_CAAR;}
            Matrix GetCAAR_STD() const {return CAAR_STD;}
            vector<Matrix> GetResults() const {return Results;}
            
            Vector GetAAR(int gr_index) const;
            Vector GetAAR_STD(int gr_index) const;
            Vector GetCAAR(int gr_index) const;
            Vector GetCAAR_STD(int gr_index) const;
    };
}