EXECUTABLE  = DinoForts
VPATH      += src
CXXFLAGS   += -Wall -Werror
LDFLAGS    += -Wall -Werror

include $(shell echo Makefile_`uname`)

.PHONY: all clean run

all: $(EXECUTABLE)

clean:
	rm -f *.o *.d $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

$(EXECUTABLE): $(patsubst src/%.cpp, %.o, $(wildcard src/*.cpp))
	$(CXX) $^ -o $@ $(LDFLAGS)

%.d: src/%.cpp
	$(CXX) $(CXXFLAGS) -MM $< > $@

ifneq ($(MAKECMDGOALS),clean)
-include $(patsubst src/%.cpp, %.d, $(wildcard src/*.cpp))
endif
