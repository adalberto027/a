#include "lcdutils.h"
#include "lcddraw.h"

void drawDefault(u_int colorBGR) {
  // Clear the screen with a festive background color
  clearScreen(colorBGR);
  
  // Draw a festive title at the top
  drawString5x7(10, 15, "Merry Christmas", COLOR_WHITE, colorBGR);
  
  // Get the screen dimensions
  u_char width = screenWidth, height = screenHeight;

  // Find the location for the top triangle (tree top)
  int centerCol = width / 2, centerRow = height / 4;
  int sideLength = 20; // Side length of each triangle

  // Draw the top triangle (tree top)
  for (int row = 0; row < sideLength; row++) {
    for (int col = -row; col <= row; col++) {
      drawPixel(centerCol + col, centerRow + row, COLOR_GREEN);
    }
  }

  // Draw the bottom-left triangle (left side of the tree)
  int leftCenterCol = centerCol - sideLength;
  int leftCenterRow = centerRow + sideLength;
  for (int row = 0; row < sideLength; row++) {
    for (int col = -row; col <= row; col++) {
      drawPixel(leftCenterCol + col, leftCenterRow + row, COLOR_GREEN);
    }
  }

  // Draw the bottom-right triangle (right side of the tree)
  int rightCenterCol = centerCol + sideLength;
  int rightCenterRow = centerRow + sideLength;
  for (int row = 0; row < sideLength; row++) {
    for (int col = -row; col <= row; col++) {
      drawPixel(rightCenterCol + col, rightCenterRow + row, COLOR_GREEN);
    }
  }

  // Draw the tree trunk
  int trunkHeight = 10, trunkWidth = 6;
  int trunkCenterRow = centerRow + 2 * sideLength;
  for (int row = 0; row < trunkHeight; row++) {
    for (int col = -trunkWidth / 2; col <= trunkWidth / 2; col++) {
      drawPixel(centerCol + col, trunkCenterRow + row, COLOR_BROWN);
    }
  }
}
