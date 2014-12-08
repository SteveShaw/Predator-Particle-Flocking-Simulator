// Copyright 2014 Aaron Baker (bakeraj4)

#include "FlockItem.h"
#include <vector>
#include <string>
#include "ClCmdQueue.h"
#pragma once

typedef std::vector<float> floats;

class CLHandler {
private:
	std::vector<FlockItem>* particles;
	floats avePosX, avePosY, avePosZ, aveRotE, aveRotT;
	std::vector<ClCmdQueue> queues;
	std::vector<cl::Kernel> kernels;

	void resetAverages();
	void calcAverages();
	std::vector<floats> hunt(int myIndex, int preyIndex);
	std::vector<floats> hideFromClosestPackMember(int myIndex, int predIndex);
	std::vector<floats> hideFromPack(int myIndex, int predIndex);
	std::vector<floats> alignment(int myIndex);
	std::vector<floats> seperation(int myIndex);
	std::vector<floats> cohesion(int myIndex);
	
public:
	CLHandler(std::vector<FlockItem>* flocks, std::vector<std::string>& kerenelFile,
		std::vector<std::string>& kernelFuncts, std::string mode);
	void oneIterationOfFlocking();
};
