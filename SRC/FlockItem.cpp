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
	rotX = Vec(nMembers);
	rotY = Vec(nMembers);
	rotZ = Vec(nMembers);
	vels = Vec(nMembers);
}

FlockItem::FlockItem(int level, std::string& name, int nMembers) {
	initVecs(nMembers);
    // 7 random floats [-x, x] for pos, [0, 2pi] rot, [-2, 2] vel
	for (int i = 0; i < nMembers; i++) {
		float r1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float r2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float r3 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	
		// The range based om the current view point is [-2,2]

		r1 = (r1 * level) - ((float) level / 2.0f);
		r2 = (r2 * level) - ((float) level / 2.0f);
		r3 = (r3 * level) - ((float) level / 2.0f);
	
		setPosX(r1, i);
		setPosY(r2, i);
		setPosZ(r3, i);

		r1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		r2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		r3 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		r1 = (r1 * (2 * 3.14f));
		r2 = (r1 * (2 * 3.14f));
		r3 = (r1 * (2 * 3.14f));
	
		setRotX(r1, i);
		setRotY(r2, i);
		setRotZ(r3, i);
	
		r1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		setVel(((r1 + level) * 4.0f) - 2.0f, i);
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

Vec FlockItem::getRotX() {
	return rotX;
}

Vec FlockItem::getRotY() {
	return rotY;
}

Vec FlockItem::getRotZ() {
	return rotZ;
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

float FlockItem::getRotX(int index) {
	return rotX[index];
}

float FlockItem::getRotY(int index) {
	return rotY[index];
}

float FlockItem::getRotZ(int index) {
	return rotZ[index];
}

float FlockItem::getVels(int index) {
	return vels[index];
}

void FlockItem::setPosX(float n_x, int index) {
	posX[index] = n_x;
}

void FlockItem::setPosY(float n_y, int index) {
	posY[index] = n_y;
}

void FlockItem::setPosZ(float n_z, int index) {
	posZ[index] = n_z;
}

void FlockItem::setRotX(float n_x, int index) {
	rotX[index] = n_x;
}

void FlockItem::setRotY(float n_y, int index) {
	rotY[index] = n_y;
}

void FlockItem::setRotZ(float n_z, int index) {
	rotZ[index] = n_z;
}

void FlockItem::setVel(float n_v, int index) {
	vels[index] = n_v;
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