#ifndef DECAF_INPUT_GAMEPAD_HH_
#define DECAF_INPUT_GAMEPAD_HH_

#include "decaf\math\vector.hh"

namespace decaf
{

	class Gamepad
	{

	public:

		enum class Index
		{
			ONE = 0,
			TWO,
			THREE,
			FOUR
		};

		enum class Axis
		{
			LSTICK_X,
			LSTICK_Y,
			RSTICK_X,
			RSTICK_Y,
			LTRIGGER,
			RTRIGGER
		};

		enum class Button
		{
			DPAD_UP = 0x0001,
			DPAD_DOWN = 0x0002,
			DPAD_LEFT = 0x0004,
			DPAD_RIGHT = 0x0008,
			START = 0x0010,
			BACK = 0x0020,
			LTHUMB = 0x0040,
			RTHUMB = 0x0080,
			LSHOULDER = 0x0100,
			RSHOULDER = 0x0200,
			A = 0x1000,
			B = 0x2000,
			X = 0x4000,
			Y = 0x8000
		};

		struct State
		{
			Vector2f leftStick;
			Vector2f rightStick;
			float leftTrigger;
			float rightTrigger;
			uint16_t buttons;
			bool connected;
		};

	public:

		static State GetState(Index index);
		static State GetState(Index index, float deadzone);
		static void SetRumble(Index index, float left, float right);

	public:

		Gamepad(Index index);

		bool Poll();
		bool IsConnected() const;
		bool StateChanged() const;
		void Clear();

		const Vector2f& LeftStick() const;
		const Vector2f& RightStick() const;
		const float& LeftTrigger() const;
		const float& RightTrigger() const;

		bool IsButtonDown(Button button) const;
		bool WasButtonPressed(Button button) const;
		bool WasButtonReleased(Button button) const;

		void SetRumble(float left, float right);

	private:

		Index m_index;
		State m_lastState;
		State m_currState;

	};

}

#endif
