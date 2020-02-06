project(
  'comfywm',
  'cpp',
  'c',
  version : '0.1',
  license: 'MIT',
  default_options : [
    'warning_level=3',
    'cpp_std=c++17',
  ],
)

add_global_arguments(
  '-DWLR_USE_UNSTABLE',
  language : ['cpp', 'c'],
)

cc = meson.get_compiler('cpp')

wayland_server = dependency('wayland-server')
wayland_client = dependency('wayland-client')
wayland_protos = dependency('wayland-protocols', version: '>=1.14')

wlroots_version = '>=0.6'
wlroots_proj = subproject(
  'wlroots',
  default_options: [
    'rootston=false',
    'examples=false'
  ],
  required: false,
  version: wlroots_version,
)

if wlroots_proj.found()
  wlroots = wlroots_proj.get_variable('wlroots')
	wlroots_conf = wlroots_proj.get_variable('conf_data')
	wlroots_has_xwayland = wlroots_conf.get('WLR_HAS_XWAYLAND') == 1
else
	wlroots = dependency('wlroots', version: wlroots_version)
	wlroots_has_xwayland = cc.get_define('WLR_HAS_XWAYLAND', prefix: '#include <wlr/config.h>', dependencies: wlroots) == '1'
endif

inc = include_directories('include')

subdir('include')
subdir('protocols')
subdir('src')

