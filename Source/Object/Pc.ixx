module;

#include <entt/entt.hpp>

export module Pc;

import WorldObject;

export class Pc final : public WorldObject
{
public:
    Pc() = default;
    Pc( entt::entity entity );

    ~Pc() final = default;
};

Pc::Pc( entt::entity entity )
: WorldObject{ entity }
{
}

export using PcPtr = std::shared_ptr< Pc >;
