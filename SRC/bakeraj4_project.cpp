// Copyright 2014 Aaron Baker (bakeraj4)

#include <iostream>
#include <vector>
#include "FlockItem.h"
#include <stdlib.h>
#include <time.h>
#include <string> 
#include <fstream>
#include <GL/freeglut.h>
#pragma once
typedef std::vector<FlockItem> Flock;
const int W = 512, H = 512, SLICES = 25, STACKS = 20;
std::vector<Flock> allParticles;
float n, l, m;

void sphere() {
	glutSolidSphere(0.01, SLICES, STACKS);
}

void IT(double sx, double sy, double sz, double dx, double dy, double dz,
		double deg, double vx, double vy, double vz) {
	glPushMatrix();
	glTranslatef(dx, dy, dz);
	glRotatef(deg, vx, vy, vz);
	glScalef(sx, sy, sz);
	sphere();
	glPopMatrix();
}


void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1, 2, 3, 0, 0, 0, 0, 1, 0);

	glLineWidth(4);
	std::cout << allParticles.size();
	for (unsigned int i = 0; i < allParticles.size(); i++) {
		l = (float) i; // the level of the current flock
		m = (n - l) / n;
		// set color
		glColor3f(m, m, m);
		std::cout << "\nlevel : " << i << "\n";
		for(unsigned int j = 0; j < allParticles[i].size(); j++) {
			std::cout << allParticles[i][j].getPos()[0] << "\t" << allParticles[i][j].getPos()[1] << "\t" << allParticles[i][j].getPos()[2] << "\n";
			IT(1, 1, 1, allParticles[i][j].getPos()[0], allParticles[i][j].getPos()[1], allParticles[i][j].getPos()[2], 0, 0, 1, 0);
		}
	}

	glFlush();
	glutSwapBuffers();
}


// static bool continueSimulatoion = true	

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
		    << "There needs to be <(CPU|GPU) (input file)>.\n"
			<< "The user provided " << argc << ".\nAnd they are:\n";
			for (int i = 0; i < argc; i++ ) {
				std::cout << argv[i] << "\n";
			}
		return -1;
    }
	
	// create a log file of the state of the program at every generation and an image from the openGL buffer.
	
	srand(time(NULL));
	std::string file(argv[2]);
	allParticles = makeAllParticles(file);
	n = (float) allParticles.size();


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(W, H);
	glutCreateWindow("Experiment");
	glutDisplayFunc(display);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2, 2, -2, 2, -10, 10);

	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);
	float white[4] = {1,1,1,1};
	float gray[4] = {0.5,0.5,0.5,1};
	float black[4] = {0,0,0,1};
	float pos[4] = {0,0,10,1};
	glLightfv(GL_LIGHT0, GL_AMBIENT, gray);
	glLightfv(GL_LIGHT0, GL_POSITION, pos);

	glutMainLoop();

//	CL cl = createCL("file.cl", "function_name", &allParticles);
//	EXP exp = createProject(cl, flock)
}