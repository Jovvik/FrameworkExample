#include "../../ESPStructure.hpp"

#include "xorstr.hpp"

#include "../../../../../GUI/Elements/ClickableColorButton.hpp"

TextSetting::TextSetting(const char* id)
	: id(id)
	, enabled(false)
	, fontScale(1.0f)
	, fontColor(ImGuiColors::white)
	, shadow(false)
	, shadowColor(ImGuiColors::black)
{
}

void TextSetting::Draw(ImDrawList* drawList, float x, float y, bool centered, const char* text) const
{
	if (!enabled)
		return;

	// Hack
	const float oldFontScale = ImGui::GetFont()->Scale;
	ImGui::GetFont()->Scale = fontScale;
	ImGui::PushFont(ImGui::GetFont());

	const ImVec2 size = ImGui::CalcTextSize(text);

	const ImVec2 position(x - (centered ? size.x / 2.0f : 0.0f), y);

	if (shadow)
		drawList->AddText(ImVec2(position.x + 1.0f, position.y + 1.0f), shadowColor, text);

	drawList->AddText(position, fontColor, text);

	ImGui::GetFont()->Scale = oldFontScale;
	ImGui::PopFont();
}

bool TextSetting::operator==(const TextSetting& other) const
{
	// clang-format off
	return
		enabled == other.enabled &&
		fontScale == other.fontScale &&
		fontColor == other.fontColor &&
		shadow == other.shadow &&
		shadowColor == other.shadowColor;
	// clang-format on
}

float TextSetting::GetLineHeight() const
{
	return ImGui::GetTextLineHeightWithSpacing() * fontScale;
}

void TextSetting::Copy(TextSetting& src)
{
	enabled = src.enabled;
	fontScale = src.fontScale;
	fontColor = src.fontColor;
	shadow = src.shadow;
	shadowColor = src.shadowColor;
}

void TextSetting::SetupGUI()
{
	ImGui::PushID(id);
	ImGui::Checkbox(id, &enabled);

	ImGui::SameLine();
	if (ImGui::Button("..."))
		ImGui::OpenPopup(id);

	if (ImGui::BeginPopup(id)) {
		ImGui::SliderFloat(xorstr_("Font scale"), &fontScale, 0.1f, 2.0f, "%.2f");
		ImGui::ClickableColorButton(xorstr_("Font color"), fontColor);
		ImGui::Checkbox(xorstr_("Shadow"), &shadow);
		if (shadow)
			ImGui::ClickableColorButton(xorstr_("Shadow color"), shadowColor);

		ImGui::EndPopup();
	}

	ImGui::PopID();
}

BEGIN_SERIALIZED_STRUCT(TextSetting::Serializer, id)
SERIALIZED_TYPE(xorstr_("Enabled"), enabled)
SERIALIZED_TYPE(xorstr_("Font scale"), fontScale)
SERIALIZED_TYPE(xorstr_("Font color"), fontColor)
SERIALIZED_TYPE(xorstr_("Shadow"), shadow)
SERIALIZED_TYPE(xorstr_("Shadow color"), shadowColor)
END_SERIALIZED_STRUCT
