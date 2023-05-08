# make -f main-only.mak

# final linking
mian: 
	g++ -o ./out/mian.o ./src/main.cpp
# clean
clean:
	rm -f ./out/mian.o