enigma: enigma.o utils.o cryptography.o
	g++ ./build/enigma.o ./build/utils.o -o ./build/enigma

enigma.o:
	g++ -c ./src/enigma.cpp -o ./build/enigma.o

utils.o:
	g++ -c ./src/utils.cpp -o ./build/utils.o

cryptography.o:
	g++ -c ./src/cryptography.cpp -o ./build/cryptography.o

run: enigma
	./build/enigma

clean:
	rm ./build/*