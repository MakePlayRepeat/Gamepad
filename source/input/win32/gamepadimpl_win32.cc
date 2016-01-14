#include <cmath>

#include <Windows.h>
#pragma comment (lib, "XInput.lib")
#include <Xinput.h>

#include "decaf/input/win32/gamepadimpl_win32.hh"

namespace decaf
{

	////////////////////////////////////////////////////////////
	void ParseXInputState(const XINPUT_STATE& xis, Gamepad::State& gps)
	{
		constexpr float dzL = (float)XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE / 32767;
		constexpr float dzR = (float)XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE / 32767;

		float nLX = fmaxf(-1.0f, (float)xis.Gamepad.sThumbLX / 32767.0f);
		float nLY = fmaxf(-1.0f, (float)xis.Gamepad.sThumbLY / 32767.0f);

		gps.leftStick[0] = (abs(nLX) < dzL ? 0 : (abs(nLX) - dzL) * (nLX * abs(nLX)));
		gps.leftStick[1] = (abs(nLY) < dzL ? 0 : (abs(nLY) - dzL) * (nLY * abs(nLY)));

		float nRX = fmaxf(-1.0f, (float)xis.Gamepad.sThumbRX / 32767.0f);
		float nRY = fmaxf(-1.0f, (float)xis.Gamepad.sThumbRY / 32767.0f);

		gps.rightStick[0] = (abs(nRX) < dzR ? 0 : (abs(nRX) - dzR) * (nRX * abs(nRX)));
		gps.rightStick[1] = (abs(nRY) < dzR ? 0 : (abs(nRY) - dzR) * (nRY * abs(nRY)));

		gps.leftStick *= 1 / (1 - dzL);
		gps.rightStick *= 1 / (1 - dzR);

		gps.leftTrigger = (float)xis.Gamepad.bLeftTrigger / 255;
		gps.rightTrigger = (float)xis.Gamepad.bRightTrigger / 255;

		gps.buttons = xis.Gamepad.wButtons;

		gps.connected = true;
	}


	////////////////////////////////////////////////////////////
	void ParseXInputState(const XINPUT_STATE& xis, Gamepad::State& gps, float deadzone)
	{
		float nLX = fmaxf(-1.0f, (float)xis.Gamepad.sThumbLX / 32767.0f);
		float nLY = fmaxf(-1.0f, (float)xis.Gamepad.sThumbLY / 32767.0f);

		gps.leftStick[0] = (abs(nLX) < deadzone ? 0 : (abs(nLX) - deadzone) * (nLX * abs(nLX)));
		gps.leftStick[1] = (abs(nLY) < deadzone ? 0 : (abs(nLY) - deadzone) * (nLY * abs(nLY)));

		float nRX = fmaxf(-1.0f, (float)xis.Gamepad.sThumbRX / 32767.0f);
		float nRY = fmaxf(-1.0f, (float)xis.Gamepad.sThumbRY / 32767.0f);

		gps.rightStick[0] = (abs(nRX) < deadzone ? 0 : (abs(nRX) - deadzone) * (nRX * abs(nRX)));
		gps.rightStick[1] = (abs(nRY) < deadzone ? 0 : (abs(nRY) - deadzone) * (nRY * abs(nRY)));

		gps.leftStick *= 1 / (1 - deadzone);
		gps.rightStick *= 1 / (1 - deadzone);

		gps.leftTrigger = (float)xis.Gamepad.bLeftTrigger / 255;
		gps.rightTrigger = (float)xis.Gamepad.bRightTrigger / 255;

		gps.buttons = xis.Gamepad.wButtons;

		gps.connected = true;
	}


	////////////////////////////////////////////////////////////
	Gamepad::State GamepadImpl_Win32::GetState(Gamepad::Index index)
	{
		XINPUT_STATE xis = { 0 };
		Gamepad::State result = { 0 };

		if (XInputGetState(static_cast<int>(index), &xis) == ERROR_SUCCESS)
			ParseXInputState(xis, result);
	
		return result;
	}


	////////////////////////////////////////////////////////////
	Gamepad::State GamepadImpl_Win32::GetState(Gamepad::Index index, float deadzone)
	{
		XINPUT_STATE xis = { 0 };
		Gamepad::State result = { 0 };

		if (XInputGetState(static_cast<int>(index), &xis) == ERROR_SUCCESS)
			ParseXInputState(xis, result, deadzone);

		return result;
	}


	////////////////////////////////////////////////////////////
	void GamepadImpl_Win32::SetRumble(Gamepad::Index index, float left, float right)
	{
		XINPUT_VIBRATION xiv;
		xiv.wLeftMotorSpeed = (WORD)(left * 65535);
		xiv.wRightMotorSpeed = (WORD)(right * 65535);

		XInputSetState(static_cast<int>(index), &xiv);
	}

}
