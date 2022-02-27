#pragma once

#include <opencv-glib/color.h>
#include <opencv-glib/matrix.h>
#include <opencv-glib/point.h>
#include <opencv-glib/rectangle.h>
#include <opencv-glib/size.h>

G_BEGIN_DECLS

/**
 * GCVHersheyFont:
 * @GCV_HERSHEY_FONT_HERSHEY_SIMPLEX: See `cv::HersheyFonts::FONT_HERSHEY_SIMPLEX`.
 * @GCV_HERSHEY_FONT_HERSHEY_PLAIN: See `cv::HersheyFonts::FONT_HERSHEY_PLAIN`.
 * @GCV_HERSHEY_FONT_HERSHEY_DUPLEX: See `cv::HersheyFonts::FONT_HERSHEY_DUPLEX`.
 * @GCV_HERSHEY_FONT_HERSHEY_COMPLEX: See `cv::HersheyFonts::FONT_HERSHEY_COMPLEX`.
 * @GCV_HERSHEY_FONT_HERSHEY_TRIPLEX: See `cv::HersheyFonts::FONT_HERSHEY_TRIPLEX`.
 * @GCV_HERSHEY_FONT_HERSHEY_COMPLEX_SMALL: See `cv::HersheyFonts::FONT_HERSHEY_COMPLEX_SMALL`.
 * @GCV_HERSHEY_FONT_HERSHEY_SCRIPT_SIMPLEX: See `cv::HersheyFonts::FONT_HERSHEY_SCRIPT_SIMPLEX`.
 * @GCV_HERSHEY_FONT_HERSHEY_SCRIPT_COMPLEX: See `cv::HersheyFonts::FONT_HERSHEY_SCRIPT_COMPLEX`.
 * @GCV_HERSHEY_FONT_ITALIC: See `cv::HersheyFonts::FONT_ITALIC`.
 *
 * Line type for drawing functions corresponding to `cv::HersheyFonts`.
 *
 * See also [OpenCV documents](https://docs.opencv.org/).
 *
 * We don't have a link to the latest `cv::HersheyFonts` document.
 * But we can link to a specific version:
 * [OpenCV 3.4.1's `cv::HersheyFonts`](https://docs.opencv.org/3.4.1/d0/de1/group__core.html#ga0f9314ea6e35f99bb23f29567fc16e11).
 *
 * Since 1.0.2
 */
typedef enum {
  GCV_HERSHEY_FONT_HERSHEY_SIMPLEX = 0,
  GCV_HERSHEY_FONT_HERSHEY_PLAIN = 1,
  GCV_HERSHEY_FONT_HERSHEY_DUPLEX = 2,
  GCV_HERSHEY_FONT_HERSHEY_COMPLEX = 3,
  GCV_HERSHEY_FONT_HERSHEY_TRIPLEX = 4,
  GCV_HERSHEY_FONT_HERSHEY_COMPLEX_SMALL = 5,
  GCV_HERSHEY_FONT_HERSHEY_SCRIPT_SIMPLEX = 6,
  GCV_HERSHEY_FONT_HERSHEY_SCRIPT_COMPLEX = 7,
  GCV_HERSHEY_FONT_ITALIC = 16
} GCVHersheyFont;

/**
 * GCVLineType:
 * @GCV_LINE_TYPE_FILLED: See `cv::LineTypes::FILLED`.
 * @GCV_LINE_TYPE_LINE_4: See `cv::LineTypes::LINE_4`.
 * @GCV_LINE_TYPE_LINE_8: See `cv::LineTypes::LINE_8`.
 * @GCV_LINE_TYPE_LINE_AA: See `cv::LineTypes::LINE_AA`.
 *
 * Line type for drawing functions corresponding to `cv::LineTypes`.
 *
 * See also [OpenCV documents](https://docs.opencv.org/).
 *
 * We don't have a link to the latest `cv::LineTypes` document.
 * But we can link to a specific version:
 * [OpenCV 3.4.1's `cv::LineTypes`](https://docs.opencv.org/3.4.1/d0/de1/group__core.html#gaf076ef45de481ac96e0ab3dc2c29a777).
 *
 * Since 1.0.2
 */
