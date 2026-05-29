CXX = g++
CXXFLAGS = -Wall

proj2: DoodleGod.o Game.o proj2.cpp
	$(CXX) $(CXXFLAGS) DoodleGod.o Game.o proj2.cpp -o proj2

Game.o: DoodleGod.o Game.cpp Game.h
	$(CXX) $(CXXFLAGS) -c Game.cpp

DoodleGod.o: DoodleGod.h DoodleGod.cpp Element.h
	$(CXX) $(CXXFLAGS) -c DoodleGod.cpp

clean:
	rm *.o*
	rm *~ 

run:
	./proj2

ta1:
	./proj2 < proj2_ta1.txt

ta2:
	./proj2 < proj2_ta2.txt
