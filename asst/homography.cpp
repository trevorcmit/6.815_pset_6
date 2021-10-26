#include "homography.h"
#include "matrix.h"

using namespace std;

void applyHomography(const Image &source, const Matrix &H, Image &out, bool bilinear) {
  // --------- HANDOUT  PS06 ------------------------------
  // Transform image source using the homography H, and composite in onto out.
  // if bilinear == true, using bilinear interpolation. Use nearest neighbor
  // otherwise.
  Matrix H_inv = H.inverse(); // Find inverse of H to use for calculations

  for (int h = 0; h < out.height(); h++) {
    for (int w = 0; w < out.width(); w++) {

      Matrix coords = Matrix::Zero(3, 1); // create column matrix [x y 1]
      coords << w, h, 1;

      Matrix xyw_prime = H_inv * coords; // Multiply H^-1 times output column matrix

      float x_prime = xyw_prime(0, 0) / xyw_prime(2, 0); // x'/w'
      float y_prime = xyw_prime(1, 0) / xyw_prime(2, 0); // y'/w'

      if ((x_prime < source.width() && x_prime > 0) &&   // Check bounds, only utilize if valid in source image
          (y_prime < source.height() && y_prime > 0)) {
        
        for (int c = 0; c < out.channels(); c++) { // Iterate for all channels, coords are the same
          if (bilinear) {
            out(w, h, c) = interpolateLin(source, x_prime, y_prime, c, true); // If True use bilinear
          }
          else {
            out(w, h, c) = source.smartAccessor(round(x_prime), round(y_prime), c, true);
          }
        }
      }
    }
  }
}

Matrix computeHomography(const CorrespondencePair correspondences[4]) {
  // --------- HANDOUT  PS06 ------------------------------
  // Compute a homography from 4 point correspondences.
	Matrix A(8, 8);
	Matrix B(8, 1);

  for (int n = 0; n < 4; n++) {
    B(2*n)   = correspondences[n].point2[0];
    B(2*n+1) = correspondences[n].point2[1];

    A(2*n, 0) = correspondences[n].point1[0];
    A(2*n, 1) = correspondences[n].point1[1];
    A(2*n, 2) = correspondences[n].point1[2];
    A(2*n, 3) = 0;
    A(2*n, 4) = 0;
    A(2*n, 5) = 0;
    A(2*n, 6) = -correspondences[n].point1[0]*correspondences[n].point2[0];
    A(2*n, 7) = -correspondences[n].point1[1]*correspondences[n].point2[0];
    A(2*n+1, 0) = 0;
    A(2*n+1, 1) = 0;
    A(2*n+1, 2) = 0;
    A(2*n+1, 3) = correspondences[n].point1[0];
    A(2*n+1, 4) = correspondences[n].point1[1];
    A(2*n+1, 5) = correspondences[n].point1[2];
    A(2*n+1, 6) = -correspondences[n].point1[0]*correspondences[n].point2[1];
    A(2*n+1, 7) = -correspondences[n].point1[1]*correspondences[n].point2[1];
  }

  Matrix x(8, 1);      // Initialize column vector for x
	x = A.inverse() * B; // Solving Ax = b
  Matrix output(3, 3); // Turn x into a 3x3 matrix
	output << x(0, 0), x(1, 0), x(2, 0), x(3, 0), x(4, 0), x(5, 0), x(6, 0), x(7, 0), 1;
  return output;
}

BoundingBox computeTransformedBBox(int imwidth, int imheight, Matrix H) {
  // --------- HANDOUT  PS06 ------------------------------
  // Predict the bounding boxes that encompasses all the transformed
  // coordinates for pixels frow and Image with size (imwidth, imheight)
  return BoundingBox(0, 0, 0, 0);
}

BoundingBox bboxUnion(BoundingBox B1, BoundingBox B2) {
  // --------- HANDOUT  PS06 ------------------------------
  // Compute the bounding box that tightly bounds the union of B1 an B2.
  return BoundingBox(0, 0, 0, 0);
}

Matrix makeTranslation(BoundingBox B) {
  // --------- HANDOUT  PS06 ------------------------------
  // Compute a translation matrix (as a homography matrix) that translates the
  // top-left corner of B to (0,0).
  return Matrix::Zero(3, 3);
}

Image stitch(const Image &im1, const Image &im2,
             const CorrespondencePair correspondences[4]) {
  // --------- HANDOUT  PS06 ------------------------------
  // Transform im1 to align with im2 according to the set of correspondences.
  // make sure the union of the bounding boxes for im2 and transformed_im1 is
  // translated properly (use makeTranslation)
  return im1;
}

// debug-useful
Image drawBoundingBox(const Image &im, BoundingBox bbox) {
  // --------- HANDOUT  PS06 ------------------------------
  /*
    ________________________________________
   / Draw me a bounding box!                \
   |                                        |
   | "I jumped to my                        |
   | feet, completely thunderstruck. I      |
   | blinked my eyes hard. I looked         |
   | carefully all around me. And I saw a   |
   | most extraordinary small person, who   |
   | stood there examining me with great    |
   | seriousness."                          |
   \              Antoine de Saint-Exupery  /
    ----------------------------------------
           \   ^__^
            \  (oo)\_______
               (__)\       )\/\
                   ||----w |
                   ||     ||
  */
  return im;
}

void applyHomographyFast(const Image &source, const Matrix &H, Image &out, bool bilinear) {
  // --------- HANDOUT  PS06 ------------------------------
  // Same as apply but change only the pixels of out that are within the
  // predicted bounding box (when H maps source to its new position).
}
