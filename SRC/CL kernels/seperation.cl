#pragma OPENCL EXTENSION cl_khr_fp64 : enable __kernel
void seperate(__global float* posX, __global float* posY, __global float* posZ,
    __gloabal float* rotT, __gloabal float* rotE, __global float* avePos,
    int size, __global float* vel, __global float* cohesionT,
    __global float* cohesionE) {
    size_t i = get_local_id(0);
	if (i < size) {
		float theta, epsilon;
		float a, b, c;
		float ax, ay, az, bx, by, bz, cx, cy, cz;
		ax = avePos[0] - posX[i];
		ay = avePos[1] - posY[i];
		az = avePos[2] - posZ[i];
		
		// 0 T
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
		theta = acos((-((c *c) - (a * a) - (b * b))) / (2.0f * a * b));
		
		// 0 E
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
		epsilon = acos((-((c *c) - (a * a) - (b * b))) / (2.0f * a * b));
		
		theta = fmod(theta, 3.14f); // theta % 3.14f;
		epsilon = fmod(epsilon, (2.0f * 3.14f)); // epsilon % (2.0f * 3.14)f;
		cohesionE[i] = -epsilon;
		cohesionT[i] = -theta;
	}
}