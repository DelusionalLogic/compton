#pragma once

struct XWindowData {
    Window id;
    Window client_win;
    Window leader;
    wintype_t type;
    bool wmwin;
    XWindowAttributes attrs;
};
