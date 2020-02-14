#pragma once

extern "C" {
#include <wlr/types/wlr_cursor.h>
#include <wlr/types/wlr_output_layout.h>
#include <wlr/types/wlr_xcursor_manager.h>
#define static
// ...
#undef static
}

#include "output_layout.hpp"

class CMFYCursor {
public:
  wlr_cursor* wlroots_cursor;
  wlr_xcursor_manager* wlroots_cursor_mgr;
  CMFYCursor();
  ~CMFYCursor();
  void attach_output_layout(CMFYOutputLayout* output_layout);
};
