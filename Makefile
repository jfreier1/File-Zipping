# Configure compiler settings
CXX=clang++
CXXFLAGS=-g -std=c++11 -Werror
# The object files for the program.
OFILES = huffmannode.o zipfunctions.o
# The header files for the program
HFILES = $(shell ls -1 *.h)

# This target builds your main program.
main: $(HFILES) $(OFILES) main.o
	$(CXX) $(CXXFLAGS) -o $@ main.o $(OFILES)

# This target builds your manual testing program.
manualTests: manualTests.o $(HFILES) $(OFILES)
	$(CXX) $(CXXFLAGS) -o $@ manualTests.o $(OFILES)

# This target describes how to compile a .o file from a .cpp file.
%.o: %.cpp $(HFILES)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# This target deletes the temporary files we have built.
.PHONY: clean
clean:
	rm -f *.o
	rm -f huffmannode
	rm -f zipfunctions
	rm -f manualTests
	rm -f main
