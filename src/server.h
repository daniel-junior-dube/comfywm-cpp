#include <wayland-server.h>
#include <wlr/backend.h>

class Server {

  // ? Connection to a wayland display
  wl_display* wayland_display;

  // ? Display event loop context
	wl_event_loop* wayland_event_loop;
  wlr_backend* backend;
public:
  Server(wl_display* display, wl_event_loop* event_loop);
  ~Server();
private:
};
