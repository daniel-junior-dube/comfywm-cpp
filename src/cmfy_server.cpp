#include "cmfy_server.hpp"

void new_output_handler(wl_listener* listener, void* data) {
  CMFYServer* server = wl_container_of(listener, server, new_output_listener);
  wlr_output* wlroots_output = static_cast<wlr_output*>(data);
  if (!wl_list_empty(&wlroots_output->modes)) {
    wlr_output_mode* mode = wl_container_of(wlroots_output->modes.prev, mode, link);
    wlr_output_set_mode(wlroots_output, mode);
  }
  CMFYOutput* output = new CMFYOutput(wlroots_output, server);
  wl_list_insert(&server->outputs, &output->link);
  std::cout << "New output added" << std::endl;
}

CMFYServer::CMFYServer(wl_display* display, wl_event_loop* event_loop, wlr_backend* backend) :
  wayland_display{display}, wayland_event_loop{event_loop}, wlroots_backend{backend}
{
  wl_list_init(&this->outputs);

  this->new_output_listener.notify = new_output_handler;
  wl_signal_add(&this->wlroots_backend->events.new_output, &this->new_output_listener);

  std::cout << "CMFYServer created" << std::endl;
}

CMFYServer::~CMFYServer() {
  if (this->wayland_display) {
    wl_display_destroy(this->wayland_display);
  }
}

std::optional<CMFYServer> CMFYServer::TryCreate() {
  // ?
  auto wl_display = wl_display_create();
  if (!wl_display) return {};
  
  // ?
  auto wl_event_loop = wl_display_get_event_loop(wl_display);
  if (!wl_event_loop) return {};

  auto wlr_backend = wlr_backend_autocreate(wl_display, nullptr);
  if (!wlr_backend) return {};

  // ?
  return {
    CMFYServer(wl_display, wl_event_loop, wlr_backend)
  };
}

void CMFYServer::start() {
  if (!wlr_backend_start(this->wlroots_backend)) {
    std::cout << "Failed to start the backend" << std::endl;
    return;
  }
  wl_display_run(this->wayland_display);
}

void CMFYServer::on_new_output(wl_listener* listener, void* data) {

}

