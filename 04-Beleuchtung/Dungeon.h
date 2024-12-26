#pragma once
#include "../framework/Model.h"
#include "../framework/glmmath.h"
#include "../framework/Program.h"
#include "../framework/Uniform.h"
#include <vector>
#include <queue>

class Dungeon {
public:
	Dungeon();

	void draw(Program& program, Uniform<glm::mat4>& modelMatrix, Uniform<int>& materialUniform);

	float generateFlameWeight(const int smoothIntervall);
private:
	void loadAndSetup();

	struct DungeonModel {
		Model model;
		std::vector<glm::mat4> modelMatrix;
		int material = 0;

		void draw(Program& program, Uniform<glm::mat4>& modelMatrixUniform, Uniform<int>& materialUniform);
	};

	//All models (Models made by Quanternius https://quaternius.com/)
	DungeonModel m_wall;
	DungeonModel m_floor;
	DungeonModel m_pillar;
	DungeonModel m_arch;
	DungeonModel m_coins;
	DungeonModel m_skull;
	struct {
		DungeonModel wood;
		DungeonModel metal;
	}m_table;
	struct {
		DungeonModel fire;
		DungeonModel base;
	}m_torch;
	struct {
		DungeonModel metal;
		DungeonModel wood;
		DungeonModel fabric;
	}m_banner;
	struct {
		DungeonModel gold;
		DungeonModel metal;
		DungeonModel wood_top;
		DungeonModel wood_bottom;
	}m_chest;
	struct {
		DungeonModel blade;
		DungeonModel metal;
		DungeonModel handle;
	}m_sword;

	std::queue<float> m_fireSmoothQueue{{0.f}};
	float m_fireSum = 0.f;
};