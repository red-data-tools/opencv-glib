#include <opencv-glib/color.hpp>
#include <opencv-glib/enums.h>
#include <opencv-glib/image.hpp>
#include <opencv-glib/image-error.h>
#include <opencv-glib/point.hpp>
#include <opencv-glib/rectangle.hpp>
#include <opencv-glib/size.hpp>

#include <opencv2/imgproc.hpp>
#include <vector>

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

/*************************************/

typedef struct {
  gboolean normalize;
// const Scalar &borderValue=morphologyDefaultBorderValue()
// const Size &dstsize=Size()
  gdouble delta;
  gdouble psi;
  gdouble scale;
  gdouble sigma_y;
  gint border_type;
  gint iterations;
  gint ksize;
  GCVKType ktype;
  //gint ktype;
  gint max_level;
  GCVPoint *anchor;
// TermCriteria termcrit=TermCriteria(TermCriteria::MAX_ITER+TermCriteria::EPS, 5, 1)
} GCVImageFilterOptionsPrivate;

G_DEFINE_TYPE_WITH_PRIVATE(GCVImageFilterOptions,
                           gcv_image_filter_options,
                           G_TYPE_OBJECT)

#define GCV_IMAGE_FILTER_OPTIONS_GET_PRIVATE(object) \
  static_cast<GCVImageFilterOptionsPrivate *>(      \
    gcv_image_filter_options_get_instance_private(   \
      GCV_IMAGE_FILTER_OPTIONS(object)))

// TODO
enum {
  PROP_NORMALIZE = 1,
  PROP_BORDER_VALUE,
  PROP_DSTSIZE,
  PROP_DELTA,
  PROP_PSI,
  PROP_SCALE,
  PROP_SIGMA_Y,
  PROP_BORDER_TYPE,
  PROP_ITERATIONS,
  PROP_KSIZE,
  PROP_KTYPE,
  PROP_MAX_LEVEL,
  PROP_ANCHOR,
};

static void
gcv_image_filter_options_get_property(GObject *object,
                                 guint prop_id,
                                 GValue *value,
                                 GParamSpec *pspec)
{
  auto priv = GCV_IMAGE_FILTER_OPTIONS_GET_PRIVATE(object);

  switch (prop_id) {
  case PROP_NORMALIZE:
    g_value_set_boolean(value, priv->normalize);
    break;
/* TODO
  case PROP_BORDER_VALUE:
    g_value_set_XXX(value, priv->border_value);
    break;
  case PROP_DSTSIZE:
    g_value_set_XXX(value, priv->dstsize);
    break;
*/
  case PROP_DELTA:
    g_value_set_double(value, priv->delta);
    break;
  case PROP_PSI:
    g_value_set_double(value, priv->psi);
    break;
  case PROP_SCALE:
    g_value_set_double(value, priv->scale);
    break;
  case PROP_SIGMA_Y:
    g_value_set_double(value, priv->sigma_y);
    break;
  case PROP_BORDER_TYPE:
    g_value_set_enum(value, priv->border_type);
    break;
  case PROP_ITERATIONS:
    g_value_set_int(value, priv->iterations);
    break;
  case PROP_KSIZE:
    g_value_set_int(value, priv->ksize);
    break;
  case PROP_KTYPE:
    g_value_set_enum(value, priv->ktype);
    break;
  case PROP_MAX_LEVEL:
    g_value_set_int(value, priv->max_level);
    break;
  case PROP_ANCHOR:
    g_value_set_object(value, priv->anchor);
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
    break;
  }

}

