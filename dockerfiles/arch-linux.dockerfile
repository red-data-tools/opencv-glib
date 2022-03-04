FROM archlinux

RUN \
  pacman --sync --noconfirm --refresh && \
  pacman --sync --noconfirm \
    fmt \
    gcc \
    git \
    glew \
    gobject-introspection \
    hdf5 \
    jack2 \
    jsoncpp \
    make \
    meson \
    opencv \
    openmpi \
    pkg-config \
    pugixml \
    qt5 \
    ruby \
    sudo \
    vtk

RUN \
  gem install --no-user-install \
    gobject-introspection \
    test-unit

RUN \
  useradd --user-group --create-home opencv-glib

RUN \
  echo "opencv-glib ALL=(ALL:ALL) NOPASSWD:ALL" | \
    EDITOR=tee visudo -f /etc/sudoers.d/opencv-glib

COPY . /home/opencv-glib/opencv-glib
RUN chown -R opencv-glib: /home/opencv-glib/opencv-glib

USER opencv-glib
WORKDIR /home/opencv-glib/opencv-glib

CMD \
  BUILD_DIR=../opencv-glib.build; \
  meson ${BUILD_DIR} && \
  ninja -C ${BUILD_DIR} && \
  (ninja -C ${BUILD_DIR} test; \
   code=$?; \
   cat ${BUILD_DIR}/meson-logs/testlog.txt; \
   exit $code)
