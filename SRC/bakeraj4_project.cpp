// Copyright 2014 Aaron Baker (bakeraj4)

#include <iostream>
#include <vector>
#include "FlockItem.h"
#include <stdlib.h>
#include <time.h>
#include <string> 
#include <fstream>
#include <unordered_map>
#include <GL/freeglut.h>
#pragma once

typedef FlockItem Flock;
typedef std::unordered_map<unsigned int, std::vector<float>> Colors;

const int W = 512, H = 512, SLICES = 25, STACKS = 20;
std::vector<Flock> allParticles;
Colors c;

void display(void); // forward declaration

void moveAllFlocks() {
	for (Flock& f: allParticles) {
		f.move();
	}
	display(); // HERE FOR NOW. ONLY FOR ANIMATION
}

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

void setColor(unsigned int num) {
	glColor3f((GLfloat)c[num][0], (GLfloat)c[num][1], (GLfloat)c[num][2]);
	std::cout << "COLOR:\n" << c[num][0] << "\t" << c[num][1] << "\t" << c[num][2] << "\n";
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1, 2, 3, 0, 0, 0, 0, 1, 0);

	glLineWidth(4);
	std::cout << allParticles.size();
	for (unsigned int i = 0; i < allParticles.size(); i++) {
		setColor(i);
		std::cout << "\nlevel : " << i << "\n";
		for(unsigned int j = 0; j < allParticles[i].getAmnt(); j++) {
			std::cout << allParticles[i].getPosX(j) << "\t" << allParticles[i].getPosY(j) << "\t" << allParticles[i].getPosZ(j) << "\n";
			IT(1, 1, 1, allParticles[i].getPosX(j), allParticles[i].getPosY(j), allParticles[i].getPosZ(j), 0, 0, 1, 0);
		}
	}

	glFlush();
	glutSwapBuffers();
	// hunting here
	moveAllFlocks();
}

// static bool continueSimulatoion = true	

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
		particles.push_back(FlockItem(level, pName, amnt));
		++level;
	}
	
	file.close();
	return particles;
}

void setUpColors() {
	// only 10 colors for now
	std::vector<float> color;
	// red
	color.push_back(1.0f);
	color.push_back(0.0);
	color.push_back(0.0);
	c[0] = color;
	color.clear();
	// green
	color.push_back(0.0f);
	color.push_back(1.0);
	color.push_back(0.0);
	c[1] = color;
	color.clear();
	// blue
	color.push_back(0.0f);
	color.push_back(0.0);
	color.push_back(1.0);
	c[2] = color;
	color.clear();
	// white
	color.push_back(1.0f);
	color.push_back(1.0);
	color.push_back(1.0);
	c[3] = color;
	color.clear();
	// orange
	color.push_back(1.0f);
	color.push_back(106.0f / 255.0f);
	color.push_back(0.0);
	c[4] = color;
	color.clear();
	// yellow
	color.push_back(251.0f / 255.0f);
	color.push_back(1.0f);
	color.push_back(56.0f / 255.0f);
	c[5] = color;
	color.clear();
	// purple
	color.push_back(178.0f / 255.0f);
	color.push_back(0.0);
	color.push_back(1.0);
	c[6] = color;
	color.clear();
	// pink
	color.push_back(1.0f);
	color.push_back(127.0f / 255.0f);
	color.push_back(179.0f / 255.0f);
	c[7] = color;
	color.clear();
	// dark pink
	color.push_back(122.0f / 255.0f);
	color.push_back(61.0f / 255.0f);
	color.push_back(86.0f / 255.0f);
	c[8] = color;
	color.clear();
	// grey
	color.push_back(158.0f / 255.0f);
	color.push_back(158.0f / 255.0f);
	color.push_back(158.0f / 255.0f);
	c[9] = color;
	color.clear();
}

void openGLSetUp() {
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
	float gray[4] = {0.5,0.5,0.5,1};
	float pos[4] = {0,0,10,1};
	glLightfv(GL_LIGHT0, GL_AMBIENT, gray);
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
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
	setUpColors();
	glutInit(&argc, argv);
	openGLSetUp();
	glutMainLoop();

//	CL cl = createCL("file.cl", "function_name", &allParticles);
//	EXP exp = createProject(cl, flock)
}