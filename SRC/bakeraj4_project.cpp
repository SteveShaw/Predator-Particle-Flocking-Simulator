// Copyright 2014 Aaron Baker (bakeraj4)

#include <iostream>
#include <vector>
#include "FlockItem.h"
#include "CLHandler.h"
#include <stdlib.h>
#include <time.h>
#include <string> 
#include <fstream>
#include <unordered_map>
#include <GL/freeglut.h>
#include <iterator>
#pragma once

typedef FlockItem Flock;
typedef std::unordered_map<unsigned int, std::vector<float>> Colors;

const int W = 512, H = 512, SLICES = 25, STACKS = 20;
std::vector<Flock> allParticles;
Colors c;
CLHandler clH;
float numMin;
clock_t t;
double timerInterval = 0.00001;
int generations = 0;
float genTime = 0.5f;
std::ofstream output;

void display(void); // forward declaration

bool continueExperiment() {
	float timePassed = ((((float)(clock() - t)) / CLOCKS_PER_SEC) / 60.0f);
	std::cout << "Time passed = " << timePassed << "\n";
	if (timePassed >= numMin) { 
		return false;
	}
	for (unsigned int i = 0; i < allParticles.size(); i++) {
		if (allParticles[i].getAmnt() == 0 || allParticles[i].getAmnt() > allParticles[i].getThreshold()) {
			return false;
		}
	}
	return true;
}

std::vector<std::string> kernelFiles() {
	std::vector<std::string> ret;
	ret.push_back("averagePosRot.cl");
	ret.push_back("hunt.cl");
	ret.push_back("hideFromHunter.cl");
	ret.push_back("hideFromHunters.cl");
	ret.push_back("alignment.cl");
	ret.push_back("seperation.cl");
	ret.push_back("cohesion.cl");
	return ret;
}

std::vector<std::string> kernelFuncts() {
	std::vector<std::string> ret;
	ret.push_back("avePosRot");
	ret.push_back("hunt");
	ret.push_back("hideFromHunter");
	ret.push_back("hideFromHunters");
	ret.push_back("align");
	ret.push_back("seperate");
	ret.push_back("cohesion");
	return ret;
}

void moveAllFlocks() {
	for (unsigned int i = allParticles.size(); i > 0; i--) {
		if (i != 1 ) {
			allParticles[i - 1].eatPrey(allParticles[i - 2]);
		}
		allParticles[i - 1].move();
	}
	if (continueExperiment()) {
		float timePassed = ((((float)(clock() - t)) / CLOCKS_PER_SEC) / 60.0f);
		if (timePassed >= genTime) {
			generations++;
			genTime += 0.5;
			output << "Generation " << generations << " at time " << timePassed << " seconds\n";
			for (unsigned int i = 0; i < allParticles.size(); i++) {
				allParticles[i].populate(clH.getAvePosX()[i], clH.getAvePosY()[i], clH.getAvePosZ()[i]);
				output << allParticles[i].toString() << "\n";
			}
			output << "*******************************************************************************\n";
		 }
	} else {
		// closes the file
		output.close();
		// terminate the program with sucess
		exit(0);
	}
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
	// std::cout << "COLOR:\n" << c[num][0] << "\t" << c[num][1] << "\t" << c[num][2] << "\n";
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1, 2, 3, 0, 0, 0, 0, 1, 0);

	glLineWidth(4);
//	std::cout << allParticles.size();
	for (unsigned int i = 0; i < allParticles.size(); i++) {
		setColor(i);
//		std::cout << "\nlevel : " << i << "\t Has " << allParticles[i].getAmnt() << "many partiles.\n";
		for(unsigned int j = 0; j < allParticles[i].getAmnt(); j++) {
//			std::cout << allParticles[i].getPosX(j) << "\t" << allParticles[i].getPosY(j) << "\t" << allParticles[i].getPosZ(j) << "\n";
			IT(1, 1, 1, allParticles[i].getPosX(j), allParticles[i].getPosY(j), allParticles[i].getPosZ(j), 0, 0, 1, 0);
		}
	}

	glFlush();
	glutSwapBuffers();
	clH.oneIterationOfFlocking();
	moveAllFlocks();

	// call it back
	glutPostRedisplay();
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
    if (argc != 4) {
        std::cout << "There were not engough parameters.\n"
		    << "There needs to be <(CPU|GPU) (input file) (mins to run)>.\n"
			<< "The user provided " << argc << " many arguments.\nAnd they are:\n";
			for (int i = 0; i < argc; i++ ) {
				std::cout << argv[i] << "\n";
			}
		return -1;
    }
	// creates my log file
	output.open("ParticleTest.dat");
	// seeding random numbers
	srand(time(NULL));
	// file name of input file
	std::string file(argv[2]);
	// creates the particles
	allParticles = makeAllParticles(file);
	// write intro stuff
	output << "Generation 0 (input) at time = 0.0 seconds\n";
	for (unsigned int i = 0; i < allParticles.size(); i++) {
		output << allParticles[i].toString() << "\n";
	}
	output << "*******************************************************************************\n";
	// creates my color map
	setUpColors();
	// OpenGL things
	glutInit(&argc, argv);
	openGLSetUp();
	// pointer to the particles
	std::vector<Flock>* ptr = &allParticles;
	clH = CLHandler(ptr, kernelFiles(), kernelFuncts(), std::string(argv[1]));

	numMin = std::stof(argv[3]);
	t  = clock();
	glutMainLoop();
}
