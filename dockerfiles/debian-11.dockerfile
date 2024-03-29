FROM debian:11

RUN \
  echo "debconf debconf/frontend select Noninteractive" | \
    debconf-set-selections

RUN \
  apt update && \
  apt install -y \
    g++ \
    gcc \
    libgirepository1.0-dev \
    libopencv-dev \
    make \
    meson \
    opencv-data \
    ruby-dev \
    sudo

RUN \
  gem install \
    gobject-introspection \
    test-unit

RUN \
  useradd --user-group --create-home opencv-glib

RUN \
  echo "opencv-glib ALL=(ALL:ALL) NOPASSWD:ALL" | \
    EDITOR=tee visudo -f /etc/sudoers.d/opencv-glib

COPY . /home/opencv-glib/opencv-glib

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
