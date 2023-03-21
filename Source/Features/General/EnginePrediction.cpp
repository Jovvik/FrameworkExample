#include "../General.hpp"

#include "imgui.h"
#include "xorstr.hpp"

#include "../../GameCache.hpp"
#include "../../SDK/GameClass/CBasePlayer.hpp"
#include "../../Utils/Prediction.hpp"

#include <cstring>

bool Features::General::EnginePrediction::enabled = true;
bool Features::General::EnginePrediction::forceResetVelocityModifier = false;

CMoveData Features::General::EnginePrediction::moveData {};
int Features::General::EnginePrediction::prePredictionFlags = 0;

static float previousVelocityModifer;

void Features::General::EnginePrediction::StartPrediction(CUserCmd* cmd)
{
	moveData = {};
	if (!enabled)
		return;
	prePredictionFlags = *GameCache::GetLocalPlayer()->Flags();
	previousVelocityModifer = *GameCache::GetLocalPlayer()->VelocityModifier();
	Utils::StartPrediction(cmd, moveData);
}

void Features::General::EnginePrediction::EndPrediction()
{
	if (!enabled)
		return;

	Utils::EndPrediction();

	moveData = {};
	prePredictionFlags = 0;

	if(forceResetVelocityModifier) // I'm curious why people on UC seem to have so many problems figuring this out... Does this have some major downside, which I haven't noticed yet?
		*GameCache::GetLocalPlayer()->VelocityModifier() = previousVelocityModifer;
}

void Features::General::EnginePrediction::SetupGUI()
{
	ImGui::Checkbox(xorstr_("Enabled"), &enabled);
	if (!enabled) {
		ImGui::Text(xorstr_("Warning: Disabling engine prediction may result in massive accuracy loss"));
	}
	ImGui::Checkbox(xorstr_("Force reset velocity modifier"), &forceResetVelocityModifier);
	if(ImGui::IsItemHovered())
		ImGui::SetTooltip(xorstr_("This netvar is not being reset properly when predicting.\nNote that the \"fix\" is not intended by the engine."));
}

BEGIN_SERIALIZED_STRUCT(Features::General::EnginePrediction::Serializer, xorstr_("Engine prediction"))
SERIALIZED_TYPE(xorstr_("Enabled"), enabled)
END_SERIALIZED_STRUCT
