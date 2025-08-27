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

    ////registry.emplace< Direction >( obj->GetEntity(), 0.0f, 0.0f );

    //if constexpr ( std::is_same_v< T, Pc > )
    //{
    //    registry.emplace< Position >( obj->GetEntity(), FVector{ 1.0f, 2.0f, 0.0f } );
    //    obj->SetSender( std::make_shared< Sender >() );
    //}

    //if constexpr ( std::is_same_v< T, Npc > )
    //    registry.emplace< DestPosition >( obj->GetEntity(), FVector{ 4.0f, 5.0f, 0.0f } );

    //registry.emplace< SenderPtr >( obj->GetEntity(), obj->GetSender() );

    return obj;
}

std::array< std::pair< int, int >, 9 > GCellAccessStrategy =
{
    {
        { -1, -1 }, { -1, 0 }, { -1, 1 },
        {  0, -1 }, {  0, 0 }, {  0, 1 },
        {  1, -1 }, {  1, 0 }, {  1, 1 }
    }
};

void World::Init()
{
    for ( size_t i = 0; i < row * col; ++i )
    {
        auto& cell = *_cells.emplace_back( std::make_unique< Cell >( *this ) );
        cell.RegisterSystem< CommandSystem >();
        cell.RegisterSystem< MovementSystem >();
        cell.RegisterSystem< SpawnSystem >();
        //cell.RegisterSystem< SightSystem >();

        ////GetFactory< Pc >( cell );
        GetFactory< Npc >( cell );
    }

    for ( size_t r = 0; r < row; ++r )
    {
        for ( size_t c = 0; c < col; ++c )
        {
            auto& cell = *_cells[ World::ToCellIndex( r, c ) ];
            for ( auto& [ dr, dc ] : GCellAccessStrategy )
            {
                int nr = r + dr;
                int nc = c + dc;
                if ( nr < 0 || nr >= row || nc < 0 || nc >= col )
                    continue;

                if ( &cell == _cells[ nr * col + nc ].get() )
                    continue;

                cell.AddNeighbor( _cells[ nr * col + nc ].get() );
            }
        }
    }
}

int World::ToCellIndex( size_t r, size_t c )
{
    return r * col + c;
}

void World::EnterWorld( WorldObjectRef object )
{
    auto pos = object->GetPos();
    _cells[ ToCellIndex( 0, 0 ) ]->EnterCell( object );
}

void World::Update( float deltaTime )
{
    for ( auto& cell : _cells )
    {
        cell->Update( deltaTime );
    }
}
