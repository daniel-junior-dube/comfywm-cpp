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
  wlr_output* wlroots_output;
  wl_list link;
  CMFYOutput(wlr_output* wlroots_output);
  ~CMFYOutput();
  bool has_modes();
  std::optional<wlr_output_mode*> get_default_mode();
  std::pair<int, int> get_effective_resolution();
  void set_mode(wlr_output_mode*);
  void for_each_interacting_views_reverse(CMFYServer* server, std::function<void(CMFYView* view)> callback);
  void bind_events(CMFYServer& server);
  void unbind_events(CMFYServer& server);
  //static void on_output_destroy(wl_listener *listener, void *data);
};
