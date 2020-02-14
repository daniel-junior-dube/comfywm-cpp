#include <optional>
#include <iostream>
#include "server.hpp"

extern "C" {
  #include <wlr/util/log.h>
}

int main() {
  std::cout << "Comfy starting..." << std::endl;

  // TODO: Validate arguments

  // Initialise wlroots logger
  wlr_log_init(WLR_DEBUG, nullptr);

  // Try creating the server
  auto cmfy_server_maybe = CMFYServer::TryNew();
  if (!cmfy_server_maybe) {
    std::cerr << "Failed to create ComfyWM server" << std::endl;
    return 1;
  }

  // Start the server
  CMFYServer* cmfy_server = cmfy_server_maybe.value();
  cmfy_server->start();

  std::cout << "Comfy terminating" << std::endl;
  delete cmfy_server;
  return 0;
}
