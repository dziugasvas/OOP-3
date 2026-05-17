all: create

create:
	g++ -std=c++17 -Iinclude src/main.cpp src/funkcijos.cpp -o programa

O1:
	g++ -std=c++17 -O1 src/main.cpp src/funkcijos.cpp -o programa
	./programa

O2:
	g++ -std=c++17 -O2 src/main.cpp src/funkcijos.cpp -o programa
	./programa

O3:
	g++ -std=c++17 -O3 src/main.cpp src/funkcijos.cpp -o programa
	./programa

run: create
	./programa
	
gtest:
	g++ -std=c++17 -Iinclude \
		-I/opt/homebrew/include \
		-L/opt/homebrew/lib \
		src/funkcijos.cpp tests/testas.cpp tests/vectorTests.cpp \
		-lgtest -lgtest_main -lpthread \
		-o testai && ./testai
		
speedtest:
	g++ -std=c++17 -Iinclude tests/VectorSpeedTest.cpp -o speedtest && ./speedtest

clean:
	rm -f programa testai
