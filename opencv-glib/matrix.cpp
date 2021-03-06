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

#define GCV_MATRIX_GET_PRIVATE(object)          \
  static_cast<GCVMatrixPrivate *>(              \
    gcv_matrix_get_instance_private(            \
      GCV_MATRIX(object)))

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
 * gcv_matrix_clone:
 * @matrix: A #GCVMatrix
 *
 * Returns: (transfer full): A cloned #GCVMatrix. Data is also copied.
 *
 * Since: 1.0.0
 */
GCVMatrix *
gcv_matrix_clone(GCVMatrix *matrix)
{
  auto cv_matrix = gcv_matrix_get_raw(matrix);
  auto cv_cloned_matrix_raw = cv_matrix->clone();
  auto cv_cloned_matrix = std::make_shared<cv::Mat>(cv_cloned_matrix_raw);
  auto cloned_matrix = g_object_new(G_OBJECT_TYPE(matrix),
                                    "matrix", &cv_cloned_matrix,
                                    NULL);
  return GCV_MATRIX(cloned_matrix);
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

/**
 * gcv_matrix_get_element_size:
 * @matrix: A #GCVMatrix
 *
 * Returns: The element size of the matrix in bytes. An element contains
 *  N channels. So the element size is `channel size * N`.
 *
 * Since: 1.0.0
 */
gsize
gcv_matrix_get_element_size(GCVMatrix *matrix)
{
  auto cv_matrix = gcv_matrix_get_raw(matrix);
  return cv_matrix->elemSize();
}

/**
 * gcv_matrix_get_channel_size:
 * @matrix: A #GCVMatrix
 *
 * Returns: The channel size of the matrix in bytes.
 *
 * Since: 1.0.0
 */
gsize
gcv_matrix_get_channel_size(GCVMatrix *matrix)
{
  auto cv_matrix = gcv_matrix_get_raw(matrix);
  return cv_matrix->elemSize1();
}

/**
 * gcv_matrix_get_n_channels:
 * @matrix: A #GCVMatrix
 *
 * Returns: The number of channels of the matrix in bytes.
 *
 * Since: 1.0.0
 */
gint
gcv_matrix_get_n_channels(GCVMatrix *matrix)
{
  auto cv_matrix = gcv_matrix_get_raw(matrix);
  return cv_matrix->channels();
}

/**
 * gcv_matrix_get_n_rows:
 * @matrix: A #GCVMatrix
 *
 * Returns: The number of rows of the matrix in bytes.
 *
 * Since: 1.0.0
 */
gint
gcv_matrix_get_n_rows(GCVMatrix *matrix)
{
  auto cv_matrix = gcv_matrix_get_raw(matrix);
  return cv_matrix->rows;
}

/**
 * gcv_matrix_get_n_columns:
 * @matrix: A #GCVMatrix
 *
 * Returns: The number of columns of the matrix in bytes.
 *
 * Since: 1.0.0
 */
gint
gcv_matrix_get_n_columns(GCVMatrix *matrix)
{
  auto cv_matrix = gcv_matrix_get_raw(matrix);
  return cv_matrix->cols;
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
