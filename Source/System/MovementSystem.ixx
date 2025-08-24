export module MovementSystem;

import ISystem;

export class Cell;
export class Packet;

export class TargetingSystem final : public ISystem
{
};

export class MovementSystem final : public ISystem
{
public:
    MovementSystem( Cell& cell );
    ~MovementSystem() final = default;
    void Update( float deltaTime ) final;

private:
    Cell& _cell;
};

export class SpawnSystem final : public ISystem
{
public:
    SpawnSystem( Cell& cell );
    ~SpawnSystem() final = default;
    void Update( float deltaTime ) final;

private:
    Cell& _cell;
};
