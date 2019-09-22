#include "cmfy_view.hpp"

void xdg_surface_map_handler(struct wl_listener *listener, void *data) {
  /* Called when the surface is mapped, or ready to display on-screen. */
  CMFYView* view = wl_container_of(listener, view, map);
  view->is_mapped = true;

  // TODO: Implement
  std::logic_error("Function not yet implemented");
  //focus_view(view, view->xdg_surface->surface);
}

void xdg_surface_unmap_handler(struct wl_listener *listener, void *data) {
  /* Called when the surface is unmapped, and should no longer be shown. */
  CMFYView* view = wl_container_of(listener, view, unmap);
  view->is_mapped = false;
}

void xdg_surface_destroy_handler(struct wl_listener *listener, void *data) {
  CMFYView* view = wl_container_of(listener, view, destroy);
  wl_list_remove(&view->link);
  delete view;
}

void xdg_toplevel_request_move_handler(struct wl_listener *listener, void *data) {
  /* This event is raised when a client would like to begin an interactive
   * move, typically because the user clicked on their client-side
   * decorations. Note that a more sophisticated compositor should check the
   * provied serial against a list of button press serials sent to this
   * client, to prevent the client from requesting this whenever they want. */
  CMFYView* view = wl_container_of(listener, view, request_move);

  // TODO: Implement
  std::logic_error("Function not yet implemented");
  //begin_interactive(view, TINYWL_CURSOR_MOVE, 0);
}

void xdg_toplevel_request_resize_handler(struct wl_listener *listener, void *data) {
  /* This event is raised when a client would like to begin an interactive
   * resize, typically because the user clicked on their client-side
   * decorations. Note that a more sophisticated compositor should check the
   * provied serial against a list of button press serials sent to this
   * client, to prevent the client from requesting this whenever they want. */
  wlr_xdg_toplevel_resize_event* resize_event = static_cast<wlr_xdg_toplevel_resize_event*>(data);
  CMFYView* view = wl_container_of(listener, view, request_resize);

  // TODO: Implement
  std::logic_error("Function not yet implemented");
  //begin_interactive(view, TINYWL_CURSOR_RESIZE, resize_event->edges);
}


CMFYView::CMFYView(CMFYServer* server, wlr_xdg_surface* xdg_surface) :
  server{server}, xdg_surface{xdg_surface}
{
  // XdgSurface events
  this->map.notify = xdg_surface_map_handler;
  wl_signal_add(&xdg_surface->events.map, &this->map);

  this->unmap.notify = xdg_surface_unmap_handler;
  wl_signal_add(&xdg_surface->events.unmap, &this->unmap);

  this->destroy.notify = xdg_surface_destroy_handler;
  wl_signal_add(&xdg_surface->events.destroy, &this->destroy);

  // TopLevel events
  wlr_xdg_toplevel* toplevel = xdg_surface->toplevel;
  this->request_move.notify = xdg_toplevel_request_move_handler;
  wl_signal_add(&toplevel->events.request_move, &this->request_move);

  this->request_resize.notify = xdg_toplevel_request_resize_handler;
  wl_signal_add(&toplevel->events.request_resize, &this->request_resize);
}

CMFYView::~CMFYView() {}
