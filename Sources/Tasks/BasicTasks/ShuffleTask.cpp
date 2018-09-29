#include <Tasks/BasicTasks/ShuffleTask.h>

#include <random>

namespace Hearthstonepp::BasicTasks
{
TaskID ShuffleTask::GetTaskID() const
{
    return TaskID::SHUFFLE;
}

MetaData ShuffleTask::Impl(Player& player1, Player&)
{
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::shuffle(player1.cards.begin(), player1.cards.end(), gen);

    return MetaData::SHUFFLE_SUCCESS;
}
}  // namespace Hearthstonepp::BasicTasks