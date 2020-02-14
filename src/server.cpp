#include "server.hpp"

CMFYServer::CMFYServer(
  wl_display* display,
  wl_event_loop* event_loop,
  wlr_backend* backend,
  wlr_renderer* wlroots_renderer,
  wlr_output_layout* wlroots_output_layout
) :
  wayland_display{display},
  wayland_event_loop{event_loop},
  wlroots_backend{backend},
  renderer{CMFYRenderer(wlroots_renderer)},
  output_layout{CMFYOutputLayout(wlroots_output_layout)}
{
  // Configure shells
  /* Set up our list of views and the xdg-shell. The xdg-shell is a Wayland
   * protocol which is used for application windows. For more detail on
   * shells, refer to my article:
   * https://drewdevault.com/2018/07/29/Wayland-shells.html
   */
  wl_list_init(&this->views);
  this->main_xdg_shell = wlr_xdg_shell_create(this->wayland_display);
  this->new_xdg_surface_listener.notify = CMFYServer::on_new_xdg_surface;
  wl_signal_add(&this->main_xdg_shell->events.new_surface, &this->new_xdg_surface_listener);

  /* Add a Unix socket to the Wayland display. */
  this->socket_name = wl_display_add_socket_auto(this->wayland_display);
  std::cout << "Display socket : '" << this->socket_name << "'" << std::endl;

  // Configure outputs
  this->new_output_listener.notify = CMFYServer::on_new_output;
  wl_signal_add(&this->wlroots_backend->events.new_output, &this->new_output_listener);
  this->destroy_output_listener.notify = CMFYServer::on_destroy_output;

  /* Set the WAYLAND_DISPLAY environment variable to our socket. */
  setenv("WAYLAND_DISPLAY", this->socket_name, true);

  /* Creates a cursor, which is a wlroots utility for tracking the cursor
   * image shown on screen.
   */
  this->set_cursor(CMFYCursor());

  /*
   * Configures a seat, which is a single "seat" at which a user sits and
   * operates the computer. This conceptually includes up to one keyboard,
   * pointer, touch, and drawing tablet device. We also rig up a listener to
   * let us know when new input devices are available on the backend.
   */
  wl_list_init(&this->keyboards);
  this->new_input_listener.notify = CMFYServer::on_new_input;
  wl_signal_add(&this->wlroots_backend->events.new_input, &this->new_input_listener);
  this->seat = wlr_seat_create(this->wayland_display, "seat0");
  this->request_cursor_listener.notify = CMFYServer::on_seat_request_cursor;
  wl_signal_add(&this->seat->events.request_set_cursor, &this->request_cursor_listener);
}

CMFYServer::~CMFYServer() {
  if (this->wayland_display) {
    wlr_backend_destroy(this->wlroots_backend);
    //wl_display_destroy_clients(this->wayland_display);
    wl_display_destroy(this->wayland_display);
  }
}

/*

 */
void CMFYServer::on_new_input(wl_listener* listener, void* data) {
  // TODO: Implement
  std::logic_error("Function not yet implemented");
}

/*

 */
void CMFYServer::on_seat_request_cursor(wl_listener* listener, void* data) {
  // TODO: Implement
  std::logic_error("Function not yet implemented");
}

/*

 */
void CMFYServer::on_new_xdg_surface(struct wl_listener *listener, void *data) {
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

/*

 */
std::optional<CMFYServer*> CMFYServer::TryNew() {
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

  /* Creates an output layout, which a wlroots utility for working with an
	 * arrangement of screens in a physical layout. */
  auto wlroots_output_layout = wlr_output_layout_create();

  return {
    new CMFYServer(wayland_display, wayland_event_loop, wlroots_backend, wlroots_renderer, wlroots_output_layout)
  };
}

/*

 */
void CMFYServer::start() {
  if (!wlr_backend_start(this->wlroots_backend)) {
    std::cerr << "Failed to start the backend" << std::endl;
    return;
  }
  std::cout << "CMFYServer started" << std::endl;
  wl_display_run(this->wayland_display);
}

/*

 */
void CMFYServer::add_view(CMFYView* view) {
  wl_list_insert(&this->views, &view->link);
}

/*

 */
void CMFYServer::set_cursor(CMFYCursor cursor) {
  this->cursor = cursor;
  this->cursor.attach_output_layout(&this->output_layout);

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

/*

 */
void CMFYServer::on_new_output(wl_listener* listener, void* data) {
  CMFYServer* server = wl_container_of(listener, server, new_output_listener);
  CMFYOutput* output = new CMFYOutput(static_cast<wlr_output*>(data));
  auto default_mode_option = output->get_default_mode();
  if (default_mode_option.has_value()) {
    output->set_mode(default_mode_option.value());
  }
  server->output_layout.add_output(output);
  server->on_output_frame_listener.notify = CMFYServer::on_output_frame;
  output->bind_events(*server);
}

/*

 */
void CMFYServer::on_destroy_output(wl_listener* listener, void* data) {
  CMFYServer* server = wl_container_of(listener, server, new_output_listener);
  wlr_output* wlroots_output = static_cast<wlr_output*>(data);
  CMFYOutput output = CMFYOutput(wlroots_output);
  output.unbind_events(*server);
  server->output_layout.remove_output(output);
  free(wlroots_output);
}

/*
 * This function is called every time an output is ready to display a frame,
 * generally at the output's refresh rate (e.g. 60Hz).
 */
void CMFYServer::on_output_frame(wl_listener* listener, void* data) {
  CMFYServer* server = wl_container_of(listener, server, on_output_frame_listener);
  CMFYOutput output = CMFYOutput(static_cast<wlr_output*>(data));
  CMFYRenderer renderer = server->renderer;
  renderer.render_output(output, [&](RenderOutputTransaction transaction) {
    /* Each subsequent window we render is rendered on top of the last. Because
     * our view list is ordered front-to-back, we iterate over it backwards.
     */
    output.for_each_interacting_views_reverse(server, [&](CMFYView* view) {
      if (!view->is_mapped) {
        /* An unmapped view should not be rendered. */
        return;
      }
      RenderData rdata {
        &output,
        view,
        &renderer,
        &transaction.start_time,
      };
      view->for_each_surface(CMFYRenderer::draw_surface, &rdata);
    });
  });
}
