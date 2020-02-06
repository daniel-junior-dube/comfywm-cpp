#include <optional>
#include <iostream>
#include "server.hpp"

extern "C" {
#include <wlr/util/log.h>
}

int main() {
  std::cout << "Comfy starting..." << std::endl;

  // ! TODO: Validate arguments

  wlr_log_init(WLR_DEBUG, nullptr);

  auto cmfy_server_maybe = CMFYServer::TryCreate();
  if (!cmfy_server_maybe) {
    std::cerr << "Failed to create ComfyWM server" << std::endl;
    return 1;
  }

  auto cmfy_server = cmfy_server_maybe.value();

  // TODO: Run provided startup command if any using cmfy_server.socket_name (See tinywl.c)

  cmfy_server->start();

  std::cout << "Comfy terminating" << std::endl;
  return 0;
}
