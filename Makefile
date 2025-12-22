enigma: enigma.o utils.o cryptography.o
	g++ -O3 -march=native ./build/enigma.o ./build/utils.o -o ./build/enigma

enigma.o:
	g++ -O3 -march=native -c ./src/enigma.cpp -o ./build/enigma.o

utils.o:
	g++ -O3 -march=native -c ./src/utils.cpp -o ./build/utils.o

cryptography.o:
	g++ -O3 -march=native -c ./src/cryptography.cpp -o ./build/cryptography.o

run: enigma
	./build/enigma

clean:
	rm ./build/*