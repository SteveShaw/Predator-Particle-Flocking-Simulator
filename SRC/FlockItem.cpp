// Copyright 2014 Aaron Baker (bakeraj4)

#include <vector>
#include "FlockItem.h"
#include <stdlib.h>

#define std::<float> Vec4
		
FlockItem::FlockItem(int level) {
    // 7 random floats [-10, 10] for pos, [0, 2pi] rot, [-2, 2] vel
	float r1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float r2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float r3 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	r1 = (r1 * 20.0f) - 10.0f;
	r2 = (r2 * 20.0f) - 10.0f;
	r3 = (r3 * 20.0f) - 10.0f;
	
	updatePos(Vec4(r1, r2, r3, 1.0f));
	
	r1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	r2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	r3 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	r1 = (r1 * (2 * 3.14f));
	r2 = (r1 * (2 * 3.14f));
	r3 = (r1 * (2 * 3.14f));
	
	updateRot(Vec4(r1, r2, r3, 1.0f));
	
	r1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	updateVel(r1 * 4.0f) - 2.0f;
	
	foodChainLevel = level;
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