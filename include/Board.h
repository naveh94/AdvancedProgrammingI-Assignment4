#ifndef BOARD_H
#define BOARD_H

#include "Block.h"

class Board
{
    public:
        /** Default constructor */
        Board(int height, int width);
        /** Default destructor */
        ~Board();

        /** Access height
         * \return The current value of height
         */
        int getHeight() const { return height; }
        /** Access width
         * \return The current value of width
         */
        int getWidth() const { return width; }
        int getMark(int i, int j) const { return this->board[i][j]->getMark(); }
        void setMark(int i, int j, int mark) { this->board[i][j]->setMark(mark); }
        char markToChar(int mark) const;
        friend ostream& operator <<(ostream& out, const Board &bor);
    protected:

    private:
        int height; //!< Member variable "height"
        int width; //!< Member variable "width"
        Block ***board; //!< Member variable "board**"
};

#endif // BOARD_H
