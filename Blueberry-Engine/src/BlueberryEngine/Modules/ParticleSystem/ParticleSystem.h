#pragma once

class ParticleSystem {

public:
	ParticleSystem();

	void OnUpdate();
	void OnRender();

	void Emit();

private:

	//glm::vec4 ColorBegin, ColorEnd;

};