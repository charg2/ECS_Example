export module IComponent;

import <concepts>;

export struct IComponent
{
};

export template< std::derived_from< IComponent > T >
class NullableComponent : public IComponent
{
};