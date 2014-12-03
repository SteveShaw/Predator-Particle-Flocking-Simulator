#include "CLHandler.h"
#include <math.h>
#include <vector>
#pragma once

typedef std::vector<float> floats;

#define HUNT_W 0.5
#define HIDE_FROM_ONE_W 0.5
#define HIDE_FROM_ALL_W 0.5
#define ALIGN_W 0.5
#define SEPERATE_W 0.5
#define COHESION_W 0.5

/*
int getDevType(const std::string& device) throw(std::runtime_error) {
    const std::string DevTypes = "CPUGPUACC";
    switch (DevTypes.find(device)) {
    case 0: return CL_DEVICE_TYPE_CPU;
    case 3: return CL_DEVICE_TYPE_GPU;
    case 6: return CL_DEVICE_TYPE_ACCELERATOR;
    }
    throw std::runtime_error("Invalid device type specified");
} */

void CLHandler::resetAverages() {
	avePosX = floats(particles->size(), 0.0f);
	avePosY = floats(particles->size(), 0.0f);
	avePosZ = floats(particles->size(), 0.0f);
	aveRotE = floats(particles->size(), 0.0f);
	aveRotT = floats(particles->size(), 0.0f);
}

void CLHandler::calcAverages() {
	// OpenCL HERE
	// for (itn i =0; i < partilces.size)(;i++) {
	//		cl::Buffer pxBuff = queue.makeBuffer(&(particles->at(i).getPosx()[0]), sizeof(float) * particles->at(i).size(), queue.ROFlags);
	//		cl::Buffer pyBuff = queue.makeBuffer(&(particles->at(i).getPosy()[0]), sizeof(float) * particles->at(i).size(), queue.ROFlags);
	//		cl::Buffer pzBuff = queue.makeBuffer(&(particles->at(i).getPosz()[0]), sizeof(float) * particles->at(i).size(), queue.ROFlags);
	//		// vector average x, y, z. 
	//		// vecotr averae rott rote
	//		// buffers for those two
	//		functs[0](pxBuff, pyBuff, pzBuff, avPosBuff, aveRotBuff, particles->at(i).size());
	//		// enqueue the averages back
	//		// save them
	// }
}

floats CLHandler::hunt(int myIndex, int preyIndex) {
	floats ret;
	// OpenCL HERE
	return ret;
}

floats CLHandler::hideFromClosestPackMember(int myIndex, int predIndex) {
	floats ret;
	// OpenCL HERE
	return ret;
}

floats CLHandler::hideFromPack(int myIndex, int predIndex) {
	floats ret;
	// OpenCL HERE
	return ret;
}

floats CLHandler::alignment(int myIndex) {
	floats ret;
	// OpenCl HERE
	return ret;
}

floats CLHandler::seperation(int myIndex) {
	floats ret;
	// OpenCL HERE
	return ret;
}

floats CLHandler::cohesion(int myIndex) {
	floats ret;
	// OpenCL HERE
	return ret;
}

void CLHandler::oneIterationOfFlocking() {
	// get the average posistions and the rots to the vectors
	float deltaRotE = 0.0f;
	float deltaRotT = 0.0f;
	floats tmp;

	for (unsigned int i = 0; i < particles->size(); i++) {
		deltaRotE = 0.0f;
		deltaRotT = 0.0f;
		if (i != 0) {
			// hunt the closest particle.
			tmp = hunt(i, i - 1);
			deltaRotT += tmp[0] * HUNT_W;
			deltaRotE += tmp[1] * HUNT_W;
		} else if(i != particles->size() - 1) {
			// hide from closest hunter
			tmp = hideFromClosestPackMember(i, i + 1);
			deltaRotT += tmp[0] * HIDE_FROM_ONE_W;
			deltaRotE += tmp[1] * HIDE_FROM_ONE_W;

			// hide from all hunters
			tmp = hideFromPack(i, i + 1);
			deltaRotT += tmp[0] * HIDE_FROM_ALL_W;
			deltaRotE += tmp[1] * HIDE_FROM_ALL_W;
		}

		// alignment
		tmp = alignment(i);
		deltaRotT += tmp[0] * ALIGN_W;
		deltaRotE += tmp[1] * ALIGN_W;

		// seperation
		tmp = seperation(i);
		deltaRotT += tmp[0] * SEPERATE_W;
		deltaRotE += tmp[1] * SEPERATE_W;

		// cohesion
		tmp = cohesion(i);
		deltaRotT += tmp[0] * COHESION_W;
		deltaRotE += tmp[1] * COHESION_W;

		deltaRotT = fmod(deltaRotT, 3.14f); // deltaRotT % 3.14f;
		deltaRotE = fmod(deltaRotE, (3.14f * 2.0f)); // deltaRotE % (2.0f * 3.14f);

		// add in the deltaRotE and T to each praticle in vector[i].
		for (unsigned int j = 0; j < particles[i].size(); j++) {
			particles->at(i).addRotT(deltaRotT, j);
			particles->at(j).addRotE(deltaRotE, j);
		}
	} // [0, pi] rotTheta, [0, 2pi) rotElpson
}


// INFINITY


////////////////////////////////////////////////////////////
// THIS BELOW WAS OLD CODE! I MAY WANT TO RE-USE IT SOMEHOW!

/*
std::string CL::readKernel(std::string fileName) {
	std::string ret = "";


	return ret;
}

CL::CL(std::vector<FlockItem>* flocks, std::vector<std::string>& kerenelFile,
		std::vector<std::string> kernelFuncts) {
	particles = flocks;
	for (unsigned int i = 0; i < kerenelFile.size(); i++) {
		// scources.push_back(readKernel(kerenelFile[i]));
	}
	kernelFunctions = kernelFuncts;
}
*/