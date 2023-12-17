#pragma once

#include <iostream>
#include <vector>
#include <map>

using namespace std;

namespace fre
{
	typedef vector<string> String;
	typedef vector<double> Vector;
	typedef vector<Vector> Matrix;
	
	vector<string> GenerateDates();
	
	class Stock_indv
	{
	  protected:
		String Date;
		Vector O_price;
		Vector H_price;
		Vector L_price;
		Vector C_price;
		Vector A_close;
		Vector Voll;
		Vector pct_returns;
		Vector Abnormal_returns;
		Vector Cumulative_returns;
		Matrix Stock_info;
		
		double reported_earnings;
		double estimated_earnings;
		double surprise_earnings;
		double surprise_perecent;
		string earnings_date;
		string start_date;
		string end_date;
		string ticker;
		string period_ending;
		string group;
		
		int N;
		int start_index;
		int end_index;
		int full_data;
		
	  public:
		Stock_indv(){}
		Stock_indv(String d_, Vector op_, Vector hp_, Vector lp_, Vector cp_, Vector acp_, Vector v_ ):Date(d_), O_price(op_), H_price(hp_), L_price(lp_), C_price(cp_), A_close(acp_), Voll(v_) {}
		String GetDate() const { return Date; }
        Vector GetOpen_price() const { return O_price; }
		Vector GetHigh_price() const { return H_price; }
		Vector GetLow_price() const { return L_price; }
		Vector GetClose_price() const { return C_price; }
		Vector GetAdjusted_close() const { return A_close; }
		Vector Getvolume() const { return Voll; }
		Vector GetReturns() const {return pct_returns;}
		Vector GetAbnormalReturns() const { return Abnormal_returns; }
		Vector GetCumulativeReturns() const { return Cumulative_returns; }
		
		void SetDate(const String & dt) { Date = dt; }
		void SetOP(const Vector & OP) { O_price = OP; }
        void SetHP(const Vector& HP) { H_price = HP; }
        void SetLP(const Vector& LP) { L_price = LP; }
        void SetCP(const Vector& CP) { C_price = CP; }
        void SetACP(const Vector& ACP) { A_close = ACP; }
        void SetVol(const Vector& Vol) { Voll = Vol; }
        void SetEarningsPeriod(string period_ending_) { period_ending = period_ending_;}
        void CalculateReturns();
        void SetStartIndex(int N_) {start_index = N_;}
        void SetEndIndex(int N_) {end_index = N_;}
        void SetGroup(string group_) {group = group_;}
        
        
        
        int SetN(int N_);
        void CalculateAbnormalReturns(map<string, Stock_indv> &GlobalStockMap);
        void CalculateCumulativeReturns();
        void DisplayDetails();
        
        void SetReportedEarnings(const double& re) { reported_earnings = re;}
        void SetEstimatedEarnings(const double& ee) { estimated_earnings = ee;}
        void SetSurpriseEarnings(const double& se) { surprise_earnings = se;}
        void SetSurprisePerecent(const double& sp) { surprise_perecent = sp;}
        void SetTicker(const string& ticker_) { ticker = ticker_;}
        void SetEarningsDate(const string& earnings_date_) { earnings_date = earnings_date_;}
        int SetDates();
        
        
        double GetReportedEarnings() { return reported_earnings; }
        double GetEstimatedEarnings() { return estimated_earnings; }
        double GetSurpriseEarnings() { return surprise_earnings; }
        double FetchSurpPercent() { return surprise_perecent; }
        string GetTicker(){ return ticker;}
        string GetEarningsDate() { return earnings_date; }
        string GetStartDate() { return start_date;}
        string GetEndDate() { return end_date;}
        string GetGroup() { return group; }
        int GetStartIndex() const { return start_index; }
        int GetEndIndex() const { return end_index; }
        int GetN() const {return N; }
	};


}
