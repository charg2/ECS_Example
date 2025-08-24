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
