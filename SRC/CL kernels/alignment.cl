#pragma OPENCL EXTENSION cl_khr_fp64 : enable __kernel
void align( __gloabal float* rotT, __gloabal float* rotE, __global float* aveRot,
    int size, __global float* alignT, __global float* alignE) {
	size_t i = get_local_id(0);
	if (i < size) {
		float theta, epsilon;
		theta = aveRot[0] - rotT[i];
		epsilon = aveRot[1] - rotE[i];
		theta = theta % (2.0f * 3.14f);
		epsilon = epsilon % 3.14f;
		alignE[i] = epsilon;
		alignT[i] = theta;
	}
}