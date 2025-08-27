export module MovementSystem;

import ISystem;
import EntityObject;

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

    void OnEnter( EntityObjectRef obj ) final;


private:
    Cell& _cell;
};
