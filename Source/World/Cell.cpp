import ISystem;
import EntityObject;
import World;
import CommandSystem;
import MovementSystem;
import SightSystem;
import SpawnSystem;
import Pc;
import Npc;
import Position;
import Sender;
import WorldObject;
import Cell;


Cell::Cell( World& world )
: entt::registry( 64 )
, _world{ world }
{
}

void Cell::Update( float deltaTime )
{
    for ( auto& system : _systems )
    {
        system->Update( deltaTime );
    }
}

void Cell::EnterCell( EntityObjectRef object )
{
    _objects.emplace( object->GetEntity(), object );
    object->SetEntity( entt::registry::create() );
}

void Cell::LeaveCell( EntityObjectRef object )
{
    _objects.erase( object->GetEntity() );
    entt::registry::destroy( object->GetEntity() );
}
