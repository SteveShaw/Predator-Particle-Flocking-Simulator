// Copyright 2014 Aaron Baker (bakeraj4)

#include <iostream>
#include <vector>
#include "FlockItem.h"
#include <stdlib.h>
#include <time.h>
#include <string> 
#include <fstream>

#define Flock std::vector<FlockItem>

Flock makeFlock(int amnt, int level, std::string& name) {
	Flock ret = Flock();
	for(int i = 0; i < amnt; i++) {
		ret.push_back(FlockItem(level, name));
	}
	return ret;
}

std::vector<Flock> makeAllParticles(std::string& fileName) {
	std::ifstream file(fileName);
	std::string pName, line;
	int level = 0, amnt;
	std::vector<Flock> particles;
	std::size_t found;
	while (getline(file, line)) {
		found = line.find("\t");
		pName = line.substr(0, found);
		amnt = stoi(line.substr(found + 1));
		particles.push_back(makeFlock(amnt, level, pName));
		++level;
	}
	
	file.close();
	return particles;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "There were not engough parameters.\n"
		    << "There needs to be <(CPU|GPU) (input file)>.\n";
		return -1;
    }
	
	// create a log file of the state of the program at every generation and an image from the openGL buffer.
	
	srand(time(NULL));
	std::string file(argv[2]);
	std::vector<Flock> allParticles = makeAllParticles(file);
//  GL gl = createGL(&Particles);
//	CL cl = createCL("file.cl", "function_name", &allParticles, gl);
//	EXP exp = createProject(cl, gl, flock)
}