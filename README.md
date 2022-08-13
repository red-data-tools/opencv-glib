# OpenCV GLib

OpenCV GLib is a wrapper library for [OpenCV][opencv]. OpenCV GLib
provides C API.

OpenCV GLib supports [GObject Introspection][gobject-introspection].
It means that you can create language bindings at runtime or compile
time.

For example, you can use OpenCV from Ruby by OpenCV GLib and
[gobject-introspection gem][gobject-introspection-gem] with the
following code:

```ruby
# Generate bindings at runtime
require "gi"
CV = GI.load("CV")

# TODO
```

## Install

You can use packages or build by yourself to install OpenCV GLib. It's
recommended that you use packages.

### Package

You can install packages from https://packages.red-data-tools.org/ .
See
https://github.com/red-data-tools/packages.red-data-tools.org#readme
for details.

### How to build by users

OpenCV GLib users should use released source archive to build OpenCV
GLib:

```console
% OPENCV_GLIB_VERSION=1.0.0
% wget https://github.com/red-data-tools/opencv-glib/releases/download/${OPENCV_GLIB_VERSION}/opencv-glib-${OPENCV_GLIB_VERSION}.tar.gz
% tar xf opencv-glib-${OPENCV_GLIB_VERSION}.tar.gz
% cd opencv-glib-${OPENCV_GLIB_VERSION}
```

You need to install the followings before you install OpenCV GLib:

  * [OpenCV][opencv]

  * [GObject Introspection][gobject-introspection]

  * [Meson][meson]

  * [Ninja][ninja]

You can build and install OpenCV GLib after you install them:

```console
% mkdir -p build
% meson build --buildtype=release
% (cd build && ninja)
% (cd build && sudo ninja install)
```

### How to build by developers

You need to install the followings before you install OpenCV GLib:

  * [OpenCV][opencv]

  * [GObject Introspection][gobject-introspection]

  * [Meson][meson]

  * [Ninja][ninja]

  * [GTK-Doc][gtk-doc]

You can install them by the followings:

On Debian GNU/Linux or Ubuntu:

```text
% sudo apt install -y -V meson ninja-build gtk-doc-tools libgirepository1.0-dev
```

On Fedora:

```text
sudo dnf install -y meson ninja-build gtk-doc gobject-introspection-devel
```

On CentOS 7 or later:

```text
% sudo yum install -y gtk-doc gobject-introspection-devel
% sudo pip install -y meson ninja
```

On macOS with [Homebrew][homebrew]:

```text
% brew install -y gtk-doc gobject-introspection meson ninja
```

You can build and install OpenCV GLib after you install them:

```console
% mkdir -p build
% meson build -Dgtk_doc=true
% (cd build && ninja)
% (cd build && sudo ninja install)
```

## Usage

TODO

### C

You can find API reference in the
`/usr/local/share/gtk-doc/html/opencv-glib/` directory. If you
specify `--prefix` to `configure`, the directory will be different.

TODO: Examples

### Language bindings

TODO

## License

[The 3-Clause BSD license][bsd-3-clause]. See LICENSE for details.

(Kouhei Sutou has a right to change the license including contributed
patches.)

[opencv]:https://opencv.org/

[gobject-introspection]:https://wiki.gnome.org/Projects/GObjectIntrospection

[gobject-introspection-gem]:https://rubygems.org/gems/gobject-introspection

[meson]:http://mesonbuild.com/

[ninja]:https://ninja-build.org/

[gtk-doc]:https://www.gtk.org/gtk-doc/

[homebrew]:https://brew.sh/

[bsd-3-clause]:https://opensource.org/licenses/BSD-3-Clause
