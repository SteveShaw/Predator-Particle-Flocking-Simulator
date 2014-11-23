// Copyright 2014 Aaron Baker (bakeraj4)

#include <vector>
#include <string>

#define Vec std::vector<float>

class FlockItem{
    private:
        Vec posX, posY, posZ, rotX, rotY, rotZ, vels;
		int amnt;
		int foodChainLevel;
		std::string pName;
		void initVecs(int nMembers);
    public:
        FlockItem(int level, std::string& name, int nMembers);
		
		int getAmnt();
		int getLevel();
		std::string getPName();
		
		Vec getPosX();
		Vec getPosY();
		Vec getPosZ();
		Vec getRotX();
		Vec getRotY();
		Vec getRotZ();
		Vec getVels();

		float getPosX(int index);
		float getPosY(int index);
		float getPosZ(int index);
		float getRotX(int index);
		float getRotY(int index);
		float getRotZ(int index);
		float getVels(int index);

		void setPosX(float n_x, int index);
		void setPosY(float n_y, int index);
		void setPosZ(float n_z, int index);
		void setRotX(float n_x, int index);
		void setRotY(float n_y, int index);
		void setRotZ(float n_z, int index);
		void setVel(float n_v, int index);
};