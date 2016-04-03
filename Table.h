/*
 * Course ICP @ FIT VUT Brno, 2016
 * ICP 2016 Project - Othello
 *
 * Authors:
 * Pavol Plaskon  - xplask00
 * Matej Postolka - xposto02
 *
 * Unless otherwise stated, all code is licensed under a
 * GNU General Public License v2.0
 *
 */

#include <string>
#include <vector>

class Table
{
  public:
    const int minRows = 4;
    const int minCols = 4;

    enum Stone
    {
      STONE_FREE,
      STONE_BLACK,
      STONE_WHITE
    };
    
    Table(int initRows, int initC1ols);
    void putStone(int row, int col, Stone stone);
    void print();
 
  private:
    
    int rows;
    int cols;
    int blackStones;
    int whiteStones;

    std::vector<Stone> table;

    int getVecIndex(int row, int col);
    bool turnStonesByVector(int x, int y, int startRow, int startCol, Stone ownStone);

};
