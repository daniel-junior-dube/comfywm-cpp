#pragma once

extern "C" {
#include <wlr/types/wlr_xdg_shell.h>
#define static
// ...
#undef static
}

#include <iostream>
#include <wayland-server.h>
#include <functional>

class CMFYServer;

class CMFYView {
public:
  wl_list link;
  CMFYServer* server;
  wlr_xdg_surface* top_level_xdg_surface;
  wl_listener map;
  wl_listener unmap;
  wl_listener destroy;
  wl_listener request_move;
  wl_listener request_resize;
  bool is_mapped;
  int x, y;
  CMFYView(CMFYServer* server, wlr_xdg_surface* top_level_xdg_surface);
  ~CMFYView();
  void bind_events();
  void for_each_surface(wlr_surface_iterator_func_t callback, void *user_data);
  static void on_xdg_surface_map(struct wl_listener *listener, void *data);
  static void on_xdg_surface_unmap(struct wl_listener *listener, void *data);
  static void on_xdg_surface_destroy(struct wl_listener *listener, void *data);
  static void on_xdg_toplevel_request_move(struct wl_listener *listener, void *data);
  static void on_xdg_toplevel_request_resize(struct wl_listener *listener, void *data);
private:
};
