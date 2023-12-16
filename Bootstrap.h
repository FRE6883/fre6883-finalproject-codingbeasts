# pragma once
#include "Group.h"
#include "Matrix.h"
#include "Stocks.h"
#include "Bootstrap.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;
namespace fre
{
    class Bootstrap{
        private:
            int mcn = 40;
            int M = 30;
            int T;
            Sort* grpPtr;
            map<string, Stock>* mapPtr;
            
            //populated as part of output of Bootstrap  
            Matrix AAR_STD; //group x time   
            Matrix CAAR_STD; //group x time   
            Matrix Avg_AAR; //group x time   
            Matrix Avg_CAAR; //group x time  
            vector<Matrix> Results; // group x output(AAR,AAR_STD,CAAR,CAAR_STD) x time
            
        public:
            Bootstrap() {}
            Bootstrap(Group* GroupPtr_, map<string, Stocks>* myMap_, int n);
            ~Bootstrap(){}
            
            
            // Setter functions
            void SetMCN(int N_);
            void SetM(int M_);
            void SetT(int T_);
            
            // Run bootstrap and populate Avg_AAR, AAR-STD, Avg_CAAR, CAAR_STD
            void RunBootstrap(); 
            
            //Plot GNU Plot for Avg_CAAR for each group (Beat, Meet, Miss)
            void plotResults(Vector r1, Vector r2, Vector r3, int N);
            void DisplayResults(int n);
            
            //Random sample generator
            String generateSample(int gr_n);
            //Abnormal return calculation
            Vector AbnormRet(string ticker);
            //Return AAR calculation across sample stocks (of 1 sample) for 2N timesteps (2N x 1)
            Vector Cal_AAR(int gr_n); 
            //Return cumulative sum of input vectors
            Vector cumsum(const Vector& V);
            

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