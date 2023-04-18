// A lot of this code is based off the xcb documentation
// for OpenGL https://xcb.freedesktop.org/opengl/


#include <X11/Xlib-xcb.h>
#include <xcb/xcb.h>
#include <GL/glew.h>
#include <iostream>
#include <GL/glx.h>
#include <cstring>
#include <GL/gl.h>



// Pulled directly form https://xcb.freedesktop.org/opengl/
// Used for setting up frame buffer configurations
// https://registry.khronos.org/OpenGL-Refpages/gl2.1/xhtml/glXChooseFBConfig.xml
static int visual_attribs[] = {
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


int main() {
  Display *display;
  int screen_id;

  // Serves as connection through Xlib
  // https://www.x.org/releases/X11R7.5/doc/man/man3/XOpenDisplay.3.html
  display = XOpenDisplay(0);
  if (!display)
    return 1;


  // Gets XCB connection using Xlib display
  // https://www.x.org/releases/current/doc/man/man3/XGetXCBConnection.3.xhtml
  screen_id = DefaultScreen(display);
  xcb_connection_t *connection = XGetXCBConnection(display);
  if (!connection) {
    XCloseDisplay(display);
    return 1;
  }


  // Lets XCB control event queue
  // https://www.x.org/releases/current/doc/man/man3/XSetEventQueueOwner.3.xhtml
  XSetEventQueueOwner(display, XCBOwnsEventQueue);


  // Get screen
  // https://xcb.freedesktop.org/windowcontextandmanipulation/
  xcb_screen_t *screen = xcb_setup_roots_iterator(xcb_get_setup(connection)).data;
  

  // Returns GLX frame buffer configs
  // https://registry.khronos.org/OpenGL-Refpages/gl2.1/xhtml/glXChooseFBConfig.xml
  int num_fb_configs = 0;
  GLXFBConfig *fb_configs = glXChooseFBConfig(display, screen_id, visual_attribs, &num_fb_configs);
  if (!fb_configs || num_fb_configs == 0)
    return 1;
  GLXFBConfig fb_config = fb_configs[0];


  // "return information about a GLX frame buffer configuration"
  // https://registry.khronos.org/OpenGL-Refpages/gl2.1/xhtml/glXGetFBConfigAttrib.xml
  int visual_id = 0;
  glXGetFBConfigAttrib(display, fb_config, GLX_VISUAL_ID, &visual_id);


  // Create OpenGL context
  // https://registry.khronos.org/OpenGL-Refpages/gl2.1/xhtml/glXCreateNewContext.xml
  GLXContext gl_context = glXCreateNewContext(display, fb_config, GLX_RGBA_TYPE, 0, True);
  if (!gl_context)
    return 1;


  // Creates id's for colormap and window
  // https://xcb.freedesktop.org/opengl/
  xcb_colormap_t colormap = xcb_generate_id(connection);
  xcb_window_t window = xcb_generate_id(connection);


  // Create colormap
  // https://xcb.freedesktop.org/colorsandpixmaps/
  xcb_create_colormap(
    connection,
    XCB_COLORMAP_ALLOC_NONE,
    colormap,
    screen->root,
    visual_id  
  );


  // Create value masks for window
  // https://www.x.org/releases/X11R7.5/doc/libxcb/tutorial/
  // ^ Great resource btw
  uint32_t event_mask = XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_KEY_PRESS;
  uint32_t value_mask = XCB_CW_EVENT_MASK | XCB_CW_COLORMAP;
  uint32_t value_list[] = {event_mask, colormap, 0};


  // Creates the window
  // https://www.x.org/releases/current/doc/man/man3/xcb_create_window.3.xhtml  
  xcb_create_window(
    connection,
    XCB_COPY_FROM_PARENT,
    window,
    screen->root,
    0, 0,
    screen->width_in_pixels, screen->height_in_pixels,
    0,
    XCB_WINDOW_CLASS_INPUT_OUTPUT,
    visual_id,
    value_mask, 
    value_list
  );


  // Provide hints to DE on how window should be drawn
  // xcb_intern_atom gets the atom id
  // http://xcb-d.dpldocs.info/xcb.xproto.xcb_intern_atom.html
  // xcb_intern_atom_reply gets the value of the id?
  // https://www.systutorials.com/docs/linux/man/3-xcb_intern_atom_reply/
  const char* wm_wtype_str = "_NET_WM_WINDOW_TYPE";
  xcb_atom_t wtype_atom = xcb_intern_atom_reply(connection, xcb_intern_atom(connection, 0, strlen(wm_wtype_str), wm_wtype_str), nullptr)->atom;
  const char* wm_wtype_desk_str = "_NET_WM_WINDOW_TYPE_DESKTOP";
  xcb_atom_t wtype_desk_atom = xcb_intern_atom_reply(connection, xcb_intern_atom(connection, 0, strlen(wm_wtype_desk_str), wm_wtype_desk_str), nullptr)->atom;


  // Changes the property defined in wm_wtype_str to the one set by wtype_desk_atom
  // https://www.x.org/releases/current/doc/man/man3/xcb_change_property.3.xhtml
  xcb_change_property(connection, XCB_PROP_MODE_REPLACE, window, wtype_atom, XCB_ATOM_ATOM, 32, 1, &wtype_desk_atom);


  // Now we map the window to the connection
  // https://www.x.org/releases/current/doc/man/man3/xcb_map_window.3.xhtml
  xcb_map_window(connection, window);


  // "create an on-screen rendering area"
  // https://registry.khronos.org/OpenGL-Refpages/gl2.1/xhtml/glXCreateWindow.xml
  GLXWindow glx_window = glXCreateWindow(display, fb_config, window, 0);
  if (!window)
  {
    xcb_destroy_window(connection, window);
    glXDestroyContext(display, gl_context);
    return 1;
  }
  
  // "attach a GLX context to a GLX drawable"
  // https://registry.khronos.org/OpenGL-Refpages/gl2.1/xhtml/glXMakeContextCurrent.xml
  GLXDrawable drawable = glx_window;
  if (!glXMakeContextCurrent(display, drawable, drawable, gl_context))
  {
    xcb_destroy_window(connection, window);
    glXDestroyContext(display, gl_context);
    return 1;
  }


  // Stuff for OpenGL
  glewInit();
  
  const GLfloat vert_buffer_data[] = {
    -1.0f, -1.0f, 0.0f,
     1.0f, -1.0f, 0.0f,
     0.0f,  1.0f, 0.0f,
  };
  GLuint vertex_buffer;
  glGenBuffers(1, &vertex_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vert_buffer_data), vert_buffer_data, GL_STATIC_DRAW);
  

  // Main loop taken from link below
  // https://xcb.freedesktop.org/opengl/
  int running = 1;
  while (running) {
    xcb_generic_event_t *event = xcb_wait_for_event(connection);
    if (!event)
      return 1;
      
    switch(event->response_type & ~0x80) {
      case XCB_EXPOSE: {
        glClear(GL_COLOR_BUFFER_BIT);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);

        glXSwapBuffers(display, drawable);
        break;
      } default: {
        break;
      }

      free(event);
    }
  }


  glXDestroyWindow(display, glx_window);
  xcb_destroy_window(connection, window);
  glXDestroyContext(display, gl_context);
  return 0;
}