all:
	g++ -L../lib -g -std=c++14 -I../build/glfw-3.2.1/include src/main.cpp src/shader.cpp src/renderer.cpp -o build -lglfw -lGLEW -lGL

run: all
	./build
