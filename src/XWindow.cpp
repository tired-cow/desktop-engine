#include "XWindow.h"


XWindow::XWindow() {
    // Has our collection of screens
    xorg_display_conn =  XOpenDisplay(0);
    if (xorg_display_conn == NULL) {
        std::cout << "Failed to establish an XServer connection!\n";
        exit(1);
    }

    xcb_conn = XGetXCBConnection(xorg_display_conn);
    if (!xcb_conn) { 
        std::cout << "Failed to establish an XCB connection!\n";
        exit(1);
    }

    XSetEventQueueOwner(xorg_display_conn, XCBOwnsEventQueue);


    // Gets first screen
    xcb_screen_t *screen = xcb_setup_roots_iterator(xcb_get_setup(xcb_conn)).data;

    // Need to do some GLX to get the number of framebuffer configs for the DEFAULT display
    int fb_cfg_len = 0;
    GLXFBConfig *fb_cfgs = glXChooseFBConfig(xorg_display_conn, DefaultScreen(xorg_display_conn), FB_ATTRIBUTES, &fb_cfg_len);
    if (fb_cfg_len == 0) {
        std::cout << "Failed to get a suitable GLX config!\n";
        exit(1);
    }


    // Select the first config and get visual id for xcb
    GLXFBConfig fb_cfg = fb_cfgs[0];
    
    int glx_visual_id;
    glXGetFBConfigAttrib(xorg_display_conn, fb_cfg, GLX_VISUAL_ID, &glx_visual_id);

    xcb_colormap_id = xcb_generate_id(xcb_conn);
    xcb_create_colormap (
        xcb_conn,
        XCB_COLORMAP_ALLOC_NONE,
        xcb_colormap_id,
        screen->root,
        glx_visual_id
    );


    // Define masks and data for window
    uint32_t value_mask = XCB_CW_EVENT_MASK | XCB_CW_COLORMAP;
    uint32_t value_mask_data[] = {
        XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_KEY_PRESS, 
        xcb_colormap_id, 0
    };

    xcb_window_id = xcb_generate_id(xcb_conn);
    xcb_create_window (
        xcb_conn, XCB_COPY_FROM_PARENT,
        xcb_window_id, screen->root,
        0, 0,
        screen->width_in_pixels, screen->height_in_pixels,
        0, XCB_WINDOW_CLASS_INPUT_OUTPUT,
        glx_visual_id, value_mask,
        value_mask_data
    );


    // Provides hints
    set_xcb_atom("_NET_WM_WINDOW_TYPE", "_NET_WM_WINDOW_TYPE_DESKTOP");


    glx_context = glXCreateNewContext(xorg_display_conn, fb_cfg, GLX_RGBA_TYPE, 0, true);
    if (glx_context == NULL) {
        std::cout << "Failed to create a GLX context!\n";
        exit(1);
    }


    glx_window = glXCreateWindow(xorg_display_conn, fb_cfg, xcb_window_id, 0);
    if (!glx_window) {
        std::cout << "Failed to create a GLX window!\n";
        exit(1);
    }


    glx_drawable = glx_window;
    if (!glXMakeContextCurrent(xorg_display_conn, glx_drawable, glx_drawable, glx_context)) {
        std::cout << "Failed to set the current context!\n";
        exit(1);
    }


    xcb_map_window(xcb_conn, xcb_window_id);
}


XWindow::~XWindow() {
    glXDestroyWindow(xorg_display_conn, glx_window);
    glXDestroyContext(xorg_display_conn, glx_context);
    xcb_free_colormap(xcb_conn, xcb_colormap_id);
    xcb_disconnect(xcb_conn);
}


void XWindow::set_xcb_atom(const char* atom_name, const char* atom_value) {
    xcb_atom_t n_atom = xcb_intern_atom_reply (xcb_conn, xcb_intern_atom(xcb_conn, 0, strlen(atom_name), atom_name), nullptr)->atom;
    xcb_atom_t v_atom = xcb_intern_atom_reply(xcb_conn, xcb_intern_atom(xcb_conn, 0, strlen(atom_value), atom_value), nullptr)->atom;
    xcb_change_property(xcb_conn, XCB_PROP_MODE_REPLACE, xcb_window_id, n_atom, XCB_ATOM_ATOM, 32, 1, &v_atom);
}

xcb_connection_t* XWindow::get_xcb_connection() {
    return xcb_conn;
}

 GLXWindow& XWindow::get_glx_window() {
    return glx_window;
 }

 GLXDrawable& XWindow::get_glx_drawable() {
    return glx_drawable;
 }

 Display* XWindow::get_xorg_display_connection() {
    return xorg_display_conn;
 }