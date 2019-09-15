#pragma once

extern "C" {
#include <wlr/backend.h>
#include <wlr/types/wlr_output.h>
}

#include <iostream>
#include <cassert>
#include <optional>
#include <wayland-server.h>

#include "cmfy_output.hpp"

class CMFYServer {

  // ? Connection to a wayland display
  wl_display* wayland_display;

  // ? Display event loop context
	wl_event_loop* wayland_event_loop;
  wlr_backend* wlroots_backend;
public:
  wl_listener new_output_listener;
  wl_list outputs;

  CMFYServer(wl_display* display, wl_event_loop* event_loop, wlr_backend* backend);
  ~CMFYServer();
  static std::optional<CMFYServer> TryCreate();
  void start();
  void on_new_output(wl_listener* listener, void* data);
private:
};
