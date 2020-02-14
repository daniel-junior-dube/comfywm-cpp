#include "output.hpp"
#include "view.hpp"
#include "server.hpp"

CMFYOutput::CMFYOutput(wlr_output* wlroots_output) :
  wlroots_output{wlroots_output}
{}

CMFYOutput::~CMFYOutput() {}

/*

 */
bool CMFYOutput::has_modes() {
  return !wl_list_empty(&this->wlroots_output->modes);
}

/*

 */
std::optional<wlr_output_mode*> CMFYOutput::get_default_mode() {
  if (!this->has_modes()) return {};
  wlr_output_mode* default_output_mode = wl_container_of(
    this->wlroots_output->modes.prev,
    default_output_mode,
    link
  );
  return { default_output_mode };
}

/*

 */
void CMFYOutput::set_mode(wlr_output_mode* mode) {
  wlr_output_set_mode(wlroots_output, mode);
}

/*

 */
std::pair<int, int> CMFYOutput::get_effective_resolution() {
  int width, height;

  // The "effective" resolution can change if you rotate your outputs.
  wlr_output_effective_resolution(this->wlroots_output, &width, &height);
  return std::make_pair(width, height);
}

/*

 */
// std::pair<double, double> CMFYOutput::get_output_layout_coords() {
//   return this->server->output_layout.get_output_origin(this->wlroots_output);
//   //double origin_x = 0, origin_y = 0;
//   //wlr_output_layout_output_coords(this->server->wlroots_output_layout, this->wlroots_output, &origin_x, &origin_y);
//   //return std::make_pair(origin_x, origin_y);
// }

/*

 */
void CMFYOutput::for_each_interacting_views_reverse(CMFYServer* server, std::function<void(CMFYView* view)> callback) {
  CMFYView* view;
  // TODO: Get output bounds
  wl_list_for_each_reverse(view, &server->views, link) {
    // TODO: Get view bounds
    // TODO: Check intersection of view and output 
    callback(view);
  }
}

/*

 */
void CMFYOutput::bind_events(CMFYServer& server) {
  wl_signal_add(&this->wlroots_output->events.destroy, &server.destroy_output_listener);
  wl_signal_add(&this->wlroots_output->events.frame, &server.on_output_frame_listener);
}

void CMFYOutput::unbind_events(CMFYServer& server) {
  wl_list_remove(&this->link);
  wl_list_remove(&server.destroy_output_listener.link);
  wl_list_remove(&server.on_output_frame_listener.link);
}
