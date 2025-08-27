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
, _neighbors{}
{
    _neighbors.reserve( 9 );
}

void Cell::AddNeighbor( Cell* cell )
{
    _neighbors.emplace_back( cell );
}

void Cell::Update( float deltaTime )
{
    for ( auto& system : _systems )
    {
        system->Update( deltaTime );
    }
}

void Cell::EnterCell( WorldObjectRef object )
{
    object->SetEntity( entt::registry::create() );
    _objects.emplace( object->GetEntity(), object );

    for ( auto& system : _systems )
        system->OnEnter( object );
}

void Cell::LeaveCell( WorldObjectRef object )
{
    _objects.erase( object->GetEntity() );
    entt::registry::destroy( object->GetEntity() );
}
