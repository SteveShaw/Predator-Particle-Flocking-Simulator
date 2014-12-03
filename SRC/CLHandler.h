// Copyright 2014 Aaron Baker (bakeraj4)

#include "FlockItem.h"
#include <vector>
#include <string>
// #include "ClCmdQueue.h"
#pragma once

typedef std::vector<float> floats;

class CLHandler {
private:
	std::vector<FlockItem>* particles;
	floats avePosX, avePosY, avePosZ, aveRotE, aveRotT;
	// std::vector<ClCmdQueue.h> queues;

	void resetAverages();
	void calcAverages();
	floats hunt(int myIndex, int preyIndex);
	floats hideFromClosestPackMember(int myIndex, int predIndex);
	floats hideFromPack(int myIndex, int predIndex);
	floats alignment(int myIndex);
	floats seperation(int myIndex);
	floats cohesion(int myIndex);

public:
	CLHandler(std::vector<FlockItem>* flocks, std::vector<std::string>& kerenelFile,
		std::vector<std::string> kernelFuncts, std::string mode);
	void oneIterationOfFlocking();
};



/* THINGS LEFT TO DO
	std::vector<std::string> kernelFunctions;
	std::vector<std::string> scources;
	void initQueues();
	std::string readKernel(std::string fileName);
	CLHandler(std::vector<FlockItem>* flocks, std::vector<std::string>& kerenelFile,
		std::vector<std::string> kernelFuncts);
*/
