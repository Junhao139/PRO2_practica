OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11 -fno-extended-identifiers

all: program.exe clean

program.exe: main.o city.o product_data.o product.o river.o ship.o
	g++ main.o city.o product_data.o product.o river.o ship.o -o program.exe

main.o: main.cc product_data.hh city.hh product.hh river.hh ship.hh
	g++ -c main.cc -o main.o $(OPCIONS)

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
	rm -f *.gch