#include <opencv-glib/color.hpp>

G_BEGIN_DECLS

/**
 * SECTION: color
 * @title: Color class
 * @include: opencv-glib/opencv-glib.h
 *
 * #GCVColor is a color class.
 *
 * Since: 1.0.0
 */

typedef struct {
  std::shared_ptr<cv::Scalar> color;
} GCVColorPrivate;

G_DEFINE_TYPE_WITH_PRIVATE(GCVColor, gcv_color, G_TYPE_OBJECT)

#define GCV_COLOR_GET_PRIVATE(obj)                         \
  (G_TYPE_INSTANCE_GET_PRIVATE((obj),                      \
                               GCV_TYPE_COLOR,             \
                               GCVColorPrivate))

enum {
  PROP_0,
  PROP_COLOR
};

static void
gcv_color_finalize(GObject *object)
{
  auto priv = GCV_COLOR_GET_PRIVATE(object);

  priv->color = nullptr;

  G_OBJECT_CLASS(gcv_color_parent_class)->finalize(object);
}

static void
gcv_color_set_property(GObject *object,
                       guint prop_id,
                       const GValue *value,
                       GParamSpec *pspec)
{
  auto priv = GCV_COLOR_GET_PRIVATE(object);

  switch (prop_id) {
  case PROP_COLOR:
    priv->color =
      *static_cast<std::shared_ptr<cv::Scalar> *>(g_value_get_pointer(value));
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
    break;
  }
}

static void
gcv_color_init(GCVColor *object)
{
}

static void
gcv_color_class_init(GCVColorClass *klass)
{
  GParamSpec *spec;

  auto gobject_class = G_OBJECT_CLASS(klass);

  gobject_class->finalize     = gcv_color_finalize;
  gobject_class->set_property = gcv_color_set_property;

  spec = g_param_spec_pointer("color",
                              "Color",
                              "The raw std::shared<cv::Scalar> *",
                              static_cast<GParamFlags>(G_PARAM_WRITABLE |
                                                       G_PARAM_CONSTRUCT_ONLY));
  g_object_class_install_property(gobject_class, PROP_COLOR, spec);
}

/**
 * gcv_color_new_brightness:
 * @brightness: A brightness
 *
 * Returns: A newly created #GCVColor for brightness.
 *
 * Since: 1.0.0
 */
GCVColor *
gcv_color_new_brightness(gdouble brightness)
{
  auto cv_color = std::make_shared<cv::Scalar>(brightness);
  return gcv_color_new_raw(&cv_color);
}

/**
 * gcv_color_new_color:
 * @pixel0: A 0th pixel value
 * @pixel1: A 1st pixel value
 * @pixel2: A 2nd pixel value
 *
 * Returns: A newly created #GCVColor for 24bit color such as BGR
 * color and RGB color.
 *
 * Since: 1.0.0
 */
GCVColor *
gcv_color_new_color(gdouble pixel0,
                    gdouble pixel1,
                    gdouble pixel2)
{
  auto cv_color = std::make_shared<cv::Scalar>(pixel0, pixel1, pixel2);
  return gcv_color_new_raw(&cv_color);
}

/**
 * gcv_color_new_color_alpha:
 * @pixel0: A 0th pixel value
 * @pixel1: A 1st pixel value
 * @pixel2: A 2nd pixel value
 * @alpha: A alpha value
 *
 * Returns: A newly created #GCVColor for 32bit color such as BGRA
 * color and RGBA color.
 *
 * Since: 1.0.0
 */
GCVColor *
gcv_color_new_color_alpha(gdouble pixel0,
                          gdouble pixel1,
                          gdouble pixel2,
                          gdouble alpha)
{
  auto cv_color = std::make_shared<cv::Scalar>(pixel0, pixel1, pixel2, alpha);
  return gcv_color_new_raw(&cv_color);
}

/**
 * gcv_color_get_brightness:
 * @color: A #GCVColor
 *
 * Returns: The brightness value of the color.
 *
 * Since: 1.0.0
 */
