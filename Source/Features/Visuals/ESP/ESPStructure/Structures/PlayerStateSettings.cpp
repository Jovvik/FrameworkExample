#include "../ESPStructure.hpp"

#include "../../../../../GUI/Elements/ClickableColorButton.hpp"
#include "../../../../../GUI/Elements/Popup.hpp"

#include "../../../../../Utils/Projection.hpp"

#include "../../../../../Interfaces.hpp"

#include "../../ESP.hpp"
#include "imgui.h"

#include <memory>
#include <utility>
#include <vector>

PlayerStateSettings::PlayerStateSettings()
	: flags({ std::make_shared<Money>(),
		std::make_shared<Scoped>(),
		std::make_shared<PinPulled>(),
		std::make_shared<Location>(),
		std::make_shared<Objective>(),
		std::make_shared<HasDefuser>(),
		std::make_shared<HasBomb>(),
		std::make_shared<Planting>(),
		std::make_shared<Spotted>(),
		std::make_shared<Ammo>(),
		std::make_shared<Immune>(),
		std::make_shared<Walking>() })
	, headDotOffset({})
{
}

bool PlayerStateSettings::IsEnabled() const
{
	return boxName.IsEnabled() || healthbar.enabled || weapon.enabled || flags.IsEnabled() || headDot.enabled;
}

void PlayerStateSettings::Draw(ImDrawList* drawList, Player& player) const
{
	if (!IsEnabled())
		return;

	const std::optional<ImVec4> rectangle = player.screenRectangle.Get();
	if (!rectangle.has_value())
		return;

	char name[MAX_NAME_LEN];
	if (boxName.nametag.enabled) { // Don't ask the engine for the name, if we don't have to
		PlayerInfo info{};
		if (Interfaces::engine->GetPlayerInfo(player.index, &info))
			strcpy(name, info.name);
	}
	boxName.Draw(drawList, rectangle.value(), name);

	healthbar.Draw(drawList, rectangle.value(), player.health);

	if (weapon.enabled) { // Don't ask for the weapon, if we don't have to
		if (player.activeWeapon > WeaponID::WEAPON_NONE) { // Also prevent invalids
			const char* localization = LocalizeWeaponID(player.activeWeapon);
			if (localization)
				this->weapon.Draw(drawList, rectangle->x + (rectangle->z - rectangle->x) * 0.5f, rectangle->w, true, localization);
		}
	}

	flags.Draw(drawList, rectangle->z + boxName.box.GetLineWidth() / 2.0f, rectangle->y, player);

	ImVec2 center2D;
	if (Utils::Project(player.headPos + headDotOffset, center2D))
		headDot.Draw(drawList, center2D);
}

void BuildMenu(PlayerStateSettings* playerStateSettings, const PlayerTeamSettings& playerTeamSettings)
{
	if (ImGui::MenuItem("Visible")) {
		*playerStateSettings = playerTeamSettings.visible;
	}
	if (ImGui::MenuItem("Occluded")) {
		*playerStateSettings = playerTeamSettings.occluded;
	}
}

void PlayerStateSettings::SetupGUI(const char* id)
{
	ImGui::PushID(id);

	if (ImGui::Popup("Copy from", "Copy from")) {
		if (ImGui::BeginMenu("Teammate")) {
			BuildMenu(this, esp.players.teammate);
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Enemy")) {
			BuildMenu(this, esp.players.enemy);
			ImGui::EndMenu();
		}
		if (ImGui::Selectable("Local")) {
			*this = esp.players.local;
		}
		ImGui::EndPopup();
	}

	boxName.SetupGUI(id);
	healthbar.SetupGUI("Healthbar");
	weapon.SetupGUI("Weapon");
	flags.SetupGUI("Flags");
	headDot.SetupGUI("Head dot");

	ImGui::Text("Head dot offset");
	ImGui::SameLine();
	if (ImGui::Popup("Head dot offset")) {
		ImGui::DragFloat("Offset X", &headDotOffset.x, 0.1f);
		ImGui::DragFloat("Offset Y", &headDotOffset.y, 0.1f);
		ImGui::DragFloat("Offset Z", &headDotOffset.z, 0.1f);
		ImGui::EndPopup();
	}

	ImGui::PopID();
}

SCOPED_SERIALIZER(PlayerStateSettings)
{
	SERIALIZE_STRUCT("Box name", boxName);
	SERIALIZE_STRUCT("Healthbar", healthbar);
	SERIALIZE_STRUCT("Weapon", weapon);
	SERIALIZE_STRUCT("Flags", flags);
	SERIALIZE_STRUCT("Head dot", headDot);
	SERIALIZE_VECTOR3D("Head dot offset", headDotOffset);
}