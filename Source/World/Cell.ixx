module;
#include <entt/entt.hpp>

export module Cell;

import ISystem;
import EntityObject;

export class Cell : public entt::registry
{
public:
    Cell();

    template< std::derived_from< ISystem > T >
    void RegisterSystem()
    {
        _systems.emplace_back( std::make_unique< T >( *this ) );
    }

    void Update( float deltaTime );
    void EnterCell( EntityObjectRef object );
    void LeaveCell( EntityObjectRef object );

private:
    std::vector< std::unique_ptr< ISystem > > _systems;
    std::unordered_map< entt::entity, EntityObjectPtr > _objects;
};
