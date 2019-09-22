comfywm_sources = files(
  'main.cpp',
  'cmfy_server.cpp',
  'cmfy_output.cpp',
)

pixman          = dependency('pixman-1')
wayland_server  = dependency('wayland-server')

exe = executable(
  'comfywm',
  sources: comfywm_sources,
  dependencies : [
    pixman,
    server_protos,
    wayland_server,
    wlroots,
  ],
  override_options : ['cpp_std=c++17'],
  #install : true
)

