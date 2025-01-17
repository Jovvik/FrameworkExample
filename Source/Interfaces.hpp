#ifndef INTERFACES
#define INTERFACES

#include "SDK/GameClass/Interfaces/CClientEntityList.hpp"
#include "SDK/GameClass/Interfaces/CEngineClient.hpp"
#include "SDK/GameClass/Interfaces/CEngineTrace.hpp"
#include "SDK/GameClass/Interfaces/CGameMovement.hpp"
#include "SDK/GameClass/Interfaces/CMaterialSystem.hpp"
#include "SDK/GameClass/Interfaces/CPanoramaUIEngine.hpp"
#include "SDK/GameClass/Interfaces/CPrediction.hpp"
#include "SDK/GameClass/Interfaces/ICvar.hpp"

namespace Interfaces {
	inline void* baseClient;
	inline CClientEntityList* entityList;
	inline CEngineClient* engine;
	inline CEngineTrace* engineTrace;
	inline ICvar* icvar;
	inline CPrediction* prediction;
	inline CGameMovement* gameMovement;
	inline CMaterialSystem* materialSystem;
	inline void* engineRenderView;
	inline CPanoramaUIEngine* panoramaUIEngine;
	inline void* fileSystem;

	void GetInterfaces();

	void* UncoverCreateFunction(void* createFunc);
}

#endif
