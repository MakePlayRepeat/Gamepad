#ifndef DECAF_INPUT_GAMEPADIMPL_HH_
#define DECAF_INPUT_GAMEPADIMPL_HH_

#include "decaf/input/gamepad.hh"

namespace decaf
{

	class IGamepadImpl
	{

	public:

		static IGamepadImpl* Instance();

		virtual Gamepad::State GetState(Gamepad::Index index) = 0;

		virtual Gamepad::State GetState(Gamepad::Index index, float deadzone) = 0;

		virtual void SetRumble(Gamepad::Index index, float left, float right) = 0;

	protected:

		IGamepadImpl() { }
		IGamepadImpl(const IGamepadImpl&) { }
		IGamepadImpl& operator=(const IGamepadImpl&) { }

		static IGamepadImpl* m_instance;

	};

}

#endif
