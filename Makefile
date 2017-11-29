%.exe: %.cpp mylib.o
	g++ --std=c++14 -o $@ $^

%.exe: %.hs
	ghc -O -o $@ $^

mylib.o: mylib.cpp
	g++ -c --std=c++14 -o $@ $<

clean:
	-rm *.o
	-rm *.hi
	-rm *.exe
