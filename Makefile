all:
	g++ -v -I include -L lib -o hello-word src/hello-word.cpp -lmingw32 -lSDL2main -lSDL2