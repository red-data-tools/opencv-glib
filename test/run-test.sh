#!/bin/sh

test_dir="$(cd $(dirname $0); pwd)"
build_dir="$(cd .; pwd)"

modules="opencv-glib"

for module in ${modules}; do
  module_build_dir="${build_dir}/${module}"
  if [ -d "${module_build_dir}" ]; then
    LD_LIBRARY_PATH="${module_build_dir}:${LD_LIBRARY_PATH}"
  fi
done

if [ -f "build.ninja" -a "${BUILD}" != "no" ]; then
  ninja || exit $?
fi

for module in ${modules}; do
  module_typelib_dir="${build_dir}/${module}"
  if [ -d "${module_typelib_dir}" ]; then
    GI_TYPELIB_PATH="${module_typelib_dir}:${GI_TYPELIB_PATH}"
  fi
done

${GDB} ruby ${test_dir}/run-test.rb "$@"
