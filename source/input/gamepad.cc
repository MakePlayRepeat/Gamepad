#include "decaf/input/gamepad.hh"
#include "decaf/input/gamepadimpl.hh"

namespace decaf
{

	////////////////////////////////////////////////////////////
	Gamepad::State Gamepad::GetState(Gamepad::Index index)
	{
		IGamepadImpl* _impl = IGamepadImpl::Instance();
		return _impl->GetState(index);
	}


	////////////////////////////////////////////////////////////
	Gamepad::State Gamepad::GetState(Gamepad::Index index, float deadzone)
	{
		IGamepadImpl* _impl = IGamepadImpl::Instance();
		return _impl->GetState(index, deadzone);
	}


	////////////////////////////////////////////////////////////
	void Gamepad::SetRumble(Gamepad::Index index, float left, float right)
	{
		IGamepadImpl* _impl = IGamepadImpl::Instance();
		_impl->SetRumble(index, left, right);
	}


	////////////////////////////////////////////////////////////
	Gamepad::Gamepad(Gamepad::Index index) 
		: m_index{ index }, m_lastState{ 0 }, m_currState{ 0 } { }


	////////////////////////////////////////////////////////////
	bool Gamepad::Poll()
	{
		memcpy(&m_lastState, &m_currState, sizeof(Gamepad::State));
		m_currState = GetState(m_index);

		return m_currState.connected;
	}


	////////////////////////////////////////////////////////////
	bool Gamepad::IsConnected() const
	{
		Gamepad::State temp = GetState(m_index);
		return temp.connected;
	}


	////////////////////////////////////////////////////////////
	bool Gamepad::StateChanged() const
	{
		return memcmp(&m_lastState, &m_currState, sizeof(Gamepad::State)) != 0;
	}


	////////////////////////////////////////////////////////////
	void Gamepad::Clear()
	{
		memset(&m_lastState, 0, sizeof(Gamepad::State));
		memset(&m_currState, 0, sizeof(Gamepad::State));
	}


	////////////////////////////////////////////////////////////
	const Vector2f& Gamepad::LeftStick() const
	{
		return m_currState.leftStick;
	}


	////////////////////////////////////////////////////////////
	const Vector2f& Gamepad::RightStick() const
	{
		return m_currState.rightStick;
	}


	////////////////////////////////////////////////////////////
	const float& Gamepad::LeftTrigger() const
	{
		return m_currState.leftTrigger;
	}


	////////////////////////////////////////////////////////////
	const float& Gamepad::RightTrigger() const
	{
		return m_currState.rightTrigger;
	}


	////////////////////////////////////////////////////////////
	bool Gamepad::IsButtonDown(Button button) const
	{
		using Type = std::underlying_type<Gamepad::Button>::type;
		return ((m_currState.buttons & static_cast<Type>(button)) != 0);
	}


	////////////////////////////////////////////////////////////
	bool Gamepad::WasButtonPressed(Button button) const
	{
		using Type = std::underlying_type<Gamepad::Button>::type;
		return ((m_currState.buttons & static_cast<Type>(button)) != 0) && ((m_lastState.buttons & static_cast<Type>(button)) == 0);
	}


	////////////////////////////////////////////////////////////
	bool Gamepad::WasButtonReleased(Button button) const
	{
		using Type = std::underlying_type<Gamepad::Button>::type;
		return ((m_currState.buttons & static_cast<Type>(button)) == 0) && ((m_lastState.buttons & static_cast<Type>(button)) != 0);
	}


	////////////////////////////////////////////////////////////
	void Gamepad::SetRumble(float left, float right)
	{
		SetRumble(m_index, left, right);
	}

}
