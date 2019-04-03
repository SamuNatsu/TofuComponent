#include "Button.h"

namespace TFC {
Button::Button() {}

Button::~Button() {}

bool Button::RegisterButton(const char* name,
                            int x1, int y1, int x2, int y2,
                            Button::VVF hover, Button::VVF press, Button::VVF release, Button::VVF leave){
	 // If the name is not available
    if (buttons.find(name) != buttons.end()) {
        error = "The name has been used";
        return false;
    }
	 // Set button attribute
    buttons[name].enabled = buttons[name].pressed = false;
	 // Set button detect rectangle
    buttons[name].x1 = x1;
    buttons[name].y1 = y1;
    buttons[name].x2 = x2;
    buttons[name].y2 = y2;
	 // Add event hook
    buttons[name].hookMgr.AddHook(
        "Hover&Leave",
        SDL_MOUSEMOTION,
        [&]() {
            static std::string nameStr = name;
            static VVF hoverFunction = hover;
            static VVF leaveFunction = leave;
            if (buttons[nameStr.c_str()].enabled && !buttons[nameStr.c_str()].pressed) {
                if (IsInRangeHover(buttons[name])) {
                    hoverFunction();
                }
                else {
                    leaveFunction();
                }
            }
        });
    buttons[name].hookMgr.AddHook(
        "Press",
        SDL_MOUSEBUTTONDOWN,
        [&]() {
            static std::string nameStr = name;
            static VVF pressFunction = press;
            if (buttons[nameStr.c_str()].enabled && IsInRangePress(buttons[name])) {
                buttons[nameStr.c_str()].pressed = true;
                pressFunction();
            }
        });
    buttons[name].hookMgr.AddHook(
        "Release&Hover",
        SDL_MOUSEBUTTONUP,
        [&]() {
            static std::string nameStr = name;
            static VVF releaseFunction = release;
            static VVF hoverFunction = hover;
            if (buttons[nameStr.c_str()].enabled && IsInRangePress(buttons[name])) {
                buttons[nameStr.c_str()].pressed = false;
                releaseFunction();
                hoverFunction();
            }
        });
	 // Initialize button
    EventHook::CallHook(buttons[name].hookMgr.GetHookID("Hover&Leave"));
    EventHook::CallHook(buttons[name].hookMgr.GetHookID("Press"));
    EventHook::CallHook(buttons[name].hookMgr.GetHookID("Release&Hover"));
    buttons[name].enabled = true;
	 // Return success
    return true;
}

bool Button::DeleteButton(const char *name) {
	 // If not exist
    if (buttons.find(name) == buttons.end()) {
        error = "Button not found";
        return false;
    }
	 // Delete button
    buttons.erase(name);
	 // Return success
    return true;
}

bool Button::EnableButton(const char* name) {
	 // If not exist
    if (buttons.find(name) == buttons.end()) {
        error = "Button not found";
        return false;
    }
	 // Set button attribute
    buttons[name].enabled = true;
	 // Return success
    return true;
}

bool Button::DisableButton(const char* name) {
	 // If not exist
    if (buttons.find(name) == buttons.end()) {
        error = "Button not found";
        return false;
    }
	 // Set button attribute
    buttons[name].enabled = false;
	 // Return request
    return true;
}

bool Button::IsEnabled(const char* name) {
	 // If not exist
    if (buttons.find(name) == buttons.end()) {
        error = "Button not found";
        return false;
    }
	 // Return request
    return buttons[name].enabled;
}

bool Button::DrawDebugLayer() {
	 // Store default render color
    Uint8 r, g, b, a;
    if (!TFC::Canvas::GetDrawColor(r, g, b, a)) {
        error = TFC::Canvas::CanvasData::error;
        return false;
    }
	 // Draw rectangle
    for (auto& i : buttons) {
        if (i.second.enabled) {
			 // Green for enabled button
            TFC::Canvas::SetDrawColor(0x0, 0xFF, 0x0);
            TFC::Canvas::DrawRect(i.second.x1, i.second.y1, i.second.x2 - i.second.x1, i.second.y2 - i.second.y1);
        }
        else {
			 // Red for disabled button
            TFC::Canvas::SetDrawColor(0xFF, 0x0, 0x0);
            TFC::Canvas::DrawRect(i.second.x1, i.second.y1, i.second.x2 - i.second.x1, i.second.y2 - i.second.y1);
        }
    }
	 // Reset render color
    if (!TFC::Canvas::SetDrawColor(r, g, b, a)) {
        error = TFC::Canvas::CanvasData::error;
        return false;
    }
	 // Return success
    return true;
}

std::string Button::GetError() const {
	 // Return request
    return error;
}

bool Button::IsInRangeHover(Button::btn &button) const {
	 // Return request
    return button.x1 <= TFC::Display::DisplayData::event.motion.x && button.x2 >= TFC::Display::DisplayData::event.motion.x && button.y1 <= TFC::Display::DisplayData::event.motion.y && button.y2 >= TFC::Display::DisplayData::event.motion.y;
}

bool Button::IsInRangePress(Button::btn &button) const {
	 // Return request
    return button.x1 <= TFC::Display::DisplayData::event.button.x && button.x2 >= TFC::Display::DisplayData::event.button.x && button.y1 <= TFC::Display::DisplayData::event.button.y && button.y2 >= TFC::Display::DisplayData::event.button.y;
}
} // TFC
