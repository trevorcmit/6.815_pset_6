#include "homography.h"
#include "matrix.h"

using namespace std;

void applyHomography(const Image &source, const Matrix &H, Image &out,
                     bool bilinear) {
  // --------- HANDOUT  PS06 ------------------------------
  // Transform image source using the homography H, and composite in onto out.
  // if bilinear == true, using bilinear interpolation. Use nearest neighbor
  // otherwise.

  Matrix H_inv = H.inverse(); // Find inverse of H to use for calculations

  for (int h; h < out.height(); h++) {
    for (int w; w < out.width(); w++) {

      Matrix coords(3, 1); // create column matrix [x' y' 1]
      coords(0, 0) = w;
      coords(1, 0) = h;
      coords(2, 0) = 1;

      Matrix xyw_prime = H_inv * coords; // Multiply H^-1 times output column matrix

      float x_prime = xyw_prime(0, 0) / xyw_prime(2, 0); // x'/w'
      float y_prime = xyw_prime(1, 0) / xyw_prime(2, 0); // y'/w'

      if ((x_prime < source.width() && x_prime > 0) &&   // Check bounds, only utilize if valid in source image
          (y_prime < source.height() && y_prime > 0)) {
        
        for (int c; c < out.channels(); c++) {
          if (bilinear) {
            out(w, h, c) = interpolateLin(source, x_prime, y_prime, c); // If True use bilinear
          }
          else {
            out(w, h, c) = source(round(x_prime), round(y_prime), c); // Else nearest neighbor by rounding
          }
        }
      }
    }
  }
}

Matrix computeHomography(const CorrespondencePair correspondences[4]) {
  // --------- HANDOUT  PS06 ------------------------------
  // Compute a homography from 4 point correspondences.

  Matrix output(3, 3);


  return output
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
