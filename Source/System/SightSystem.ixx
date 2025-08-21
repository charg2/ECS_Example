export module CommandSystem;

import ISystem;

export class Cell;

export class CommandSystem final : public ISystem
{
public:
    CommandSystem( Cell& cell );
    ~CommandSystem() final = default;

    void Update( float deltaTime ) final
    {
    }

private:
    Cell& _cell;
};
