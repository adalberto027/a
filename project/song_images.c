#include "lcdutils.h"
#include "lcddraw.h"

void drawDefault(u_int colorBGR) {
  clearScreen(colorBGR);
  drawString5x7(10, 15, "The Legend of Zelda", COLOR_GOLD, colorBGR);

  // Find the height and width of the screen
  u_char width = screenWidth, height = screenHeight;

  // Find the location of the top of the tree
  int centerCol = width / 2, centerRow = height / 4;
  int sideLength = 20; // Base width of each section of the tree

  // Draw the tree (three stacked triangles to form a pine tree)
  for (int level = 0; level < 3; level++) {
    int levelRowStart = centerRow + level * sideLength / 2; // Start row for each level
    int levelSideLength = sideLength + level * 10;         // Each level gets wider
    for (int row = 0; row < sideLength / 2; row++) {
      for (int col = -row; col <= row; col++) {
        drawPixel(centerCol + col, levelRowStart + row, COLOR_GREEN);
      }
    }
  }

  // Draw the trunk of the tree
  int trunkWidth = 6, trunkHeight = 10;
  int trunkRowStart = centerRow + sideLength;              // Start of the trunk below the tree
  for (int row = 0; row < trunkHeight; row++) {
    for (int col = -trunkWidth / 2; col <= trunkWidth / 2; col++) {
      drawPixel(centerCol + col, trunkRowStart + row, COLOR_BROWN);
    }
  }
}
