comfywm_sources = files(
  'main.cpp',
  'server.cpp',
)

pixman          = dependency('pixman-1')
wayland_server  = dependency('wayland-server')
wlroots         = dependency('wlroots')

exe = executable(
  'comfywm',
  sources: comfywm_sources,
  dependencies : [
    pixman,
    wayland_server,
    wlroots,
  ],
  #install : true
)

