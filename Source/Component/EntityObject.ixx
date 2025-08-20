module;
#include <entt/entt.hpp>

export module EntityObject;
import Sender;

export class EntityObject
{
public:
    EntityObject() = default;
    EntityObject( entt::entity entity )
    : _entity{ entity }
    {
    }
    virtual ~EntityObject() = default;

    constexpr entt::entity GetEntity() const { return _entity; }
    void SetEntity( entt::entity entity ) { _entity = entity; }

private:
    entt::entity _entity{};
};

export using EntityObjectPtr = std::shared_ptr< EntityObject >;
export using EntityObjectRef = const EntityObjectPtr&;

export class WorldObject : public EntityObject
{
public:
    WorldObject() = default;
    WorldObject( entt::entity entity )
    : EntityObject{ entity }
    {
    }

    ~WorldObject() override = default;

    void SetSender( SenderRef sender )
    {
        _sender = sender;
    }

    SenderPtr GetSender() const
    {
        return _sender;
    }

    SenderPtr _sender{};
};

export using WorldObjectPtr = std::shared_ptr< WorldObject >;
export using WorldObjectRef = const WorldObjectPtr&;