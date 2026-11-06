#include "../include/googletest/googletest/include/gtest/gtest.h"
#include "engine.hpp"

TEST(EngineTest, MakeMove) {
    Game game;
    game.play(0);
    game.play(1);
    game.play(0);

    EXPECT_NE(0, game.getBoardO() & game.bitAt(0, 0));
    EXPECT_NE(0, game.getBoardO() & game.bitAt(0, 1));
    EXPECT_NE(0, game.getBoardX() & game.bitAt(1, 0));
}

TEST(EngineTest, MakeMoveOOB) {
    Game game;
    game.play(7);
    game.play(99);
    game.play(-30);

    EXPECT_EQ(0, game.getBoardO() | game.getBoardX());
}

TEST(EngineTest, UndoMoveEmptyColumn) {
    Game game;
    game.play(0);
    game.undo(0);
    game.undo(0);
    game.undo(0);
    game.undo(0);
    game.play(0);

    EXPECT_EQ(0, game.getBoardO() & game.bitAt(0, 0));
}

TEST(EngineTest, UndoMove) {
    Game game;
    game.play(0);
    game.play(0);
    game.undo(0);
    game.play(0);

    EXPECT_NE(0, game.getBoardO() & game.bitAt(0, 0));
    EXPECT_NE(0, game.getBoardX() & game.bitAt(0, 1));
}

TEST(EngineTest, TestColumnFull) {
    Game game;
    game.play(0);
    game.play(0);
    game.play(0);
    game.play(0);
    game.play(0);
    game.play(0);
    // Bogus play
    game.play(0);

    auto c = game.getColumn(0);
    EXPECT_TRUE(c <= ((1 << 6) - 1));

    EXPECT_TRUE(game.isColumnFull(0));
    game.undo(0);
    EXPECT_FALSE(game.isColumnFull(0));
}

TEST(EngineTest, MakeMoveFullColumn) {
    Game game;
    game.play(0);
    game.play(0);
    game.play(0);
    game.play(0);
    game.play(0);
    game.play(0);

    // Bogus move
    game.play(0);
    game.play(0);

    EXPECT_NE(0, game.getBoardX() & game.bitAt(0, 5));
    EXPECT_EQ(0, game.getBoardX() & game.bitAt(1, 0));
}

TEST(EngineTest, CheckWinColumn) {
    Game game;
    game.play(0);
    game.play(1);
    game.play(0);
    game.play(1);
    game.play(0);
    game.play(1);
    game.play(0);

    EXPECT_TRUE(game.hasWin(game.getBoardO()));
}

TEST(EngineTest, CheckWinRow) {
    Game game;
    game.play(0);
    game.play(0);
    game.play(1);
    game.play(1);
    game.play(2);
    game.play(2);
    game.play(3);

    EXPECT_TRUE(game.hasWin(game.getBoardO()));
}

TEST(EngineTest, CheckWinDiagnoal1) {
    Game game;
    game.play(0);
    game.play(1);
    game.play(1);

    game.play(2);
    game.play(2);
    game.play(0);
    game.play(2);

    game.play(3);
    game.play(3);
    game.play(3);
    game.play(3);

    EXPECT_TRUE(game.hasWin(game.getBoardO()));
}
