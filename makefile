seaice: seaice.cpp
	g++ -std=c++11 -o seaice seaice.cpp

t: ./seaice
	./seaice

