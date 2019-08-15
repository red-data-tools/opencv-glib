#include <opencv-glib/color.hpp>
#include <opencv-glib/enums.h>
#include <opencv-glib/image.hpp>
#include <opencv-glib/image-error.h>
#include <opencv-glib/rectangle.hpp>

#include <opencv2/imgproc.hpp>

G_BEGIN_DECLS

/**
 * SECTION: image
 * @title: Image class
 * @include: opencv-glib/opencv-glib.h
 *
 * #GCVImage is a special matrix class for image.
 *
 * Since: 1.0.0
 */

typedef struct {
  gint thickness;
  GCVLineType line_type;
  gint shift;
} GCVDrawingOptionsPrivate;

G_DEFINE_TYPE_WITH_PRIVATE(GCVDrawingOptions, gcv_drawing_options, G_TYPE_OBJECT)

#define GCV_DRAWING_OPTIONS_GET_PRIVATE(obj)              \
  (G_TYPE_INSTANCE_GET_PRIVATE((obj),                     \
                               GCV_TYPE_DRAWING_OPTIONS,  \
                               GCVDrawingOptionsPrivate))

enum {
  PROP_THICKNESS = 1,
  PROP_LINE_TYPE,
  PROP_SHIFT
};

static void
gcv_drawing_options_get_property(GObject *object,
                                 guint prop_id,
                                 GValue *value,
                                 GParamSpec *pspec)
{
  auto priv = GCV_DRAWING_OPTIONS_GET_PRIVATE(object);

  switch (prop_id) {
  case PROP_THICKNESS:
    g_value_set_int(value, priv->thickness);
    break;
  case PROP_LINE_TYPE:
    g_value_set_enum(value, priv->line_type);
    break;
  case PROP_SHIFT:
    g_value_set_int(value, priv->shift);
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
    break;
  }
}

static void
gcv_drawing_options_set_property(GObject *object,
                                 guint prop_id,
                                 const GValue *value,
                                 GParamSpec *pspec)
{
  auto priv = GCV_DRAWING_OPTIONS_GET_PRIVATE(object);

  switch (prop_id) {
  case PROP_THICKNESS:
    priv->thickness = g_value_get_int(value);
    break;
  case PROP_LINE_TYPE:
    priv->line_type = static_cast<GCVLineType>(g_value_get_enum(value));
    break;
  case PROP_SHIFT:
    priv->shift = g_value_get_int(value);
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
    break;
  }
}

static void
gcv_drawing_options_init(GCVDrawingOptions *object)
{
}

static void
gcv_drawing_options_class_init(GCVDrawingOptionsClass *klass)
{
  GParamSpec *spec;

  auto gobject_class = G_OBJECT_CLASS(klass);

  gobject_class->get_property = gcv_drawing_options_get_property;
  gobject_class->set_property = gcv_drawing_options_set_property;

  spec = g_param_spec_int("thickness",
                          "Thickness",
                          "The thickness of line to be drawn",
                          0, G_MAXINT, 1,
                          static_cast<GParamFlags>(G_PARAM_READWRITE |
                                                   G_PARAM_CONSTRUCT));
  g_object_class_install_property(gobject_class, PROP_THICKNESS, spec);
  spec = g_param_spec_enum("line-type",
                           "Line type",
                           "The type of line to be drawn",
                           GCV_TYPE_LINE_TYPE,
                           GCV_LINE_TYPE_LINE_8,
                           static_cast<GParamFlags>(G_PARAM_READWRITE |
                                                    G_PARAM_CONSTRUCT));
  g_object_class_install_property(gobject_class, PROP_LINE_TYPE, spec);
  spec = g_param_spec_int("shift",
                          "Shift",
                          "The number of fractional bits in the point coordinates",
                          0, G_MAXINT, 0,
                          static_cast<GParamFlags>(G_PARAM_READWRITE |
                                                   G_PARAM_CONSTRUCT));
  g_object_class_install_property(gobject_class, PROP_SHIFT, spec);
}

/**
 * gcv_drawing_options_new:
 *
 * Returns a newly created #GCVDrawingOptions.
 *
 * Since: 1.0.1
 */
GCVDrawingOptions *
gcv_drawing_options_new(void)
{
  return GCV_DRAWING_OPTIONS(g_object_new(GCV_TYPE_DRAWING_OPTIONS, NULL));
}

G_DEFINE_TYPE(GCVImage, gcv_image, GCV_TYPE_MATRIX)

static void
gcv_image_init(GCVImage *object)
{
}

