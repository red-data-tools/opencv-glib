FROM debian:10

RUN \
  echo "debconf debconf/frontend select Noninteractive" | \
    debconf-set-selections

RUN \
  apt update && \
  apt install -y \
    g++ \
    gcc \
    libopencv-dev \
    make \
    meson \
    opencv-data \
    ruby-dev \
    sudo

RUN \
  gem install bundler

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
  bundle install && \
  (bundle exec ninja -C ${BUILD_DIR} test; \
   code=$?; \
   cat ${BUILD_DIR}/meson-logs/testlog.txt; \
   exit $code)
