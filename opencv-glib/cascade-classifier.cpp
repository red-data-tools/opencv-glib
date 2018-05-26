#include <opencv-glib/config.h>

#include <opencv-glib/cascade-classifier.hpp>
#include <opencv-glib/cascade-classifier-error.h>
#include <opencv-glib/image.hpp>
#include <opencv-glib/rectangle.hpp>

G_BEGIN_DECLS

/**
 * SECTION: cascade-classifier
 * @title: CascadeClassifier class
 * @include: opencv-glib/opencv-glib.h
 *
 * #GCVCascadeClassifier is a class for object detection.
 *
 * Since: 1.0.0
 */

typedef struct {
  std::shared_ptr<cv::CascadeClassifier> cascade_classifier;
} GCVCascadeClassifierPrivate;

G_DEFINE_TYPE_WITH_PRIVATE(GCVCascadeClassifier,                        \
                           gcv_cascade_classifier,                      \
                           G_TYPE_OBJECT)

#define GCV_CASCADE_CLASSIFIER_GET_PRIVATE(obj)                     \
  (G_TYPE_INSTANCE_GET_PRIVATE((obj),                               \
                               GCV_TYPE_CASCADE_CLASSIFIER,         \
                               GCVCascadeClassifierPrivate))

enum {
  PROP_0,
  PROP_CASCADE_CLASSIFIER
};

static void
gcv_cascade_classifier_finalize(GObject *object)
{
  auto priv = GCV_CASCADE_CLASSIFIER_GET_PRIVATE(object);

  priv->cascade_classifier = nullptr;

  G_OBJECT_CLASS(gcv_cascade_classifier_parent_class)->finalize(object);
}

static void
gcv_cascade_classifier_set_property(GObject *object,
                                    guint prop_id,
                                    const GValue *value,
                                    GParamSpec *pspec)
{
  auto priv = GCV_CASCADE_CLASSIFIER_GET_PRIVATE(object);

  switch (prop_id) {
  case PROP_CASCADE_CLASSIFIER:
    priv->cascade_classifier =
      *static_cast<std::shared_ptr<cv::CascadeClassifier> *>(g_value_get_pointer(value));
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
    break;
  }
}

static void
gcv_cascade_classifier_init(GCVCascadeClassifier *object)
{
}

static void
gcv_cascade_classifier_class_init(GCVCascadeClassifierClass *klass)
{
  GParamSpec *spec;

  auto gobject_class = G_OBJECT_CLASS(klass);

  gobject_class->finalize     = gcv_cascade_classifier_finalize;
  gobject_class->set_property = gcv_cascade_classifier_set_property;

  spec = g_param_spec_pointer("cascade-classifier",
                              "Cascade classifier",
                              "The raw std::shared<cv::CascadeClassifier> *",
                              static_cast<GParamFlags>(G_PARAM_WRITABLE |
                                                       G_PARAM_CONSTRUCT_ONLY));
  g_object_class_install_property(gobject_class, PROP_CASCADE_CLASSIFIER, spec);
}

/**
 * gcv_cascade_classifier_new:
 * @filename: (type filename): A filename that stores model.
 * @error: (nullable): Return locatipcn for a #GError or %NULL.
 *
 * Returns: (nullable):
 *   A newly created #GCVCascadeClassifier or %NULL on error.
 *
 * Since: 1.0.0
 */
GCVCascadeClassifier *
gcv_cascade_classifier_new(const gchar *filename, GError **error)
{
  if (g_path_is_absolute(filename)) {
    auto cv_classifier = std::make_shared<cv::CascadeClassifier>(filename);
    if (cv_classifier->empty()) {
      g_set_error(error,
                  GCV_CASCADE_CLASSIFIER_ERROR,
                  GCV_CASCADE_CLASSIFIER_ERROR_LOAD,
                  "Failed to load the model file: <%s>",
                  filename);
      return NULL;
    }
    return gcv_cascade_classifier_new_raw(&cv_classifier);
  } else {
    gchar *completed_filename = NULL;
    if (g_str_has_prefix(filename, "haarcascade_")) {
      completed_filename = g_build_filename(OPENCV_DATA_DIRECTORY,
                                            "haarcascades",
                                            filename,
                                            NULL);
    } else if (g_strstr_len(filename, -1, G_DIR_SEPARATOR_S)) {
      completed_filename = g_build_filename(OPENCV_DATA_DIRECTORY,
                                            filename,
                                            NULL);
    } else if (g_str_has_suffix(filename, ".xml")) {
      completed_filename = g_build_filename(OPENCV_DATA_DIRECTORY,
                                            "haarcascades",
                                            filename,
                                            NULL);
    } else {
      std::string completed_basename("haarcascade_");
      completed_basename += filename;
      completed_basename += ".xml";
      completed_filename = g_build_filename(OPENCV_DATA_DIRECTORY,
                                            "haarcascades",
                                            completed_basename.c_str(),
                                            NULL);
    }
    auto cv_classifier =
      std::make_shared<cv::CascadeClassifier>(completed_filename);
    if (cv_classifier->empty()) {
      g_set_error(error,
                  GCV_CASCADE_CLASSIFIER_ERROR,
                  GCV_CASCADE_CLASSIFIER_ERROR_LOAD,
                  "Failed to load the model file: <%s>",
                  completed_filename);
      g_free(completed_filename);
      return NULL;
    }
    g_free(completed_filename);
    return gcv_cascade_classifier_new_raw(&cv_classifier);
  }
}

/**
 * gcv_cascade_classifier_detect:
 * @classifier: A #GCVCascadeClassifier
 * @image: A #GCVImage to be detected. It must be a gray-scale image.
 *
 * Returns: (element-type GCVRectangle) (transfer full):
 *   Detected objects.
 *
 * Since: 1.0.0
 */
GList *
gcv_cascade_classifier_detect(GCVCascadeClassifier *classifier,
                              GCVImage *image)
{
  auto cv_classifier = gcv_cascade_classifier_get_raw(classifier);
  auto cv_image = gcv_matrix_get_raw(GCV_MATRIX(image));
  std::vector<cv::Rect> cv_objects_raw;
  cv_classifier->detectMultiScale(*cv_image, cv_objects_raw);

  GList *objects = NULL;
  for (auto cv_object_raw : cv_objects_raw) {
    auto cv_object = std::make_shared<cv::Rect>(cv_object_raw);
    auto object = gcv_rectangle_new_raw(&cv_object);
    objects = g_list_prepend(objects, object);
  }
  return g_list_reverse(objects);
}

G_END_DECLS

GCVCascadeClassifier *
gcv_cascade_classifier_new_raw(std::shared_ptr<cv::CascadeClassifier> *cv_classifier)
{
  auto classifier = g_object_new(GCV_TYPE_CASCADE_CLASSIFIER,
                                 "cascade-classifier", cv_classifier,
                                 NULL);
  return GCV_CASCADE_CLASSIFIER(classifier);
}

std::shared_ptr<cv::CascadeClassifier>
gcv_cascade_classifier_get_raw(GCVCascadeClassifier *classifier)
{
  auto priv = GCV_CASCADE_CLASSIFIER_GET_PRIVATE(classifier);
  return priv->cascade_classifier;
}
