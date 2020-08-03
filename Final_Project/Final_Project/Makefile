output: Final_Project.o Reversi.o
        g++ Final_Project.o Reversi.o -o output
Final_Project.o: Final_Project.cpp
        g++ -c -O5 Final_Project.cpp
Reversi.o: Reversi.cpp Reversi.h
        g++ -c -O5 Reversi.cpp
clean:
        rm *.o output