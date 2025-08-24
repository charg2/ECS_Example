export module SpawnSystem;

import ISystem;

export class Cell;
export class Packet;

export class SpawnSystem final : public ISystem
{
public:
    SpawnSystem( Cell& cell )
    : _cell{ cell }
    {
    }
    ~SpawnSystem() final = default;
    void Update( float deltaTime ) final;

private:
    Cell& _cell;
};
