#include "lcdutils.h"
#include "lcddraw.h"

void drawDefault(u_int colorBGR) {
  // Clear the screen with a festive background color
  clearScreen(colorBGR);
  
  // Draw a festive title at the top
  drawString5x7(10, 10, "Jingle Bells", COLOR_WHITE, colorBGR);
  
  // Get the screen dimensions
  u_char width = screenWidth, height = screenHeight;

  // Draw a Christmas tree at the center of the screen
  int centerCol = width / 2, centerRow = height / 4;
  int treeHeight = 30;  // Height of the tree

  // Draw the main triangle of the tree
  for (int row = 0; row < treeHeight; row++) {
    for (int col = -row; col <= row; col++) {
      drawPixel(centerCol + col, centerRow + row, COLOR_GREEN);
    }
  }

  // Draw the trunk of the tree
  int trunkHeight = 10, trunkWidth = 6;
  for (int row = 0; row < trunkHeight; row++) {
    for (int col = -trunkWidth / 2; col <= trunkWidth / 2; col++) {
      drawPixel(centerCol + col, centerRow + treeHeight + row, COLOR_BROWN);
    }
  }

  // Draw a decoration at the top of the tree (star)
  drawPixel(centerCol, centerRow - 1, COLOR_YELLOW);
  drawPixel(centerCol - 1, centerRow, COLOR_YELLOW);
  drawPixel(centerCol + 1, centerRow, COLOR_YELLOW);
  drawPixel(centerCol, centerRow + 1, COLOR_YELLOW);
}
