#include "output_layout.hpp"
#include "output.hpp"
#include "server.hpp"

CMFYOutputLayout::CMFYOutputLayout(wlr_output_layout* wlroots_output_layout) :
  wlroots_output_layout{wlroots_output_layout}
{
  // Configure outputs
  // Sets a listener to be notified when new outputs are available on the backend.
  wl_list_init(&this->outputs);
}

CMFYOutputLayout::~CMFYOutputLayout() {}

/*

 */
void CMFYOutputLayout::add_output(CMFYOutput* output) {
  // TODO: FIX THIS : `output->link` is specific to the class arount the wlr_output. CAN'T COUNT ON IT....
  wl_list_insert(&this->outputs, &output->link);
}

void CMFYOutputLayout::remove_output(CMFYOutput& output) {
  wl_list_remove(&output.link);
}

/*

 */
std::pair<double, double> CMFYOutputLayout::get_output_origin(CMFYOutput* output) {
  double origin_x = 0, origin_y = 0;
  wlr_output_layout_output_coords(this->wlroots_output_layout, output->wlroots_output, &origin_x, &origin_y);
  return std::make_pair(origin_x, origin_y);
}
