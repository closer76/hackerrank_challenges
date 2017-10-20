%.exe: %.cpp
	g++ --std=c++14 -o $@ $<
