#include "cursor.hpp"

const char *XCURSOR_THEME_NAME = NULL;
const uint32_t XCURSOR_THEME_BASE_SIZE = 24;
const float XCURSOR_THEME_BASE_SCALE = 1.0f;

CMFYCursor::CMFYCursor() {
  this->wlroots_cursor = wlr_cursor_create();

  /* Creates an xcursor manager, another wlroots utility which loads up
   * Xcursor themes to source cursor images from and makes sure that cursor
   * images are available at all scale factors on the screen (necessary for
   * HiDPI support). */
  this->wlroots_cursor_mgr = wlr_xcursor_manager_create(XCURSOR_THEME_NAME, XCURSOR_THEME_BASE_SIZE);
  wlr_xcursor_manager_load(this->wlroots_cursor_mgr, XCURSOR_THEME_BASE_SCALE);
}

CMFYCursor::~CMFYCursor() {}


void CMFYCursor::attach_output_layout(CMFYOutputLayout* output_layout) {
  wlr_cursor_attach_output_layout(this->wlroots_cursor, output_layout->wlroots_output_layout);
}
