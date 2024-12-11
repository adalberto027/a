#include "lcdutils.h"
#include "lcddraw.h"

void drawDefault(u_int colorBGR) {
  clearScreen(colorBGR);
  drawString5x7(10, 15, "Merry Christmas!", COLOR_WHITE, colorBGR);
  
  // Find the height and width of the screen
  u_char width = screenWidth, height = screenHeight;

  // Define the location and dimensions of the tree
  int centerCol = width / 2, centerRow = height / 4;
  int treeHeight = 40; // Height of the tree

  // Draw the tree (a large green triangle with decorations)
  for (int row = 0; row < treeHeight; row++) {
    for (int col = -row; col <= row; col++) {
      if (row % 6 == 0 && col % 3 == 0) { 
        // Add decorations in random positions
        drawPixel(centerCol + col, centerRow + row, COLOR_RED);  // Red lights
      } else {
        drawPixel(centerCol + col, centerRow + row, COLOR_GREEN);  // Tree body
      }
    }
  }

  // Draw the trunk of the tree (a small brown rectangle)
  int trunkHeight = 10, trunkWidth = 6;
  int trunkRowStart = centerRow + treeHeight;
  for (int row = 0; row < trunkHeight; row++) {
    for (int col = -trunkWidth / 2; col <= trunkWidth / 2; col++) {
      drawPixel(centerCol + col, trunkRowStart + row, COLOR_BROWN);
    }
  }

  // Draw a star at the top of the tree (a small yellow cross)
  drawPixel(centerCol, centerRow - 1, COLOR_YELLOW);
  drawPixel(centerCol - 1, centerRow, COLOR_YELLOW);
  drawPixel(centerCol + 1, centerRow, COLOR_YELLOW);
  drawPixel(centerCol, centerRow + 1, COLOR_YELLOW);

  // Draw a gift box next to the tree
  int giftColStart = centerCol + treeHeight / 2 + 10;  // Position to the right of the tree
  int giftRowStart = centerRow + treeHeight - 5;       // Align with the base of the tree
  int giftWidth = 14, giftHeight = 10;

  // Draw the box
  for (int row = 0; row < giftHeight; row++) {
    for (int col = 0; col < giftWidth; col++) {
      drawPixel(giftColStart + col, giftRowStart + row, COLOR_RED);  // Box body
    }
  }

  // Draw the ribbon on the box
  for (int row = 0; row < giftHeight; row++) {
    drawPixel(giftColStart + giftWidth / 2, giftRowStart + row, COLOR_YELLOW);  // Vertical ribbon
  }
  for (int col = 0; col < giftWidth; col++) {
    drawPixel(giftColStart + col, giftRowStart + giftHeight / 2, COLOR_YELLOW);  // Horizontal ribbon
  }
}
