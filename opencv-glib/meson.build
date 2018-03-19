sources = files(
  'matrix.cpp',
)

c_headers = files(
  'matrix.h',
  'opencv-glib.h',
)

cpp_headers = files(
  'matrix.hpp',
  'opencv-glib.hpp',
)

headers = c_headers + cpp_headers
install_headers(headers, subdir: meson.project_name())


dependencies = [
  dependency('opencv'),
  dependency('gobject-2.0'),
]
libopencv_glib = library('opencv-glib',
                         sources: sources,
                         install: true,
                         dependencies: dependencies,
                         include_directories: [
                           root_inc,
                         ],
                         soversion: so_version,
                         version: library_version)
libopencv_glib_dependency = declare_dependency(link_with: libopencv_glib,
                                               include_directories: [
                                                 root_inc,
                                               ],
                                               dependencies: dependencies)

pkgconfig.generate(filebase: meson.project_name(),
                   name: 'OpenCV GLib',
                   description: 'C API for OpenCV based on GLib',
                   version: meson.project_version(),
                   requires: ['gobject-2.0', 'opencv'],
                   libraries: [libopencv_glib],
                   subdirs: ['opencv-glib'])

opencv_glib_gir = gnome.generate_gir(libopencv_glib,
                                     sources: sources + c_headers,
                                     namespace: 'CV',
                                     nsversion: api_version,
                                     identifier_prefix: 'GCV',
                                     symbol_prefix: 'gcv',
                                     export_packages: 'opencv-glib',
                                     includes: [
                                       'GObject-2.0',
                                     ],
                                     install: true,
                                     extra_args: [
                                       '--warn-all',
                                     ])
opencv_glib_gir_dependency = declare_dependency(sources: opencv_glib_gir)
