FLAGS=-O2 -std=c++11
CXX=g++

ALL: isomorphic_generator

isomorphic_generator: isomorphic_generator.o
	$(CXX) $(FLAGS) isomorphic_generator.o -o isomorphic_generator

isomorphic_generator.o: isomorphic_generator.cpp
	$(CXX) $(FLAGS) -c isomorphic_generator.cpp -o isomorphic_generator.o

clean:
	rm -rf isomorphic_generator *.o 
