CXX = g++
CXXFLAGS = -Wall

proj4: driver.o cache.o
	$(CXX) $(CXXFLAGS) driver.o cache.o -o proj4

test: mytest.o cache.o
	$(CXX) $(CXXFLAGS) mytest.o cache.o -o test

driver.o: driver.cpp cache.h
	$(CXX) $(CXXFLAGS) -c driver.cpp

mytest.o: mytest.cpp cache.h
	$(CXX) $(CXXFLAGS) -c mytest.cpp

cache.o: cache.cpp cache.h
	$(CXX) $(CXXFLAGS) -c cache.cpp

run: proj4
	./proj4

run1: test
	./test

val:
	valgrind ./proj4

clean:
	rm -f *.o *~ proj4 test
