# The following just specifies some variables for "flexibility".

# Specify the C++ compiler
CXX     = g++

# Specify options to pass to the compiler. Here it sets the optimisation
# level, outputs debugging info for gdb, and C++ version to use.
CXXFLAGS = -O0 -g3 -std=c++17

All: all
all: main

# These are the two executables to be produced
main: main.cpp Object.o Enemy.o Player.o Room.o Objective.o Game.o
	$(CXX) $(CXXFLAGS) main.cpp Object.o Enemy.o Player.o Room.o Objective.o Game.o -o main

# These are the "intermediate" object files
# The -c command produces them
Object.o: Object.cpp Object.h
	$(CXX) $(CXXFLAGS) -c Object.cpp -o Object.o

Enemy.o: Enemy.cpp Enemy.h
	$(CXX) $(CXXFLAGS) -c Enemy.cpp -o Enemy.o

Player.o: Player.cpp Player.h
	$(CXX) $(CXXFLAGS) -c Player.cpp -o Player.o

Room.o: Room.cpp Room.h
	$(CXX) $(CXXFLAGS) -c Room.cpp -o Room.o

Objective.o: Objective.cpp Objective.h
	$(CXX) $(CXXFLAGS) -c Objective.cpp -o Objective.o

Game.o: Game.cpp Game.h
	$(CXX) $(CXXFLAGS) -c Game.cpp -o Game.o

# Some cleanup functions, invoked by typing "make clean" or "make deepclean"
deepclean:
	rm -f *~ *.o main main.exe *.stackdump

clean:
	rm -f *~ *.o *.stackdump
