CXX = g++
CXXFLAGS = -Wall
OBJECTS = Game.o Area.o Hero.o Item.o

proj5: $(OBJECTS) proj5.cpp
	$(CXX) $(CXXFLAGS) $(OBJECTS) proj5.cpp -o proj5

Game.o: Game.h Game.cpp Map.o Node.o Hero.o Area.o Item.o
	$(CXX) $(CXXFLAGS) -c Game.cpp

Area.o: Area.h Area.cpp
	$(CXX) $(CXXFLAGS) -c Area.cpp

Map.o: Node.o Map.cpp
	$(CXX) $(CXXFLAGS) -c Map.cpp

Node.o: Node.cpp
	$(CXX) $(CXXFLAGS) -c Node.cpp

Item.o: Item.h Item.cpp
	$(CXX) $(CXXFLAGS) -c Item.cpp

Hero.o: Hero.h Hero.cpp Node.o Map.o
	$(CXX) $(CXXFLAGS) -c Hero.cpp

##Use this when you want to test just your Queue
mtest: Map.o map_test.cpp Node.o
	$(CXX) $(CXXFLAGS) Map.o Node.o map_test.cpp -o mtest

##Use this when you want to valgrind your Queue tests
mtest2:
	valgrind ./mtest

clean:
	rm *.o
	rm *~

run1:
	./proj5 proj5_map2.txt proj5_craft.txt

val1:
	valgrind ./proj5 proj5_map2.txt proj5_craft.txt
