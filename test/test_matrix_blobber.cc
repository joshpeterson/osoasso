#include "../test_harness/test.h"
#include "../include/matrix_blobber.h"
#include "../include/matrix.h"

using namespace osoasso;

Define(MatrixBlobber)
{
    It("Blobs a matrix")
    {
        matrix<double> test_matrix = { { 3.14, 1.0, 3.19 }, { 2.72, 8.9, 5.42 } };
        matrix_blobber<double> blobber;
        blob<double> blob = blobber.make_blob(test_matrix);
        AssertEqual("39e175cf dd17d2d1 c5774db9 780e221a 7af6761c", blob.name());
    } Done
}
