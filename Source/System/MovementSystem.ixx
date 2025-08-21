export module MovementSystem;

import ISystem;

export class Cell;

export class MovementSystem final : public ISystem
{
public:
    MovementSystem( Cell& cell );
    ~MovementSystem() final = default;

    void Update( float deltaTime ) final;

private:
    Cell& _cell;
};
