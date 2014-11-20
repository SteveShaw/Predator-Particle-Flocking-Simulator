// Copyright 2014 Aaron Baker (bakeraj4)

#include <vector>
#include "FlockItem.h"
#include <stdlib.h>
#include <iostream>

#define Vec4 std::vector<float>
		
FlockItem::FlockItem(int level, std::string& name) {
    // 7 random floats [-10, 10] for pos, [0, 2pi] rot, [-2, 2] vel
	float r1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float r2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float r3 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	r1 = (r1 * ((20.0f * level) + 1.0f))
		- (((10.0f + (float) level) + 1.0f) / 2.0f);
	r2 = (r2 * ((20.0f * level) + 1.0f))
		- (((10.0f + (float) level) + 1.0f) / 2.0f);
	r3 = (r3 * ((20.0f * level) + 1.0f))
		- (((10.0f + (float) level) + 1.0f) / 2.0f);
	
	Vec4 tmp;
	tmp.push_back(r1);
	tmp.push_back(r2);
	tmp.push_back(r3);
	tmp.push_back(1.0f);
	
	updatePos(tmp);
	tmp.clear();
	
	r1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	r2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	r3 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	r1 = (r1 * (2 * 3.14f));
	r2 = (r1 * (2 * 3.14f));
	r3 = (r1 * (2 * 3.14f));
	
	tmp.push_back(r1);
	tmp.push_back(r2);
	tmp.push_back(r3);
	tmp.push_back(1.0f);
	
	updateRot(tmp);
	tmp.clear();
	
	r1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	updateVel(((r1 + level) * 4.0f) - 2.0f);
	
	foodChainLevel = level;
	pName = name;
}

Vec4 FlockItem::getRot() {
	return rot;
}

void FlockItem::updateRot(Vec4 n_rot) {
	rot = n_rot;
}

Vec4 FlockItem::getPos() {
	return pos;
}

void FlockItem::updatePos(Vec4 n_pos) {
	pos = n_pos;
}

float FlockItem::getVel() {
	return vel;
}

void FlockItem::updateVel(float n_vel) {
	vel = n_vel;
}

int FlockItem::getLevel() {
	return foodChainLevel;
}