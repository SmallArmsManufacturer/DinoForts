EXECUTABLE  = DinoForts
VPATH      += src
CXXFLAGS   += -Wall -Werror -std=c++11 -stdlib=libc++
LDFLAGS    += -Wall -Werror -std=c++11 -stdlib=libc++ -framework OpenGL -lglfw

.PHONY: all clean run

all: $(EXECUTABLE)

clean:
	rm -f *.o $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

$(EXECUTABLE): $(patsubst src/%.cpp, %.o, $(wildcard src/*.cpp))
	$(CXX) $(LDFLAGS) $^ -o $@
