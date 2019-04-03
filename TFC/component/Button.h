#ifndef BUTTON_H
#define BUTTON_H

#include "../event/FSM/BaseState.h"
#include "../event/FSM/FiniteStateMachine.h"
#include "../event/EventHookMgr.h"
#include "../graph/Canvas.h"
#include "../graph/Display.h"
#include "../TFC_header.h"

#include <string>
#include <functional>
#include <unordered_map>

namespace TFC {
class Button {
using VVF = std::function<void()>;
public:
     // Construction & Destruction
    Button();
    ~Button();
     // Manage
    bool RegisterButton(const char*, int, int, int, int, VVF, VVF, VVF, VVF);
    bool DeleteButton(const char*);
    bool EnableButton(const char*);
    bool IsEnabled(const char*);
    bool DisableButton(const char*);
    bool DrawDebugLayer();
     // Get
    std::string GetError() const;
private:
	 // Default button structure
    struct btn {
        bool enabled, pressed;
        int x1, y1, x2, y2;
        TFC::EventHookMgr hookMgr;
    };
	 // Button map
    std::unordered_map<std::string, btn> buttons;
	 // Error string
    std::string error = "";
	 // Judge
    bool IsInRangeHover(btn&) const;
    bool IsInRangePress(btn&) const;
};
} // TFC

#endif // BUTTON_H
