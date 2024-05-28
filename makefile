OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11 -fno-extended-identifiers

all: program.exe clean

program.exe: program.o city.o product_data.o product.o river.o ship.o
	g++ program.o city.o product_data.o product.o river.o ship.o -o program.exe

program.o: program.cc product_data.hh city.hh product.hh river.hh ship.hh
	g++ -c program.cc -o program.o $(OPCIONS)

city.o: city.cc
	g++ -c city.cc -o city.o $(OPCIONS)

product_data.o: product_data.cc
	g++ -c product_data.cc -o product_data.o $(OPCIONS)

product.o: product.cc
	g++ -c product.cc -o product.o $(OPCIONS)

river.o: river.cc
	g++ -c river.cc -o river.o $(OPCIONS)

ship.o: ship.cc
	g++ -c ship.cc -o ship.o $(OPCIONS)

clean:
	rm -f *.o