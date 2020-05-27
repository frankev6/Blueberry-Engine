#include "bepch.h"
#include "BEbehaviour.h"

namespace BE
{
	
	BEbehaviour::BEbehaviour() {

		BEbehaviour::Start();
	}

	BEbehaviour::~BEbehaviour() {
		BEbehaviour::OnDestroy();
		delete this;
	}

	void BEbehaviour::Start() {
		BE_C_INFO("start");
	}
	void BEbehaviour::Update() {
		BE_C_INFO("update");
	}
	void BEbehaviour::OnDestroy() {
		BE_C_INFO("OnDestroy");
	}
}