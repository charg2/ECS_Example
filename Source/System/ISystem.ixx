export module ISystem;

export class ISystem
{
public:
    virtual ~ISystem() = default;
    virtual void Update( float deltaTime ) = 0;
};
