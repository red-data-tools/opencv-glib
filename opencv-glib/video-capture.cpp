#include <opencv-glib/image.hpp>
#include <opencv-glib/video-capture.hpp>

G_BEGIN_DECLS

/**
 * SECTION: video-capture
 * @title: Video capture class
 * @include: opencv-glib/opencv-glib.h
 *
 * #GCVVideoImage is a class for reading images from video.
 *
 * Since: 1.0.0
 */

typedef struct {
  std::shared_ptr<cv::VideoCapture> video_capture;
} GCVVideoCapturePrivate;

G_DEFINE_TYPE_WITH_PRIVATE(GCVVideoCapture, gcv_video_capture, G_TYPE_OBJECT)

#define GCV_VIDEO_CAPTURE_GET_PRIVATE(obj)              \
  (G_TYPE_INSTANCE_GET_PRIVATE((obj),                   \
                               GCV_TYPE_VIDEO_CAPTURE,  \
                               GCVVideoCapturePrivate))

enum {
  PROP_0,
  PROP_VIDEO_CAPTURE
};

static void
gcv_video_capture_finalize(GObject *object)
{
  auto priv = GCV_VIDEO_CAPTURE_GET_PRIVATE(object);

  priv->video_capture = nullptr;

  G_OBJECT_CLASS(gcv_video_capture_parent_class)->finalize(object);
}

static void
gcv_video_capture_set_property(GObject *object,
                               guint prop_id,
                               const GValue *value,
                               GParamSpec *pspec)
{
  auto priv = GCV_VIDEO_CAPTURE_GET_PRIVATE(object);

  switch (prop_id) {
  case PROP_VIDEO_CAPTURE:
    priv->video_capture =
      *static_cast<std::shared_ptr<cv::VideoCapture> *>(g_value_get_pointer(value));
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
    break;
  }
}

static void
gcv_video_capture_init(GCVVideoCapture *object)
{
}

static void
gcv_video_capture_class_init(GCVVideoCaptureClass *klass)
{
  GParamSpec *spec;

  auto gobject_class = G_OBJECT_CLASS(klass);

  gobject_class->finalize     = gcv_video_capture_finalize;
  gobject_class->set_property = gcv_video_capture_set_property;

  spec = g_param_spec_pointer("video-capture",
                              "Video capture",
                              "The raw std::shared<cv::VideoCapture> *",
                              static_cast<GParamFlags>(G_PARAM_WRITABLE |
                                                       G_PARAM_CONSTRUCT_ONLY));
  g_object_class_install_property(gobject_class, PROP_VIDEO_CAPTURE, spec);
}

/**
 * gcv_video_capture_read:
 *
 * It reads an image from the video capture. If no image is left, it
 * returns NULL.
 *
 * Returns: (nullable) (transfer full):
 *   A captured #GCVImage or %NULL.
 *
 * Since: 1.0.0
 */
GCVImage *
gcv_video_capture_read(GCVVideoCapture *capture)
{
  auto priv = GCV_VIDEO_CAPTURE_GET_PRIVATE(capture);
  auto cv_video_capture = priv->video_capture;
  auto cv_image = std::make_shared<cv::Mat>();
  if (cv_video_capture->read(*cv_image)) {
    return gcv_image_new_raw(&cv_image);
  } else {
    return NULL;
  }
}

G_END_DECLS

GCVVideoCapture *
gcv_video_capture_new_raw(std::shared_ptr<cv::VideoCapture> *cv_video_capture)
{
  auto video_capture = g_object_new(GCV_TYPE_VIDEO_CAPTURE,
                                    "video-capture", cv_video_capture,
                                    NULL);
  return GCV_VIDEO_CAPTURE(video_capture);
}

std::shared_ptr<cv::VideoCapture>
gcv_video_capture_get_raw(GCVVideoCapture *video_capture)
{
  auto priv = GCV_VIDEO_CAPTURE_GET_PRIVATE(video_capture);
  return priv->video_capture;
}
