/*****************************************************************************
 * Copyright (c) 2014-2020 OpenRCT2 developers
 *
 * For a complete list of all authors, please refer to contributors.md
 * Interested in contributing? Visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is licensed under the GNU General Public License version 3.
 *****************************************************************************/

#pragma once

#include "../network/network.h"
#include "GameAction.h"

DEFINE_GAME_ACTION(PlayerKickAction, GAME_COMMAND_KICK_PLAYER, GameActions::Result)
{
private:
    NetworkPlayerId_t _playerId{ -1 };

public:
    PlayerKickAction() = default;

    PlayerKickAction(NetworkPlayerId_t playerId)
        : _playerId(playerId)
    {
    }

    uint16_t GetActionFlags() const override
    {
        return GameAction::GetActionFlags() | GameActions::Flags::AllowWhilePaused;
    }

    void Serialise(DataSerialiser & stream) override
    {
        GameAction::Serialise(stream);

        stream << DS_TAG(_playerId);
    }
    GameActions::Result::Ptr Query() const override
    {
        return network_kick_player(_playerId, false);
    }

    GameActions::Result::Ptr Execute() const override
    {
        return network_kick_player(_playerId, true);
    }
};
