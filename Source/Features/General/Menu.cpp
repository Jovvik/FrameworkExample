#include "Menu.hpp"

#include "xorstr.hpp"

#include "../../GUI/Elements/Keybind.hpp"
#include "../../GUI/GUI.hpp"

#include "EventLog.hpp"

int Features::General::Menu::menuKey = static_cast<int>(ImGuiKey_Insert);

#ifdef DEBUG
bool isShowingDemoWindow = false;
bool isShowingMetricsWindow = false;
bool isShowingDebugLogWindow = false;
bool isShowingStackToolWindow = false;
bool isShowingAboutWindow = false;
bool isShowingStyleEditor = false;
bool isShowingUserGuide = false;
#endif

bool wasPressed = false;

void Features::General::Menu::ImGuiLoop()
{
#ifdef DEBUG
	if (isShowingDemoWindow)
		ImGui::ShowDemoWindow();
	if (isShowingMetricsWindow)
		ImGui::ShowMetricsWindow();
	if (isShowingDebugLogWindow)
		ImGui::ShowDebugLogWindow();
	if (isShowingStackToolWindow)
		ImGui::ShowStackToolWindow();
	if (isShowingAboutWindow)
		ImGui::ShowAboutWindow();
	if (isShowingStyleEditor)
		ImGui::ShowStyleEditor();
	if (isShowingUserGuide)
		ImGui::ShowUserGuide();
#endif

	bool isPressed = IsInputDown(menuKey, false, false);

	if (isPressed && !wasPressed) {
		Gui::visible = !Gui::visible;
		Features::General::EventLog::CreateReport(xorstr_("%s the menu"), Gui::visible ? xorstr_("Opened") : xorstr_("Closed"));
	}
	wasPressed = isPressed;
}

void Features::General::Menu::SetupGUI()
{
	ImGui::InputSelector(xorstr_("Menu key (%s)"), menuKey);
#ifdef DEBUG
	ImGui::Checkbox("Show Demo Window", &isShowingDemoWindow);
	ImGui::Checkbox("Show Metrics Window", &isShowingMetricsWindow);
	ImGui::Checkbox("Show Debug Log Window", &isShowingDebugLogWindow);
	ImGui::Checkbox("Show Stack Tool Window", &isShowingStackToolWindow);
	ImGui::Checkbox("Show About Window", &isShowingAboutWindow);
	ImGui::Checkbox("Show Style Editor", &isShowingStyleEditor);
	// ImGui::Checkbox("Show Style Selector", &isShowingStyleSelector); // I wrote that myself under this ifdef
	// ImGui::Checkbox("Show Font Selector", &isShowingFontSelector); // I only add one font, kinda pointless to make a selector with only one option
	ImGui::Checkbox("Show User Guide", &isShowingUserGuide);
#endif
	if (ImGui::Button(xorstr_("Set style to dark"))) {
		ImGui::StyleColorsDark(&ImGui::GetStyle());
	}
	ImGui::SameLine();
	if (ImGui::Button(xorstr_("Set style to light"))) {
		ImGui::StyleColorsLight(&ImGui::GetStyle());
	}
	ImGui::SameLine();
	if (ImGui::Button(xorstr_("Set style to classic"))) {
		ImGui::StyleColorsClassic(&ImGui::GetStyle());
	}

	ImGui::Text(xorstr_("ImGui Version: %s"), ImGui::GetVersion());
}

BEGIN_SERIALIZED_STRUCT(Features::General::Menu::Serializer, xorstr_("Menu"))
SERIALIZED_TYPE(xorstr_("Menu key"), menuKey)
// Intentionally not saving the showing...window because nobody needs those
END_SERIALIZED_STRUCT