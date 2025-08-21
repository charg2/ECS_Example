module;
#include <entt/entt.hpp>

export module World;

import ISystem;
import EntityObject;

export class Cell : public entt::registry
{
public:
    Cell()
    : entt::registry( 64 )
    {
    }

    template< std::derived_from< ISystem > T >
    void RegisterSystem()
    {
        _systems.emplace_back( std::make_unique< T >( *this ) );
    }

    void Update( float deltaTime )
    {
        for ( auto& system : _systems )
        {
            system->Update( deltaTime );
        }
    }

    void EnterCell( EntityObjectRef object )
    {
        _objects.emplace( object->GetEntity(), object );
        object->SetEntity( entt::registry::create() );
    }

    void LeaveCell( EntityObjectRef object )
    {
        _objects.erase( object->GetEntity() );
        entt::registry::destroy( object->GetEntity() );
    }

private:
    std::vector< std::unique_ptr< ISystem > > _systems;
    std::unordered_map< entt::entity, EntityObjectPtr > _objects;
};
