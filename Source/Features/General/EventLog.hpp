#ifndef FEATURES_GENERAL_EVENTLOG
#define FEATURES_GENERAL_EVENTLOG

#include "imgui.h"
#include "SDL.h"

namespace Features::General::EventLog {
	// Settings
	extern bool enabled;
	extern int duration;

	void ImGuiRender(ImDrawList* drawList);

	// GUI
	void SetupGUI();

	// API
	void CreateReport(const char* fmt, ...);
}

#endif
