#include <opencv-glib/enums.h>
#include <opencv-glib/image.hpp>
#include <opencv-glib/image-error.h>

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

G_END_DECLS

GCVImage *
gcv_image_new_raw(std::shared_ptr<cv::Mat> *cv_matrix)
{
  auto matrix = g_object_new(GCV_TYPE_IMAGE,
                             "matrix", cv_matrix,
                             NULL);
  return GCV_IMAGE(matrix);
}
