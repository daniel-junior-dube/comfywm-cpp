#pragma once

extern "C" {
#include <wlr/backend.h>
}

#include <wayland-server.h>

class Server {

  // ? Connection to a wayland display
  wl_display* wayland_display;

  // ? Display event loop context
	wl_event_loop* wayland_event_loop;
  wlr_backend* wlroots_backend;
public:
  Server(wl_display* display, wl_event_loop* event_loop, wlr_backend* backend);
  ~Server();
private:
};
