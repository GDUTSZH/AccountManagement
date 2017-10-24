rm ./*.o

make

g++ -levent main.o Interface.h Register.h HttpCommon.o Error.o Login.o Play.o -o main

rm ./*.o
rm ./*.d
