// Copyright 2014 Aaron Baker (bakeraj4)

#include <vector>

#define std::<float> Vec4

class FlockItem{
    private:
        Vec4 pos, rot;
		float vel;
		int foodChainLevel;
    public:
        FlockItem(int level);
		Vec4 getRot();
		void updateRot(Vec4 n_rot);
		Vec4 getPos();
		void updatePos(Vec4 n_pos);
		float getVel();
		void updateVel(float n_vel);
		int getLevel();
};