enigma: enigma.o utils.o
	g++ ./build/enigma.o ./build/utils.o -o ./build/enigma

enigma.o:
	g++ -c ./src/enigma.cpp -o ./build/enigma.o

utils.o:
	g++ -c ./src/utils.cpp -o ./build/utils.o

run: enigma
	./build/enigma

clean:
	rm ./build/*