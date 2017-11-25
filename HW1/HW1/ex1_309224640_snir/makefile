COMP = g++-5.3.0
#put all your object files here
OBJS = Main.o Parser.o Puzzle.o Element.o
#The executable filename DON'T CHANGE
EXEC = ex1
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
	
Puzzle.o: Puzzle.cpp Puzzle.h Element.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

Element.o: Element.cpp Element.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
	
clean:
	rm -f $(OBJS) $(EXEC)