project('opencv-glib', 'c', 'cpp',
        version: '1.0.2',
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

tag_message = '@0@ @1@ has been released!!!'.format(meson.project_name(),
						    meson.project_version())
tag = custom_target('tag',
                    command: [
                      'git',
                      'tag',
                      '-a',
                      '-m', tag_message,
                      meson.project_version(),
                    ],
                    output: ['tag'])

tag_push = custom_target('tag-push',
                         command: ['git', 'push', '--tags'],
                         depends: [tag],
                         output: ['tag-push'])

custom_target('release',
              command: ['echo', tag_message],
              depends: [tag_push],
              output: ['release'])
