#pragma once

extern "C" {
#include <wlr/types/wlr_cursor.h>
#define static
// ...
#undef static
}

// ...

class CMFYCursor {
public:
  wlr_cursor* wlroots_cursor;
  CMFYCursor();
  ~CMFYCursor();
private:
};
