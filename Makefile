all: run

run:
	g++ -std=c++11 main.cpp -o main.exe

clean:
	rm -rf *.exe