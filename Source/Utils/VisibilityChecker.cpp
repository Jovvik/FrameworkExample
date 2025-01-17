#include "VisibilityChecker.hpp"

#include "imgui.h"

#include "Raytrace.hpp"

bool VisibilityChecker::IsVisible(CBasePlayer* localPlayer, CBasePlayer* otherPlayer)
{
	if (considerEveryoneVisibleWhenDead && !localPlayer->IsAlive())
		return true;

	if (considerSpottedEntitiesAsVisible && *otherPlayer->Spotted())
		return true;

	const Vector playerEye = localPlayer->GetEyePosition();
	const Vector head = otherPlayer->GetBonePosition(8);

	if (considerSmokedOffEntitiesAsOccluded && Memory::LineGoesThroughSmoke(playerEye, head, 1))
		return false;

	CTraceFilterEntity filter(localPlayer);
	const Trace trace = Utils::TraceRay(playerEye, head, &filter);

	return trace.m_pEnt == otherPlayer;
}

void VisibilityChecker::SetupGUI()
{
	ImGui::Checkbox("Consider spotted entities as visible", &considerSpottedEntitiesAsVisible);
	ImGui::Checkbox("Consider smoked off entities as occluded", &considerSmokedOffEntitiesAsOccluded);
	ImGui::Checkbox("Consider everyone visible when dead", &considerEveryoneVisibleWhenDead);
}

SCOPED_SERIALIZER(VisibilityChecker)
{
	SERIALIZE("Consider spotted entities as visible", considerSpottedEntitiesAsVisible);
	SERIALIZE("Consider smoked off entities as occluded", considerSmokedOffEntitiesAsOccluded);
	SERIALIZE("Consider everyone visible when dead", considerEveryoneVisibleWhenDead);
}