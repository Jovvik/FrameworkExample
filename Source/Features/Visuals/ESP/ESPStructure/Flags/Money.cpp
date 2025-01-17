#include "../PlayerFlags.hpp"

#include "imgui.h"
#include <string>

std::optional<std::string> Money::GetText(const Player& player) const
{
	return "$" + std::to_string(player.account);
}