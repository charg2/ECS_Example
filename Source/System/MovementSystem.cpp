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
        Position diff = ( destPos - pos );

        auto distance = diff.Size();
        auto moveAmount = 2.0f * deltaTime;

        if ( distance < moveAmount )
        {
            moveAmount = distance;
            // ������ ����
            //destPos = pos;
        }

        Position dir      = diff.GetNormalize();
        Position moveDist = dir * moveAmount;

        //  �̵� ���ͷ� ���� ��ġ�� ������Ʈ
        Position nextPos = fromPos + moveDist;

        /// �� ��踦 �������  üũ
        /// if ( pos.x < 0.0f || pos.x > 10.0f || pos.y < 0.0f || pos.y > 10.0f )
        {
            /// �� ��踦 ����ٸ�, �ٸ� ���� �̵�
            //_cell.LeaveCell( sender );
            //_cell.EnterCell( sender );
        }

        //// �̵� ��� ����
        //if ( sender )
        //{
        //    C_Move move{ .fromPos = fromPos, .toPos = pos };
        //    sender->Send( move );
        //}
    }
}

void MovementSystem::OnEnter( EntityObjectRef obj )
{
    auto worldObject = std::static_pointer_cast< WorldObject >( obj );

    _cell.emplace< Position >( obj->GetEntity(), FVector{ 1.0f, 2.0f, 0.0f } );
    _cell.emplace< DestPosition >( obj->GetEntity(), FVector{ 2.0f, 4.0f, 0.0f } );
    _cell.emplace< SenderPtr >( obj->GetEntity(), worldObject->GetSender() );
}