typedef enum {
  GCV_LINE_TYPE_FILLED = -1,
  GCV_LINE_TYPE_LINE_4 = 4,
  GCV_LINE_TYPE_LINE_8 = 8,
  GCV_LINE_TYPE_LINE_AA = 16
} GCVLineType;

/**
 * GCVMarkerType:
 * @GCV_MARKER_TYPE_CROSS: See `cv::MarkerTypes::MARKER_CROSS`.
 * @GCV_MARKER_TYPE_TILTED_CROSS: See `cv::MarkerTypes::MARKER_TILTED_CROSS`.
 * @GCV_MARKER_TYPE_STAR: See `cv::MarkerTypes::MARKER_STAR`.
 * @GCV_MARKER_TYPE_DIAMOND: See `cv::MarkerTypes::MARKER_DIAMOND`.
 * @GCV_MARKER_TYPE_SQUARE: See `cv::MarkerTypes::MARKER_SQUARE`.
 * @GCV_MARKER_TYPE_TRIANGLE_UP: See `cv::MarkerTypes::MARKER_TRIANGLE_UP`.
 * @GCV_MARKER_TYPE_TRIANGLE_DOWN: See `cv::MarkerTypes::MARKER_TRIANGLE_DOWN`.
 *
 * Line type for drawing functions corresponding to `cv::MarkerTypes`.
 *
 * See also [OpenCV documents](https://docs.opencv.org/).
 *
 * We don't have a link to the latest `cv::MarkerTypes` document.
 * But we can link to a specific version:
 * [OpenCV 3.4.1's `cv::MarkerTypes`](https://docs.opencv.org/3.4.1/d6/d6e/group__imgproc__draw.html#ga0ad87faebef1039ec957737ecc633b7b).
 *
 * Since 1.0.2
 */
typedef enum {
  GCV_MARKER_TYPE_CROSS = 0,
  GCV_MARKER_TYPE_TILTED_CROSS = 1,
  GCV_MARKER_TYPE_STAR = 2,
  GCV_MARKER_TYPE_DIAMOND = 3,
  GCV_MARKER_TYPE_SQUARE = 4,
  GCV_MARKER_TYPE_TRIANGLE_UP = 5,
  GCV_MARKER_TYPE_TRIANGLE_DOWN = 6
} GCVMarkerType;

#define GCV_TYPE_DRAWING_OPTIONS (gcv_drawing_options_get_type())
G_DECLARE_DERIVABLE_TYPE(GCVDrawingOptions,
                         gcv_drawing_options,
                         GCV,
                         DRAWING_OPTIONS,
                         GObject)

struct _GCVDrawingOptionsClass
{
  GObjectClass parent_class;
};

GCVDrawingOptions *gcv_drawing_options_new(void);

/**********************************************/

/**
 * GCVBorderTypes:
 * @GCV_BORDER_TYPE_BORDER_CONSTANT: See `cv::BorderTypes::BORDER_CONSTANT`.
 * @GCV_BORDER_TYPE_BORDER_REPLICATE : See `cv::BorderTypes::BORDER_REPLICATE `.
 * @GCV_BORDER_TYPE_BORDER_REFLECT : See `cv::BorderTypes::BORDER_REFLECT `.
 * @GCV_BORDER_TYPE_BORDER_WRAP : See `cv::BorderTypes::BORDER_WRAP `.
 * @GCV_BORDER_TYPE_BORDER_REFLECT_101 : See `cv::BorderTypes::BORDER_REFLECT_101 `.
 * @GCV_BORDER_TYPE_BORDER_TRANSPARENT : See `cv::BorderTypes::BORDER_TRANSPARENT `.
 * @GCV_BORDER_TYPE_BORDER_REFLECT101 : See `cv::BorderTypes::BORDER_REFLECT101 `.
 * @GCV_BORDER_TYPE_BORDER_DEFAULT : See `cv::BorderTypes::BORDER_DEFAULT `.
 * @GCV_BORDER_TYPE_BORDER_ISOLATED : See `cv::BorderTypes::BORDER_ISOLATED `.
 *
 * Line type for drawing functions corresponding to `cv::BorderTypes`.
 *
 * See also [OpenCV documents](https://docs.opencv.org/).
 *
 * We don't have a link to the latest `cv::border_types` document.
 * But we can link to a specific version:
 * [OpenCV `cv::border_types`]().
 *
 * Since 1.0.2
 */
