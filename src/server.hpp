#pragma once

extern "C" {
#include <wlr/backend.h>
#include <wlr/types/wlr_output.h>
//#include <wlr/types/wlr_output_layout.h>
#include <wlr/types/wlr_xdg_shell.h>
#include <wlr/types/wlr_seat.h>
#define static
#include <wlr/types/wlr_matrix.h>
#include <wlr/render/wlr_renderer.h>
#include <wlr/types/wlr_compositor.h>
#include <wlr/types/wlr_data_device.h>
#undef static
}

#include <iostream>
#include <cassert>
#include <time.h>
#include <optional>
#include <wayland-server.h>

#include "output.hpp"
#include "output_layout.hpp"
#include "view.hpp"
#include "cursor.hpp"
#include "renderer.hpp"

class CMFYServer {
  wl_display* wayland_display;
  wl_event_loop* wayland_event_loop;
  wlr_backend* wlroots_backend;
  wlr_xdg_shell* main_xdg_shell;
  CMFYCursor cursor;
  wlr_seat* seat;
public:
  wl_listener destroy_output_listener;
  wl_listener new_output_listener;
  wl_listener new_xdg_surface_listener;
  wl_listener new_input_listener;
  wl_listener request_cursor_listener;
  wl_listener on_output_frame_listener;
  //wlr_output_layout* wlroots_output_layout;
  CMFYOutputLayout output_layout;
  CMFYRenderer renderer;
  //wl_list outputs;
  wl_list views;
  wl_list keyboards;
  const char* socket_name;
  CMFYServer(wl_display* display, wl_event_loop* event_loop, wlr_backend* backend, wlr_renderer* wlroots_renderer,
    wlr_output_layout* wlroots_output_layout);
  ~CMFYServer();
  static std::optional<CMFYServer*> TryNew();
  void start();
  void add_view(CMFYView* view);
  void set_cursor(CMFYCursor cursor);
  static void on_new_output(wl_listener* listener, void* data);
  static void on_destroy_output(wl_listener* listener, void* data);
  static void on_output_frame(wl_listener* listener, void* data);
  static void on_new_input(wl_listener* listener, void* data);
  static void on_seat_request_cursor(wl_listener* listener, void* data);
  static void on_new_xdg_surface(struct wl_listener* listener, void* data);
private:
};
