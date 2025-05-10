#include "../pch.h"
#include "ComponentSystem.h"

void ComponentSystem::AddEvent(function<void()> func)
{
	m_event = func;
}