typedef enum {
  GCV_BORDER_TYPE_BORDER_CONSTANT = 0,
  GCV_BORDER_TYPE_BORDER_REPLICATE = 1,
  GCV_BORDER_TYPE_BORDER_REFLECT = 2,
  GCV_BORDER_TYPE_BORDER_WRAP = 3,
  GCV_BORDER_TYPE_BORDER_REFLECT_101 = 4,
  GCV_BORDER_TYPE_BORDER_TRANSPARENT = 5,
  GCV_BORDER_TYPE_BORDER_REFLECT101 = 6,
  GCV_BORDER_TYPE_BORDER_DEFAULT = 7,
  GCV_BORDER_TYPE_BORDER_ISOLATED = 8
} GCVBorderType;

#define GCV_TYPE_IMAGE_FILTERING_OPTIONS (gcv_image_filtering_options_get_type())
G_DECLARE_DERIVABLE_TYPE(GCVImageFilteringOptions,
                         gcv_image_filtering_options,
                         GCV,
                         IMAGE_FILTERING_OPTIONS,
                         GObject)

struct _GCVImageFilteringOptionsClass
{
  GObjectClass parent_class;
};

GCVImageFilteringOptions *gcv_image_filtering_options_new(void);


/**********************************************/


/**
 * GCVImageReadFlags:
 * @GCV_IMAGE_READ_FLAG_UNCHANGED: See `cv::IMREAD_UNCHANGED`.
 * @GCV_IMAGE_READ_FLAG_GRAYSCALE: See `cv::IMREAD_GREAYSCALE`.
 * @GCV_IMAGE_READ_FLAG_COLOR: See `cv::IMREAD_COLOR`.
 * @GCV_IMAGE_READ_FLAG_ANY_DEPTH: See `cv::IMREAD_ANYDEPTH`.
 * @GCV_IMAGE_READ_FLAG_ANY_COLOR: See `cv::IMREAD_ANYCOLOR`.
 * @GCV_IMAGE_READ_FLAG_LOAD_GDAL: See `cv::IMREAD_LOAD_GDAL`.
 * @GCV_IMAGE_READ_FLAG_REDUCED_GRAYSCALE_2:
 *   See `cv::IMREAD_REDUCED_GRAYSCALE_2`.
 * @GCV_IMAGE_READ_FLAG_REDUCED_COLOR_2:
 *   See `cv::IMREAD_REDUCED_COLOR_2`.
 * @GCV_IMAGE_READ_FLAG_REDUCED_GRAYSCALE_4:
 *   See `cv::IMREAD_REDUCED_GRAYSCALE_4`.
 * @GCV_IMAGE_READ_FLAG_REDUCED_COLOR_4:
 *   See `cv::IMREAD_REDUCED_COLOR_4`.
 * @GCV_IMAGE_READ_FLAG_REDUCED_GRAYSCALE_8:
 *   See `cv::IMREAD_REDUCED_GRAYSCALE_8`.
 * @GCV_IMAGE_READ_FLAG_REDUCED_COLOR_8:
 *   See `cv::IMREAD_REDUCED_COLOR_8`.
 * @GCV_IMAGE_READ_FLAG_IGNORE_ORIENTATION:
 *   See `cv::IMREAD_IGNORE_ORIENTATION`.
 *
 * They are for gcv_image_read(). You can combine one or more them.
 *
 * They are corresponding to `cv::ImreadModes` values.
 *
 * See also [OpenCV documents](https://docs.opencv.org/).
 *
 * We don't have a link to the latest `cv::ImreadModes` document.
 * But we can link to a specific version:
 * [OpenCV 3.4.1's `cv::ImreadModes`](https://docs.opencv.org/3.4.1/d4/da8/group__imgcodecs.html#ga61d9b0126a3e57d9277ac48327799c80).
 *
 * Since: 1.0.4
 */
