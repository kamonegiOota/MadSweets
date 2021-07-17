#include"PlayerInputer.h"

namespace basecross
{
	int PlayerInputer::m_rotationSensitivityLevel = 5;
	int PlayerInputer::m_mouseSensitivityLevel = 5;

	Vec2 PlayerInputer::GetMoveDirection()
	{
		static const auto& inputDevice = App::GetApp()->GetMyInputDevice();
		static const auto& keyBoard = inputDevice->GetKeyBoard();
		static const auto& xinput = inputDevice->GetXInputGamePad();

		Vec2 direction;

		if (keyBoard.IsInputPush(KeyCode::D))
		{
			direction.x += 1;
		}

		if (keyBoard.IsInputPush(KeyCode::A))
		{
			direction.x -= 1;
		}

		if (keyBoard.IsInputPush(KeyCode::W))
		{
			direction.y += 1;
		}

		if (keyBoard.IsInputPush(KeyCode::S))
		{
			direction.y -= 1;
		}


		direction.x += xinput.GetLeftThumb().x;
		direction.y += xinput.GetLeftThumb().y;

		direction.x = MyMath::Clamp(direction.x, -1.0f, 1.0f);

		direction.y = MyMath::Clamp(direction.y, -1.0f, 1.0f);

		if (direction.length() > 1.0f)
		{
			direction.normalize();
		}

		return direction;
	}

	Vec2 PlayerInputer::GetCameraRotation()
	{
		static const auto& inputDevice = App::GetApp()->GetMyInputDevice();
		static const auto& keyBoard = inputDevice->GetKeyBoard();
		static const auto& xinput = inputDevice->GetXInputGamePad();

		Vec2 rotation;

		rotation.x += xinput.GetRightThumb().x;
		rotation.y += xinput.GetRightThumb().y;

		auto mouseMovePoint = inputDevice->GetMouseState().GetMouseMove();
		auto mouseMove = Vec2(mouseMovePoint.x, mouseMovePoint.y);

		rotation += mouseMove / MOUSE_SENSITIVITY_DEFAULT_VALUE * 
			(m_mouseSensitivityLevel / static_cast<float>(MAX_SENSITIVITY_LEVEL));

		rotation *= m_rotationSensitivityLevel / static_cast<float>(MAX_SENSITIVITY_LEVEL);

		rotation *= XMConvertToRadians(12);

		return rotation;

	}

	void PlayerInputer::SetMouseSensitivityLevel(const int level)
	{
		m_mouseSensitivityLevel = level;
	}

	void PlayerInputer::SetRotationSensitivityLevel(const int level)
	{
		m_rotationSensitivityLevel = level;
	}

	int PlayerInputer::GetMouseSensitivityLevel()
	{
		return m_mouseSensitivityLevel;
	}

	int PlayerInputer::GetRotationSensitivityLevel()
	{
		return m_rotationSensitivityLevel;
	}

	bool PlayerInputer::IsDecision()
	{
		return App::GetApp()->GetMyInputDevice()->GetKeyBoard().IsInputDown(KeyCode::Space) ||
			App::GetApp()->GetMyInputDevice()->GetXInputGamePad().IsInputDown(XInputCode::A);
	}

	bool PlayerInputer::IsCancel()
	{
		return App::GetApp()->GetMyInputDevice()->GetKeyBoard().IsInputDown(KeyCode::X) ||
			App::GetApp()->GetMyInputDevice()->GetXInputGamePad().IsInputDown(XInputCode::B);
	}

	bool PlayerInputer::IsChangeStance()
	{
		return App::GetApp()->GetMyInputDevice()->GetKeyBoard().IsInputDown(KeyCode::C) ||
			App::GetApp()->GetMyInputDevice()->GetXInputGamePad().IsInputDown(XInputCode::RightThumb);
	}

	bool PlayerInputer::IsMenuDown()
	{
		return App::GetApp()->GetMyInputDevice()->GetKeyBoard().IsInputDown(KeyCode::Tab) ||
			App::GetApp()->GetMyInputDevice()->GetXInputGamePad().IsInputDown(XInputCode::Start);
	}

	bool PlayerInputer::IsDashPush()
	{
		return App::GetApp()->GetMyInputDevice()->GetKeyBoard().IsInputPush(KeyCode::LeftShift) ||
			App::GetApp()->GetMyInputDevice()->GetXInputGamePad().IsInputPush(XInputCode::LeftShoulder);
	}
}