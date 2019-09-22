#include <optional>
#include <iostream>
#include "cmfy_server.hpp"

extern "C" {
#include <wlr/util/log.h>
}

int main() {
  std::cout << "Comfy starting..." << std::endl;

  // ! TODO: Validate arguments

  wlr_log_init(WLR_DEBUG, nullptr);

  auto cmfy_server_maybe = CMFYServer::TryCreate();
  if (!cmfy_server_maybe) {
    std::cout << "Failed to create ComfyWM server" << std::endl;
    return 1;
  }

  auto cmfy_server = cmfy_server_maybe.value();
  cmfy_server->start();

  std::cout << "Comfy terminating" << std::endl;
  return 0;
}
