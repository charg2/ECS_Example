export module WorldObject;

import Sender;
import EntityObject;

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

    SenderRef GetSenderRef() const
    {
        return _sender;
    }


    SenderPtr _sender{};
};

export using WorldObjectPtr = std::shared_ptr< WorldObject >;
export using WorldObjectRef = const WorldObjectPtr&;