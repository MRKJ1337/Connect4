#include "engine.hpp"

#include <math.h>
#include <cstdint>
#include <iostream>
#include <sstream>

Game::Game() {

}

uint64_t* Game::getCurrentBoard() {
    if((this->counter & 1) == 0) {
        return &this->boardO;
    } else {
        return &this->boardX;
    }
}

void Game::play(int column) {
    if(0 <= column && column < 7) {
        if (this->heights[column] < this->originalHeights[column + 1] - 1) {
            uint64_t move = uint64_t{1} << this->heights[column];
            auto cb = this->getCurrentBoard();
            *cb ^= move;

            this->heights[column]++;
            this->counter++;
        }
    }
}

void Game::undo(int column) {
    if(0 <= column && column < 7) {
        if(this->heights[column] > this->originalHeights[column] - 1) {
            this->counter--;

            uint64_t move = uint64_t{1} << --this->heights[column];
            auto cb = this->getCurrentBoard();
            *cb ^= move;
        }
    }
}

int64_t Game::getBoardO() {
    return this->boardO;
}

int64_t Game::getBoardX() {
    return this->boardX;
}

void Game::display() {
    std::cout << this->toString();
}

int64_t Game::getColumn(int column) {
    uint64_t bitboard = this->getBoardO() | this->getBoardX();
    auto c = (bitboard >> (column * 7));
    uint64_t cMask = (1 << (6 + 1)) - 1;
    return c & cMask;
}

bool Game::isColumnFull(int column) {
    auto c = this->getColumn(column);
    uint64_t cMask = (1 << 6) - 1;
    return c == cMask;
}

bool Game::hasWin(uint64_t bitboard) {
    if (bitboard & (bitboard >> 6) & (bitboard >> 12) & (bitboard >> 18) != 0) return true; // diagonal
    if (bitboard & (bitboard >> 8) & (bitboard >> 16) & (bitboard >> 24) != 0) return true; // diagonal
    if (bitboard & (bitboard >> 7) & (bitboard >> 14) & (bitboard >> 21) != 0) return true; // horizontal
    if (bitboard & (bitboard >> 1) & (bitboard >>  2) & (bitboard >>  3) != 0) return true; // vertical
    return false;
}

std::string Game::toString() {
    std::ostringstream buffer;
    for (int row = 5; row >= 0; --row) {
        buffer << '|';
        for (int column = 0; column < 7; ++column) {
            uint64_t mask = this->bitAt(column, row);
            const char piece = (this->boardO & mask) ? 'O'
                             : (this->boardX & mask) ? 'X'
                                                     : ' ';
            buffer << ' ' << piece << " |";
        }
        buffer << '\n';
    }

    buffer << "+---+---+---+---+---+---+---+\n"
           << "  0   1   2   3   4   5   6\n";
    return buffer.str();
}

uint64_t Game::bitAt(int x, int y) {
    if (x < 0 || x >= 7 || y < 0 || y > 6) {
        return 0;
    }

    return uint64_t{1} << (x * 7 + y);
}
