import MovementSystem;

#include <entt/entt.hpp>

import IComponent;
import WorldObject;
import Packet;
import Cell;
import World;
import Packet;
import Position;
import Sender;
import MovementSystem;

MovementSystem::MovementSystem( Cell& cell )
: _cell{ cell }
{
}

void MovementSystem::Update( float deltaTime )
{
    auto view = _cell.view< Position, DestPosition, SenderPtr >();
    for ( auto [ entity, pos, destPos, sender ] : view.each() )
    {
        auto fromPos = pos;
        Position diff;
        diff.x = destPos.x - pos.x;
        diff.y = destPos.y - pos.y;

        auto distance = std::sqrt( diff.x * diff.x + diff.y * diff.y );
        auto moveAcount = 2.0f * deltaTime;
        if ( distance < moveAcount )
            moveAcount = distance;

        auto moveX = diff.x / distance * moveAcount;
        auto moveY = diff.y / distance * moveAcount;
        pos.x += moveX;
        pos.y += moveY;

        /// 도착 여부 검사
        if ( std::abs( pos.x - destPos.x ) < 0.01f && std::abs( pos.y - destPos.y ) < 0.01f )
        {
            /// 도착시 목적지를 변경
            {
                // 임시로 목적지를 변경
                destPos.x += 1.0f;
                destPos.y += 1.0f;
            }
        }

        /// 셀 경계를 벗어낫는지  체크
        /// if ( pos.x < 0.0f || pos.x > 10.0f || pos.y < 0.0f || pos.y > 10.0f )
        {
            /// 셀 경계를 벗어났다면, 다른 셀로 이동
            //_cell.LeaveCell( sender );
            //_cell.EnterCell( sender );
        }

        // 이동 결과 전송
        if ( sender )
        {
            C_Move move{ .fromPos = fromPos, .toPos = pos };
            sender->Send( move );
        }
    }
}
