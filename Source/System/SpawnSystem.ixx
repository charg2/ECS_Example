export module SpawnSystem;

import ISystem;
import EntityObject;

export class Cell;

export class SpawnSystem final : public ISystem
{
public:
    SpawnSystem( Cell& cell );
    ~SpawnSystem() final = default;

    void Update( float deltaTime ) final;

    void OnEnter( EntityObjectRef ) final
    {
    }

private:
    Cell& _cell;
};