gdouble
gcv_color_get_brightness(GCVColor *color)
{
  auto cv_color = gcv_color_get_raw(color);
  return cv_color->val[0];
}

/**
 * gcv_color_set_brightness:
 * @color: A #GCVColor
 * @brightness: A new brightness value of the color.
 *
 * Since: 1.0.0
 */
void
gcv_color_set_brightness(GCVColor *color, gdouble brightness)
{
  auto cv_color = gcv_color_get_raw(color);
  cv_color->val[0] = brightness;
}

/**
 * gcv_color_get_pixel0:
 * @color: A #GCVColor
 *
 * Returns: The 0th pixel value of the color.
 *
 * Since: 1.0.0
 */
gdouble
gcv_color_get_pixel0(GCVColor *color)
{
  auto cv_color = gcv_color_get_raw(color);
  return cv_color->val[0];
}

/**
 * gcv_color_set_pixel0:
 * @color: A #GCVColor
 * @pixel0: A new 0th pixel value of the color.
 *
 * Since: 1.0.0
 */
void
gcv_color_set_pixel0(GCVColor *color, gdouble pixel0)
{
  auto cv_color = gcv_color_get_raw(color);
  cv_color->val[0] = pixel0;
}

/**
 * gcv_color_get_pixel1:
 * @color: A #GCVColor
 *
 * Returns: The 1st pixel value of the color.
 *
 * Since: 1.0.0
 */
gdouble
gcv_color_get_pixel1(GCVColor *color)
{
  auto cv_color = gcv_color_get_raw(color);
  return cv_color->val[1];
}

/**
 * gcv_color_set_pixel1:
 * @color: A #GCVColor
 * @pixel1: A new 1st pixel value of the color.
 *
 * Since: 1.0.0
 */
void
gcv_color_set_pixel1(GCVColor *color, gdouble pixel1)
{
  auto cv_color = gcv_color_get_raw(color);
  cv_color->val[1] = pixel1;
}

/**
 * gcv_color_get_pixel2:
 * @color: A #GCVColor
 *
 * Returns: The 2nd pixel value of the color.
 *
 * Since: 1.0.0
 */
gdouble
gcv_color_get_pixel2(GCVColor *color)
{
  auto cv_color = gcv_color_get_raw(color);
  return cv_color->val[2];
}

/**
 * gcv_color_set_pixel2:
 * @color: A #GCVColor
 * @pixel2: A new 2nd pixel value of the color.
 *
 * Since: 1.0.0
 */
void
gcv_color_set_pixel2(GCVColor *color, gdouble pixel2)
{
  auto cv_color = gcv_color_get_raw(color);
  cv_color->val[2] = pixel2;
}

/**
 * gcv_color_get_alpha:
 * @color: A #GCVColor
 *
 * Returns: The alpha value of the color.
 *
 * Since: 1.0.0
 */
gdouble
gcv_color_get_alpha(GCVColor *color)
{
  auto cv_color = gcv_color_get_raw(color);
  return cv_color->val[3];
}

/**
 * gcv_color_set_alpha:
 * @color: A #GCVColor
 * @alpha: A new alpha value of the color.
 *
 * Since: 1.0.0
 */
void
gcv_color_set_alpha(GCVColor *color, gdouble alpha)
{
  auto cv_color = gcv_color_get_raw(color);
  cv_color->val[3] = alpha;
}


G_END_DECLS

GCVColor *
gcv_color_new_raw(std::shared_ptr<cv::Scalar> *cv_color)
{
  auto color = g_object_new(GCV_TYPE_COLOR,
                            "color", cv_color,
                            NULL);
  return GCV_COLOR(color);
}

std::shared_ptr<cv::Scalar>
gcv_color_get_raw(GCVColor *color)
{
  auto priv = GCV_COLOR_GET_PRIVATE(color);
  return priv->color;
}
