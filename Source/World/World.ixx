module;
#include <entt/entt.hpp>
#include <memory>

export module World;

import ISystem;
import WorldObject;
import Cell;

export constexpr size_t row{ 2 };
export constexpr size_t col{ 2 };

export class World
{
public:
    World();
    void Init();
    static int ToCellIndex( size_t r, size_t c );
    void EnterWorld( WorldObjectRef object );
    void Update( float deltaTime );

private:
    std::vector< std::unique_ptr< Cell > > _cells;
};

export inline extern std::unique_ptr< World > GWorld{};
