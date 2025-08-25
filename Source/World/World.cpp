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


World::World()
{
}

template< std::derived_from< WorldObject > T >
auto GetFactory( Cell& registry )
{
    auto obj{ std::make_shared< T >( registry.create() ) };

    registry.emplace< Position >( obj->GetEntity(), FVector{ 1.0f, 2.0f, 0.0f } );
    //registry.emplace< Direction >( obj->GetEntity(), 0.0f, 0.0f );

    if constexpr ( std::is_same_v< T, Pc > )
        obj->SetSender( std::make_shared< Sender >() );

    if constexpr ( std::is_same_v< T, Npc > )
        registry.emplace< DestPosition >( obj->GetEntity(), FVector{ 4.0f, 5.0f, 0.0f } );

    registry.emplace< SenderPtr >( obj->GetEntity(), obj->GetSender() );

    return obj;
}

void World::Init()
{
    for ( size_t i = 0; i < row * col; ++i )
    {
        auto& cell = *_cells.emplace_back( std::make_unique< Cell >( *this ) );
        cell.RegisterSystem< CommandSystem >();
        cell.RegisterSystem< MovementSystem >();
        cell.RegisterSystem< SpawnSystem >();
        cell.RegisterSystem< SightSystem >();

        //GetFactory< Pc >( cell );
        GetFactory< Npc >( cell );
    }
}

void World::EnterWorld( EntityObjectRef object )
{
}

void World::Update( float deltaTime )
{
    for ( auto& cell : _cells )
    {
        cell->Update( deltaTime );
    }
}
