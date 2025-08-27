export module CommandSystem;

import ISystem;
import EntityObject;

export class Cell;

export class CommandSystem final : public ISystem
{
public:
    CommandSystem( Cell& cell );
    ~CommandSystem() final = default;

    void Update( float deltaTime ) final
    {
    }

    void OnEnter( EntityObjectRef ) final
    {
    }

private:
    Cell& _cell;
};
