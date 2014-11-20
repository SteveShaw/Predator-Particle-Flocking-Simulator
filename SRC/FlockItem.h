// Copyright 2014 Aaron Baker (bakeraj4)

#include <vector>
#include <string>

#define Vec4 std::vector<float>

class FlockItem{
    private:
        Vec4 pos, rot;
		float vel;
		int foodChainLevel;
		std::string pName;
    public:
        FlockItem(int level, std::string& name);
		Vec4 getRot();
		void updateRot(Vec4 n_rot);
		Vec4 getPos();
		void updatePos(Vec4 n_pos);
		float getVel();
		void updateVel(float n_vel);
		int getLevel();
		std::string getPName();
};