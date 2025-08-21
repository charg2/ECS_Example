import MovementSystem;

#include <entt/entt.hpp>

import World;
import IComponent;
import Position;
import Sender;
import WorldObject;
import Packet;

MovementSystem::MovementSystem( Cell& cell )
: _cell{ cell }
{
}


void MovementSystem::Update( float deltaTime )
{
    auto view = _cell.view< Position, const DestPosition, const Velocity, SenderPtr >();
    for ( auto [ entity, pos, destPos, vel, sender ] : view.each() )
    {
        auto fromPos = pos;

        pos.x += vel.x * deltaTime;
        pos.y += vel.y * deltaTime;
        if ( pos.x >= destPos.x && pos.y >= destPos.y )
            std::cout << "µµÂø" << pos.x << ", " << pos.y << std::endl;

        if ( sender )
        {
            C_Move move{ .fromPos = fromPos, .toPos = pos };
            sender->Send( move );
        }
    }
}
