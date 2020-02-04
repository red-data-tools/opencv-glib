sources = files(
  'camera.cpp',
  'camera-error.cpp',
  'cascade-classifier.cpp',
  'cascade-classifier-error.cpp',
  'color.cpp',
  'image.cpp',
  'image-error.cpp',
  'matrix.cpp',
  'point.cpp',
  'rectangle.cpp',
  'size.cpp',
  'video-capture.cpp',
)

c_headers = files(
  'camera.h',
  'camera-error.h',
  'cascade-classifier.h',
  'cascade-classifier-error.h',
  'color.h',
  'image.h',
  'image-error.h',
  'matrix.h',
  'opencv-glib.h',
  'point.h',
  'rectangle.h',
  'size.h',
  'video-capture.h',
)

cpp_headers = files(
  'camera.hpp',
  'cascade-classifier.hpp',
  'color.hpp',
  'image.hpp',
  'matrix.hpp',
  'opencv-glib.hpp',
  'point.hpp',
  'rectangle.hpp',
  'size.hpp',
  'video-capture.hpp',
)

enums = gnome.mkenums('enums',
                      sources: c_headers,
                      identifier_prefix: 'GCV',
                      symbol_prefix: 'gcv',
                      c_template: 'enums.c.template',
                      h_template: 'enums.h.template',
                      install_dir: join_paths(include_dir, meson.project_name()),
                      install_header: true)
enums_source = enums[0]
enums_header = enums[1]

headers = c_headers + cpp_headers
install_headers(headers, subdir: meson.project_name())

opencv = dependency('opencv')
opencv_data_directory = join_paths(opencv.get_pkgconfig_variable('prefix'),
				   'share',
				   'opencv')
config_h_data = configuration_data()
config_h_data.set_quoted('OPENCV_DATA_DIRECTORY', opencv_data_directory)
config_h = configure_file(input: 'config.h.meson',
			  output: 'config.h',
			  configuration: config_h_data)

dependencies = [
  opencv,
  dependency('gobject-2.0'),
]
libopencv_glib = library('opencv-glib',
                         sources: sources + enums + [config_h],
                         install: true,
                         dependencies: dependencies,
                         include_directories: [
                           root_inc,
                         ],
                         version: library_version)
libopencv_glib_dependency = declare_dependency(link_with: libopencv_glib,
                                               include_directories: [
                                                 root_inc,
                                               ],
                                               dependencies: dependencies,
                                               sources: enums_header)

pkgconfig.generate(filebase: meson.project_name(),
                   name: 'OpenCV GLib',
                   description: 'C API for OpenCV based on GLib',
                   version: meson.project_version(),
                   requires: ['gobject-2.0', 'opencv'],
                   libraries: [libopencv_glib])

opencv_glib_gir = gnome.generate_gir(libopencv_glib,
                                     sources: sources + c_headers + enums,
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
