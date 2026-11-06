#include <cstdint>
#include <string>

#define HEIGHT 6
#define WIDTH  7

enum Player { O, X };

/// Reference : https://github.com/denkspuren/BitboardC4/blob/master/BitboardDesign.md
/// Dimensions : W=7 * H=6
///
/// ^    6 13 20 27 34 41 48   55 62     Additional row
/// |  +---------------------+ 
/// |  | 5 12 19 26 33 40 47 | 54 61     top row
/// |  | 4 11 18 25 32 39 46 | 53 60
/// |  | 3 10 17 24 31 38 45 | 52 59
/// |  | 2  9 16 23 30 37 44 | 51 58
/// |  | 1  8 15 22 29 36 43 | 50 57
/// |  | 0  7 14 21 28 35 42 | 49 56 63  bottom row
/// |  +---------------------+
/// 0----------------------------------->
/// 63 62 61 60 ... 48 47 46 45 ... 3 2 1 0
class Game
{
    public:
        Game();

        void display();
        std::string toString();

        /// Returns the one-hot mask for (x, y); y=6 is the sentinel row.
        /// Returns 0 for coordinates outside the 7x7 bitboard layout.
        uint64_t bitAt(int x, int y);

        /// Make a move. As the counter is initialized to 0,
        /// player O starts.
        void play(int column);
        void undo(int column);

        bool hasWin(uint64_t bitboard);
        bool isColumnFull(int column);
        int64_t getColumn(int column);

        int64_t getBoardO();
        int64_t getBoardX();

    private:
        void switchPlayer();
        /// Get the pointer to the current board
        /// so the game engine can directly edit the board.
        uint64_t* getCurrentBoard();

        int heights[8] = { 0, 7, 14, 21, 28, 35, 42, 49 };
        int originalHeights[8] = { 0, 7, 14, 21, 28, 35, 42, 49 };
        uint64_t counter = 0;
        uint64_t boardO = 0;
        uint64_t boardX = 0;
};
