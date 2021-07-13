#pragma once
#include"MathHelper.h"

namespace basecross
{
	using namespace itbs::Input;
	using namespace itbs::Math;

	class PlayerInputer : public InputerBase
	{
		static constexpr int MIN_SENSITIVITY_LEVEL = 1;
		static constexpr int MAX_SENSITIVITY_LEVEL = 10;

		static constexpr float MOUSE_SENSITIVITY_DEFAULT_VALUE = 10;

		static int m_mouseSensitivityLevel;

		static int m_rotationSensitivityLevel;
	public:
		static Vec2 GetMoveDirection();

		static Vec2 GetCameraRotation();

		static void SetMouseSensitivityLevel(const int level);

		static void SetRotationSensitivityLevel(const int level);

		static int GetMouseSensitivityLevel();

		static int GetRotationSensitivityLevel();

		static bool IsDecision();

		static bool IsCancel();

		static bool IsChangeStance();

		static bool IsMenuDown();
	};
}