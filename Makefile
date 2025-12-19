enigma: enigma.o utils.o
	g++ ./out/enigma.o ./out/utils.o -o ./build/enigma

enigma.o:
	g++ -c ./src/enigma.cpp -o ./out/enigma.o

utils.o:
	g++ -c ./src/utils.cpp -o ./out/utils.o

run: enigma
	./build/enigma

clean:
	rm ./build/*
	rm ./out/*