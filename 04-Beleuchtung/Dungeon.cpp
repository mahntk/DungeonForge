#include "Dungeon.h"

using namespace glm;

Dungeon::Dungeon() {
	loadAndSetup();
}

void Dungeon::loadAndSetup() {

	//
	// 
	//Load in Models from Obj
	//
	//

	m_wall.model = Model("models/modular_wall.obj");
	m_floor.model = Model("models/modular_floor.obj");
	m_pillar.model = Model("models/pillar.obj");
	m_arch.model = Model("models/arch.obj");
	m_coins.model = Model("models/coin_pile.obj");
	m_skull.model = Model("models/skull.obj");
	m_table.metal.model = Model("models/table_metal.obj");
	m_table.wood.model = Model("models/table_wood.obj");
	m_torch.fire.model = Model("models/torch_fire.obj");
	m_torch.base.model = Model("models/torch_body.obj");
	m_banner.fabric.model = Model("models/banner_fabric.obj");
	m_banner.metal.model = Model("models/banner_metal.obj");
	m_banner.wood.model = Model("models/banner_wood.obj");
	m_chest.gold.model = Model("models/chest_gold.obj");
	m_chest.metal.model = Model("models/chest_lock.obj");
	m_chest.wood_bottom.model = Model("models/chest_wood_bottom.obj");
	m_chest.wood_top.model = Model("models/chest_wood_top.obj");
	m_sword.blade.model = Model("models/sword_blade.obj");
	m_sword.handle.model = Model("models/sword_handle.obj");
	m_sword.metal.model = Model("models/sword_metal.obj");

	//
	//
	//Set the world matrix for each model
	//
	//

	mat4 worldMat;

	//
	//Floor
	//
	for (int x = -1; x <= 1; x++) {
		for (int z = -1; z <= 2; z++) {
			worldMat = translate(mat4(1.f), vec3(x*2.f, 0, z*2.f));
			m_floor.modelMatrix.push_back(worldMat);
		}
	}
	//
	//Walls
	// 
	
	//Back
	for (int x = -1; x <= 1; x++) {
		worldMat = translate(mat4(1.f), vec3(x * 2.f, 1.f,-3.f));
		m_wall.modelMatrix.push_back(worldMat);
	}
	//Right
	for (int z = -1; z <= 1; z++) {
		worldMat = mat4(1.f);
		worldMat = translate(worldMat, vec3(3.f, 1.f, z * 2.f));
		worldMat = rotate(worldMat, radians(-90.f), vec3(0, 1.f, 0));
		m_wall.modelMatrix.push_back(worldMat);
	}
	//Left
	for (int z = -1; z <= 1; z++) {
		worldMat = mat4(1.f);
		worldMat = translate(worldMat, vec3(-3.f, 1.f, z * 2.f));
		worldMat = rotate(worldMat, radians(-90.f), vec3(0, 1.f, 0));
		m_wall.modelMatrix.push_back(worldMat);
	}
	//Front
	worldMat = translate(mat4(1.f), vec3(2.f, 1.f, 3.f));
	m_wall.modelMatrix.push_back(worldMat);
	worldMat = translate(mat4(1.f), vec3(-2.f, 1.f, 3.f));
	m_wall.modelMatrix.push_back(worldMat);

	//
	//Pillars
	//

	//Back
	worldMat = translate(mat4(1.f), vec3(-1.f, 0.f, -2.95f));
	worldMat = scale(worldMat, vec3(0.5f));
	m_pillar.modelMatrix.push_back(worldMat);
	worldMat = translate(mat4(1.f), vec3(1.f, 0.f, -2.95f));
	worldMat = scale(worldMat, vec3(0.5f));
	m_pillar.modelMatrix.push_back(worldMat);

	//Left
	worldMat = translate(mat4(1.f), vec3(-2.95f, 0.f, -1.f));
	worldMat = scale(worldMat, vec3(0.5f));
	m_pillar.modelMatrix.push_back(worldMat);

	worldMat = translate(mat4(1.f), vec3(-2.95f, 0.f, 1.f));
	worldMat = scale(worldMat, vec3(0.5f));
	m_pillar.modelMatrix.push_back(worldMat);

	//Right
	worldMat = translate(mat4(1.f), vec3(2.95f, 0.f, -1.f));
	worldMat = scale(worldMat, vec3(0.5f));
	m_pillar.modelMatrix.push_back(worldMat);

	worldMat = translate(mat4(1.f), vec3(2.95f, 0.f, 1.f));
	worldMat = scale(worldMat, vec3(0.5f));
	m_pillar.modelMatrix.push_back(worldMat);
	//
	//Arch
	//
	worldMat = translate(mat4(1.f), vec3(0.f, 0.f, 3.f));
	worldMat = scale(worldMat, vec3(0.5f, 0.5f, 1.f));
	m_arch.modelMatrix.push_back(worldMat);

	//
	//Table
	//
	worldMat = translate(mat4(1.f), vec3(0.075f, 0.1f, -2.25f));
	worldMat = scale(worldMat, vec3(0.75f));
	worldMat = rotate(worldMat, radians(-90.f), vec3(0, 1.f, 0));
	m_table.wood.modelMatrix.push_back(worldMat);
	m_table.metal.modelMatrix.push_back(worldMat);

	//
	//Coins on Table
	//
	worldMat = translate(mat4(1.f), vec3(0.f, 0.71f, -2.3f));
	worldMat = scale(worldMat, vec3(1.5f));
	m_coins.modelMatrix.push_back(worldMat);

	//
	//Torches
	//

	//Left
	worldMat = translate(mat4(1.f), vec3(-1.f, 1.f, -2.5f));
	worldMat = scale(worldMat, vec3(0.75f));
	m_torch.base.modelMatrix.push_back(worldMat);
	m_torch.fire.modelMatrix.push_back(worldMat);

	//Right
	worldMat = translate(mat4(1.f), vec3(1.f, 1.f, -2.5f));
	worldMat = scale(worldMat, vec3(0.75f));
	m_torch.base.modelMatrix.push_back(worldMat);
	m_torch.fire.modelMatrix.push_back(worldMat);
	
	//
	//Banner
	//
	worldMat = translate(mat4(1.f), vec3(2.f, 0.1f, -2.f));
	worldMat = scale(worldMat, vec3(0.45f));
	worldMat = rotate(worldMat, radians(325.f), vec3(0, 1.f, 0));
	m_banner.fabric.modelMatrix.push_back(worldMat);
	m_banner.metal.modelMatrix.push_back(worldMat);
	m_banner.wood.modelMatrix.push_back(worldMat);

	//
	//Skull
	//
	worldMat = translate(mat4(1.f), vec3(2.015f, 1.66f, -2.02f));
	worldMat = scale(worldMat, vec3(0.5f));
	worldMat = rotate(worldMat, radians(48.f), vec3(0, 1.f, 0));
	worldMat = rotate(worldMat, radians(45.f), vec3(0, 0.f, 1.f));
	m_skull.modelMatrix.push_back(worldMat);

	//
	//Chest with Gold
	//
	worldMat = translate(mat4(1.f), vec3(-2.15f, 0.135 , 2.125f));
	worldMat = scale(worldMat, vec3(0.7f));
	worldMat = rotate(worldMat, radians(135.f), vec3(0, 1.f, 0));
	m_chest.gold.modelMatrix.push_back(worldMat); 
	m_chest.metal.modelMatrix.push_back(worldMat);
	m_chest.wood_bottom.modelMatrix.push_back(worldMat);

	worldMat = translate(mat4(1.f), vec3(-2.47f, 0.125, 2.44f));
	worldMat = scale(worldMat, vec3(0.7f));
	worldMat = rotate(worldMat, radians(135.f), vec3(0, 1.f, 0));
	worldMat = rotate(worldMat, radians(60.f), vec3(1.f, 0.f, 0));
	m_chest.wood_top.modelMatrix.push_back(worldMat);

	//
	//Gold Sword
	//
	worldMat = translate(mat4(1.f), vec3(-2.175f, 1.2409f,2.1468f));
	worldMat = scale(worldMat, vec3(0.5f));
	worldMat = rotate(worldMat, radians(-180.f), vec3(1.f, 0.f, 0.f));
	worldMat = rotate(worldMat, radians(45.f), vec3(0, 1.f, 0));
	m_sword.blade.modelMatrix.push_back(worldMat);
	m_sword.handle.modelMatrix.push_back(worldMat);
	m_sword.metal.modelMatrix.push_back(worldMat);

	//
	// 
	//Set Materials
	//
	//

	//0 - Wall
	//1 - Floor
	//2 - Wood
	//3 - Metal
	//4 - Gold
	//5 - Skull
	//6 - Fabric
	//7 - Fire
	//8 - Pillar

	m_floor.material = 1;
	m_wall.material = 0;
	m_pillar.material = 8;
	m_arch.material = 0;
	m_table.metal.material = 3;
	m_table.wood.material = 2;
	m_coins.material = 4;
	m_torch.base.material = 3;
	m_torch.fire.material = 7;
	m_banner.fabric.material = 6;
	m_banner.metal.material = 3;
	m_banner.wood.material = 2;
	m_skull.material = 5;
	m_chest.gold.material = 4;
	m_chest.metal.material = 3;
	m_chest.wood_bottom.material = 2;
	m_chest.wood_top.material = 2;
	m_sword.blade.material = 4;
	m_sword.metal.material = 3;
	m_sword.handle.material = 6;
}

