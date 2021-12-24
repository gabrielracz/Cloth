objects = build/vector2D.o build/mass.o build/spring.o build/ropesim.o build/main.o 
all: $(objects) rpe

build/vector2D.o: src/vector2D.cpp include/vector2D.hpp
	g++ -O3 -c src/vector2D.cpp -o build/vector2D.o
	
build/mass.o: src/mass.cpp include/mass.hpp
	g++ -O3 -c src/mass.cpp -o build/mass.o

build/spring.o: src/spring.cpp include/spring.hpp
	g++ -O3 -c src/spring.cpp -o build/spring.o

build/ropesim.o: src/ropesim.cpp
	g++ -O3 -c src/ropesim.cpp -o build/ropesim.o

build/main.o: src/main.cpp
	g++ -O3 -c src/main.cpp -o build/main.o


rpe: ${objects}
	g++ -O3 -o rpe $(objects) -lsfml-graphics -lsfml-window -lsfml-system -lm

clean:
	rm -f build/*
	rm -f rpe