#include "../ESPStructure.hpp"

#include "xorstr.hpp"

#include "../../../../../GUI/Elements/ClickableColorButton.hpp"
#include "../../../../../GUI/Elements/Popup.hpp"
#include "../../../../../GUI/ImGuiColors.hpp"

TextSetting::TextSetting()
	: enabled(false)
	, fontScale(1.0f)
	, fontColor(ImGuiColors::white)
	, shadow(true)
	, shadowColor(ImGuiColors::black)
{
}

void TextSetting::Draw(ImDrawList* drawList, float x, float y, bool centered, const char* text, std::optional<ImColor> colorOverride) const
{
	if (!enabled || !text)
		return;

	if (fontScale <= 0.0f)
		return;

	// Hack
	const float oldFontScale = ImGui::GetFont()->Scale;
	ImGui::GetFont()->Scale *= fontScale;
	ImGui::PushFont(ImGui::GetFont());

	const ImVec2 size = ImGui::CalcTextSize(text);

	const ImVec2 position(x - (centered ? size.x / 2.0f : 0.0f), y);

	if (shadow)
		drawList->AddText(ImVec2(position.x + 1.0f, position.y + 1.0f), shadowColor, text);

	drawList->AddText(position, colorOverride.has_value() ? colorOverride.value() : fontColor, text);

	ImGui::GetFont()->Scale = oldFontScale;
	ImGui::PopFont();
}

float TextSetting::GetLineHeight() const
{
	return ImGui::GetTextLineHeight() * fontScale;
}

void TextSetting::SetupGUI(const char* id)
{
	ImGui::PushID(id);
	ImGui::Checkbox(id, &enabled);

	ImGui::SameLine();

	if (ImGui::Popup(id)) {
		ImGui::SliderFloat(xorstr_("Font scale"), &fontScale, 0.1f, 2.0f, xorstr_("%.2f"));
		ImGui::ClickableColorButton(xorstr_("Font color"), fontColor);
		ImGui::Checkbox(xorstr_("Shadow"), &shadow);
		if (shadow)
			ImGui::ClickableColorButton(xorstr_("Shadow color"), shadowColor);

		ImGui::EndPopup();
	}

	ImGui::PopID();
}

SCOPED_SERIALIZER(TextSetting)
{
	SERIALIZE(xorstr_("Enabled"), enabled);
	SERIALIZE(xorstr_("Font scale"), fontScale);
	SERIALIZE_VECTOR4D(xorstr_("Font color"), fontColor.Value);
	SERIALIZE(xorstr_("Shadow"), shadow);
	SERIALIZE_VECTOR4D(xorstr_("Shadow color"), shadowColor.Value);
}