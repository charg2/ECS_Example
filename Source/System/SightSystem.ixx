export module SightSystem;

import ISystem;

export class Cell;


export class SightSystem final : public ISystem
{
public:
    SightSystem( Cell& cell )
    : _cell{ cell }
    {
    }

    ~SightSystem() final = default;

    void Update( float deltaTime ) final
    {
    }

private:
    Cell& _cell;
};
