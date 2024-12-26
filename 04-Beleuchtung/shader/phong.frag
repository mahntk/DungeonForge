#version 330 core

in vec3 fWorldPos; // fragment world position
in vec3 fWorldNormal; // fragment world normal
in vec3 vDiffuseColor;
in vec3 vSpecularColor;
in float vExponent;

const vec3 lightFlamePosition[2] = vec3[2](vec3(-1.0f, 1.5f, -2.45f), vec3(1.0f, 1.5f, -2.45f));

// Farbverlauf für die Flamme
const vec3 flameBaseColor = vec3(1.0, 0.2, 0.0);  // Rot unten
const vec3 flameTopColor = vec3(2.0, 0.0, 0.0);   // Orange oben
  // Dunkelrot oben

vec3 lightFlameIntensity[2] = vec3[2](vec3(0.3, 0.0, 0.0) * 8.f, vec3(1.0, 0.38, 0.12) * 12.f);






const vec3 lightSpotPosition[2] = vec3[2](vec3(1.903f, 1.728f, -1.9595f), vec3(1.9608f, 1.728f, -1.8922f));
const vec3 lightSpotDirection[2] = vec3[2](vec3(-0.7379f, -0.1775f, 0.6511f), vec3(-0.6572f, -0.1777f, 0.7324f));
vec3 lightSpotIntensity = vec3(1.f, 1.f, 1.f) * 32.f;

const float cosSpotAngle = 0.9756912;
const float spotExponent = 64.f;

out vec3 fragmentColor;

uniform bool gammaCorrect;
uniform vec3 cameraPosition;
uniform int materialId;
uniform float flameWeight;

// Gamma-Korrektur
vec3 gammaCorrection(vec3 color, bool correct) {
	return correct ? pow(color, vec3(1.0 / 2.2)) : color;
}

void main() {
	vec3 N = normalize(fWorldNormal);
	vec3 V = normalize(cameraPosition - fWorldPos);
	vec3 phongLighting = vec3(0.0);

	// Flammenmaterial (Material-ID 7)
	if (materialId == 7) {
		float heightFactor = clamp((fWorldPos.y - 1.3) / 1.5, 0.0, 1.0);
		vec3 flameColor = mix(flameBaseColor, flameTopColor, heightFactor);
		fragmentColor = pow(flameColor, vec3(1.0 / 2.2));
		return;
	}

	// Punktlichter (Phong-Beleuchtung)
	for (int i = 0; i < 2; i++) {
		vec3 L = normalize(lightFlamePosition[i] - fWorldPos);
		float d = length(lightFlamePosition[i] - fWorldPos);
		float falloff = 1.0 / (d * d + 0.5 * d);

		vec3 intensity = mix(lightFlameIntensity[0], lightFlameIntensity[1], flameWeight);
		float NdotL = max(dot(N, L), 0.0);

		vec3 H = normalize(L + V);
		float NdotH = max(dot(N, H), 0.0);
		vec3 specular = vSpecularColor * pow(NdotH, vExponent);

		phongLighting += (vDiffuseColor * NdotL + specular) * intensity * falloff;
	}

	// Spotlichter
	for (int i = 0; i < 2; i++) {
		vec3 L = normalize(lightSpotPosition[i] - fWorldPos);
		vec3 spotDir = normalize(-lightSpotDirection[i]);
		float d = length(lightSpotPosition[i] - fWorldPos);
		float falloff = 1.0 / (d * d);

		float spotFactor = pow(max(dot(L, spotDir), cosSpotAngle), spotExponent);
		spotFactor = (dot(L, spotDir) > cosSpotAngle) ? spotFactor : 0.0;

		float NdotL = max(dot(N, L), 0.0);
		vec3 H = normalize(L + V);
		float NdotH = max(dot(N, H), 0.0);
		vec3 specular = vSpecularColor * pow(NdotH, vExponent);

		phongLighting += (vDiffuseColor * NdotL + specular) * lightSpotIntensity * falloff * spotFactor;
	}

	// Gamma-Korrektur
	fragmentColor = pow(phongLighting, vec3(1.0 / 2.3));  // Geringfügig weniger Helligkeit

 // Sanft wärmere und weichere Darstellung

}
