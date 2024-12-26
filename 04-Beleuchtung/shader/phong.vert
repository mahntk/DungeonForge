#version 330 core

layout(location = 0) in vec3 in_pos;
layout(location = 1) in vec3 in_normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform int materialId; // for shading

out vec3 fWorldPos; // fragment world position
out vec3 fWorldNormal; // fragment world normal

out vec3 vDiffuseColor;
out vec3 vSpecularColor;
out float vExponent;

uniform bool gammaCorrect;
uniform float flameWeight;
uniform float time;

void getMaterial(out vec3 diffuseColor, out vec3 specular, out float exponent, float flameInterpolationWeight) {
	switch(materialId) {
		case 0:	//Wall
		diffuseColor = vec3(0.48);
		specular = vec3(0.1);
		exponent = 2.0;
		break;
		case 1:	//Floor
		diffuseColor = vec3(0.15);
		specular = vec3(0.1);
		exponent = 2.0;
		break;
		case 2:	//Wood
		diffuseColor = vec3(0.235, 0.112, 0.054);
		specular = vec3(0.15);
		exponent = 4.0;
		break;
		case 3: // Metal
		diffuseColor = vec3(0.05);
		specular = vec3(0.4);
		exponent = 6.0;
		break;
		case 4: //Gold
		diffuseColor = vec3(0.3, 0.204, 0.0);
		specular = vec3(1.0, 0.76, 0.05);
		exponent = 12.0;
		break;
		case 5: //Skull
		diffuseColor = vec3(0.8, 0.64, 0.446);
		specular = vec3(0.1);
		exponent = 16.0;
		break;
		case 6: //Fabric
		diffuseColor = vec3(0.05, 0.05, 0.8);
		specular = vec3(0.0);
		exponent = 1.0;
		break;
		case 7: //Fire
		vec3 color1 = vec3(0.3, 0.0, 0.0);
		vec3 color2 = vec3(1.0, 0.55, 0.19);
		diffuseColor = mix(color1, color2, flameInterpolationWeight);
		specular = vec3(0.);
		exponent = 1.0;
		break;
		case 8: //Pillar
		diffuseColor = vec3(0.615);
		specular = vec3(0.1);
		exponent = 8.0;
		break;
	}
}

float computeFlameWeight(float height, float flameWeight) {
	float t = (height - 0.36) / (0.88 - 0.36); // Normalisiere Höhe
	return mix(flameWeight, 0.0, clamp(t, 0.0, 1.0));
}

vec3 gammaCorrection(vec3 color, bool correct) {
	return correct ? pow(color, vec3(2.2)) : color;
}

void main() {
	fWorldPos = (model * vec4(in_pos, 1.0)).xyz;
	fWorldNormal = normalize((model * vec4(in_normal, 0.0)).xyz);

	vec3 diffuseColor, specularColor;
	float exponent;
	float flameInterpolationWeight = 0.5;

	if(materialId == 7) {
		// Berechnung der Flammenanimation
		float flameMovement = sin(time * 2.0) * 0.05; // Flammenbewegung in x-Richtung
		fWorldPos.x += flameMovement;

		// Berechnung des Interpolationsgewichts
		flameInterpolationWeight = computeFlameWeight(in_pos.y, flameWeight);
	}

	getMaterial(diffuseColor, specularColor, exponent, flameInterpolationWeight);

	vDiffuseColor = gammaCorrection(diffuseColor, gammaCorrect);
	vSpecularColor = gammaCorrection(specularColor, gammaCorrect);
	vExponent = exponent;

	gl_Position = projection * view * vec4(fWorldPos, 1.0);
}
