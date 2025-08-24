import IComponent;
import WorldObject;
import Packet;
import Cell;
import World;
import Packet;
import Position;
import Sender;
import SpawnSystem;

//SpawnSystem::SpawnSystem( Cell& cell )
//: _cell{ cell }
//{
//}

void SpawnSystem::Update( float deltaTime )
{
    auto view = _cell.view< Position, DestPosition, SenderPtr >();
    for ( auto [ entity, pos, destPos, sender ] : view.each() )
    {
    }
}
