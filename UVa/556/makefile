CC = g++
CWARFLAGS = -ansi -pedantic -Wextra -Wall -W -Weffc++ \
            -Wfloat-equal -Wconversion -Wshadow -Wcast-qual -Wwrite-strings -Wfloat-equal \
            -Wpointer-arith -Wcast-align -Wswitch-default -Wswitch-enum \
            -Wunreachable-code -Wformat=2 -std=c++11 -pipe 
COPTFLAGS = -O0
CASSGENFLAGS = -S -fverbose-asm
CLIBS = -lm -lcrypt

main:	main.cpp
	$(CC) main.cpp -o main $(CWARFLAGS) $(COPTFLAGS) $(CLIBS)
	