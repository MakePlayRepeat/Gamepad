#ifndef DECAF_INPUT_WIN32_GAMEPADIMPLWIN32_HH_
#define DECAF_INPUT_WIN32_GAMEPADIMPLWIN32_HH_

#include "decaf/input/gamepadimpl.hh"

namespace decaf
{

	class GamepadImpl_Win32 : public IGamepadImpl
	{

	public:

		virtual Gamepad::State GetState(Gamepad::Index index);

		virtual Gamepad::State GetState(Gamepad::Index index, float deadzone);

		virtual void SetRumble(Gamepad::Index index, float left, float right);

	};

}

#endif
