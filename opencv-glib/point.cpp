#include <opencv-glib/point.hpp>

G_BEGIN_DECLS

/**
 * SECTION: point
 * @title: Point class
 * @include: opencv-glib/opencv-glib.h
 *
 * #GCVPoint is a point class.
 *
 * Since: 1.0.1
 */

typedef struct {
  std::shared_ptr<cv::Point> point;
} GCVPointPrivate;

G_DEFINE_TYPE_WITH_PRIVATE(GCVPoint, gcv_point, G_TYPE_OBJECT)

#define GCV_POINT_GET_PRIVATE(obj)                     \
  (G_TYPE_INSTANCE_GET_PRIVATE((obj),                  \
                               GCV_TYPE_POINT,         \
                               GCVPointPrivate))

enum {
  PROP_POINT = 1
};

static void
gcv_point_finalize(GObject *object)
{
  auto priv = GCV_POINT_GET_PRIVATE(object);

  priv->point = nullptr;

  G_OBJECT_CLASS(gcv_point_parent_class)->finalize(object);
}

static void
gcv_point_set_property(GObject *object,
                       guint prop_id,
                       const GValue *value,
                       GParamSpec *pspec)
{
  auto priv = GCV_POINT_GET_PRIVATE(object);

  switch (prop_id) {
  case PROP_POINT:
    priv->point =
      *static_cast<std::shared_ptr<cv::Point> *>(g_value_get_pointer(value));
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
    break;
  }
}

static void
gcv_point_init(GCVPoint *object)
{
}

static void
gcv_point_class_init(GCVPointClass *klass)
{
  GParamSpec *spec;

  auto gobject_class = G_OBJECT_CLASS(klass);

  gobject_class->finalize     = gcv_point_finalize;
  gobject_class->set_property = gcv_point_set_property;

  spec = g_param_spec_pointer("point",
                              "Point",
                              "The raw std::shared<cv::Point> *",
                              static_cast<GParamFlags>(G_PARAM_WRITABLE |
                                                       G_PARAM_CONSTRUCT_ONLY));
  g_object_class_install_property(gobject_class, PROP_POINT, spec);
}

/**
 * gcv_point_new:
 * @x: A X value of the point
 * @y: A Y value of the point
 *
 * Returns: A newly created #GCVPoint.
 *
 * Since: 1.0.1
 */
GCVPoint *
gcv_point_new(gint x, gint y)
{
  auto cv_point = std::make_shared<cv::Point>(x, y);
  return gcv_point_new_raw(&cv_point);
}

/**
 * gcv_point_new_empty:
 *
 * Returns: A newly created empty #GCVPoint.
 *
 * Since: 1.0.1
 */
GCVPoint *
gcv_point_new_empty(void)
{
  auto cv_point = std::make_shared<cv::Point>();
  return gcv_point_new_raw(&cv_point);
}

/**
 * gcv_point_get_x:
 * @point: A #GCVPoint
 *
 * Returns: The X value of the point.
 *
 * Since: 1.0.1
 */
gint
gcv_point_get_x(GCVPoint *point)
{
  auto cv_point = gcv_point_get_raw(point);
  return cv_point->x;
}

/**
 * gcv_point_set_x:
 * @point: A #GCVPoint
 * @x: A new X value of the point.
 *
 * Since: 1.0.1
 */
void
gcv_point_set_x(GCVPoint *point, gint x)
{
  auto cv_point = gcv_point_get_raw(point);
  cv_point->x = x;
}

/**
 * gcv_point_get_y:
 * @point: A #GCVPoint
 *
 * Returns: The Y value of the point.
 *
 * Since: 1.0.1
 */
gint
gcv_point_get_y(GCVPoint *point)
{
  auto cv_point = gcv_point_get_raw(point);
  return cv_point->y;
}

/**
 * gcv_point_set_y:
 * @point: A #GCVPoint
 * @y: A new Y value of the point.
 *
 * Since: 1.0.1
 */
void
gcv_point_set_y(GCVPoint *point, gint y)
{
  auto cv_point = gcv_point_get_raw(point);
  cv_point->y = y;
}

G_END_DECLS

GCVPoint *
gcv_point_new_raw(std::shared_ptr<cv::Point> *cv_point)
{
  auto point = g_object_new(GCV_TYPE_POINT,
                            "point", cv_point,
                            NULL);
  return GCV_POINT(point);
}

std::shared_ptr<cv::Point>
gcv_point_get_raw(GCVPoint *point)
{
  auto priv = GCV_POINT_GET_PRIVATE(point);
  return priv->point;
}
