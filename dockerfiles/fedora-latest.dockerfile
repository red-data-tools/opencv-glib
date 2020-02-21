FROM fedora:latest

RUN \
  dnf install -y \
    gcc \
    gcc-c++ \
    gobject-introspection \
    make \
    meson \
    opencv-devel \
    redhat-rpm-config \
    ruby-devel \
    sudo

RUN \
  gem install bundler

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
  bundle install && \
  (bundle exec ninja -C ${BUILD_DIR} test; \
   code=$?; \
   cat ${BUILD_DIR}/meson-logs/testlog.txt; \
   exit $code)
