// #include <iostream>
// #include <X11/Xlib.h>

// int main() {
// 	Display* display;
// 	Window window;
// 	Screen* screen;
// }

#include <iostream>
#include <cstring>

#include <GL/glx.h>
#include <GL/gl.h>
#include <xcb/xcb.h>
#include <X11/Xlib-xcb.h>


int main()
{
	/* Open the connection to the X server */
	xcb_connection_t *connection = xcb_connect(NULL, NULL);


	/* Get the first screen */
	const xcb_setup_t      *setup  = xcb_get_setup(connection);
	xcb_screen_iterator_t   iter   = xcb_setup_roots_iterator(setup);
	xcb_screen_t           *screen = iter.data;


	/* Create graphcis context */
	uint32_t contextId = xcb_generate_id(connection);
	uint32_t graphValueMask = XCB_GC_FOREGROUND | XCB_GC_GRAPHICS_EXPOSURES;
	uint32_t graphValueList[] = {
		screen->width_in_pixels,
		0
	};
	xcb_create_gc(connection, contextId, screen->root, graphValueMask, graphValueList);


	/* Create value masks */
	uint32_t winValueMask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
	uint32_t winValueList[] = {
			screen->black_pixel, 
			XCB_EVENT_MASK_EXPOSURE
		};


	/* Create the window */
	xcb_window_t window = xcb_generate_id(connection);
	xcb_create_window(connection,                      						  /* Connection          */
						XCB_COPY_FROM_PARENT,         						  /* depth(same as root)*/
						window,                        						  /* window Id           */
						screen->root,                  						  /* parent window       */
						0, 0,                         						  /* x, y                */
						screen->width_in_pixels, screen->height_in_pixels,    /* width, height       */
						10,                            						  /* border_width        */
						XCB_WINDOW_CLASS_INPUT_OUTPUT, 						  /* class               */
						screen->root_visual,           						  /* visual              */
						winValueMask, winValueList );                     	  /* masks				 */
	

	/* Set window properties */
	const char* wmWindowTypeName = "_NET_WM_WINDOW_TYPE";
	xcb_atom_t windowTypeAtom = xcb_intern_atom_reply(connection, xcb_intern_atom(connection, 0, strlen(wmWindowTypeName), wmWindowTypeName), nullptr)->atom;
	const char* selectionName = "_NET_WM_WINDOW_TYPE_DESKTOP";
	xcb_atom_t selectionAtom = xcb_intern_atom_reply(connection, xcb_intern_atom(connection, 0, strlen(selectionName), selectionName), nullptr)->atom;
	xcb_change_property(connection, XCB_PROP_MODE_REPLACE, window, windowTypeAtom, XCB_ATOM_ATOM, 32, 1, &selectionAtom);


	/* Map the window on the screen */
	xcb_map_window(connection, window);


	/* Make sure commands are sent before we start*/
	xcb_flush(connection);


	/* DATA */
	xcb_rectangle_t rectangles[] = {
		{ 500, 300, 500, 200},
		{ 950, 800, 300, 4000}
	};

	/* Poll for events */
	xcb_generic_event_t *event;
	while((event = xcb_wait_for_event(connection))) {
		switch(event->response_type & ~0x80) {
			case XCB_EXPOSE: {
				xcb_poly_rectangle(connection, window, contextId, 2, rectangles);
				xcb_flush(connection);
				break;
			} default: {
				break;
			}
		}

		free(event);
	}


	/* Clean up */
	xcb_disconnect(connection);
	return 0;
}