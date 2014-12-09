#pragma OPENCL EXTENSION cl_khr_fp64 : enable __kernel
void hideFromHunter(__global float* posX, __global float* posY,
    __global float* posZ, __gloabal float* rotT,
    __gloabal float* rotE __global float* vel, __global float* predPosX,
    __global float* predPosY, __global float* predPosZ, int sizePrey,
    int sizePred __global float* hideT, __gobal float* hideE) {
    
	size_t i = get_local_id(0);
	if (i < sizePrey) {
        float theta, epsilon;
		float a, b, c;
		float ax, ay, az, bx, by, bz, cx, cy, cz;
		float dist = 99999999.9f; // large float
		int index = 0;
        for (int j = 0; i < sizePred; j++) {
            float myDist = sqrt(
                ((posX[i] - predPosX[j]) * (posX[i] - predPosX[j])) +
                ((posY[i] - predPosY[j]) * (posY[i] - predPosY[j])) +
                ((posZ[i] - predPosZ[j]) * (posZ[i] - predPosZ[j])));
            if (myDist < dist) {
                index = j;
            }
        }
		
		// 0 E
		ax = predPosX[index] - posX[i];
		ay = predPosY[index] - posY[i];
		az = predPosZ[index] - posZ[i];
		bx = vel[i] * (sin(rotT[i]) * cos(0.0f));
		by = vel[i] * (sin(rotT[i]) * sin(0.0f));
		bz = vel[i] * cos(rotT[i]);
		cx = ax - bx;
		cy = ay - by;
		cz = az - bz;
		
		// c^2 = a^2 + b^2 - 2abcos(alpha)
		c = sqrt((abs(cx) * abs(cx)) + (abs(cy) * abs(cy)) + (abs(cz) * abs(cz)));
		b = sqrt((abs(bx) * abs(bx)) + (abs(by) * abs(by)) + (abs(bz) * abs(bz)));
		a = sqrt((abs(ax) * abs(ax)) + (abs(ay) * abs(ay)) + (abs(az) * abs(az)));
		theta = arccos((-((c *c) - (a * a) - (b * ))) / (2.0f * a * b));
		
		// 0 T
		bx = vel[i] * (sin(0.0f) * cos(rotE[i]));
		by = vel[i] * (sin(0.0f) * sin(rotE[i]));
		bz = vel[i] * cos(0.0f);
		cx = ax - bx;
		cy = ay - by;
		cz = az - bz;
		
		// c^2 = a^2 + b^2 - 2abcos(alpha)
		c = sqrt((abs(cx) * abs(cx)) + (abs(cy) * abs(cy)) + (abs(cz) * abs(cz)));
		b = sqrt((abs(bx) * abs(bx)) + (abs(by) * abs(by)) + (abs(bz) * abs(bz)));
		a = sqrt((abs(ax) * abs(ax)) + (abs(ay) * abs(ay)) + (abs(az) * abs(az)));
		theta = arccos((-((c *c) - (a * a) - (b * ))) / (2.0f * a * b));
		
		theta = fmod(theta, 3.14f); // theta % 3.14f;
		epsilon = fmod(epsilon, (2.0f * 3.14f)); // epsilon % (2.0f * 3.14)f;
		huntE[i] = -epsilon;
		huntT[i] = -theta;
	}
}