.default: all

all: sjf

clean:
	rm -rf ppd *.o *.dSYM

sjf: main.o ../pcb.o ../processor.o ../schedules.o
	g++ -Wall -Werror -std=c++20 -g -O -o ../$@ $^

# rule for compiling .cpp files
%.o: %.cpp
	g++ -Wall -Werror -std=c++20 -g -O -c $<