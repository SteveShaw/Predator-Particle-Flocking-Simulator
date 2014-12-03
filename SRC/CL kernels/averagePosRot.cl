#pragma OPENCL EXTENSION cl_khr_fp64 : enable __kernel
void avePosRot(__global float* posX, __global float* posY,__global float* posZ,
    __gloabal float* rotT, __gloabal float* rotE, __gloabl float* avePos,
    __global float* aveRot, int size) {
    // avePos is size 3 [x, y, z], aveRot is size 2 [theta, elsipon] and all indicies are initialized to 0.0f

	local float x, y, z, t, e;
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	e = 0.0f;
	t = 0.0f;
	barrier(CLK_LOCAL_MEM_FENCE);
	
	size_t i = get_global_id(0);
	if (i < size) {
		atomic_add(&x, posX[i]);
		atomic_add(&y, posY[i]);
		atomic_add(&x, posZ[i]);
		atomic_add(&t, posT[i]);
		atomic_add(&e, posE[i]);
	}
	barrier(CLK_LOCAL_MEM_FENCE);
	
	if (i == 0) {
		atomic_add(avePos[0], (x / ((float) size));
		atomic_add(avePos[1], (y / ((float) size));
		atomic_add(avePos[2], (z / ((float) size));
		atomic_add(aveRot[0], (t / ((float) size));
		atomic_add(aveRot[1], (e / ((float) size));
	}
}