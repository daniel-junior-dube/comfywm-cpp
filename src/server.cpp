#include "server.h"

Server::Server(wl_display* display, wl_event_loop* event_loop) :
  wayland_display{display}, wayland_event_loop{event_loop} {

}
Server::~Server() {}
