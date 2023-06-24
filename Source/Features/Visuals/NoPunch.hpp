#ifndef FEATURES_VISUALS_NOPUNCH
#define FEATURES_VISUALS_NOPUNCH

#include "../Features.hpp"

#include "imgui.h"
#include "xorstr.hpp"

#include "../../SDK/GameClass/CViewSetup.hpp"

#include "../../GUI/ImGuiColors.hpp"

inline class NoPunch : public Feature {
public:
	NoPunch()
		: Feature(xorstr_("Visuals"), xorstr_("No punch"))
	{
	}

	bool hideViewPunch = false;
	bool hideAimPunch = false;

	void HidePunch();
	void RestorePunch();

	virtual void SetupGUI() override;
	virtual SERIALIZER() override;
} noPunch;

#endif