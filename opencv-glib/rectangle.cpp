#include <opencv-glib/rectangle.hpp>

G_BEGIN_DECLS

/**
 * SECTION: rectangle
 * @title: Rectangle class
 * @include: opencv-glib/opencv-glib.h
 *
 * #GCVRectangle is a rectangle class.
 *
 * Since: 1.0.0
 */

typedef struct {
  std::shared_ptr<cv::Rect> rectangle;
} GCVRectanglePrivate;

G_DEFINE_TYPE_WITH_PRIVATE(GCVRectangle, gcv_rectangle, G_TYPE_OBJECT)

#define GCV_RECTANGLE_GET_PRIVATE(object)                       \
  static_cast<GCVRectanglePrivate *>(                           \
    gcv_rectangle_get_instance_private(                         \
      GCV_RECTANGLE(object)))

enum {
  PROP_0,
  PROP_RECTANGLE
};

static void
gcv_rectangle_finalize(GObject *object)
{
  auto priv = GCV_RECTANGLE_GET_PRIVATE(object);

  priv->rectangle = nullptr;

  G_OBJECT_CLASS(gcv_rectangle_parent_class)->finalize(object);
}

static void
gcv_rectangle_set_property(GObject *object,
                           guint prop_id,
                           const GValue *value,
                           GParamSpec *pspec)
{
  auto priv = GCV_RECTANGLE_GET_PRIVATE(object);

  switch (prop_id) {
  case PROP_RECTANGLE:
    priv->rectangle =
      *static_cast<std::shared_ptr<cv::Rect> *>(g_value_get_pointer(value));
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
    break;
  }
}

static void
gcv_rectangle_init(GCVRectangle *object)
{
}

static void
gcv_rectangle_class_init(GCVRectangleClass *klass)
{
  GParamSpec *spec;

  auto gobject_class = G_OBJECT_CLASS(klass);

  gobject_class->finalize     = gcv_rectangle_finalize;
  gobject_class->set_property = gcv_rectangle_set_property;

  spec = g_param_spec_pointer("rectangle",
                              "Rectangle",
                              "The raw std::shared<cv::Rect> *",
                              static_cast<GParamFlags>(G_PARAM_WRITABLE |
                                                       G_PARAM_CONSTRUCT_ONLY));
  g_object_class_install_property(gobject_class, PROP_RECTANGLE, spec);
}

/**
 * gcv_rectangle_new:
 * @x: A X value of the top-left corner
 * @y: A Y value of the top-left corner
 * @width: A width of the new rectangle
 * @height: A height of the new rectangle
 *
 * Returns: A newly created #GCVRectangle.
 *
 * Since: 1.0.0
 */
GCVRectangle *
gcv_rectangle_new(gint x, gint y, gint width, gint height)
{
  auto cv_rectangle = std::make_shared<cv::Rect>(x, y, width, height);
  return gcv_rectangle_new_raw(&cv_rectangle);
}

/**
 * gcv_rectangle_new_empty:
 *
 * Returns: A newly created empty #GCVRectangle.
 *
 * Since: 1.0.0
 */
GCVRectangle *
gcv_rectangle_new_empty(void)
{
  auto cv_rectangle = std::make_shared<cv::Rect>();
  return gcv_rectangle_new_raw(&cv_rectangle);
}

/**
 * gcv_rectangle_get_x:
 * @rectangle: A #GCVRectangle
 *
 * Returns: The X value of the top-left corner.
 *
 * Since: 1.0.0
 */
gint
gcv_rectangle_get_x(GCVRectangle *rectangle)
{
  auto cv_rectangle = gcv_rectangle_get_raw(rectangle);
  return cv_rectangle->x;
}

/**
 * gcv_rectangle_set_x:
 * @rectangle: A #GCVRectangle
 * @x: A new X value of the top-left corner.
 *
 * Since: 1.0.0
 */
void
gcv_rectangle_set_x(GCVRectangle *rectangle, gint x)
{
  auto cv_rectangle = gcv_rectangle_get_raw(rectangle);
  cv_rectangle->x = x;
}

/**
 * gcv_rectangle_get_y:
 * @rectangle: A #GCVRectangle
 *
 * Returns: The Y value of the top-left corner.
 *
 * Since: 1.0.0
 */
gint
gcv_rectangle_get_y(GCVRectangle *rectangle)
{
  auto cv_rectangle = gcv_rectangle_get_raw(rectangle);
  return cv_rectangle->y;
}

/**
 * gcv_rectangle_set_y:
 * @rectangle: A #GCVRectangle
 * @y: A new Y value of the top-left corner.
 *
 * Since: 1.0.0
 */
void
gcv_rectangle_set_y(GCVRectangle *rectangle, gint y)
{
  auto cv_rectangle = gcv_rectangle_get_raw(rectangle);
  cv_rectangle->y = y;
}

/**
 * gcv_rectangle_get_width:
 * @rectangle: A #GCVRectangle
 *
 * Returns: The width of the rectangle.
 *
 * Since: 1.0.0
 */
gint
gcv_rectangle_get_width(GCVRectangle *rectangle)
{
  auto cv_rectangle = gcv_rectangle_get_raw(rectangle);
  return cv_rectangle->width;
}

/**
 * gcv_rectangle_set_width:
 * @rectangle: A #GCVRectangle
 * @width: A new width of the rectangle.
 *
 * Since: 1.0.0
 */
void
gcv_rectangle_set_width(GCVRectangle *rectangle, gint width)
{
  auto cv_rectangle = gcv_rectangle_get_raw(rectangle);
  cv_rectangle->width = width;
}

/**
 * gcv_rectangle_get_height:
 * @rectangle: A #GCVRectangle
 *
 * Returns: The height of the rectangle.
 *
 * Since: 1.0.0
 */
gint
gcv_rectangle_get_height(GCVRectangle *rectangle)
{
  auto cv_rectangle = gcv_rectangle_get_raw(rectangle);
  return cv_rectangle->height;
}

/**
 * gcv_rectangle_set_height:
 * @rectangle: A #GCVRectangle
 * @height: A new height of the rectangle.
 *
 * Since: 1.0.0
 */
void
gcv_rectangle_set_height(GCVRectangle *rectangle, gint height)
{
  auto cv_rectangle = gcv_rectangle_get_raw(rectangle);
  cv_rectangle->height = height;
}

G_END_DECLS

GCVRectangle *
gcv_rectangle_new_raw(std::shared_ptr<cv::Rect> *cv_rectangle)
{
  auto rectangle = g_object_new(GCV_TYPE_RECTANGLE,
                                "rectangle", cv_rectangle,
                                NULL);
  return GCV_RECTANGLE(rectangle);
}

std::shared_ptr<cv::Rect>
gcv_rectangle_get_raw(GCVRectangle *rectangle)
{
  auto priv = GCV_RECTANGLE_GET_PRIVATE(rectangle);
  return priv->rectangle;
}
