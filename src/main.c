// Standard Headers
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// CE Toolchain Headers
#include <graphx.h>
#include <keypadc.h>
#include <tice.h>

// Representation of a complex number
typedef struct {
  double r;
  double i;
} complex_t;

// Scale between pixel coordinates and real graphed values
#define SCALE 20
#define CX LCD_WIDTH / 2
#define CY LCD_HEIGHT / 2

// Nice set of default colors
const uint16_t colors[10] = {
    gfx_RGBTo1555(45, 181, 0),   gfx_RGBTo1555(247, 244, 54),
    gfx_RGBTo1555(0, 181, 147),  gfx_RGBTo1555(114, 0, 229),
    gfx_RGBTo1555(229, 0, 185),  gfx_RGBTo1555(141, 229, 0),
    gfx_RGBTo1555(229, 0, 91),   gfx_RGBTo1555(0, 181, 255),
    gfx_RGBTo1555(252, 120, 32), gfx_RGBTo1555(0, 0, 0)};

// Distance between two complex numbers
double distance(complex_t, complex_t);

void renderPixel(int x, int y, int iter, complex_t roots[], int numRoots) {
  // First, we need to offset global x y from the center
  double realX, realY;
  realX = x - CX;
  realY = y - CY;
  // We then scale values to fit in a nicer size
  realX /= SCALE;
  // Y also needs to be flipped
  realY /= -1.0 * SCALE;

  complex_t pixel = {realX, realY};

  // First demo is just using 0 iterations and finding closest root
  int closestRoot = 0;
  double minDist = distance(pixel, roots[0]);
  double newDist;
  int i;
  for (i = 1; i < numRoots; ++i) {
    newDist = distance(pixel, roots[i]);
    if (newDist < minDist) {
        closestRoot = i;
        minDist = newDist;
    }
  }
  gfx_SetColor(colors[closestRoot]);
  // The physical pixel location is still the passed-in x y
  gfx_SetPixel(x, y);
}

int main(void) {
  complex_t root_0 = {-4, 3};
  complex_t root_1 = {0, -4};
  complex_t root_2 = {5, 5};
  complex_t roots[10] = {root_0, root_1, root_2};
  uint8_t numRoots = 3;
  gfx_Begin();
  gfx_FillScreen(0);
  for (int x = 0; x < LCD_WIDTH; ++x) {
    for (int y = 0; y < LCD_HEIGHT; ++y) {
        renderPixel(x, y, 0, roots, numRoots);
    }
  }

  while (!os_GetCSC()) {
  }

  gfx_End();
  return 0;
}

double distance(complex_t n1, complex_t n2) {
  return sqrt(pow(n1.r - n2.r, 2) + pow(n1.i - n2.i, 2));
}