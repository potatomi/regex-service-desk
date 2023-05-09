# final linking
mian: 
	mkdir -p out
	g++ -o ./out/mian.o ./src/main.cpp

run:
	./out/mian.o
# clean
clean:
	rm -f ./out/mian.o