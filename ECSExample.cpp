// ECSExample.cpp : 애플리케이션의 진입점을 정의합니다.
//

#include "ECSExample.h"
#include <execution>
#include <chrono>
#include <entt/entt.hpp>

import ISystem;
import CommandSystem;
import MovementSystem;
import IComponent;
import Position;

import Packet;
import EntityObject;
import WorldObject;

import Sender;
import Pc;
import Npc;
import World;

using namespace std;


class SightSystem final : public ISystem
{
public:
    SightSystem( Cell& cell )
    : _cell{ cell }
    {
    }

    ~SightSystem() final = default;

    void Update( float deltaTime ) final
    {
    }

private:
    Cell& _cell;
};


template< std::derived_from< WorldObject > T >
auto GetFactory( Cell& registry )
{
    auto obj{ std::make_shared< T >( registry.create() ) };

    registry.emplace< Position >( obj->GetEntity(), 1.0f, 2.0f );
    registry.emplace< Velocity >( obj->GetEntity(), 2.0f, 4.0f );

    if constexpr ( std::is_same_v< T, Pc > )
        obj->SetSender( std::make_shared< Sender >() );

    if constexpr ( std::is_same_v< T, Npc > )
        registry.emplace< DestPosition >( obj->GetEntity(), 4.0f, 5.0f );

    registry.emplace< SenderPtr >( obj->GetEntity(), obj->GetSender() );

    return obj;
}

constexpr size_t row{ 2 };
constexpr size_t col{ 2 };

class World
{
public:
    World()
    {
    }

    void Init()
    {
        for ( size_t i = 0; i < row * col; ++i )
        {
            auto& cell = _cells[ i ];
            cell.RegisterSystem< CommandSystem >();
            cell.RegisterSystem< MovementSystem >();
            cell.RegisterSystem< SightSystem >();

            GetFactory< Pc >( cell );
            GetFactory< Npc >( cell );
        }
    }

    void EnterWorld( EntityObjectRef object )
    {
    }

    void Update( float deltaTime )
    {
        for ( auto& cell : _cells )
        {
            cell.Update( deltaTime );
        }
    }

private:
    std::array< Cell, row * col > _cells;
};

inline static std::unique_ptr< World > GWorld{};

auto main() -> int
{
    GWorld = std::make_unique< World >();
    GWorld->Init();

    std::chrono::duration< float > deltaTime{};
    std::chrono::duration< float > runTime{};

    while ( runTime < 10s )
    {
        auto start = std::chrono::system_clock::now();

        GWorld->Update( deltaTime.count() );

        std::this_thread::sleep_for( 16ms );

        deltaTime = std::chrono::system_clock::now  () - start;

        runTime += deltaTime;
    }

	return 0;
}