static void
gcv_image_class_init(GCVImageClass *klass)
{
}

/**
 * gcv_image_read:
 * @filename: The filename to be read.
 * @flags: The flags that control how to read an image.
 * @error: (nullable): Return locatipcn for a #GError or %NULL.
 *
 * It reads an image from file. Image format is determined by the
 * content, not by the extension of the filename.
 *
 * Returns: (nullable) (transfer full):
 *   A newly read #GCVImage.
 *
 * Since: 1.0.0
 */
GCVImage *
gcv_image_read(const gchar *filename,
               GCVImageReadFlags flags,
               GError **error)
{
  auto cv_matrix_raw = cv::imread(filename, static_cast<int>(flags));
  if (cv_matrix_raw.empty()) {
    g_set_error(error,
                GCV_IMAGE_ERROR,
                GCV_IMAGE_ERROR_READ,
                "Failed to read image: %s", filename);
    return NULL;
  }
  auto cv_matrix = std::make_shared<cv::Mat>(cv_matrix_raw);
  return gcv_image_new_raw(&cv_matrix);
}

/**
 * gcv_image_write:
 * @image: A #GCVImage.
 * @filename: The filename to be read.
 * @error: (nullable): Return locatipcn for a #GError or %NULL.
 *
 * It writes the image to file. Image format is determined from
 * extension of the filename.
 *
 * Returns: %TRUE on success, %FALSE if there was an error.
 *
 * Since: 1.0.0
 */
gboolean
gcv_image_write(GCVImage *image,
                const gchar *filename,
                GError **error)
{
  auto cv_matrix = gcv_matrix_get_raw(GCV_MATRIX(image));
  try {
    if (!cv::imwrite(filename, *cv_matrix)) {
      g_set_error(error,
                  GCV_IMAGE_ERROR,
                  GCV_IMAGE_ERROR_WRITE,
                  "Failed to write image: %s", filename);
      return FALSE;
    }
  } catch (cv::Exception exception) {
    g_set_error(error,
                GCV_IMAGE_ERROR,
                GCV_IMAGE_ERROR_WRITE,
                "Failed to write image: %s: %s",
                filename, exception.what());
    return FALSE;
  }
  return TRUE;
}

/**
 * gcv_image_convert_color:
 * @image: A #GCVImage.
 * @code: A code to specify how to convert color.
 *
 * It converts color of the image. The converted image is returned as
 * a new image.
 *
 * Returns: (transfer full): A color converted #GCVImage.
 *
 * Since: 1.0.0
 */
GCVImage *
gcv_image_convert_color(GCVImage *image,
                        GCVColorConversionCode code)
{
  auto cv_image = gcv_matrix_get_raw(GCV_MATRIX(image));
  auto cv_converted_image = std::make_shared<cv::Mat>();
  cv::cvtColor(*cv_image,
               *cv_converted_image,
               static_cast<int>(code));
  return gcv_image_new_raw(&cv_converted_image);
}

/**
 * gcv_image_draw_rectangle:
 * @image: A #GCVImage.
 * @rectangle: A #GCVRectangle to specify area.
 * @color: A #GCVColor to specify line color.
 * @drawing_options: (nullable): A #GCVDrawingOptions to specify optional parameters.
 *
 * It draws a rectangle to @rectangle area with @color color and @drawing_options options.
 *
 * Since: 1.0.0
 */
void
gcv_image_draw_rectangle(GCVImage *image,
                         GCVRectangle *rectangle,
                         GCVColor *color,
                         GCVDrawingOptions *drawing_options)
{
  auto cv_image = gcv_matrix_get_raw(GCV_MATRIX(image));
  auto cv_rectangle = gcv_rectangle_get_raw(rectangle);
  auto cv_color = gcv_color_get_raw(color);
  if (drawing_options) {
    auto options_priv = GCV_DRAWING_OPTIONS_GET_PRIVATE(drawing_options);
    cv::rectangle(*cv_image,
                  *cv_rectangle,
                  *cv_color,
                  options_priv->thickness,
                  options_priv->line_type,
                  options_priv->shift);
  } else {
    cv::rectangle(*cv_image,
                  *cv_rectangle,
                  *cv_color);
  }
}

G_END_DECLS

GCVImage *
gcv_image_new_raw(std::shared_ptr<cv::Mat> *cv_matrix)
{
  auto matrix = g_object_new(GCV_TYPE_IMAGE,
                             "matrix", cv_matrix,
                             NULL);
  return GCV_IMAGE(matrix);
}
