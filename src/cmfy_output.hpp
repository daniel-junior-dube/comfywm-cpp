
extern "C" {
#include <wlr/types/wlr_output.h>
}

#include <wayland-server.h>

class CMFYServer;

class CMFYOutput {
public:
  wlr_output* wlroots_output;
  CMFYServer* server;
  wl_listener frame;
  wl_listener destroy;
  wl_list link;
  CMFYOutput(wlr_output* wlroots_output, CMFYServer* server);
  ~CMFYOutput();
};

