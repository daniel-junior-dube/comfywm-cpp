#include "cursor.hpp"

CMFYCursor::CMFYCursor() {
  this->wlroots_cursor = wlr_cursor_create();
}

CMFYCursor::~CMFYCursor() {}
