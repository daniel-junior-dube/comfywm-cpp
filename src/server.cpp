#include "server.hpp"

Server::Server(wl_display* display, wl_event_loop* event_loop, wlr_backend* backend) :
  wayland_display{display}, wayland_event_loop{event_loop}, wlroots_backend{backend} {
}
Server::~Server() {}