typedef enum { /*< flags >*/
  GCV_IMAGE_READ_FLAG_UNCHANGED = -1,
  GCV_IMAGE_READ_FLAG_GRAYSCALE = 0,
  GCV_IMAGE_READ_FLAG_COLOR = 1,
  GCV_IMAGE_READ_FLAG_ANY_DEPTH = 2,
  GCV_IMAGE_READ_FLAG_ANY_COLOR = 4,
  GCV_IMAGE_READ_FLAG_LOAD_GDAL = 8,
  GCV_IMAGE_READ_FLAG_REDUCED_GRAYSCALE_2 = 16,
  GCV_IMAGE_READ_FLAG_REDUCED_COLOR_2 = 17,
  GCV_IMAGE_READ_FLAG_REDUCED_GRAYSCALE_4 = 32,
  GCV_IMAGE_READ_FLAG_REDUCED_COLOR_4 = 33,
  GCV_IMAGE_READ_FLAG_REDUCED_GRAYSCALE_8 = 64,
  GCV_IMAGE_READ_FLAG_REDUCED_COLOR_8 = 65,
  GCV_IMAGE_READ_FLAG_IGNORE_ORIENTATION = 128,
} GCVImageReadFlags;

#define GCV_TYPE_IMAGE (gcv_image_get_type())
G_DECLARE_DERIVABLE_TYPE(GCVImage,
                         gcv_image,
                         GCV,
                         IMAGE,
                         GCVMatrix)
struct _GCVImageClass
{
  GCVMatrixClass parent_class;
};

GCVImage *gcv_image_read(const gchar *filename,
                         GCVImageReadFlags flags,
                         GError **error);
gboolean gcv_image_write(GCVImage *image,
                         const gchar *filename,
                         GError **error);

GCVImage *gcv_image_convert_color(GCVImage *image,
                                  GCVColorConversionCode code);
void gcv_image_draw_arrowed_line(GCVImage *image,
                                 GCVPoint *point1,
                                 GCVPoint *point2,
                                 GCVColor *color,
                                 GCVDrawingOptions *drawing_options);
void gcv_image_draw_circle(GCVImage *image,
                           GCVPoint *center,
                           gint radius,
                           GCVColor *color,
                           GCVDrawingOptions *drawing_options);
void gcv_image_draw_marker(GCVImage *image,
                           GCVPoint *position,
                           GCVColor *color,
                           GCVDrawingOptions *drawing_options);
void gcv_image_draw_ellipse_point(GCVImage *image,
                                  GCVPoint *center,
                                  GCVSize *axes,
                                  gdouble angle,
                                  gdouble start_angle,
                                  gdouble end_angle,
                                  GCVColor *color,
                                  GCVDrawingOptions *drawing_options);
void gcv_image_draw_line(GCVImage *image,
                         GCVPoint *point1,
                         GCVPoint *point2,
                         GCVColor *color,
                         GCVDrawingOptions *drawing_options);
void gcv_image_put_text(GCVImage *image,
                        const gchar *text,
                        GCVPoint *org,
                        GCVHersheyFont font_face,
                        gdouble font_scale,
                        GCVColor *color,
                        GCVDrawingOptions *drawing_options);
void gcv_image_draw_rectangle(GCVImage *image,
                              GCVRectangle *rectangle,
                              GCVColor *color,
                              GCVDrawingOptions *drawing_options);
void gcv_image_draw_rectangle_points(GCVImage *image,
                                     GCVPoint *point1,
                                     GCVPoint *point2,
                                     GCVColor *color,
                                     GCVDrawingOptions *drawing_options);

GCVImage *
gcv_image_abs_diff(GCVImage *image,
                   GCVImage *other_image);

GList *gcv_image_split(GCVImage *image);

GCVImage *gcv_image_median_blur(GCVImage *image,
                                gint ksize,
                                GError **error);

GCVImage *gcv_image_blur(GCVImage *image,
                                GCVSize *ksize,
                                GCVImageFilteringOptions *options,
                                GError **error);
G_END_DECLS
