#include "Behaviour.h"

void Behaviour::SetEnabled(bool enable)
{
    if (_enabled == enable)
        return;

    if (enable)
        OnEnable();
    else
        OnDisable();

    _enabled = enable;
}

bool Behaviour::GetEnabled() const
{
    return _enabled;
}

bool Behaviour::operator==(const Behaviour& other) const
{
    return this == &other;
}
