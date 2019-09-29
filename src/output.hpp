#pragma once

extern "C" {
#include <wlr/types/wlr_output.h>
#include <wlr/types/wlr_xdg_shell.h>
#include <wlr/types/wlr_output.h>
#include <wlr/types/wlr_output_layout.h>
#define static
#include <wlr/types/wlr_matrix.h>
#include <wlr/render/wlr_renderer.h>
#undef static
}

#include <wayland-server.h>
#include <wayland-util.h>
#include <time.h>
#include <optional>
#include <utility>
#include <functional>

class CMFYServer;
class CMFYView;

class CMFYOutput {
public:
  wl_listener frame;
  wl_listener destroy;
  wlr_output* wlroots_output;
  CMFYServer* server;
  wl_list link;
  CMFYOutput(wlr_output* wlroots_output, CMFYServer* server);
  ~CMFYOutput();
  static void on_output_destroy(wl_listener *listener, void *data);
  static void on_output_frame(wl_listener *listener, void *data);
  bool has_modes();
  std::optional<wlr_output_mode*> get_default_mode();
  std::pair<int, int> get_effective_resolution();
  void set_mode(wlr_output_mode*);
  std::pair<double, double> get_output_layout_coords();
  void for_each_views_reverse(std::function<void(CMFYView* view)> callback);
  void bind_events();
};
