#pragma once

extern "C" {
#include <wlr/types/wlr_output_layout.h>
#define static
// ...
#undef static
}

#include <wayland-server.h>

class CMFYServer;
class CMFYOutput;

class CMFYOutputLayout {
public:
  wlr_output_layout* wlroots_output_layout;
  wl_list outputs;
  CMFYOutputLayout(wlr_output_layout* wlroots_output_layout);
  ~CMFYOutputLayout();
  void add_output(CMFYOutput* output);
  void remove_output(CMFYOutput& output);
  std::pair<double, double> get_output_origin(CMFYOutput* output);
  //void bind_events(CMFYServer* server);
};
