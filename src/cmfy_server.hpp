#pragma once

extern "C" {
#include <wlr/backend.h>
#include <wlr/types/wlr_output.h>
#include <wlr/types/wlr_output_layout.h>
#include <wlr/types/wlr_xdg_shell.h>
#define static
#include <wlr/render/wlr_renderer.h>
#include <wlr/types/wlr_compositor.h>
#include <wlr/types/wlr_data_device.h>
#undef static
}

#include <iostream>
#include <cassert>
#include <optional>
#include <wayland-server.h>

#include "cmfy_output.hpp"
#include "cmfy_view.hpp"

class CMFYServer {

  // ? Connection to a wayland display
  wl_display* wayland_display;

  // ? Display event loop context
  wl_event_loop* wayland_event_loop;
  wlr_backend* wlroots_backend;
  wlr_output_layout* wlroots_output_layout;
  wlr_xdg_shell* main_xdg_shell;
public:
  wl_listener new_output_listener;
  wl_listener new_xdg_surface_listener;
  wlr_renderer* wlroots_renderer;
  wl_list outputs;
  wl_list views;

  CMFYServer(wl_display* display, wl_event_loop* event_loop, wlr_backend* backend, wlr_renderer* wlroots_renderer, wlr_output_layout* output_layout);
  ~CMFYServer();
  static std::optional<CMFYServer*> TryCreate();
  void start();
  void add_view(CMFYView* view);
private:
};
