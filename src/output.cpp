#include "output.hpp"
#include "view.hpp"
#include "server.hpp"

void CMFYOutput::on_output_destroy(wl_listener *listener, void *data) {
  CMFYOutput* output = wl_container_of(listener, output, destroy);
  wl_list_remove(&output->link);
  wl_list_remove(&output->destroy.link);
  wl_list_remove(&output->frame.link);
  free(output);
}

/*
 * This function is called every time an output is ready to display a frame,
 * generally at the output's refresh rate (e.g. 60Hz).
 */
void CMFYOutput::on_output_frame(wl_listener* listener, void* data) {
  CMFYOutput* output = wl_container_of(listener, output, frame);
  CMFYRenderer renderer = output->server->renderer;

  struct timespec now;
  clock_gettime(CLOCK_MONOTONIC, &now);

  renderer.render_output(*output, [&]() {
    /* Each subsequent window we render is rendered on top of the last. Because
     * our view list is ordered front-to-back, we iterate over it backwards. */
    CMFYView* view;
    wl_list_for_each_reverse(view, &output->server->views, link) {
      if (!view->is_mapped) {
        /* An unmapped view should not be rendered. */
        continue;
      }
      RenderData rdata {
        .output = output->wlroots_output,
        .view = view,
        .renderer = renderer.wlroots_renderer,
        .when = &now,
      };
      /* This calls our render_surface function for each surface among the
      * xdg_surface's toplevel and popups. */
      wlr_xdg_surface_for_each_surface(view->xdg_surface, CMFYRenderer::draw_surface, &rdata);
    }
  });
}

CMFYOutput::CMFYOutput(wlr_output* wlroots_output, CMFYServer* server) :
  wlroots_output{wlroots_output}, server{server}
{}

CMFYOutput::~CMFYOutput() {}

bool CMFYOutput::has_modes() {
  return !wl_list_empty(&this->wlroots_output->modes);
}

std::optional<wlr_output_mode*> CMFYOutput::get_default_mode() {
  if (!this->has_modes()) {
    return {};
  }
  wlr_output_mode* default_output_mode = wl_container_of(
    this->wlroots_output->modes.prev,
    default_output_mode,
    link
  );
  return { default_output_mode };
}

void CMFYOutput::set_mode(wlr_output_mode* mode) {
  wlr_output_set_mode(wlroots_output, mode);
}

std::pair<int, int> CMFYOutput::get_effective_resolution() {
  int width, height;

  // The "effective" resolution can change if you rotate your outputs.
  wlr_output_effective_resolution(this->wlroots_output, &width, &height);
  return std::make_pair(width, height);
}

void CMFYOutput::bind_events() {
  // ? Binding "On destroy" event handler to output
  this->destroy.notify = CMFYOutput::on_output_destroy;
  wl_signal_add(&wlroots_output->events.destroy, &this->destroy);

  // ? Binding "On frame" event handler to output
  this->frame.notify = CMFYOutput::on_output_frame;
  wl_signal_add(&wlroots_output->events.frame, &this->frame);
}
