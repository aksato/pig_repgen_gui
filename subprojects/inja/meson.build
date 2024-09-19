project(
  'inja',
  'cpp',
  version: '3.4.0',
  default_options: ['cpp_std=c++17', 'warning_level=3'],
  meson_version: '>=0.56'
)


inja_dep = declare_dependency(
  include_directories: include_directories('include', 'third_party/include')
)


install_headers(
  'include/inja/config.hpp',
  'include/inja/environment.hpp',
  'include/inja/exceptions.hpp',
  'include/inja/function_storage.hpp',
  'include/inja/inja.hpp',
  'include/inja/lexer.hpp',
  'include/inja/node.hpp',
  'include/inja/parser.hpp',
  'include/inja/renderer.hpp',
  'include/inja/statistics.hpp',
  'include/inja/template.hpp',
  'include/inja/token.hpp',
  'include/inja/utils.hpp',
  subdir: 'inja'
)