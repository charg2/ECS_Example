export module WorldObject;

import Sender;
import EntityObject;
import Position;

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

    Position GetPos()
    {
        return _pos;
    }

    Position& GetPosRef()
    {
        return _pos;
    }

    Sight _sight;
    Position _pos{ {} };
    SenderPtr _sender{};
};

export using WorldObjectPtr = std::shared_ptr< WorldObject >;
export using WorldObjectRef = const WorldObjectPtr&;