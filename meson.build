project('opencv-glib', 'c', 'cpp',
        version: '1.0.0',
        license: 'BSD-3-Clause')

api_version = '1.0'
library_version = '1.0.0'

c_compiler = meson.get_compiler('c')
cpp_compiler = meson.get_compiler('cpp')

prefix = get_option('prefix')
include_dir = join_paths(prefix, get_option('includedir'))
data_dir = join_paths(prefix, get_option('datadir'))

gnome = import('gnome')
pkgconfig = import('pkgconfig')

root_inc = include_directories('.')

subdir('opencv-glib')

if get_option('gtk_doc')
  subdir('doc/reference')
endif

run_test = find_program('test/run-test.sh')
test('unit test', run_test)
