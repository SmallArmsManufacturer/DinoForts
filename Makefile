EXECUTABLE  = DinoForts
VPATH      += src
CXXFLAGS   += -Wall -Werror -std=c++11 -stdlib=libc++
LDFLAGS    += -Wall -Werror -std=c++11 -stdlib=libc++ -framework OpenGL -lglfw

.PHONY: all clean run

all: $(EXECUTABLE)

clean:
	rm -f *.o *.d $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

$(EXECUTABLE): $(patsubst src/%.cpp, %.o, $(wildcard src/*.cpp))
	$(CXX) $(LDFLAGS) $^ -o $@

%.d: src/%.cpp
	$(CXX) $(CXXFLAGS) -MM $< > $@

ifneq ($(MAKECMDGOALS),clean)
-include $(patsubst src/%.cpp, %.d, $(wildcard src/*.cpp))
endif