static void
gcv_image_filter_options_set_property(GObject *object,
                                 guint prop_id,
                                 const GValue *value,
                                 GParamSpec *pspec)
{
  auto priv = GCV_IMAGE_FILTER_OPTIONS_GET_PRIVATE(object);

  switch (prop_id) {
  case PROP_NORMALIZE:
    priv->normalize = g_value_get_boolean(value);
    break;
/* TODO
  case PROP_BORDER_VALUE:
    priv->border_value = g_value_get_XXX(value);
    break;
  case PROP_DSTSIZE:
    priv->dstsize = g_value_get_XXX(value);
    break;
*/
  case PROP_DELTA:
    priv->delta = g_value_get_double(value);
    break;
  case PROP_PSI:
    priv->psi = g_value_get_double(value);
    break;
  case PROP_SCALE:
    priv->scale = g_value_get_double(value);
    break;
  case PROP_SIGMA_Y:
    priv->sigma_y = g_value_get_double(value);
    break;
  case PROP_BORDER_TYPE:
    priv->border_type = static_cast<GCVBorderType>(g_value_get_enum(value));
    break;
  case PROP_ITERATIONS:
    priv->iterations = g_value_get_int(value);
    break;
  case PROP_KSIZE:
    priv->ksize = g_value_get_int(value);
    break;
  case PROP_KTYPE:
    priv->ktype = static_cast<GCVKType>(g_value_get_enum(value));
    break;
  case PROP_MAX_LEVEL:
    priv->max_level = g_value_get_int(value);
    break;
  case PROP_ANCHOR:
    {
      auto anchor = g_value_get_object(value);
      if (priv->anchor && priv->anchor == anchor) {
        break;
      }
      if (priv->anchor) {
        g_object_unref(priv->anchor);
      }
      if (anchor) {
        priv->anchor = GCV_POINT(g_object_ref(anchor));
      } else {
        priv->anchor = NULL;
      }
    }
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
    break;
  }
}


static void
gcv_image_filter_options_init(GCVImageFilterOptions *object)
{
}

static void
gcv_image_filter_options_class_init(GCVImageFilterOptionsClass *klass)
{
  GParamSpec *spec;

  auto gobject_class = G_OBJECT_CLASS(klass);

  gobject_class->get_property = gcv_image_filter_options_get_property;
  gobject_class->set_property = gcv_image_filter_options_set_property;

  spec = g_param_spec_boolean("normalize",
                              "Normalize",
                              "normalize", // TODO
                              FALSE,
                              static_cast<GParamFlags>(G_PARAM_READWRITE));
  g_object_class_install_property(gobject_class, PROP_NORMALIZE, spec);

  spec = g_param_spec_double("delta",
                             "Delta",
                             "added to the filtered pixels before storing them in dst.",
                             0, G_MAXDOUBLE, 0,
                             static_cast<GParamFlags>(G_PARAM_READWRITE));
  g_object_class_install_property(gobject_class, PROP_DELTA, spec);

/*
  spec = g_param_spec_double("psi",
                             "Psi",
                             "PSI TODO",
                             0, G_MAXDOUBLE, cv::CV_PI * 0.5,
                             static_cast<GParamFlags>(G_PARAM_READWRITE));
  g_object_class_install_property(gobject_class, PROP_PSI, spec);
*/

  spec = g_param_spec_double("scale",
                             "Scale",
                             "Scale TODO",
                             0, G_MAXDOUBLE, 1.0,
                             static_cast<GParamFlags>(G_PARAM_READWRITE));
  g_object_class_install_property(gobject_class, PROP_SCALE, spec);

  spec = g_param_spec_double("sigmaY",
                             "Sigma Y",
                             "sigmaY TODO",
                             0, G_MAXDOUBLE, 0.0,
                             static_cast<GParamFlags>(G_PARAM_READWRITE));
  g_object_class_install_property(gobject_class, PROP_SIGMA_Y, spec);

  spec = g_param_spec_enum("border-type",
                           "Border type",
                           "The type of border to be filter",
                           GCV_TYPE_BORDER_TYPE,
                           GCV_BORDER_TYPE_BORDER_DEFAULT,
                           static_cast<GParamFlags>(G_PARAM_READWRITE));
  g_object_class_install_property(gobject_class, PROP_BORDER_TYPE, spec);

  spec = g_param_spec_int("iterations",
                          "Iterations",
                          "The number of iterations",
                          0, G_MAXINT, 1,
                          static_cast<GParamFlags>(G_PARAM_READWRITE));
  g_object_class_install_property(gobject_class, PROP_ITERATIONS, spec);

  spec = g_param_spec_int("ksize",
                          "Ksize",
                          "KSize", // TODO
                          0, G_MAXINT, 1, // TODO
                          static_cast<GParamFlags>(G_PARAM_READWRITE));
  g_object_class_install_property(gobject_class, PROP_KSIZE, spec);

  spec = g_param_spec_enum("ktype",
                           "Ktype",
                           "KType", // TODO
                           GCV_TYPE_KTYPE, GCV_KTYPE_CV32F, // TODO
                           static_cast<GParamFlags>(G_PARAM_READWRITE));
  g_object_class_install_property(gobject_class, PROP_KTYPE, spec);

  spec = g_param_spec_int("max-level",
                          "Max Level",
                          "Max Level", // TODO
                          0, G_MAXINT, 1,
                          static_cast<GParamFlags>(G_PARAM_READWRITE));
  g_object_class_install_property(gobject_class, PROP_MAX_LEVEL, spec);

  spec = g_param_spec_object("anchor",
                             "Anchor",
                             "Anchor", // TODO
                             GCV_TYPE_POINT,
                             static_cast<GParamFlags>(G_PARAM_READWRITE));
  g_object_class_install_property(gobject_class, PROP_ANCHOR, spec);
}

