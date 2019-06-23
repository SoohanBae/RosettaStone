// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_MCTS_BOARD_NODE_MAP_IMPL_HPP
#define ROSETTASTONE_TORCH_MCTS_BOARD_NODE_MAP_IMPL_HPP

#include "BoardNodeMap.hpp"
#include "TreeNode.hpp"

#include <memory>
#include <shared_mutex>
#include <unordered_map>

namespace RosettaTorch::MCTS
{
inline TreeNode* BoardNodeMap::GetOrCreateNode(const RosettaStone::Game& game,
                                               bool* newNodeCreated)
{
    const auto boardView = game.CreateView();

    {
        std::shared_lock<RosettaStone::SharedSpinLock> lock(m_mutex);

        if (m_map)
        {
            const auto it = m_map->find(boardView);
            if (it != m_map->end())
            {
                return it->second.get();
            }
        }
    }

    {
        std::lock_guard<RosettaStone::SharedSpinLock> lock(m_mutex);
        auto& item = GetLockedMap()[boardView];
        if (!item)
        {
            item.reset(new TreeNode());

            if (newNodeCreated)
            {
                *newNodeCreated = true;
            }

            return item.get();
        }
    }

    return nullptr;
}
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_MCTS_BOARD_NODE_MAP_IMPL_HPP