// ECSExample.cpp : 애플리케이션의 진입점을 정의합니다.
//

#include "ECSExample.h"
#include <entt/entt.hpp>

using namespace std;

struct Position
{
    float x;
    float y;
    float z;
};

struct Velocity
{
    float x;
    float y;
};

void Update( entt::registry& registry )
{
    auto view = registry.view< const Position, Velocity >();

    for ( auto [ entity, pos, vel ] : view.each() )
    {
        std::cout << format( "{}, {}, {} ", pos.x, pos.y, pos.z ) << std::endl;
        std::cout << format( "{}, {}", vel.x, vel.y  )<< std::endl;
    }
}

int main()
{
	cout << "Hello ECS." << endl;

    entt::registry registry;

    const auto entity = registry.create();
    registry.emplace< Position >( entity, 1.0f, 2.0f, 3.0f );
    registry.emplace< Velocity >( entity, 1.0f, 2.0f );

    Update( registry );

	return 0;
}
