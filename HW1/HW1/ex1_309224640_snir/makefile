COMP = g++-5.3.0
#put all your object files here
OBJS = Main.o Parser.o Puzzle.o BaseSolver.o RotationRecursiveSolver.o TopRecursiveSolver.o RightRecursiveSolver.o BottomRecursiveSolver.o LeftRecursiveSolver.o Element.o 
#The executable filename DON'T CHANGE
EXEC = ex2
CPP_COMP_FLAG = -std=c++14 -Wall -Wextra \
-Werror -pedantic-errors -DNDEBUG

$(EXEC): $(OBJS)
	$(COMP) $(OBJS) -o $@
#a rule for building a simple c++ source file
#use g++ -MM main.cpp to see dependencies
Main.o: Main.cpp Parser.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

Parser.o: Parser.cpp Parser.h Puzzle.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
	
Puzzle.o: Puzzle.cpp Puzzle.h BaseSolver.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
	
BaseSolver.o: BaseSolver.cpp BaseSolver.h Element.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
	
RotationRecursiveSolver.o : RotationRecursiveSolver.cpp RotationRecursiveSolver.h BaseSolver.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
	
TopRecursiveSolver.o: TopRecursiveSolver.cpp TopRecursiveSolver.h BaseSolver.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
	
LeftRecursiveSolver.o: LeftRecursiveSolver.cpp LeftRecursiveSolver.h BaseSolver.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
	
BottomRecursiveSolver.o: BottomRecursiveSolver.cpp BottomRecursiveSolver.h Puzzle.h BaseSolver.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
	
RightRecursiveSolver.o: RightRecursiveSolver.cpp RightRecursiveSolver.h Puzzle.h BaseSolver.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

Element.o: Element.cpp Element.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
	
clean:
	rm -f $(OBJS) $(EXEC)