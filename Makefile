# Copyright 2016, Gurobi Optimization, Inc.

PLATFORM = linux64
INC      = $(GUROBI_HOME)/include/
CC       = gcc
CPP      = g++
CARGS    = -m64 -g
CLIB     = -L$(GUROBI_HOME)/lib/ -lgurobi70
CPPLIB   = -L$(GUROBI_HOME)/lib/ -lgurobi_c++ -lgurobi70
EXEC     = mochila_frac

mochila_frac: mochila_frac.cpp
	$(CPP) $(CARGS) -o $(EXEC) mochila_frac.cpp -I$(INC) $(CLIB) -lm

clean:
	rm -rf $(EXEC)
	rm -rf mochila *.o
	rm -rf *.out
