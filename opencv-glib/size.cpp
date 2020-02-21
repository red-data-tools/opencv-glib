#include <opencv-glib/point.hpp>
#include <opencv-glib/size.hpp>

#include <opencv2/imgproc.hpp>

G_BEGIN_DECLS

/**
 * SECTION: size
 * @title: Size class
 * @include: opencv-glib/opencv-glib.h
 *
 * #GCVSize is a size class.
 *
 * Since: 1.0.3
 */

typedef struct {
  std::shared_ptr<cv::Size> size;
} GCVSizePrivate;

G_DEFINE_TYPE_WITH_PRIVATE(GCVSize, gcv_size, G_TYPE_OBJECT)

#define GCV_SIZE_GET_PRIVATE(object)           \
  static_cast<GCVSizePrivate *>(               \
    gcv_size_get_instance_private(             \
      GCV_SIZE(object)))

enum {
  PROP_SIZE = 1
};

static void
gcv_size_finalize(GObject *object)
{
  auto priv = GCV_SIZE_GET_PRIVATE(object);

  priv->size = nullptr;

  G_OBJECT_CLASS(gcv_size_parent_class)->finalize(object);
}

static void
gcv_size_set_property(GObject *object,
                      guint prop_id,
                      const GValue *value,
                      GParamSpec *pspec)
{
  auto priv = GCV_SIZE_GET_PRIVATE(object);

  switch (prop_id) {
  case PROP_SIZE:
    priv->size =
      *static_cast<std::shared_ptr<cv::Size> *>(g_value_get_pointer(value));
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
    break;
  }
}

static void
gcv_size_init(GCVSize *object)
{
}

static void
gcv_size_class_init(GCVSizeClass *klass)
{
  GParamSpec *spec;

  auto gobject_class = G_OBJECT_CLASS(klass);

  gobject_class->finalize     = gcv_size_finalize;
  gobject_class->set_property = gcv_size_set_property;

  spec = g_param_spec_pointer("size",
                              "Size",
                              "The raw std::shared<cv::Size> *",
                              static_cast<GParamFlags>(G_PARAM_WRITABLE |
                                                       G_PARAM_CONSTRUCT_ONLY));
  g_object_class_install_property(gobject_class, PROP_SIZE, spec);
}

/**
 * gcv_size_new:
 * @width: A width value of the size
 * @height: A height value value of the size
 *
 * Returns: A newly created #GCVSize.
 *
 * Since: 1.0.3
 */
GCVSize *
gcv_size_new(gint width, gint height)
{
  auto cv_size = std::make_shared<cv::Size>(width, height);
  return gcv_size_new_raw(&cv_size);
}

/**
 * gcv_size_new_empty:
 *
 * Returns: A newly created empty #GCVSize.
 *
 * Since: 1.0.3
 */
GCVSize *
gcv_size_new_empty(void)
{
  auto cv_size = std::make_shared<cv::Size>();
  return gcv_size_new_raw(&cv_size);
}

/**
 * gcv_size_get_width:
 * @size: A #GCVSize
 *
 * Returns: The width value of the size.
 *
 * Since: 1.0.3
 */
gint
gcv_size_get_width(GCVSize *size)
{
  auto cv_size = gcv_size_get_raw(size);
  return cv_size->width;
}

/**
 * gcv_size_set_width:
 * @size: A #GCVSize
 * @width: A new width value of the size.
 *
 * Since: 1.0.3
 */
void
gcv_size_set_width(GCVSize *size, gint width)
{
  auto cv_size = gcv_size_get_raw(size);
  cv_size->width = width;
}

/**
 * gcv_size_get_height:
 * @size: A #GCVSize
 *
 * Returns: The height value of the size.
 *
 * Since: 1.0.3
 */
gint
gcv_size_get_height(GCVSize *size)
{
  auto cv_size = gcv_size_get_raw(size);
  return cv_size->height;
}

/**
 * gcv_size_set_height:
 * @size: A #GCVSize
 * @height: A new height value of the size.
 *
 * Since: 1.0.3
 */
void
gcv_size_set_height(GCVSize *size, gint height)
{
  auto cv_size = gcv_size_get_raw(size);
  cv_size->height = height;
}

/**
 * gcv_size_clip_line:
 * @size: A #GCVSize
 * @point1: (inout): A #GCVPoint to specify the first point
 * @point2: (inout): A #GCVPoint to specify the second point
 *
 * Returns: %FALSE if the line segment is completely outside the rectangle. Otherwise %TRUE.
 *
 * Since: 1.0.3
 */
gboolean
gcv_size_clip_line(GCVSize *size, GCVPoint **point1, GCVPoint **point2)
{
  auto cv_size = gcv_size_get_raw(size);
  auto cv_point1 = gcv_point_get_raw(*point1);
  auto cv_point2 = gcv_point_get_raw(*point2);
  gboolean ret = cv::clipLine(*cv_size, *cv_point1, *cv_point2);
  return ret;
}

G_END_DECLS

GCVSize *
gcv_size_new_raw(std::shared_ptr<cv::Size> *cv_size)
{
  auto size = g_object_new(GCV_TYPE_SIZE,
                           "size", cv_size,
                           NULL);
  return GCV_SIZE(size);
}

std::shared_ptr<cv::Size>
gcv_size_get_raw(GCVSize *size)
{
  auto priv = GCV_SIZE_GET_PRIVATE(size);
  return priv->size;
}
