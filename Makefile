objects = build/vector2D.o build/mass.o build/spring.o build/ropesim.o build/model.o build/view.o build/controller.o  build/main.o 
all: $(objects) rpe
CFLAGS= -O3

build/vector2D.o: src/vector2D.cpp include/vector2D.hpp
	g++ $(CFLAGS) -c src/vector2D.cpp -o build/vector2D.o
	
build/mass.o: src/mass.cpp include/mass.hpp
	g++ $(CFLAGS) -c src/mass.cpp -o build/mass.o

build/spring.o: src/spring.cpp include/spring.hpp
	g++ $(CFLAGS) -c src/spring.cpp -o build/spring.o

build/ropesim.o: src/ropesim.cpp
	g++ $(CFLAGS) -c src/ropesim.cpp -o build/ropesim.o

build/model.o: src/model.cpp
	g++ $(CFLAGS) -c src/model.cpp -o build/model.o

build/controller.o: src/controller.cpp
	g++ $(CFLAGS) -c src/controller.cpp -o build/controller.o

build/view.o: src/view.cpp
	g++ $(CFLAGS) -c src/view.cpp -o build/view.o

build/main.o: src/main.cpp
	g++ $(CFLAGS) -c src/main.cpp -o build/main.o

rpe: ${objects}
	g++ $(CFLAGS) -o rpe $(objects) -lsfml-graphics -lsfml-window -lsfml-system -lm

clean:
	rm -f build/*
	rm -f rpe
