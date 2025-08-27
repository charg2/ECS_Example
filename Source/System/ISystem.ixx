export module ISystem;

import EntityObject;

//export class EntityObject;
//export using EntityObjectPtr    = std::shared_ptr< EntityObject >;
//export using EntityObjectPtrRef = const EntityObjectPtr&;

export class ISystem
{
public:
    virtual ~ISystem() = default;
    virtual void Update( float deltaTime ) = 0;
    virtual void OnEnter( EntityObjectRef ) = 0;
};
