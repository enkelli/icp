/*
 * Course ICP @ FIT VUT Brno, 2016
 * ICP 2016 Project - Othello
 *
 * @author Plaskon Pavol, xplask00@stud.fit.vutbr.cz
 * @author Postolka Matej, xposto02@stud.fit.vutbr.cz
 *
 * @brief A representation of Othello table.
 * @file table.h
 *
 * Unless otherwise stated, all code is licensed under a
 * GNU General Public License v2.0
 *
 */

#include <string>
#include <vector>

/* 
 * @brief A representation of Othello table.
 */
class Table
{
  public:
    /// Representation of the black stone on the table.
    static const std::string CLI_BLACK_STONE;
    /// Representation of the white stone on the table.
    static const std::string CLI_WHITE_STONE;

    enum class Stone
    {
      FREE,
      BLACK,
      WHITE
    };

  public:    
    Table(); 
    Table(int initRows, int initCols);

    void putStone(int row, int col, Stone stone);
    void print() const;

  private: 
    int getVecIndex(int row, int col) const;
    bool turnStonesByVector(int x, int y, int startRow, int startCol, Stone ownStone);

  private:
    /// Rows count.
    int rows;
    /// Columns count.
    int cols;
    /// Count of black stones on the table.
    int blackStones;
    /// Count of white stones on the table.
    int whiteStones;

    std::vector<Stone> table;
    
    /// @name Table constants.
    /// @{
    static const int minRows = 4;
    static const int minCols = 4;
    static const int defaultRows = 8;
    static const int defaultCols = 8;
    /// @}

};
