#include <iostream>
#include <cassert>
#include "server.hpp"

int main() {
  // ?
  auto wl_display = wl_display_create();
  assert(wl_display);

  // ?
  auto wl_event_loop = wl_display_get_event_loop(wl_display);
  assert(wl_event_loop);

  auto wlr_backend = wlr_backend_autocreate(wl_display, nullptr);

  // ?
  Server server(wl_display, wl_event_loop, wlr_backend);

  std::cout << "Comfy Terminating" << std::endl;
  return 0;
}
