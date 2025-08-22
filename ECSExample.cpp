// ECSExample.cpp : 애플리케이션의 진입점을 정의합니다.
//

#include "ECSExample.h"
#include <execution>
#include <chrono>
#include <entt/entt.hpp>

import ISystem;
import CommandSystem;
import MovementSystem;
import IComponent;
import Position;

import Packet;
import EntityObject;
import WorldObject;

import Sender;
import Pc;
import Npc;
import World;

using namespace std;

auto main() -> int
{
    GWorld = std::make_unique< World >();
    GWorld->Init();

    std::chrono::duration< float > deltaTime{};
    std::chrono::duration< float > runTime{};

    while ( runTime < 10s )
    {
        auto start = std::chrono::system_clock::now();

        GWorld->Update( deltaTime.count() );

        std::this_thread::sleep_for( 16ms );

        deltaTime = std::chrono::system_clock::now  () - start;

        runTime += deltaTime;
    }

	return 0;
}
