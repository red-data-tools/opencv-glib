#include <opencv-glib/matrix.hpp>

G_BEGIN_DECLS

/**
 * SECTION: matrix
 * @title: Matrix class
 * @include: opencv-glib/opencv-glib.h
 *
 * #GCVMatrix is a matrix class.
 *
 * Since: 1.0.0
 */

typedef struct {
  std::shared_ptr<cv::Mat> matrix;
} GCVMatrixPrivate;

G_DEFINE_TYPE_WITH_PRIVATE(GCVMatrix, gcv_matrix, G_TYPE_OBJECT)

#define GCV_MATRIX_GET_PRIVATE(obj)                     \
  (G_TYPE_INSTANCE_GET_PRIVATE((obj),                   \
                               GCV_TYPE_MATRIX,         \
                               GCVMatrixPrivate))

enum {
  PROP_0,
  PROP_MATRIX
};

static void
gcv_matrix_finalize(GObject *object)
{
  auto priv = GCV_MATRIX_GET_PRIVATE(object);

  priv->matrix = nullptr;

  G_OBJECT_CLASS(gcv_matrix_parent_class)->finalize(object);
}

static void
gcv_matrix_set_property(GObject *object,
                        guint prop_id,
                        const GValue *value,
                        GParamSpec *pspec)
{
  auto priv = GCV_MATRIX_GET_PRIVATE(object);

  switch (prop_id) {
  case PROP_MATRIX:
    priv->matrix =
      *static_cast<std::shared_ptr<cv::Mat> *>(g_value_get_pointer(value));
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
    break;
  }
}

static void
gcv_matrix_init(GCVMatrix *object)
{
}

static void
gcv_matrix_class_init(GCVMatrixClass *klass)
{
  GParamSpec *spec;

  auto gobject_class = G_OBJECT_CLASS(klass);

  gobject_class->finalize     = gcv_matrix_finalize;
  gobject_class->set_property = gcv_matrix_set_property;

  spec = g_param_spec_pointer("matrix",
                              "Matrix",
                              "The raw std::shared<cv::Mat> *",
                              static_cast<GParamFlags>(G_PARAM_WRITABLE |
                                                       G_PARAM_CONSTRUCT_ONLY));
  g_object_class_install_property(gobject_class, PROP_MATRIX, spec);
}

/**
 * gcv_matrix_new:
 *
 * Returns: A newly created empty #GCVMatrix.
 *
 * Since: 1.0.0
 */
GCVMatrix *
gcv_matrix_new(void)
{
  auto cv_matrix = std::make_shared<cv::Mat>();
  return gcv_matrix_new_raw(&cv_matrix);
}

/**
 * gcv_matrix_is_empty:
 * @matrix: A #GCVMatrix
 *
 * Returns: %TRUE if the matrix is empty, %FALSE otherwise.
 *
 * Since: 1.0.0
 */
gboolean
gcv_matrix_is_empty(GCVMatrix *matrix)
{
  auto cv_matrix = gcv_matrix_get_raw(matrix);
  return cv_matrix->empty();
}

/**
 * gcv_matrix_get_bytes:
 * @matrix: A #GCVMatrix
 *
 * Returns: (transfer full): The raw data of the matrix as #GBytes.
 *   The raw data aren't copied. So you can't use the raw data when
 *   the matrix is freed.
 *
 * Since: 1.0.0
 */
GBytes *
gcv_matrix_get_bytes(GCVMatrix *matrix)
{
  auto cv_matrix = gcv_matrix_get_raw(matrix);
  return g_bytes_new_static(cv_matrix->ptr(),
                            cv_matrix->elemSize() * cv_matrix->total());
}

G_END_DECLS

GCVMatrix *
gcv_matrix_new_raw(std::shared_ptr<cv::Mat> *cv_matrix)
{
  auto matrix = g_object_new(GCV_TYPE_MATRIX,
                             "matrix", cv_matrix,
                             NULL);
  return GCV_MATRIX(matrix);
}

std::shared_ptr<cv::Mat>
gcv_matrix_get_raw(GCVMatrix *matrix)
{
  auto priv = GCV_MATRIX_GET_PRIVATE(matrix);
  return priv->matrix;
}