void Dungeon::DungeonModel::draw(Program& program, Uniform<mat4>& modelMatrixUniform, Uniform<int>& materialUniform) {
	for (size_t i = 0; i < modelMatrix.size(); i++) {
		modelMatrixUniform.set(modelMatrix[i]);
		materialUniform.set(material);
		model.draw(program);
	}
}

void Dungeon::draw(Program& program, Uniform<mat4>& modelMatrix, Uniform<int>& materialUniform) {
	//Draw everything
	m_floor.draw(program, modelMatrix, materialUniform);
	m_wall.draw(program, modelMatrix, materialUniform);
	m_pillar.draw(program, modelMatrix, materialUniform);
	m_arch.draw(program, modelMatrix, materialUniform);
	m_table.wood.draw(program, modelMatrix, materialUniform);
	m_table.metal.draw(program, modelMatrix, materialUniform);
	m_coins.draw(program, modelMatrix, materialUniform);
	m_torch.base.draw(program, modelMatrix, materialUniform);
	m_torch.fire.draw(program, modelMatrix, materialUniform);
	m_banner.fabric.draw(program, modelMatrix, materialUniform);
	m_banner.metal.draw(program, modelMatrix, materialUniform);
	m_banner.wood.draw(program, modelMatrix, materialUniform);
	m_skull.draw(program, modelMatrix, materialUniform);
	m_chest.gold.draw(program, modelMatrix, materialUniform);
	m_chest.metal.draw(program, modelMatrix, materialUniform);
	m_chest.wood_bottom.draw(program, modelMatrix, materialUniform);
	m_chest.wood_top.draw(program, modelMatrix, materialUniform);
	m_sword.blade.draw(program, modelMatrix, materialUniform);
	m_sword.handle.draw(program, modelMatrix, materialUniform);
	m_sword.metal.draw(program, modelMatrix, materialUniform);
}

float Dungeon::generateFlameWeight(const int smoothInterval) {
	// Neue Zufallszahl im Bereich [0,1] generieren
	float randomValue = float(std::rand()) / RAND_MAX;

	// Neue Zufallszahl zur Queue hinzufügen und zur Summe addieren
	m_fireSmoothQueue.push(randomValue);
	m_fireSum += randomValue;

	// Queue-Glättung: Falls die Größe das Intervall überschreitet, erstes Element entfernen
	if (m_fireSmoothQueue.size() > smoothInterval) {
		m_fireSum -= m_fireSmoothQueue.front();
		m_fireSmoothQueue.pop();
	}

	// Durchschnitt der Queue zurückgeben (Gleitender Mittelwert)
	return m_fireSum / float(m_fireSmoothQueue.size());
}