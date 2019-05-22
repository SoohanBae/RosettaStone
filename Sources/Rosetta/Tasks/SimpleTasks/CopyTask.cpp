// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/CopyTask.hpp>
#include "Rosetta/Cards/Cards.hpp"

namespace RosettaStone::SimpleTasks
{
CopyTask::CopyTask(EntityType entityType, int amount, bool isOpposite,
                   ZoneType zoneType)
    : ITask(entityType),
      m_amount(amount),
      m_isOpposite(isOpposite),
      m_zoneType(zoneType)
{
    // Do nothing
}

TaskID CopyTask::GetTaskID() const
{
    return TaskID::COPY;
}

TaskStatus CopyTask::Impl(Player& player)
{
    std::vector<Entity*> result;

    switch (m_entityType)
    {
        case EntityType::STACK:
        {
            IZone* zone = m_isOpposite ? GetZone(*player.opponent, m_zoneType)
                                       : GetZone(player, m_zoneType);

            for (auto& entity : player.GetGame()->taskStack.entities)
            {
                if (zone != nullptr && zone->IsFull())
                {
                    break;
                }

                for (int i = 0; i < m_amount; ++i)
                {
                    if (zone != nullptr && zone->IsFull())
                    {
                        break;
                    }

                    auto card =
                        Cards::GetInstance().FindCardByID(entity->card.id);

                    result.emplace_back(
                        m_isOpposite
                            ? Entity::GetFromCard(*player.opponent,
                                                  std::move(card), std::nullopt,
                                                  zone)
                            : Entity::GetFromCard(player, std::move(card),
                                                  std::nullopt, zone));
                }
            }
            break;
        }
        default:
            throw std::invalid_argument(
                "CopyTask::Impl() - Invalid entity type");
    }

    player.GetGame()->taskStack.entities = result;

    return TaskStatus::COMPLETE;
}

IZone* CopyTask::GetZone(Player& player, ZoneType zoneType)
{
    switch (zoneType)
    {
        case ZoneType::PLAY:
            return &player.GetFieldZone();
        case ZoneType::DECK:
            return &player.GetDeckZone();
        case ZoneType::HAND:
            return &player.GetHandZone();
        case ZoneType::GRAVEYARD:
            return &player.GetGraveyardZone();
        case ZoneType::SETASIDE:
            return &player.GetSetasideZone();
        case ZoneType::SECRET:
            return &player.GetSecretZone();
        case ZoneType::INVALID:
        case ZoneType::REMOVEDFROMGAME:
            return nullptr;
    }

    return nullptr;
}
}  // namespace RosettaStone::SimpleTasks
