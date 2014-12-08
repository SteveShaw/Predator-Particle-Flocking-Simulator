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


int getDevType(const std::string& device) throw(std::runtime_error) {
    const std::string DevTypes = "CPUGPUACC";
    switch (DevTypes.find(device)) {
    case 0: return CL_DEVICE_TYPE_CPU;
    case 3: return CL_DEVICE_TYPE_GPU;
    case 6: return CL_DEVICE_TYPE_ACCELERATOR;
    }
    throw std::runtime_error("Invalid device type specified");
}

void CLHandler::resetAverages() {
	avePosX = floats(particles->size(), 0.0f);
	avePosY = floats(particles->size(), 0.0f);
	avePosZ = floats(particles->size(), 0.0f);
	aveRotE = floats(particles->size(), 0.0f);
	aveRotT = floats(particles->size(), 0.0f);
}

void CLHandler::calcAverages() {
	for (unsigned int i = 0; i < particles->size();i++) {
		floats avePos, aveRot;
		avePos = floats(3, 0.0f);
		aveRot = floats(3, 0.0f);
		cl::Buffer pxBuff = queues[0].makeBuffer(&(particles->at(i).getPosX()[0]), sizeof(float) * particles->at(i).getAmnt(), queues[0].ROFlags);
		cl::Buffer pyBuff = queues[0].makeBuffer(&(particles->at(i).getPosY()[0]), sizeof(float) * particles->at(i).getAmnt(), queues[0].ROFlags);
		cl::Buffer pzBuff = queues[0].makeBuffer(&(particles->at(i).getPosZ()[0]), sizeof(float) * particles->at(i).getAmnt(), queues[0].ROFlags);
		cl::Buffer avePosBuff = queues[0].makeBuffer(&(avePos[0]), sizeof(float) * avePos.size(), queues[0].ROFlags);
		cl::Buffer aveRotBuff = queues[0].makeBuffer(&(aveRot[0]), sizeof(float) * aveRot.size(), queues[0].ROFlags);
		cl::NDRange globalRange(particles->at(i).getAmnt());
		cl::KernelFunctor funct(kernels[0], queues[0].getQueue(), cl::NullRange,
			globalRange, cl::NullRange);
		funct(pxBuff, pyBuff, pzBuff, avePosBuff, aveRotBuff, particles->at(i).getAmnt());
		queues[0].getQueue().enqueueMapBuffer(avePosBuff, CL_TRUE, CL_MAP_READ, 0, 3 * sizeof(float));
		queues[0].getQueue().enqueueMapBuffer(aveRotBuff, CL_TRUE, CL_MAP_READ, 0, 2 * sizeof(float));
		avePosX[i] = avePos[0];
		avePosY[i] = avePos[1];
		avePosZ[i] = avePos[2];
	}
}

std::vector<floats> CLHandler::hunt(int myIndex, int preyIndex) {
	std::vector<floats> ret;
	floats t = floats(particles->at(myIndex).getAmnt(), 0.0f), e = floats(particles->at(myIndex).getAmnt(), 0.0f);
	cl::Buffer predXBuff = queues[1].makeBuffer(&(particles->at(myIndex).getPosX()[0]), sizeof(float) * particles->at(myIndex).getAmnt(), queues[1].ROFlags);
	cl::Buffer predYBuff = queues[1].makeBuffer(&(particles->at(myIndex).getPosY()[0]), sizeof(float) * particles->at(myIndex).getAmnt(), queues[1].ROFlags);
	cl::Buffer predZBuff = queues[1].makeBuffer(&(particles->at(myIndex).getPosZ()[0]), sizeof(float) * particles->at(myIndex).getAmnt(), queues[1].ROFlags);
	cl::Buffer predRotT = queues[1].makeBuffer(&(particles->at(myIndex).getRotTheta()[0]), sizeof(float)* particles->at(myIndex).getAmnt(), queues[1].ROFlags);
	cl::Buffer predRotE = queues[1].makeBuffer(&(particles->at(myIndex).getRotEpsilon()[0]), sizeof(float)* particles->at(myIndex).getAmnt(), queues[1].ROFlags);
	cl::Buffer predVel = queues[1].makeBuffer(&(particles->at(myIndex).getVels()[0]), sizeof(float)* particles->at(myIndex).getAmnt(), queues[1].ROFlags);
	cl::Buffer preyXBuff = queues[1].makeBuffer(&(particles->at(preyIndex).getPosX()[0]), sizeof(float) * particles->at(preyIndex).getAmnt(), queues[1].ROFlags);
	cl::Buffer preyYBuff = queues[1].makeBuffer(&(particles->at(preyIndex).getPosY()[0]), sizeof(float) * particles->at(preyIndex).getAmnt(), queues[1].ROFlags);
	cl::Buffer preyZBuff = queues[1].makeBuffer(&(particles->at(preyIndex).getPosZ()[0]), sizeof(float) * particles->at(preyIndex).getAmnt(), queues[1].ROFlags);
	cl::Buffer predTBuff = queues[1].makeBuffer(&(t[0]), sizeof(float) * t.size(), queues[1].ROFlags);
	cl::Buffer predEBuff = queues[1].makeBuffer(&(e[0]), sizeof(float) * e.size(), queues[1].ROFlags);
	cl::NDRange globalRange(particles->at(myIndex).getAmnt());
	cl::KernelFunctor funct(kernels[1], queues[1].getQueue(), cl::NullRange,
			globalRange, cl::NullRange);
	funct(predXBuff, predYBuff, predZBuff, predRotT, predRotE, predVel, preyXBuff, preyYBuff, preyZBuff,  particles->at(myIndex).getAmnt(), particles->at(preyIndex).getAmnt(), predTBuff, predEBuff);
	queues[1].getQueue().enqueueMapBuffer(predTBuff, CL_TRUE, CL_MAP_READ, 0, t.size() * sizeof(float));
	queues[1].getQueue().enqueueMapBuffer(predEBuff, CL_TRUE, CL_MAP_READ, 0, e.size() * sizeof(float));
	ret.push_back(t);
	ret.push_back(e);
	return ret;
}

std::vector<floats> CLHandler::hideFromClosestPackMember(int myIndex, int predIndex) {
	std::vector<floats> ret;
	// OpenCL HERE
	return ret;
}

std::vector<floats> CLHandler::hideFromPack(int myIndex, int predIndex) {
	std::vector<floats> ret;
	// OpenCL HERE
	return ret;
}

std::vector<floats> CLHandler::alignment(int myIndex) {
	std::vector<floats> ret;
	// OpenCl HERE
	return ret;
}

std::vector<floats> CLHandler::seperation(int myIndex) {
	std::vector<floats> ret;
	// OpenCL HERE
	return ret;
}

std::vector<floats> CLHandler::cohesion(int myIndex) {
	std::vector<floats> ret;
	// OpenCL HERE
	return ret;
}

void CLHandler::oneIterationOfFlocking() {
	// get the average posistions and the rots to the vectors
	floats deltaRotE;
	floats deltaRotT;
	std::vector<floats> tmp;

	for (unsigned int i = 0; i < particles->size(); i++) {
		deltaRotE = floats(particles->at(i).getAmnt(), 0.0f);
		deltaRotT = floats(particles->at(i).getAmnt(), 0.0f);
		if (i != 0) {
			// hunt the closest particle.
			tmp = hunt(i, i - 1);
			for(unsigned int j = 0; j < particles->at(i).getAmnt(); j++) {
				deltaRotT[j] += tmp[0][j] * HUNT_W;
				deltaRotE[j] += tmp[1][j] * HUNT_W;
			}
		} else if(i != particles->size() - 1) {
			// hide from closest hunter
			tmp = hideFromClosestPackMember(i, i + 1);
			for(unsigned int j = 0; j < particles->at(i).getAmnt(); j++) {
				deltaRotT[j] += tmp[0][j] * HIDE_FROM_ONE_W;
				deltaRotE[j] += tmp[1][j] * HIDE_FROM_ONE_W;
			}
			// hide from all hunters
			tmp = hideFromPack(i, i + 1);
			for(unsigned int j = 0; j < particles->at(i).getAmnt(); j++) {
				deltaRotT[j] += tmp[0][j] * HIDE_FROM_ALL_W;
				deltaRotE[j] += tmp[1][j] * HIDE_FROM_ALL_W;
			}
		}

		// alignment
		tmp = alignment(i);
		for(unsigned int j = 0; j < particles->at(i).getAmnt(); j++) {
			deltaRotT[j] += tmp[0][j] * ALIGN_W;
			deltaRotE[j] += tmp[1][j] * ALIGN_W;
		}

		// seperation
		tmp = seperation(i);
		for(unsigned int j = 0; j < particles->at(i).getAmnt(); j++) {
			deltaRotT[j] += tmp[0][j] * SEPERATE_W;
			deltaRotE[j] += tmp[1][j] * SEPERATE_W;
		}

		// cohesion
		for(unsigned int j = 0; j < particles->at(i).getAmnt(); j++) {
			tmp = cohesion(i);
			deltaRotT[j] += tmp[0][j] * COHESION_W;
			deltaRotE[j] += tmp[1][j] * COHESION_W;
		}

		for(unsigned int j = 0; j < particles->at(i).getAmnt(); j++) {
			deltaRotT[j] = fmod(deltaRotT[j], 3.14f); // deltaRotT % 3.14f;
			deltaRotE[j] = fmod(deltaRotE[j], (3.14f * 2.0f)); // deltaRotE % (2.0f * 3.14f);
		}

		// add in the deltaRotE and T to each praticle in vector[i].
		for (unsigned int j = 0; j < particles[i].size(); j++) {
			particles->at(i).addRotT(deltaRotT[j], j);
			particles->at(j).addRotE(deltaRotE[j], j);
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