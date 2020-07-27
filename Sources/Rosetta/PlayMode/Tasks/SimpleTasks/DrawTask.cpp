// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/Actions/Draw.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/DrawTask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
DrawTask::DrawTask(int amount, bool toStack)
    : m_amount(amount), m_toStack(toStack)
{
    // Do nothing
}

TaskStatus DrawTask::Impl(Player* player)
{
    std::vector<Playable*> cards;

    for (int i = 0; i < m_amount; ++i)
    {
        Playable* card = Generic::Draw(player, nullptr);
        cards.emplace_back(card);
    }

    if (cards.empty() || cards.at(0) == nullptr)
    {
        return TaskStatus::COMPLETE;
    }

    if (m_toStack)
    {
        for (auto& card : cards)
        {
            player->game->taskStack.playables.emplace_back(card);
        }
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> DrawTask::CloneImpl()
{
    return std::make_unique<DrawTask>(m_amount, m_toStack);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks