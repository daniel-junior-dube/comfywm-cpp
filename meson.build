project(
  'comfywm',
  'cpp',
  version : '0.1',
  license: 'MIT',
  default_options : ['warning_level=3', 'cpp_std=c++14'],
)

add_global_arguments('-DWLR_USE_UNSTABLE', language : 'cpp')

cc = meson.get_compiler('cpp')

wlroots_proj = subproject('wlroots')
wlroots_dep = wlroots_proj.get_variable('wlr_deps')

inc = include_directories('include')

subdir('include')
subdir('src')
