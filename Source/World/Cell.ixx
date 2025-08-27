module;
#include <entt/entt.hpp>

export module Cell;

import ISystem;
import EntityObject;
import WorldObject;

export class World;

export class Cell : public entt::registry
{
public:
    Cell( World& world );

    template< std::derived_from< ISystem > T >
    void RegisterSystem()
    {
        _systems.emplace_back( std::make_unique< T >( *this ) );
    }

    void AddNeighbor( Cell* cell );
    void Update( float deltaTime );
    void EnterCell( WorldObjectRef object );
    void LeaveCell( WorldObjectRef object );

private:
    World& _world;
    std::vector< std::unique_ptr< ISystem > > _systems;
    std::unordered_map< entt::entity, WorldObjectPtr > _objects;
    std::vector< Cell* > _neighbors{ 9 };
};
