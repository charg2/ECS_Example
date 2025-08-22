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

        /// ���� ���� �˻�
        if ( std::abs( pos.x - destPos.x ) < 0.01f && std::abs( pos.y - destPos.y ) < 0.01f )
        {
            /// ������ �������� ����
            {
                // �ӽ÷� �������� ����
                destPos.x += 1.0f;
                destPos.y += 1.0f;
            }
        }

        /// �� ��踦 �������  üũ
        /// if ( pos.x < 0.0f || pos.x > 10.0f || pos.y < 0.0f || pos.y > 10.0f )
        {
            /// �� ��踦 ����ٸ�, �ٸ� ���� �̵�
            //_cell.LeaveCell( sender );
            //_cell.EnterCell( sender );
        }

        // �̵� ��� ����
        if ( sender )
        {
            C_Move move{ .fromPos = fromPos, .toPos = pos };
            sender->Send( move );
        }
    }
}
