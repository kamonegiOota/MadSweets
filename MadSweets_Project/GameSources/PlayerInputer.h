#pragma once
#include"MathHelper.h"

namespace basecross
{
	using namespace itbs::Input;
	using namespace itbs::Math;

	class PlayerInputer : public InputerBase, public I_BasicInputer
	{
		static constexpr int MIN_SENSITIVITY_LEVEL = 1;
		static constexpr int MAX_SENSITIVITY_LEVEL = 10;

		static constexpr float MOUSE_SENSITIVITY_DEFAULT_VALUE = 50;

		static int m_mouseSensitivityLevel;

		static int m_rotationSensitivityLevel;

		static std::shared_ptr<PlayerInputer> m_playerInputer;

		const std::shared_ptr<itbs::Input::InputDevice> m_inputDevice;

	public:
		PlayerInputer();

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

		static bool IsDashPush();

		static bool IsUpChoices();

		static bool IsDownChoices();

		static std::shared_ptr<PlayerInputer> GetInstance();

		bool IsDesitionDown() const override;

		bool IsCancelDown() const override;

		bool IsUpDown() const override;

		bool IsUp() const override;

		bool IsDownDown() const override;

		bool IsDown() const override;

		bool IsLeftDown() const override;

		bool IsLeft() const override;

		bool IsRightDown() const override;

		bool IsRight() const override;
	};
}