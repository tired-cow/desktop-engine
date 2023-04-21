#pragma once

#include <X11/Xlib-xcb.h>
#include <xcb/xcb.h>
#include <GL/glx.h>
#include <iostream>
#include <cstring>
#include <stdio.h> // Used for exit

class XWindow {
private:
    // Needed to get FB configs
    const int FB_ATTRIBUTES[23] = {
        GLX_X_RENDERABLE, True,
        GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
        GLX_RENDER_TYPE, GLX_RGBA_BIT,
        GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
        GLX_RED_SIZE, 8,
        GLX_GREEN_SIZE, 8,
        GLX_BLUE_SIZE, 8,
        GLX_ALPHA_SIZE, 8,
        GLX_DEPTH_SIZE, 24,
        GLX_STENCIL_SIZE, 8,
        GLX_DOUBLEBUFFER, True,
        None
    };

private:
    Display *xorg_display_conn;
    xcb_connection_t *xcb_conn;
    xcb_screen_t *xcb_screen;
    xcb_colormap_t xcb_colormap_id;
    xcb_window_t xcb_window_id;

    GLXContext glx_context;
    GLXWindow glx_window;
    GLXDrawable glx_drawable;
    

private:
    void set_xcb_atom(const char*, const char*);

public:
    XWindow();
    ~XWindow();

    xcb_connection_t* get_xcb_connection();
    GLXWindow& get_glx_window();
    GLXDrawable& get_glx_drawable();
    Display* get_xorg_display_connection();
};