#!/bin/sh

if ! pkg-config --cflags --libs gobject-introspection-1.0 > /dev/null 2>&1; then
  if type brew > /dev/null 2>&1; then
    libffi_pkg_config_path=$(brew --prefix libffi)/lib/pkgconfig
    if [ -z "$PKG_CONFIG_PATH" ]; then
      PKG_CONFIG_PATH="${libffi_pkg_config_path}"
    else
      PKG_CONFIG_PATH="${libffi_pkg_config_path};${PKG_CONFIG_PATH}"
    fi
  fi
fi

"$@"
