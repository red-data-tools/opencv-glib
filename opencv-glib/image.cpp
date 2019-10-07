#include <opencv-glib/color.hpp>
#include <opencv-glib/enums.h>
#include <opencv-glib/image.hpp>
#include <opencv-glib/image-error.h>
#include <opencv-glib/point.hpp>
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
  GCVLineType line_type;
  gint marker_size;
  GCVMarkerType marker_type;
  gint shift;
  gint thickness;
  gdouble tip_length;
  gboolean use_bottom_left_origin;
} GCVDrawingOptionsPrivate;

G_DEFINE_TYPE_WITH_PRIVATE(GCVDrawingOptions, gcv_drawing_options, G_TYPE_OBJECT)

#define GCV_DRAWING_OPTIONS_GET_PRIVATE(object) \
  static_cast<GCVDrawingOptionsPrivate *>(      \
    gcv_drawing_options_get_instance_private(   \
      GCV_DRAWING_OPTIONS(object)))

enum {
  PROP_LINE_TYPE = 1,
  PROP_MARKER_SIZE,
  PROP_MARKER_TYPE,
  PROP_SHIFT,
  PROP_THICKNESS,
  PROP_TIP_LENGTH,
  PROP_USE_BOTTOM_LEFT_ORIGIN
};

static void
gcv_drawing_options_get_property(GObject *object,
                                 guint prop_id,
                                 GValue *value,
                                 GParamSpec *pspec)
{
  auto priv = GCV_DRAWING_OPTIONS_GET_PRIVATE(object);

  switch (prop_id) {
  case PROP_LINE_TYPE:
    g_value_set_enum(value, priv->line_type);
    break;
  case PROP_MARKER_SIZE:
    g_value_set_int(value, priv->marker_size);
    break;
  case PROP_MARKER_TYPE:
    g_value_set_enum(value, priv->marker_type);
    break;
  case PROP_SHIFT:
    g_value_set_int(value, priv->shift);
    break;
  case PROP_THICKNESS:
    g_value_set_int(value, priv->thickness);
    break;
  case PROP_TIP_LENGTH:
    g_value_set_double(value, priv->tip_length);
    break;
  case PROP_USE_BOTTOM_LEFT_ORIGIN:
    g_value_set_boolean(value, priv->use_bottom_left_origin);
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
  case PROP_LINE_TYPE:
    priv->line_type = static_cast<GCVLineType>(g_value_get_enum(value));
    break;
  case PROP_MARKER_SIZE:
    priv->marker_size = g_value_get_int(value);
    break;
  case PROP_MARKER_TYPE:
    priv->marker_type = static_cast<GCVMarkerType>(g_value_get_enum(value));
    break;
  case PROP_SHIFT:
    priv->shift = g_value_get_int(value);
    break;
  case PROP_THICKNESS:
    priv->thickness = g_value_get_int(value);
    break;
  case PROP_TIP_LENGTH:
    priv->tip_length = g_value_get_double(value);
    break;
  case PROP_USE_BOTTOM_LEFT_ORIGIN:
    priv->use_bottom_left_origin = g_value_get_boolean(value);
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

  spec = g_param_spec_enum("line-type",
                           "Line type",
                           "The type of line to be drawn",
                           GCV_TYPE_LINE_TYPE,
                           GCV_LINE_TYPE_LINE_8,
                           static_cast<GParamFlags>(G_PARAM_READWRITE |
                                                    G_PARAM_CONSTRUCT));
  g_object_class_install_property(gobject_class, PROP_LINE_TYPE, spec);
  spec = g_param_spec_int("marker-size",
                          "Marker size",
                          "The length of the marker axis",
                          0, G_MAXINT, 20,
                          static_cast<GParamFlags>(G_PARAM_READWRITE |
                                                   G_PARAM_CONSTRUCT));
  g_object_class_install_property(gobject_class, PROP_MARKER_SIZE, spec);
  spec = g_param_spec_enum("marker-type",
                           "Marker type",
                           "The type of marker to be drawn",
                           GCV_TYPE_MARKER_TYPE,
                           GCV_MARKER_TYPE_CROSS,
                           static_cast<GParamFlags>(G_PARAM_READWRITE |
                                                    G_PARAM_CONSTRUCT));
  g_object_class_install_property(gobject_class, PROP_MARKER_TYPE, spec);
  spec = g_param_spec_int("shift",
                          "Shift",
                          "The number of fractional bits in the point coordinates",
                          0, G_MAXINT, 0,
                          static_cast<GParamFlags>(G_PARAM_READWRITE |
                                                   G_PARAM_CONSTRUCT));
  g_object_class_install_property(gobject_class, PROP_SHIFT, spec);
  spec = g_param_spec_int("thickness",
                          "Thickness",
                          "The thickness of line to be drawn",
                          0, G_MAXINT, 1,
                          static_cast<GParamFlags>(G_PARAM_READWRITE |
                                                   G_PARAM_CONSTRUCT));
  g_object_class_install_property(gobject_class, PROP_THICKNESS, spec);
  spec = g_param_spec_double("tip-length",
                             "Tip length",
                             "The length of the arrow tip in relation to the arrow length",
                             0, G_MAXDOUBLE, 0.1,
                             static_cast<GParamFlags>(G_PARAM_READWRITE |
                                                      G_PARAM_CONSTRUCT));
  g_object_class_install_property(gobject_class, PROP_TIP_LENGTH, spec);
  spec = g_param_spec_boolean("use-bottom-left-origin",
                              "Use bottom left origin",
                              "When true, the image data origin is at the bottom-left corner. Otherwise, it is at the top-left corner.",
                              FALSE,
                              static_cast<GParamFlags>(G_PARAM_READWRITE |
                                                       G_PARAM_CONSTRUCT));
  g_object_class_install_property(gobject_class, PROP_USE_BOTTOM_LEFT_ORIGIN, spec);
}

/**
 * gcv_drawing_options_new:
 *
 * Returns a newly created #GCVDrawingOptions.
 *
 * Since: 1.0.2
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
  } catch (const cv::Exception &exception) {
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
 * gcv_image_draw_arrowed_line:
 * @image: A #GCVImage.
 * @point1: A #GCVPoint to specify the point the arrow starts from.
 * @point2: A #GCVPoint to specify the point the arrow points to.
 * @color: A #GCVColor to specify line color.
 * @drawing_options: (nullable): A #GCVDrawingOptions to specify optional parameters.
 *
 * It draws a arrow segment pointing from @point1 to @point2
  *
 * Since: 1.0.2
 */
void
gcv_image_draw_arrowed_line(GCVImage *image,
                            GCVPoint *point1,
                            GCVPoint *point2,
                            GCVColor *color,
                            GCVDrawingOptions *drawing_options)
{
  auto cv_image = gcv_matrix_get_raw(GCV_MATRIX(image));
  auto cv_point1 = gcv_point_get_raw(point1);
  auto cv_point2 = gcv_point_get_raw(point2);
  auto cv_color = gcv_color_get_raw(color);
  if (drawing_options) {
    auto options_priv = GCV_DRAWING_OPTIONS_GET_PRIVATE(drawing_options);
    cv::arrowedLine(*cv_image,
                    *cv_point1,
                    *cv_point2,
                    *cv_color,
                    options_priv->thickness,
                    options_priv->line_type,
                    options_priv->shift,
                    options_priv->tip_length);
  } else {
    cv::arrowedLine(*cv_image,
                    *cv_point1,
                    *cv_point2,
                    *cv_color);
  }
}

/**
 * gcv_image_draw_circle:
 * @image: A #GCVImage.
 * @center: A #GCVPoint to specify center.
 * @radius: The radius of the circle.
 * @color: A #GCVColor to specify line color.
 * @drawing_options: (nullable): A #GCVDrawingOptions to specify optional parameters.
 *
 * It draws a circle with a given @center point, @radius, @color color and @drawing_options options.
 *
 * Since: 1.0.2
 */
void
gcv_image_draw_circle(GCVImage *image,
                      GCVPoint *center,
                      gint radius,
                      GCVColor *color,
                      GCVDrawingOptions *drawing_options)
{
  auto cv_image = gcv_matrix_get_raw(GCV_MATRIX(image));
  auto cv_center = gcv_point_get_raw(center);
  auto cv_color = gcv_color_get_raw(color);
  if (drawing_options) {
    auto options_priv = GCV_DRAWING_OPTIONS_GET_PRIVATE(drawing_options);
    cv::circle(*cv_image,
               *cv_center,
               radius,
               *cv_color,
               options_priv->thickness,
               options_priv->line_type,
               options_priv->shift);
  } else {
    cv::circle(*cv_image,
               *cv_center,
               radius,
               *cv_color);
  }
}

/**
 * gcv_image_draw_marker:
 * @image: A #GCVImage.
 * @position: A #GCVPoint to specify the point where the crosshair is positioned.
 * @color: A #GCVColor to specify line color.
 * @drawing_options: (nullable): A #GCVDrawingOptions to specify optional parameters.
 *
 * It draws a marker on @position with @color color and @drawing_options options.
 *
 * Since: 1.0.2
 */
void
gcv_image_draw_marker(GCVImage *image,
                      GCVPoint *position,
                      GCVColor *color,
                      GCVDrawingOptions *drawing_options)
{
  auto cv_image = gcv_matrix_get_raw(GCV_MATRIX(image));
  auto cv_position = gcv_point_get_raw(position);
  auto cv_color = gcv_color_get_raw(color);
  if (drawing_options) {
    auto options_priv = GCV_DRAWING_OPTIONS_GET_PRIVATE(drawing_options);
    cv::drawMarker(*cv_image,
                   *cv_position,
                   *cv_color,
                   options_priv->marker_type,
                   options_priv->marker_size,
                   options_priv->thickness,
                   options_priv->line_type);
  } else {
    cv::drawMarker(*cv_image,
                   *cv_position,
                   *cv_color);
  }
}

/**
 * gcv_image_draw_line:
 * @image: A #GCVImage.
 * @point1: A #GCVPoint to specify the first point of the line segment.
 * @point2: A #GCVPoint to specify the second point of the line segment.
 * @color: A #GCVColor to specify line color.
 * @drawing_options: (nullable): A #GCVDrawingOptions to specify optional parameters.
 *
 * It draws a line segment between @point1 and @point2 with @color color and @drawing_options options.
 *
 * Since: 1.0.2
 */
void
gcv_image_draw_line(GCVImage *image,
                    GCVPoint *point1,
                    GCVPoint *point2,
                    GCVColor *color,
                    GCVDrawingOptions *drawing_options)
{
  auto cv_image = gcv_matrix_get_raw(GCV_MATRIX(image));
  auto cv_point1 = gcv_point_get_raw(point1);
  auto cv_point2 = gcv_point_get_raw(point2);
  auto cv_color = gcv_color_get_raw(color);
  if (drawing_options) {
    auto options_priv = GCV_DRAWING_OPTIONS_GET_PRIVATE(drawing_options);
    cv::line(*cv_image,
             *cv_point1,
             *cv_point2,
             *cv_color,
             options_priv->thickness,
             options_priv->line_type,
             options_priv->shift);
  } else {
    cv::line(*cv_image,
             *cv_point1,
             *cv_point2,
             *cv_color);
  }
}

/**
 * gcv_image_put_text
 * @image: A #GCVImage.
 * @text: The text string to be drawn.
 * @org: The bottom-left corner of the text string in the image.
 * @font_face: The font type.
 * @font_scale: The font scale factor that is multiplied by the font-specific base size.
 * @color: A #GCVColor to specify text color.
 * @drawing_options: (nullable): A #GCVDrawingOptions to specify optional parameters.
 *
 * It draws the specified @text in the image with @color color and @drawing_options options.
 *
 * Since: 1.0.2
 */
void
gcv_image_put_text(GCVImage *image,
                   const gchar *text,
                   GCVPoint *org,
                   GCVHersheyFont font_face,
                   gdouble font_scale,
                   GCVColor *color,
                   GCVDrawingOptions *drawing_options)
{
  auto cv_image = gcv_matrix_get_raw(GCV_MATRIX(image));
  auto cv_org = gcv_point_get_raw(org);
  auto cv_color = gcv_color_get_raw(color);
  if (drawing_options) {
    auto options_priv = GCV_DRAWING_OPTIONS_GET_PRIVATE(drawing_options);
    cv::putText(*cv_image,
                text,
                *cv_org,
                font_face,
                font_scale,
                *cv_color,
                options_priv->thickness,
                options_priv->line_type,
                options_priv->use_bottom_left_origin);
  } else {
    cv::putText(*cv_image,
                text,
                *cv_org,
                font_face,
                font_scale,
                *cv_color);
  }
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

/**
 * gcv_image_draw_rectangle_points:
 * @image: A #GCVImage.
 * @point1: A #GCVPoint to specify the vertex of the rectangle.
 * @point2: A #GCVPoint to specify the vertex of the rectangle opposite to @point1.
 * @color: A #GCVColor to specify line color.
 * @drawing_options: (nullable): A #GCVDrawingOptions to specify optional parameters.
 *
 * It draws a rectangle whose two opposite corners are @point1 and @point2.
 *
 * Since: 1.0.2
 */
void
gcv_image_draw_rectangle_points(GCVImage *image,
                                GCVPoint *point1,
                                GCVPoint *point2,
                                GCVColor *color,
                                GCVDrawingOptions *drawing_options)
{
  auto cv_image = gcv_matrix_get_raw(GCV_MATRIX(image));
  auto cv_point1 = gcv_point_get_raw(point1);
  auto cv_point2 = gcv_point_get_raw(point2);
  auto cv_color = gcv_color_get_raw(color);
  if (drawing_options) {
    auto options_priv = GCV_DRAWING_OPTIONS_GET_PRIVATE(drawing_options);
    cv::rectangle(*cv_image,
                  *cv_point1,
                  *cv_point2,
                  *cv_color,
                  options_priv->thickness,
                  options_priv->line_type,
                  options_priv->shift);
  } else {
    cv::rectangle(*cv_image,
                  *cv_point1,
                  *cv_point2,
                  *cv_color);
  }
}

/**
 * gcv_image_abs_diff:
 * @image: A #GCVImage.
 * @other_image: A #GCVImage.
 *
 * See also `cv::absdiff()` in OpenCV.
 *
 * Returns: (transfer full): A newly created #GCVImage that has per-element
 *   absolute difference between @image and @other_image.
 *
 * Since: 1.0.3
 */
GCVImage *
gcv_image_abs_diff(GCVImage *image,
                   GCVImage *other_image)
{
  auto cv_image = gcv_matrix_get_raw(GCV_MATRIX(image));
  auto cv_other_image = gcv_matrix_get_raw(GCV_MATRIX(other_image));
  auto cv_output = std::make_shared<cv::Mat>();
  cv::absdiff(*cv_image, *cv_other_image, *cv_output);
  return gcv_image_new_raw(&cv_output);
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
