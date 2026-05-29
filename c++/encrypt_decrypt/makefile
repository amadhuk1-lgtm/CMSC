CXX = g++
CXXFLAGS = -Wall

proj4: proj4.cpp CipherTool.o Cipher.o Atbash.o Ong.o Scytale.o
	$(CXX) $(CXXFLAGS) proj4.cpp CipherTool.o Cipher.o Atbash.o Ong.o Scytale.o -o proj4

CipherTool.o: CipherTool.h CipherTool.cpp Cipher.o Atbash.o Ong.o Scytale.o
	$(CXX) $(CXXFLAGS) -c CipherTool.cpp

Cipher.o: Cipher.h Cipher.cpp Atbash.o Ong.o Scytale.o
	$(CXX) $(CXXFLAGS) -c Cipher.cpp

Atbash.o: Atbash.h Atbash.cpp Ong.o Scytale.o
	$(CXX) $(CXXFLAGS) -c Atbash.cpp

Ong.o: Ong.h Ong.cpp Scytale.o
	$(CXX) $(CXXFLAGS) -c Ong.cpp

Scytale.o: Scytale.h Scytale.cpp
	$(CXX) $(CXXFLAGS) -c Scytale.cpp

val:
	valgrind ./proj4

run: proj4
	./proj4

clean:
	rm *~

submit:
	cp proj4.cpp Atbash.h Atbash.cpp Cipher.h Cipher.cpp CipherTool.h CipherTool.cpp Ong.h Ong.cpp Scytale.h Scytale.cpp ~/cs202proj/proj4
