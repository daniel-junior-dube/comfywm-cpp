#include "server.hpp"

const char *XCURSOR_THEME_NAME = NULL;
const uint32_t XCURSOR_THEME_BASE_SIZE = 24;
const float XCURSOR_THEME_BASE_SCALE = 1.0f;

void on_new_input(wl_listener* listener, void* data) {
  // TODO: Implement
  std::logic_error("Function not yet implemented");
}

void on_seat_request_cursor(wl_listener* listener, void* data) {
  // TODO: Implement
  std::logic_error("Function not yet implemented");
}

static void on_new_xdg_surface(struct wl_listener *listener, void *data) {
  /* This event is raised when wlr_xdg_shell receives a new xdg surface from a
   * client, either a toplevel (application window) or popup. */
  CMFYServer* server = wl_container_of(listener, server, new_xdg_surface_listener);
  wlr_xdg_surface* xdg_surface = static_cast<wlr_xdg_surface*>(data);
  if (xdg_surface->role != WLR_XDG_SURFACE_ROLE_TOPLEVEL) {
    return;
  }

  CMFYView* view = new CMFYView(server, xdg_surface);
  server->add_view(view);
  view->bind_events();
}

void on_new_output(wl_listener* listener, void* data) {
  CMFYServer* server = wl_container_of(listener, server, new_output_listener);
  CMFYOutput* output = new CMFYOutput(static_cast<wlr_output*>(data), server);

  auto default_mode_option = output->get_default_mode();
  if (default_mode_option.has_value()) {
    output->set_mode(default_mode_option.value());
  }

  server->add_output(output);
  output->bind_events();
}

CMFYServer::CMFYServer(wl_display* display, wl_event_loop* event_loop, wlr_backend* backend, wlr_renderer* wlroots_renderer, wlr_output_layout* output_layout) :
  wayland_display{display},
  wayland_event_loop{event_loop},
  wlroots_backend{backend},
  renderer{CMFYRenderer(wlroots_renderer)},
  wlroots_output_layout{output_layout}
{
  // ? Outputs
  wl_list_init(&this->outputs);
  this->new_output_listener.notify = on_new_output;
  wl_signal_add(&this->wlroots_backend->events.new_output, &this->new_output_listener);

  // ? Views for the shells
  wl_list_init(&this->views);

  // ? Shells
  this->main_xdg_shell = wlr_xdg_shell_create(this->wayland_display);
  this->new_xdg_surface_listener.notify = on_new_xdg_surface;
  wl_signal_add(&this->main_xdg_shell->events.new_surface, &this->new_xdg_surface_listener);

  /* Add a Unix socket to the Wayland display. */
  this->socket_name = wl_display_add_socket_auto(this->wayland_display);
  std::cout << "Display socket : '" << this->socket_name << "'" << std::endl;

  /* Set the WAYLAND_DISPLAY environment variable to our socket. */
  setenv("WAYLAND_DISPLAY", this->socket_name, true);

  /*
   * Creates a cursor, which is a wlroots utility for tracking the cursor
   * image shown on screen.
   */
  this->set_cursor(CMFYCursor());

  /* Creates an xcursor manager, another wlroots utility which loads up
   * Xcursor themes to source cursor images from and makes sure that cursor
   * images are available at all scale factors on the screen (necessary for
   * HiDPI support). */
  this->wlroots_cursor_mgr = wlr_xcursor_manager_create(XCURSOR_THEME_NAME, XCURSOR_THEME_BASE_SIZE);
  wlr_xcursor_manager_load(this->wlroots_cursor_mgr, XCURSOR_THEME_BASE_SCALE);


  /*
   * Configures a seat, which is a single "seat" at which a user sits and
   * operates the computer. This conceptually includes up to one keyboard,
   * pointer, touch, and drawing tablet device. We also rig up a listener to
   * let us know when new input devices are available on the backend.
   */
  wl_list_init(&this->keyboards);
  this->new_input_listener.notify = on_new_input;
  wl_signal_add(&this->wlroots_backend->events.new_input, &this->new_input_listener);
  this->seat = wlr_seat_create(this->wayland_display, "seat0");
  this->request_cursor_listener.notify = on_seat_request_cursor;
  wl_signal_add(&this->seat->events.request_set_cursor, &this->request_cursor_listener);
}

CMFYServer::~CMFYServer() {
  // TOFIX: This causes and segfault..
  //if (this->wayland_display) {
  //  wl_display_destroy_clients(this->wayland_display);
  //  wl_display_destroy(this->wayland_display);
  //}
}

std::optional<CMFYServer*> CMFYServer::TryCreate() {
  auto wayland_display = wl_display_create();
  if (!wayland_display) return {};

  auto wayland_event_loop = wl_display_get_event_loop(wayland_display);
  if (!wayland_event_loop) return {};

  auto wlroots_backend = wlr_backend_autocreate(wayland_display, nullptr);
  if (!wlroots_backend) return {};

  wlr_renderer* wlroots_renderer = wlr_backend_get_renderer(wlroots_backend);
  if (!wlroots_renderer) return {};

  wlr_renderer_init_wl_display(wlroots_renderer, wayland_display);

  /* This creates some hands-off wlroots interfaces. The compositor is
   * necessary for clients to allocate surfaces and the data device manager
   * handles the clipboard. Each of these wlroots interfaces has room for you
   * to dig your fingers in and play with their behavior if you want. */
  wlr_compositor_create(wayland_display, wlroots_renderer);
  wlr_data_device_manager_create(wayland_display);

  auto wlroots_output_layout = wlr_output_layout_create();

  return {
    new CMFYServer(wayland_display, wayland_event_loop, wlroots_backend, wlroots_renderer, wlroots_output_layout)
  };
}

void CMFYServer::start() {
  if (!wlr_backend_start(this->wlroots_backend)) {
    std::cerr << "Failed to start the backend" << std::endl;
    return;
  }
  std::cout << "CMFYServer started" << std::endl;
  wl_display_run(this->wayland_display);
}

void CMFYServer::add_view(CMFYView* view) {
  wl_list_insert(&this->views, &view->link);
}

void CMFYServer::add_output(CMFYOutput* output) {
  wl_list_insert(&this->outputs, &output->link);
}

void CMFYServer::set_cursor(CMFYCursor cursor) {
  this->cursor = cursor;
  wlr_cursor_attach_output_layout(cursor.wlroots_cursor, this->wlroots_output_layout);

  /*
   * wlr_cursor *only* displays an image on screen. It does not move around
   * when the pointer moves. However, we can attach input devices to it, and
   * it will generate aggregate events for all of them. In these events, we
   * can choose how we want to process them, forwarding them to clients and
   * moving the cursor around. More detail on this process is described in my
   * input handling blog post:
   *
   * https://drewdevault.com/2018/07/17/Input-handling-in-wlroots.html
   *
   * And more comments are sprinkled throughout the notify functions above.
   */
  //this->cursor_motion.notify = server_cursor_motion;
  //wl_signal_add(&this->cursor->events.motion, &this->cursor_motion);
  //this->cursor_motion_absolute.notify = server_cursor_motion_absolute;
  //wl_signal_add(&this->cursor->events.motion_absolute, &this->cursor_motion_absolute);
  //this->cursor_button.notify = server_cursor_button;
  //wl_signal_add(&this->cursor->events.button, &this->cursor_button);
  //this->cursor_axis.notify = server_cursor_axis;
  //wl_signal_add(&this->cursor->events.axis, &this->cursor_axis);
  //this->cursor_frame.notify = server_cursor_frame;
  //wl_signal_add(&this->cursor->events.frame, &this->cursor_frame);
}
