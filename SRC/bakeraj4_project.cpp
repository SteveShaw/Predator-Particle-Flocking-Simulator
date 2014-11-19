// Copyright 2014 Aaron Baker (bakeraj4)

#include <iostream>
#include <vector>
#include "FlockItem.h"
#include <stdlib.h>
#include <time.h>
#include <string> 

#DEFINE Flock std::vector<FlockItem>

Flock makeFlock(int amnt, int level) {
	Flock ret = Flock();
	for(int i = 0; i < amnt; i++) {
		ret.push_back(FlockItem(level));
	}
	return ret;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "There were not engough parameters.\n"
		    << "There needs to be <(CPU|GPU) number of objects to flock.";
		return -1;
    }
	
	srand(time(NULL));
	
//  Flock flock = makeFlock(std::stoi(argv[2]));
//  GL gl = createGL();
//	CL cl = createCL("file.cl", "function_name", gl);
//	EXP exp = createProject(cl, flock)
}