#include "cmfy_server.hpp"

void output_frame_handler(wl_listener* listener, void* data) {
  CMFYOutput* output = wl_container_of(listener, output, frame);
  wlr_output* wlroots_output = static_cast<wlr_output*>(data);
  wlr_renderer* renderer = wlr_backend_get_renderer(wlroots_output->backend);

  wlr_output_attach_render(wlroots_output, nullptr);
  wlr_renderer_begin(renderer, 800, 600);

  float color[4] = {1.0, 1.0, 0.0, 1.0};
  wlr_renderer_clear(renderer, color);

  //wlr_output_commit(wlroots_output);
  wlr_renderer_end(renderer);
}

void output_destroy_handler(wl_listener *listener, void *data) {
  CMFYOutput* output = wl_container_of(listener, output, destroy);
  wl_list_remove(&output->link);
  wl_list_remove(&output->destroy.link);
  wl_list_remove(&output->frame.link);
  free(output);
}

void new_output_handler(wl_listener* listener, void* data) {
  std::cout << "New output added" << std::endl;
  CMFYServer* server = wl_container_of(listener, server, new_output_listener);
  wlr_output* wlroots_output = static_cast<wlr_output*>(data);
  if (!wl_list_empty(&wlroots_output->modes)) {
    wlr_output_mode* mode = wl_container_of(wlroots_output->modes.prev, mode, link);
    wlr_output_set_mode(wlroots_output, mode);
  }
  CMFYOutput* output = new CMFYOutput(wlroots_output, server);
  wl_list_insert(&server->outputs, &output->link);

  // ? Binding "On destroy" event handler to output
  output->destroy.notify = output_destroy_handler;
  wl_signal_add(&wlroots_output->events.destroy, &output->destroy);

  // ? Binding "On frame" event handler to output
  output->frame.notify = output_frame_handler;
  wl_signal_add(&wlroots_output->events.frame, &output->frame);
}

CMFYServer::CMFYServer(wl_display* display, wl_event_loop* event_loop, wlr_backend* backend, wlr_output_layout* output_layout) :
  wayland_display{display}, wayland_event_loop{event_loop}, wlroots_backend{backend}, wlroots_output_layout{output_layout}
{
  // ? Outputs
  wl_list_init(&this->outputs);
  this->new_output_listener.notify = new_output_handler;
  wl_signal_add(&this->wlroots_backend->events.new_output, &this->new_output_listener);

  // ? Views for the shells
  wl_list_init(&this->views);

  const char *socket = wl_display_add_socket_auto(this->wayland_display);
  std::cout << "Display socket : '" << socket << "'" << std::endl;
}

CMFYServer::~CMFYServer() {
  //if (this->wayland_display) {
  //  wl_display_destroy(this->wayland_display);
  //}
}

std::optional<CMFYServer*> CMFYServer::TryCreate() {
  // ?
  auto wayland_display = wl_display_create();
  if (!wayland_display) return {};

  // ?
  auto wayland_event_loop = wl_display_get_event_loop(wayland_display);
  if (!wayland_event_loop) return {};

  auto wlroots_backend = wlr_backend_autocreate(wayland_display, nullptr);
  if (!wlroots_backend) return {};

  // ! Is this needed??
  wlr_renderer* renderer = wlr_backend_get_renderer(wlroots_backend);
  wlr_renderer_init_wl_display(renderer, wayland_display);

  wlr_compositor_create(wayland_display, renderer);
  wlr_data_device_manager_create(wayland_display);

  auto wlroots_output_layout = wlr_output_layout_create();

  // ?
  return {
    new CMFYServer(wayland_display, wayland_event_loop, wlroots_backend, wlroots_output_layout)
  };
}

void CMFYServer::start() {
  if (!wlr_backend_start(this->wlroots_backend)) {
    std::cout << "Failed to start the backend" << std::endl;
    return;
  }
  std::cout << "CMFYServer started" << std::endl;
  wl_display_run(this->wayland_display);
}

void CMFYServer::on_new_output(wl_listener* listener, void* data) {

}

