%.exe: %.cpp mylib.o
	g++ --std=c++14 -o $@ $^

mylib.o: mylib.cpp
	g++ -c --std=c++14 -o $@ $<

clean:
	-rm *.o
	-rm *.exe
