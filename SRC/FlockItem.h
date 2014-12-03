// Copyright 2014 Aaron Baker (bakeraj4)

#include <vector>
#include <string>

#define Vec std::vector<float>

class FlockItem{
    private:
        Vec posX, posY, posZ, rotTheta, rotEpsilon, vels;
		int amnt;
		int foodChainLevel;
		std::string pName;
		void addSingleParticle(float px, float py, float pz);
		void initVecs(int nMembers);
		void move(unsigned int index);
    public:
        FlockItem(int level, std::string& name, int nMembers);
		
		void removeParticleI(unsigned int index);
		void decrementAmnt();
		int getAmnt();
		int getLevel();
		std::string getPName();
		
		Vec getPosX();
		Vec getPosY();
		Vec getPosZ();
		Vec getRotTheta();
		Vec getRotEpsilon();
		Vec getVels();

		float getPosX(int index);
		float getPosY(int index);
		float getPosZ(int index);
		float getRotTheta(int index);
		float getRotEpsilon(int index);
		float getVels(int index);

		void addPosX(float n_x, int index);
		void addPosY(float n_y, int index);
		void addPosZ(float n_z, int index);
		void addRotT(float n_t, int index);
		void addRotE(float n_e, int index);

		void setRotTheta(float n_x, int index);
		void setRotEpsilon(float n_y, int index);

		void move();
		void populate(float ax, float ay, float az);
		// eat prey should be called before move
		void eatPrey(FlockItem& prey);
};