// ECSExample.cpp : 애플리케이션의 진입점을 정의합니다.
//

#include "ECSExample.h"
#include <execution>
#include <entt/entt.hpp>

using namespace std;

struct Position
{
    float x;
    float y;
};

struct DestPosition : public Position{};

struct Velocity
{
    float x;
    float y;
};

class EntityObject
{
public:
    EntityObject( entt::entity entity )
    : _entity{ entity }
    {
    }

    entt::entity GetEntity() const { return _entity; }

private:
    entt::entity _entity;
};

class Pc : public EntityObject
{
};

class Npc : public EntityObject
{
};

struct PcTag{};
struct NpcTag{};

class ISystem
{
public:
    virtual ~ISystem() = default;
    virtual void Update( int deltaTick ) = 0;
};

class World : public entt::registry
{
public:
    World() = default;

    template< std::derived_from< ISystem > T >
    void RegisterSystem()
    {
        _systems.emplace_back( std::make_unique< T >( *this ) );
    }

    void Update( int deltaTick )
    {
        for ( auto& system : _systems )
        {
            system->Update( deltaTick );
        }
    }

private:
    std::vector< std::unique_ptr< ISystem > > _systems;
};

class CommandSystem final : public ISystem
{
public:
    CommandSystem( World& world )
    : _world{ world }
    {
    }

    ~CommandSystem() final = default;

    void Update( int deltaTick ) final
    {
    }

private:
    World& _world;
};

class MovementSystem final : public ISystem
{
public:
    MovementSystem( World& world )
    : _world{ world }
    {
    }

    ~MovementSystem() final = default;

    void Update( int deltaTick ) final
    {
        auto view = _world.view< Position, const DestPosition, const Velocity >();
        for ( auto [ entity, pos, destPos, vel ] : view.each() )
        {
            pos.x += vel.x * deltaTick;
            pos.y += vel.y * deltaTick;
            if ( pos.x >= destPos.x && pos.y >= destPos.y )
                std::cout << "도착" << pos.x << ", " << pos.y << std::endl;
        }
    }

private:
    World& _world;
};

using PcPtr  = std::shared_ptr< Pc >;
using NpcPtr = std::shared_ptr< Npc >;

template< typename T >
auto GetFactory( World& registry )
{
    auto obj{ std::make_shared< T >( registry.create() ) };
    registry.emplace< Position >( obj->GetEntity(), 1.0f, 2.0f );
    registry.emplace< Velocity >( obj->GetEntity(), 1.0f, 2.0f );

    if constexpr ( std::is_same_v< T, Npc > )
        registry.emplace< DestPosition >( obj->GetEntity(), 4.0f, 5.0f );

    return obj;
}

int main()
{
    World world;

    world.RegisterSystem< CommandSystem >();
    world.RegisterSystem< MovementSystem >();

    GetFactory< Pc >( world );
    GetFactory< Npc >( world );
    GetFactory< Npc >( world );
    GetFactory< Npc >( world );

    world.Update( 16 );

	return 0;
}
