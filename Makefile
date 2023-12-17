CC = g++
CFLAGS = -Wall -ggdb3 -std=c++11 -lcurl -lpthread

Project: MenuMain.o ReadLoadData.o Stocks.o bootstrap.o Group.o Matrix.o IWV.o
	$(CC) $(CFLAGS) -o Project MenuMain.o ReadLoadData.o Stock_indv.o Group.o bootstrap.o Matrix.o IWV.o

MenuMain.o: Stock_indv.h ReadLoadData.h bootstrap.h Matrix.h Group.h MenuMain.cpp
	$(CC) $(CFLAGS) -c MenuMain.cpp
	
bootstrap.o: Stock_indv.h bootstrap.h Matrix.h Group.h
	$(CC) $(CFLAGS) -c bootstrap.cpp

Group.o: Stock_indv.h Group.h Group.cpp
	$(CC) $(CFLAGS) -c Group.cpp
	
ReadLoadData.o: Stock_indv.h ReadLoadData.h ReadLoadData.cpp 
	$(CC) $(CFLAGS) -c ReadLoadData.cpp
	
Stocks.o: Stock_indv.h Stock_indv.cpp
	$(CC) $(CFLAGS) -c Stock_indv.cpp
	
Matrix.o: Matrix.h Matrix.cpp
	$(CC) $(CFLAGS) -c Matrix.cpp
	
IWV.o: IWV.h IWV.cpp
	$(CC) $(CFLAGS) -c IWV.cpp
clean:
	rm -rf  Project *.o
