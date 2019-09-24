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

#include <functional>
#include "output.hpp"

class CMFYView;

using RGBAColor = float[4];

struct RenderData {
  wlr_output* output;
  CMFYView* view;
  wlr_renderer* renderer;
  timespec* when;
};

class CMFYRenderer {
  bool should_clear = true;
  RGBAColor clear_color = { 0.0, 0.0, 0.0, 1.0 };
public:
  wlr_renderer* wlroots_renderer;
  CMFYRenderer(wlr_renderer* wlroots_renderer);
  ~CMFYRenderer();
  void render(int width, int height, std::function<void()> callback);
  void render_output(CMFYOutput output, std::function<void()> callback);
  static void draw_surface(wlr_surface *surface, int sx, int sy, void *data);
private:
};
