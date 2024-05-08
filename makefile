OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11 -fno-extended-identifiers

program.exe: main.o dependencies.o BinTree.o
	g++ program.exe -o dependencies.o BinTree.o 

main.o: main.cc product_data.hh city.hh product.hh river.hh ship.hh
	g++ main.o -c main.cc $(OPCIONS)

dependencies.o: product_data.cc city.cc product.cc river.cc ship.cc 
	g++ dependencies.o -c product_data.cc city.cc product.cc river.cc ship.cc $(OPCIONS)

BinTree.o: BinTree.hh
	g++ BinTree.o -c BinTree.hh $(OPCIONS)

clean:
	rm *.o
	rm *.gch