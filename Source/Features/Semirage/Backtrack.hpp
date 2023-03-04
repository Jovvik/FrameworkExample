#ifndef FEATURES_SEMIRAGE_BACKTRACK
#define FEATURES_SEMIRAGE_BACKTRACK

#include "imgui.h"

#include "../../SDK/CUserCmd.hpp"
#include "../../SDK/ClientFrameStage.hpp"

namespace Features::Semirage::Backtrack {
	// Settings
	extern bool	 enabled;
	extern float timeDelta;

	void CreateMove(CUserCmd* cmd);
	void FrameStageNotify();

	// GUI
	void SetupGUI();
}

#endif