/**
 * gcv_image_filter_options_new:
 *
 * Returns a newly created #GCVImageFilterOptions.
 *
 * Since: 1.0.2
 */
GCVImageFilterOptions *
gcv_image_filter_options_new(void)
{
  return GCV_IMAGE_FILTER_OPTIONS(g_object_new(GCV_TYPE_IMAGE_FILTER_OPTIONS,
                                                  NULL));
}

/***************************** end *******************/

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
 * gcv_image_draw_ellipse_point:
 * @image: A #GCVImage.
 * @center: A #GCVPoint to specify center.
 * @axes: A #GCVSize to specify the half of the size of the ellipse main axes.
 * @angle: The ellipse rotation angle in degrees.
 * @start_angle: The starting angle of the elliptic arc in degrees.
 * @end_angle: The ending angle of the elliptic arc in degrees.
 * @color: A #GCVColor to specify line color.
 * @drawing_options: (nullable): A #GCVDrawingOptions to specify optional parameters.
 *
 * It draws an ellipse on @center position with @axes, @angle, @start_angle, @end_angle, @color and @drawing_options
 *
 * Since: 1.0.3
 */
void
gcv_image_draw_ellipse_point(GCVImage *image,
                             GCVPoint *center,
                             GCVSize *axes,
                             gdouble angle,
                             gdouble start_angle,
                             gdouble end_angle,
                             GCVColor *color,
                             GCVDrawingOptions *drawing_options)
{
  auto cv_image = gcv_matrix_get_raw(GCV_MATRIX(image));
  auto cv_center = gcv_point_get_raw(center);
  auto cv_axes = gcv_size_get_raw(axes);
  auto cv_color = gcv_color_get_raw(color);
  if (drawing_options) {
    auto options_priv = GCV_DRAWING_OPTIONS_GET_PRIVATE(drawing_options);
    cv::ellipse(*cv_image,
                *cv_center,
                *cv_axes,
                angle,
                start_angle,
                end_angle,
                *cv_color,
                options_priv->thickness,
                options_priv->line_type,
                options_priv->shift);
  } else {
    cv::ellipse(*cv_image,
                *cv_center,
                *cv_axes,
                angle,
                start_angle,
                end_angle,
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

/**
 * gcv_image_split:
 * @image: A #GCVImage.
 *
 * It splits image. The splitted image is returned as
 * a new matrix.
 *
 * Returns: (element-type GCVImage) (transfer full):
 *   The list of #GCVImage
 *
 * Since: 1.0.4
 */
GList *
gcv_image_split(GCVImage *image)
{
  auto cv_image = gcv_matrix_get_raw(GCV_MATRIX(image));
  std::vector<cv::Mat> cv_splitted_images;
  GList *values = NULL;

  cv::split(*cv_image, cv_splitted_images);
  for (const auto &cv_splitted_image : cv_splitted_images) {
    auto cv_shared_splitted_image = std::make_shared<cv::Mat>(cv_splitted_image);
    auto splitted_image = gcv_image_new_raw(&cv_shared_splitted_image);
    values = g_list_prepend(values, splitted_image);
  }

  return g_list_reverse(values);
}

/**
 * gcv_image_bilateral_filter:
 * @image: A #GCVImage.
 * @d: Diameter of each pixel neighborhood that is used during filtering. If it is non-positive, it is computed from sigmaSpace.
 * @sigma_color: Filter sigma in the color space. A larger value of the parameter means that farther colors within the pixel neighborhood (see sigmaSpace) will be mixed together, resulting in larger areas of semi-equal color.
 * @sigma_space: Filter sigma in the coordinate space. A larger value of the parameter means that farther pixels will influence each other as long as their colors are close enough (see sigmaColor ). When d>0, it specifies the neighborhood size regardless of sigmaSpace. Otherwise, d is proportional to sigmaSpace.
 * @options: (nullable): A #GCVImageFilterOptions;
 * @error: (nullable): Return locatipcn for a #GError or %NULL.
 *
 * It effects bilateral filter image. The converted image is returned as
 * a new image.
 *
 * Returns: (transfer full): A converted #GCVImage.
 *
 * Since: 1.0.4
 */
GCVImage *gcv_image_bilateral_filter(GCVImage *image,
                                     int d,
                                     double sigma_color,
                                     double sigma_space,
                                     GCVImageFilterOptions *options,
                                     GError **error)
{
  auto cv_image = gcv_matrix_get_raw(GCV_MATRIX(image));
  auto cv_converted_image = std::make_shared<cv::Mat>();

  try {
    if ( options != NULL ) {
      auto options_priv = GCV_IMAGE_FILTER_OPTIONS_GET_PRIVATE(options);
      int  border_type = options_priv->border_type;

      cv::bilateralFilter(*cv_image, *cv_converted_image,
                    d, sigma_color, sigma_space, border_type);
    } else {
      cv::bilateralFilter(*cv_image, *cv_converted_image,
                    d, sigma_color, sigma_space);
    }
  } catch (const cv::Exception &exception) {
    g_set_error(error,
                GCV_IMAGE_ERROR,
                GCV_IMAGE_ERROR_FILTER,
                "Failed to filter image: %s",
                exception.what());
    return NULL;
  }


  return gcv_image_new_raw(&cv_converted_image);
}

/**
 * gcv_image_median_blur:
 * @image: A #GCVImage.
 * @ksize: Aperture linear size; it must be odd and greater than 1
 * @error: (nullable): Return locatipcn for a #GError or %NULL.
 *
 * It effects median blur image. The converted image is returned as
 * a new image.
 *
 * Returns: (transfer full): A converted #GCVImage.
 *
 * Since: 1.0.4
 */
GCVImage *gcv_image_median_blur(GCVImage *image,
                                gint ksize,
                                GError **error)
{
  auto cv_image = gcv_matrix_get_raw(GCV_MATRIX(image));
  auto cv_converted_image = std::make_shared<cv::Mat>();

  if (ksize % 2 == 0 || ksize < 1) {
    g_set_error(error,
                GCV_IMAGE_ERROR,
                GCV_IMAGE_ERROR_FILTER,
                "ksize must be odd and greater than 1: <%d>",
                ksize);
    return NULL;
  }

  cv::medianBlur(*cv_image, *cv_converted_image, ksize);

  return gcv_image_new_raw(&cv_converted_image);
}

/**
 * gcv_image_blur:
 * @image: A #GCVImage.
 * @ksize: A #GCVSize blurring kernel size.
 * @options: (nullable): A #GCVImageFilterOptions;
 * @error: (nullable): Return locatipcn for a #GError or %NULL.
 *
 * It effects blur image. The converted image is returned as
 * a new image.
 *
 * Returns: (transfer full): A converted #GCVImage.
 *
 * Since: 1.0.4
 */
GCVImage *gcv_image_blur(GCVImage *image,
                         GCVSize *ksize,
                         GCVImageFilterOptions *options,
                         GError **error)
{
  auto cv_image = gcv_matrix_get_raw(GCV_MATRIX(image));
  auto cv_ksize = gcv_size_get_raw(ksize);
  auto cv_converted_image = std::make_shared<cv::Mat>();

  if ( options != NULL ) {
    auto options_priv = GCV_IMAGE_FILTER_OPTIONS_GET_PRIVATE(options);

    auto anchor = cv::Point(-1, -1);
    if (options_priv->anchor) {
      anchor = *gcv_point_get_raw(options_priv->anchor);
    }
    cv::blur(*cv_image, *cv_converted_image, *cv_ksize, anchor, options_priv->border_type);

  } else {
    cv::blur(*cv_image, *cv_converted_image, *cv_ksize);
  }

  return gcv_image_new_raw(&cv_converted_image);
}

/**
 * gcv_image_box_filter:
 * @image: A #GCVImage.
 * @ddepth: the output image depth
 * @ksize: blurring kernel size.
 * @options: (nullable): A #GCVImageFilterOptions;
 * @error: (nullable): Return locatipcn for a #GError or %NULL.
 *
 * HOGE
 * It effects box filter image. The converted image is returned as
 * a new image.
 *
 * Returns: (transfer full): A converted #GCVImage.
 *
 * Since: 1.0.4
 */
GCVImage *gcv_image_box_filter(GCVImage *image,
                               int ddepth,
                               GCVSize *ksize,
                               GCVImageFilterOptions *options,
                               GError **error)
{
  auto cv_image = gcv_matrix_get_raw(GCV_MATRIX(image));
  auto cv_ksize = gcv_size_get_raw(ksize);
  auto cv_converted_image = std::make_shared<cv::Mat>();

  try {
    if ( options != NULL ) {
      auto options_priv = GCV_IMAGE_FILTER_OPTIONS_GET_PRIVATE(options);
      bool normalize = true;
      int  border_type = options_priv->border_type;
      auto anchor = cv::Point(-1,-1);
      if (options_priv->anchor) {
        anchor = *gcv_point_get_raw(options_priv->anchor);
      }
      cv::boxFilter(*cv_image, *cv_converted_image, ddepth,
                    *cv_ksize, anchor, normalize, border_type);
    } else {
      cv::boxFilter(*cv_image, *cv_converted_image, ddepth, *cv_ksize);
    }
  } catch (const cv::Exception &exception) {
    g_set_error(error,
                GCV_IMAGE_ERROR,
                GCV_IMAGE_ERROR_FILTER,
                "Failed to filter image: %s",
                exception.what());
    return NULL;
  }

  return gcv_image_new_raw(&cv_converted_image);
}

/**
 * gcv_image_build_pyramid:
 * @image: A #GCVImage.
 * @max_level: 0-based index of the last (the smallest) pyramid layer. It must be non-negative.
 * @options: (nullable): A #GCVImageFilterOptions;
 * @error: (nullable): Return locatipcn for a #GError or %NULL.
 *
 * Constructs the Gaussian pyramid for an image
 * The converted image is returned as a new image.
 *
 * Returns: (transfer full): A converted #GCVImage.
 *
 * Since: 1.0.4
 */
GCVImage *gcv_image_build_pyramid(GCVImage *image,
                                  int max_level,
                                  GCVImageFilterOptions *options,
                                  GError **error)
{
  auto cv_image = gcv_matrix_get_raw(GCV_MATRIX(image));
  auto cv_converted_image = std::make_shared<cv::Mat>();

  try {
    if ( options != NULL ) {
      auto options_priv = GCV_IMAGE_FILTER_OPTIONS_GET_PRIVATE(options);
      int  border_type = options_priv->border_type;

      cv::buildPyramid(*cv_image, *cv_converted_image,
                       max_level, border_type);
    } else {
      cv::buildPyramid(*cv_image, *cv_converted_image,max_level);
    }
  } catch (const cv::Exception &exception) {
    g_set_error(error,
                GCV_IMAGE_ERROR,
                GCV_IMAGE_ERROR_FILTER,
                "Failed to filter image: %s",
                exception.what());
    return NULL;
  }


  return gcv_image_new_raw(&cv_converted_image);
}


/**
 * gcv_image_dilate:
 * @image: A #GCVImage.
 * @kernel: structuring element used for dilation.
 * @options: (nullable): A #GCVImageFilterOptions;
 * @error: (nullable): Return locatipcn for a #GError or %NULL.
 *
 * Constructs the dilate filter for an image
 * The converted image is returned as a new image.
 *
 * Returns: (transfer full): A converted #GCVImage.
 *
 * Since: 1.0.4
 */
/*
GCVImage *gcv_image_dilate(GCVImage *image,
                           GCVMatrix *kernel,
                           GCVImageFilterOptions *options,
                           GError **error)
{
  auto cv_image = gcv_matrix_get_raw(GCV_MATRIX(image));
  auto cv_kernel = gcv_matrix_get_raw(GCV_MATRIX(kernel));
  auto cv_converted_image = std::make_shared<cv::Mat>();

  try {
    if ( options != NULL ) {
      auto options_priv = GCV_IMAGE_FILTER_OPTIONS_GET_PRIVATE(options);
      int  iteration = options_priv->iteration;
      int  border_type = options_priv->border_type;

      auto anchor = cv::Point(-1,-1);
      if (options_priv->anchor) {
        anchor = *gcv_point_get_raw(options_priv->anchor);
      }

      cv::dilate(*cv_image, *cv_converted_image, *cv_kernel,
                 anchor, iteration, border_type);
    } else {
      cv::dilate(*cv_image, *cv_converted_image, *cv_kernel);
    }
  } catch (const cv::Exception &exception) {
    g_set_error(error,
                GCV_IMAGE_ERROR,
                GCV_IMAGE_ERROR_FILTER,
                "Failed to filter image: %s",
                exception.what());
    return NULL;
  }


  return gcv_image_new_raw(&cv_converted_image);
}
*/

/**
 * gcv_image_filter2d:
 * @image: A #GCVImage.
 * @ddepth: desired depth of the destination image, see combinations.
 * @kernel: convolution kernel (or rather a correlation kernel), a single-channel floating point matrix; if you want to apply different kernels to different channels, split the image into separate color planes using split and process them individually.
 * @options: (nullable): A #GCVImageFilterOptions;
 * @error: (nullable): Return locatipcn for a #GError or %NULL.
 *
 * Constructs the dilate filter for an image
 * The converted image is returned as a new image.
 *
 * Returns: (transfer full): A converted #GCVImage.
 *
 * Since: 1.0.4
 */
GCVImage *gcv_image_filter2d(GCVImage *image,
                             int ddepth,
                             GCVMatrix *kernel,
                             GCVImageFilterOptions *options,
                             GError **error)
{
  auto cv_image = gcv_matrix_get_raw(GCV_MATRIX(image));
  auto cv_kernel = gcv_matrix_get_raw(GCV_MATRIX(kernel));
  auto cv_converted_image = std::make_shared<cv::Mat>();

  try {
    if ( options != NULL ) {
      auto options_priv = GCV_IMAGE_FILTER_OPTIONS_GET_PRIVATE(options);
      int  delta = options_priv->delta;
      int  border_type = options_priv->border_type;
      auto anchor = cv::Point(-1,-1);

      if (options_priv->anchor) {
        anchor = *gcv_point_get_raw(options_priv->anchor);
      }

      cv::filter2D(*cv_image, *cv_converted_image, ddepth, *cv_kernel,
                 anchor, delta, border_type);
    } else {
      cv::filter2D(*cv_image, *cv_converted_image, ddepth, *cv_kernel);
    }
  } catch (const cv::Exception &exception) {
    g_set_error(error,
                GCV_IMAGE_ERROR,
                GCV_IMAGE_ERROR_FILTER,
                "Failed to filter image: %s",
                exception.what());
    return NULL;
  }

  return gcv_image_new_raw(&cv_converted_image);
}

/**
 * gcv_image_get_deriv_kernels:
 * @image: A #GCVImage.
 * @dx: TODO
 * @dy: TODO
 * @ksize: TODO
 * @options: (nullable): A #GCVImageFilterOptions;
 * @error: (nullable): Return locatipcn for a #GError or %NULL.
 *
 * TODO
 *
 * Returns: (transfer full): A converted #GCVImage.
 *
 * Since: 1.0.4
 */
GCVImage *gcv_image_get_deriv_kernels(GCVImage *image,
                                      int dx,
                                      int dy,
                                      int ksize,
                                      GCVImageFilterOptions *options,
                                      GError **error)
{
  auto cv_image = gcv_matrix_get_raw(GCV_MATRIX(image));
  auto cv_converted_image = std::make_shared<cv::Mat>();

  try {
    if ( options != NULL ) {
      auto options_priv = GCV_IMAGE_FILTER_OPTIONS_GET_PRIVATE(options);
      GCVKType  ktype = options_priv->ktype;
      gboolean normalize = options_priv->normalize;

      cv::getDerivKernels(*cv_image, *cv_converted_image, dx, dy, ksize,
                 normalize, ktype);
    } else {
      cv::getDerivKernels(*cv_image, *cv_converted_image, dx, dy, ksize);
    }
  } catch (const cv::Exception &exception) {
    g_set_error(error,
                GCV_IMAGE_ERROR,
                GCV_IMAGE_ERROR_FILTER,
                "Failed to filter image: %s",
                exception.what());
    return NULL;
  }

  return gcv_image_new_raw(&cv_converted_image);
}

/**
 * gcv_image_laplacian:
 * @image: A #GCVImage.
 * @ddepth: Desired depth of the destination image.
 * @options: (nullable): A #GCVImageFilterOptions;
 * @error: (nullable): Return locatipcn for a #GError or %NULL.
 *
 * It effects laplacian image. The converted image is returned as
 * a new image.
 *
 * Returns: (transfer full): A converted #GCVImage.
 *
 * Since: 1.0.4
 */
GCVImage *gcv_image_laplacian(GCVImage *image,
                              int ddepth,
                              GCVImageFilterOptions *options,
                              GError **error)
{
  auto cv_image = gcv_matrix_get_raw(GCV_MATRIX(image));
  auto cv_converted_image = std::make_shared<cv::Mat>();

  try {
    if ( options != NULL ) {
      auto options_priv = GCV_IMAGE_FILTER_OPTIONS_GET_PRIVATE(options);
      int    ksize       = options_priv->ksize;
      double scale       = options_priv->scale;
      double delta       = options_priv->delta;
      int    border_type = options_priv->border_type;

      cv::Laplacian(*cv_image, *cv_converted_image,
                    ddepth, ksize, scale, delta, border_type);
    } else {
      cv::Laplacian(*cv_image, *cv_converted_image, ddepth);
    }
  } catch (const cv::Exception &exception) {
    g_set_error(error,
                GCV_IMAGE_ERROR,
                GCV_IMAGE_ERROR_FILTER,
                "Failed to filter image: %s",
                exception.what());
    return NULL;
  }

  return gcv_image_new_raw(&cv_converted_image);
}

/**
 * gcv_image_sobel:
 * @image: A #GCVImage.
 * @ddepth: Desired depth of the destination image.
 * @intx: Order of the derivative x
 * @inty: Order of the derivative y
 * @options: (nullable): A #GCVImageFilterOptions;
 * @error: (nullable): Return locatipcn for a #GError or %NULL.
 *
 * It effects sobel image. The converted image is returned as
 * a new image.
 *
 * Returns: (transfer full): A converted #GCVImage.
 *
 * Since: 1.0.4
 */
GCVImage *gcv_image_sobel(GCVImage *image,
                          int ddepth,
                          int intx,
                          int inty,
                          GCVImageFilterOptions *options,
                          GError **error)
{
  auto cv_image = gcv_matrix_get_raw(GCV_MATRIX(image));
  auto cv_converted_image = std::make_shared<cv::Mat>();

  try {
    if ( options != NULL ) {
      auto options_priv = GCV_IMAGE_FILTER_OPTIONS_GET_PRIVATE(options);
      int    ksize       = options_priv->ksize;
      double scale       = options_priv->scale;
      double delta       = options_priv->delta;
      int    border_type = options_priv->border_type;

      cv::Sobel(*cv_image, *cv_converted_image,
                ddepth, intx, inty, ksize, scale, delta, border_type);

    } else {
      cv::Sobel(*cv_image, *cv_converted_image, ddepth, intx, inty);
    }
  } catch (const cv::Exception &exception) {
    g_set_error(error,
                GCV_IMAGE_ERROR,
                GCV_IMAGE_ERROR_FILTER,
                "Failed to filter image: %s",
                exception.what());
    return NULL;
  }

  return gcv_image_new_raw(&cv_converted_image);
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
