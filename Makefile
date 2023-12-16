CC = g++
CFLAGS = -Wall -ggdb3 -std=c++11 -lcurl -lpthread

FinalProject: MenuMain.o ReadLoadData.o Stocks.o bootstrap.o Sort.o Matrix.o
	$(CC) $(CFLAGS) -o FinalProject MenuMain.o ReadLoadData.o Stocks.o Sort.o bootstrap.o Matrix.o

MainMenu.o: Stock.h GetHistoricalData.h Bootstrap.h Matrix.h Sort.h MainMenu.cpp
	$(CC) $(CFLAGS) -c MainMenu.cpp

Bootstrap.o: Stocks.h Bootstrap.h Matrix.h Sort.h
	$(CC) $(CFLAGS) -c Bootstrap.cpp

Sort.o: Stock.h Sort.h Sort.cpp
	$(CC) $(CFLAGS) -c Sort.cpp

GetHistoricalData.o: Stock.h GetHistoricalData.h GetHistoricalData.cpp 
	$(CC) $(CFLAGS) -c GetHistoricalData.cpp

Stocks.o: Stock.h Stock.cpp
	$(CC) $(CFLAGS) -c Stock.cpp

Matrix.o: Matrix.h Matrix.cpp
	$(CC) $(CFLAGS) -c Matrix.cpp

clean:
	rm -rf  FinalProject *.o