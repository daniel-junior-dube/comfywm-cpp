#pragma once

extern "C" {
#include <wlr/types/wlr_xdg_shell.h>
#define static
// ...
#undef static
}

#include <iostream>
#include <wayland-server.h>

class CMFYServer;

class CMFYView {
public:
  wl_list link;
  CMFYServer* server;
  wlr_xdg_surface* xdg_surface;
  wl_listener map;
  wl_listener unmap;
  wl_listener destroy;
  wl_listener request_move;
  wl_listener request_resize;
  bool is_mapped;
  int x, y;
  CMFYView(CMFYServer* server, wlr_xdg_surface* xdg_surface);
  ~CMFYView();
  void bind_events();
private:
};
