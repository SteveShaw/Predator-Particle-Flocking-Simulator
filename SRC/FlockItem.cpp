// Copyright 2014 Aaron Baker (bakeraj4)

#include <vector>
#include "FlockItem.h"
#include <stdlib.h>
#include <iostream>

#define Vec std::vector<float>

void FlockItem::initVecs(int nMembers) {
	posX = Vec(nMembers);
	posY = Vec(nMembers);
	posZ = Vec(nMembers);
	rotTheta = Vec(nMembers);
	rotEpsilon = Vec(nMembers);
	vels = Vec(nMembers);
}

FlockItem::FlockItem(int level, std::string& name, int nMembers) {
	initVecs(nMembers);
    // 7 random floats [-x, x] for pos, [0, pi] rotTheta, [0, 2pi) rotElpson, [-2, 2] vel
	for (int i = 0; i < nMembers; i++) {
		float r1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float r2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float r3 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	
		// The range based om the current view point is [-2,2]

		r1 = (r1 * level) - ((float) level / 2.0f);
		r2 = (r2 * level) - ((float) level / 2.0f);
		r3 = (r3 * level) - ((float) level / 2.0f);
	
		posX[i] = r1;
		posY[i] = r2;
		posZ[i] = r3;

		r1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		r2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		r1 = (r1 * (2 * 3.14f));
		r2 = (r2 * 3.14f);
	
		setRotTheta(r1, i);
		setRotEpsilon(r2, i);
	
		r1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		vels[i] = ((r1 + level) * 4.0f) - 2.0f;
	}
	amnt = nMembers;
	foodChainLevel = level;
	pName = name;
}

Vec FlockItem::getPosX() {
	return posX;
}

Vec FlockItem::getPosY() {
	return posY;
}

Vec FlockItem::getPosZ() {
	return posZ;
}

Vec FlockItem::getRotTheta() {
	return rotTheta;
}

Vec FlockItem::getRotEpsilon() {
	return rotEpsilon;
}

Vec FlockItem::getVels() {
	return vels;
}

float FlockItem::getPosX(int index) {
	return posX[index];
}

float FlockItem::getPosY(int index) {
	return posY[index];
}

float FlockItem::getPosZ(int index) {
	return posZ[index];
}

float FlockItem::getRotTheta(int index) {
	return rotTheta[index];
}

float FlockItem::getRotEpsilon(int index) {
	return rotEpsilon[index];
}

float FlockItem::getVels(int index) {
	return vels[index];
}

void FlockItem::addPosX(float n_x, int index) {
	posX[index] += n_x;
}

void FlockItem::addPosY(float n_y, int index) {
	posY[index] += n_y;
}

void FlockItem::addPosZ(float n_z, int index) {
	posZ[index] += n_z;
}

void FlockItem::setRotTheta(float n_x, int index) {
	rotTheta[index] = n_x;
}

void FlockItem::setRotEpsilon(float n_y, int index) {
	rotEpsilon[index] = n_y;
}

int FlockItem::getAmnt() {
	return amnt;
}

int FlockItem::getLevel() {
	return foodChainLevel;
}

std::string FlockItem::getPName() {
	return pName;
}

void FlockItem::move(unsigned int index) {
	// x += precentX * vel
	// y += percentY * vel
	// z += percentZ * vel
	// the spherical cordianates of the roation
	float amntX, amntY, amntZ;
	amntX = sin(rotTheta[index]) * cos(rotEpsilon[index]);
	amntY = sin(rotTheta[index]) * sin(rotEpsilon[index]);
	amntZ = cos(rotTheta[index]);
	addPosX((amntX * vels[index]), index);
	addPosY((amntY * vels[index]), index);
	addPosZ((amntZ * vels[index]), index);
}

void FlockItem::move() {
	for (unsigned int i = 0; i < amnt; i++) {
		move(i);
	}
}