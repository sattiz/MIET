CXX = g++
CPPFLAGS = $(-Wall -pedantic)

all:
	@$(CXX) $(CPPFLAGS) -c *.cpp
	@$(CXX) $(CPPFLAGS) -o app.out *.o

run:
	./app.out

clean:
	@rm -f *.o app.out
