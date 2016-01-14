#include "decaf/input/gamepadimpl.hh"

#if defined (_WIN32)
#include "decaf/input/win32/gamepadimpl_win32.hh"
using ImplType = decaf::GamepadImpl_Win32;
#endif

namespace decaf
{

	IGamepadImpl* IGamepadImpl::m_instance = nullptr;

	IGamepadImpl* IGamepadImpl::Instance()
	{
		if (m_instance == nullptr)
			m_instance = new ImplType;

		return m_instance;
	}

}
