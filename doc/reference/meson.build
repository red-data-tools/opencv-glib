entities_conf = configuration_data()
entities_conf.set('PACKAGE', meson.project_name())
entities_conf.set('PACKAGE_BUGREPORT',
                  'https://github.com/red-data-tools/opencv-glib/issues')
entities_conf.set('PACKAGE_NAME', meson.project_name())
entities_conf.set('PACKAGE_STRING',
                  ' '.join([meson.project_name(), meson.project_version()]))
entities_conf.set('PACKAGE_URL',
		  'https://github.com/red-data-tools/opencv-glib/')
entities_conf.set('PACKAGE_VERSION', meson.project_version())
configure_file(input: 'entities.xml.in',
               output: 'entities.xml',
               configuration: entities_conf)

content_files = [
]

html_images = [
]

glib_prefix = dependency('glib-2.0').get_pkgconfig_variable('prefix')
glib_doc_path = join_paths(glib_prefix, 'share', 'gtk-doc', 'html')
doc_path = join_paths(data_dir, meson.project_name(), 'gtk-doc', 'html')

source_directories = [
  join_paths(meson.source_root(), 'opencv-glib'),
  join_paths(meson.build_root(), 'opencv-glib'),
]
dependencies = [
  libopencv_glib_dependency,
]
gnome.gtkdoc(meson.project_name(),
             main_xml: meson.project_name() + '-docs.xml',
             src_dir: source_directories,
             dependencies: dependencies,
             gobject_typesfile: meson.project_name() + '.types',
             scan_args: [
               '--rebuild-types',
               '--deprecated-guards=GCV_DISABLE_DEPRECATED',
             ],
             mkdb_args: [
               '--output-format=xml',
               '--name-space=gcv',
               '--source-suffixes=c,cpp,h',
             ],
             fixxref_args: [
               '--html-dir=' + doc_path,
               '--extra-dir=' + join_paths(glib_doc_path, 'glib'),
               '--extra-dir=' + join_paths(glib_doc_path, 'gobject'),
             ],
	     content_files: content_files,
             html_assets: html_images,
             install: true)
