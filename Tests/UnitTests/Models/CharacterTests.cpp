// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/TestUtils.hpp>
#include "gtest/gtest.h"

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Models/Character.hpp>

using namespace RosettaStone;
using namespace TestUtils;

TEST(Character, Health)
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.StartGame();
    game.ProcessUntil(Step::MAIN_START);

    Player& curPlayer = game.GetCurrentPlayer();

    auto& curField = curPlayer.GetFieldZone();

    auto card1 = GenerateMinionCard("minion1", 3, 6);
    PlayMinionCard(curPlayer, &card1);
    EXPECT_EQ(curField[0]->GetHealth(), 6);

    curField[0]->SetDamage(2);
    EXPECT_EQ(curField[0]->GetHealth(), 4);

    curField[0]->SetHealth(8);
    EXPECT_EQ(curField[0]->GetDamage(), 0);
    EXPECT_EQ(curField[0]->GetHealth(), 8);

    curField[0]->SetHealth(0);
    EXPECT_EQ(curField[0]->isDestroyed, true);
}

TEST(Character, SpellPower)
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.StartGame();
    game.ProcessUntil(Step::MAIN_START);

    Player& curPlayer = game.GetCurrentPlayer();

    auto& curField = curPlayer.GetFieldZone();

    auto card1 = GenerateMinionCard("minion1", 3, 6);
    PlayMinionCard(curPlayer, &card1);
    EXPECT_EQ(curField[0]->GetSpellPower(), 0);

    curField[0]->SetSpellPower(4);
    EXPECT_EQ(curField[0]->GetSpellPower(), 4);
}