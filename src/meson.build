comfywm_sources = files(
  'main.cpp',
  'server.cpp',
)

pixman         = dependency('pixman-1')
wayland_server = dependency('wayland-server')

exe = executable(
  'comfywm',
  comfywm_sources,
  dependencies : [
    pixman,
    wayland_server,
    wlroots_dep
  ],
  install : true
)

