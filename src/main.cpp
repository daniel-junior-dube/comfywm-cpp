#include <iostream>
#include <cassert>
#include "server.h"

int main() {
  // ?
  auto wl_display = wl_display_create();
  assert(wl_display);

  // ?
  auto wl_event_loop = wl_display_get_event_loop(wl_display);
  assert(wl_event_loop);

  // ?
  Server server(wl_display, wl_event_loop);

  std::cout << "Comfy Terminating" << std::endl;
  return 0;
}
