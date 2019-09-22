#include "cmfy_server.hpp"

/*
 * This function is called every time an output is ready to display a frame,
 * generally at the output's refresh rate (e.g. 60Hz).
 */
void output_frame_handler(wl_listener* listener, void* data) {
  CMFYOutput* output = wl_container_of(listener, output, frame);
  wlr_output* wlroots_output = static_cast<wlr_output*>(data);
  wlr_renderer* renderer = output->server->wlroots_renderer;

  // Makes the OpenGL context current.
  if (!wlr_output_attach_render(wlroots_output, nullptr)) {
    return;
  }

  // The "effective" resolution can change if you rotate your outputs.
	int width, height;
	wlr_output_effective_resolution(wlroots_output, &width, &height);

  // Begin rendering
  wlr_renderer_begin(renderer, width, height);

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

static void new_xdg_surface_handler(struct wl_listener *listener, void *data) {
  /* This event is raised when wlr_xdg_shell receives a new xdg surface from a
   * client, either a toplevel (application window) or popup. */
  CMFYServer* server = wl_container_of(listener, server, new_xdg_surface_listener);
  wlr_xdg_surface* xdg_surface = static_cast<wlr_xdg_surface*>(data);
  if (xdg_surface->role != WLR_XDG_SURFACE_ROLE_TOPLEVEL) {
    return;
  }


  // Allocate a tinywl_view for this surface
  CMFYView* view = new CMFYView(server, xdg_surface);
  server->add_view(view);

  std::cout << "new_xdg_surface" << std::endl;
}


void new_output_handler(wl_listener* listener, void* data) {
  CMFYServer* server = wl_container_of(listener, server, new_output_listener);
  wlr_output* wlroots_output = static_cast<wlr_output*>(data);
  if (!wl_list_empty(&wlroots_output->modes)) {
    wlr_output_mode* mode = wl_container_of(wlroots_output->modes.prev, mode, link);
    wlr_output_set_mode(wlroots_output, mode);
  }

  CMFYOutput* output = new CMFYOutput(wlroots_output, server);

  // ? Add the output link to the list of outputs
  wl_list_insert(&server->outputs, &output->link);

  // ? Binding "On destroy" event handler to output
  output->destroy.notify = output_destroy_handler;
  wl_signal_add(&wlroots_output->events.destroy, &output->destroy);

  // ? Binding "On frame" event handler to output
  output->frame.notify = output_frame_handler;
  wl_signal_add(&wlroots_output->events.frame, &output->frame);

  std::cout << "New output added" << std::endl;
}

CMFYServer::CMFYServer(wl_display* display, wl_event_loop* event_loop, wlr_backend* backend, wlr_renderer* wlroots_renderer, wlr_output_layout* output_layout) :
  wayland_display{display},
  wayland_event_loop{event_loop},
  wlroots_backend{backend},
  wlroots_renderer{wlroots_renderer},
  wlroots_output_layout{output_layout}
{
  // ? Outputs
  wl_list_init(&this->outputs);
  this->new_output_listener.notify = new_output_handler;
  wl_signal_add(&this->wlroots_backend->events.new_output, &this->new_output_listener);

  // ? Views for the shells
  wl_list_init(&this->views);

  this->main_xdg_shell = wlr_xdg_shell_create(this->wayland_display);
  this->new_xdg_surface_listener.notify = new_xdg_surface_handler;
  wl_signal_add(&this->main_xdg_shell->events.new_surface, &this->new_xdg_surface_listener);

  // ?
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

  wlr_renderer* wlroots_renderer = wlr_backend_get_renderer(wlroots_backend);
  if (!wlroots_renderer) return {};

  auto wlroots_output_layout = wlr_output_layout_create();

  // ?
  return {
    new CMFYServer(wayland_display, wayland_event_loop, wlroots_backend, wlroots_renderer, wlroots_output_layout)
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

void CMFYServer::add_view(CMFYView* view) {
  wl_list_insert(&this->views, &view->link);
}
