CXX = g++
CXXFLAGS = -Wall

proj3: proj3.cpp TextEditor.o Document.o Line.o
	$(CXX) $(CXXFLAGS) proj3.cpp TextEditor.o Document.o Line.o -o proj3

TextEditor.o: TextEditor.h TextEditor.cpp Document.o Line.o
	$(CXX) $(CXXFLAGS) -c TextEditor.cpp

Document.o: Document.h Document.cpp Line.o
	$(CXX) $(CXXFLAGS) -c Document.cpp

Line.o: Line.h Line.cpp
	$(CXX) $(CXXFLAGS) -c Line.cpp

val:
	valgrind ./proj3

run:
	./proj3

clean:
	rm *~

submit:
	cp proj3.cpp Line.h Line.cpp Document.h Document.cpp TextEditor.h TextEditor.cpp ~/cs202proj/proj3
