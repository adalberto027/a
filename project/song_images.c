#include "lcdutils.h"
#include "lcddraw.h"

void drawDefault(u_int colorBGR) {
  // Clear the screen with a festive background color
  clearScreen(colorBGR);
  
  // Draw a festive title at the top
  drawString5x7(10, 15, "Merry Christmas", COLOR_WHITE, colorBGR);
  
  // Get the screen dimensions
  u_char width = screenWidth, height = screenHeight;

  // Find the location of the top of the tree
  int centerCol = width / 2, centerRow = height / 4;
  int treeHeight = 40; // Height of the tree

  // Draw the main part of the tree (a large green triangle)
  for (int row = 0; row < treeHeight; row++) {
    for (int col = -row; col <= row; col++) {
      drawPixel(centerCol + col, centerRow + row, COLOR_GREEN);
    }
  }

  // Draw the tree trunk (a small brown rectangle)
  int trunkHeight = 10, trunkWidth = 6;
  int trunkCenterRow = centerRow + treeHeight;
  for (int row = 0; row < trunkHeight; row++) {
    for (int col = -trunkWidth / 2; col <= trunkWidth / 2; col++) {
      drawPixel(centerCol + col, trunkCenterRow + row, COLOR_BROWN);
    }
  }
}
