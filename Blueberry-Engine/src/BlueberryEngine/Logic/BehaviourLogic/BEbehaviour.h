#pragma once
#include "BlueberryEngine/Logic/Modules/Module.h"


namespace BE
{
	class  BEbehaviour {
	public:
		
		BEbehaviour();
		~BEbehaviour();


		void SetActive(bool active);
		bool GetActive();
		virtual void Start();
		void UpdateModules();
		virtual void Update();
		virtual void OnDestroy();

	protected:
		bool Active;
		int ModuleCount;
	};
}