#pragma once
#include<Windows.h>
#include<Xinput.h>
#include<unordered_map>
#include<array>
#include"DelegateSystem.h"
#include<queue>

namespace itbs
{
	namespace Input
	{
		/// <summary>
		/// �L�[�{�[�h�̃L�[�񋓌^
		/// </summary>
		enum class KeyCode : UINT8
		{
			MouseLeftButton = VK_LBUTTON,
			MouseRightButton = VK_RBUTTON,
			MouseMiddleButton = VK_MBUTTON,

			Backspace = VK_BACK,
			Tab = VK_TAB,
			Clear = VK_CLEAR,
			Enter = VK_RETURN,
			Shift = VK_SHIFT,
			Control = VK_CONTROL,
			Alt = VK_MENU,
			Pause = VK_PAUSE,
			CapsLock = VK_CAPITAL,
			Escape = VK_ESCAPE,
			Space = VK_SPACE,
			PageUp = VK_PRIOR,
			PageDown = VK_NEXT,
			End = VK_END,
			Home = VK_HOME,

			LeftArrow = VK_LEFT,
			UpArrow = VK_UP,
			RightArrow = VK_RIGHT,
			DownArrow = VK_DOWN,

			PrintScreen = VK_SNAPSHOT,
			Insert = VK_INSERT,
			Delete = VK_DELETE,

			Alpha0 = '0',
			Alpha1, Alpha2, Alpha3, Alpha4,
			Alpha5, Alpha6, Alpha7, Alpha8, Alpha9,

			A = 'A',
			B, C, D, E, F, G, H, I, J, K, L, M, N,
			O, P, Q, R, S, T, U, V, W, X, Y, Z,

			NumPad0 = VK_NUMPAD0,
			Numpad1, Numpad2, Numpad3, Numpad4,
			Numpad5, Numpad6, Numpad7, Numpad8, Numpad9,

			Multiply = VK_MULTIPLY,
			Add = VK_ADD,
			Subtract = VK_SUBTRACT,
			Decimal = VK_DECIMAL,
			Divide = VK_DIVIDE,

			F1 = VK_F1,
			F2, F3, F4, F5, F6, F7, F8, F9,
			F10, F11, F12, F13, F14, F15, F16,
			F17, F18, F19, F20, F21, F22, F23, F24,

			NumLock = VK_NUMLOCK,
			Scroll = VK_SCROLL,
			
			LeftShift = VK_LSHIFT,
			RightShift = VK_RSHIFT,
			LeftControll = VK_LCONTROL,
			RightControll = VK_RCONTROL,
			LeftAlt = VK_LMENU,
			RightAlt = VK_RMENU,

			Colon = VK_OEM_1,
			Plus = VK_OEM_PLUS,
			Comma = VK_OEM_COMMA,
			Minus = VK_OEM_MINUS,
			Period = VK_OEM_PERIOD,
			Slash = VK_OEM_2,
			At = VK_OEM_3,
			StartSquareBracket = VK_OEM_4,
			YenSign = VK_OEM_5,
			EndSquareBracket = VK_OEM_6,
			Tilde = VK_OEM_7,
			BackSlash = VK_OEM_102
		};

		/// <summary>
		/// XBox�Q�[���p�b�h�̃{�^���񋓌^
		/// </summary>
		enum class XInputCode : WORD
		{
			A = XINPUT_GAMEPAD_A,
			B = XINPUT_GAMEPAD_B,
			X = XINPUT_GAMEPAD_X,
			Y = XINPUT_GAMEPAD_Y,

			Start = XINPUT_GAMEPAD_START,
			Back = XINPUT_GAMEPAD_BACK,
			LeftThumb = XINPUT_GAMEPAD_LEFT_THUMB,
			RightThumb = XINPUT_GAMEPAD_RIGHT_THUMB,
			LeftShoulder = XINPUT_GAMEPAD_LEFT_SHOULDER,
			RightShoulder = XINPUT_GAMEPAD_RIGHT_SHOULDER,

			Up = XINPUT_GAMEPAD_DPAD_UP,
			Down = XINPUT_GAMEPAD_DPAD_DOWN,
			left = XINPUT_GAMEPAD_DPAD_LEFT,
			Right = XINPUT_GAMEPAD_DPAD_RIGHT
		};

		class CursorSetting
		{
			static bool m_isLock;
			static bool m_isDraw;

		public:
			static constexpr int defaultPointX = 1 + 2;

			static void SetIsLock(const bool isLock);
			static void SetIsDraw(const bool isDraw);

			static bool GetIsLock();
			static bool GetIsDraw();
		};

		template<class T>
		class I_InputEventGetter
		{
		public:
			virtual bool IsInputDown(const T& key) const = 0;
			virtual bool IsInputPush(const T& key) const = 0;
			virtual bool IsInputUp(const T& key) const = 0;
		};

		/// <summary>
		/// �}�E�X�f�[�^�Ǘ��N���X
		/// </summary>
		class MouseState
		{
			POINT m_mousePosition;

			POINT m_mouseMoveRange;

			bool m_isCursorDraw = true;

			bool m_isBeforeLock = false;
			
		public:

			void UpdateMouseState(const HWND& hwnd);

			POINT GetMouseMove() const;
		};

		class I_KeyBoardInputEventGetter : public I_InputEventGetter<KeyCode>
		{
		public:

		};

		/// <summary>
		/// �L�[�{�[�h���̓f�[�^�Ǘ��N���X
		/// </summary>
		class KeyBoardState : public I_KeyBoardInputEventGetter
		{
			/// <summary>
			/// �L�[�R�[�h�ő吔
			/// </summary>
			static constexpr int MAX_KEYCODE = 256;

			/// <summary>
			/// GetAsyncKeyState�Ŏ擾�����L�[���̉�����Ă��邩�ǂ����̃t���O�r�b�g
			/// </summary>
			static constexpr unsigned short GET_ASYNC_KEY_PUSH_BIT = 0x8000;

			/// <summary>
			/// �P��Ăяo���O�̓��͂��ꂽ�L�[�e�[�u��
			/// </summary>
			std::array<bool, MAX_KEYCODE> m_beforeKeycodeTable;
			/// <summary>
			/// ���݂̃t���[���ɓ��͂��ꂽ�L�[�e�[�u��
			/// </summary>
			std::array<bool, MAX_KEYCODE> m_nowKeycodeTable;

			std::queue<KeyCode> m_downEventQueue;

			std::queue<KeyCode> m_upEventQueue;
		public:
			/// <summary>
			/// �L�[�{�[�h���͂̍X�V
			/// </summary>
			void UpdateInputKeyState();

			/// <summary>
			/// �L�[�R�[�h�ɑΉ�����L�[�������ꂽ�u�Ԃ��𔻕ʂ���֐�
			/// </summary>
			/// <param name="keycode">���ʗp�L�[�R�[�h</param>
			/// <returns>�����ꂽ�u�ԂȂ�true</returns>
			bool IsInputDown(const KeyCode& keycode) const override;

			/// <summary>
			/// �L�[�R�[�h�ɑΉ�����L�[��������Ă��邩�𔻕ʂ���֐�
			/// </summary>
			/// <param name="keycode">���ʗp�L�[�R�[�h</param>
			/// <returns>������Ă���Ȃ�true</returns>
			bool IsInputPush(const KeyCode& keycode) const override;

			/// <summary>
			/// �L�[�R�[�h�ɑΉ�����L�[�������ꂽ�u�Ԃ��𔻕ʂ���֐�
			/// </summary>
			/// <param name="keycode">���ʗp�L�[�R�[�h</param>
			/// <returns>�����ꂽ�u�ԂȂ�true</returns>
			bool IsInputUp(const KeyCode& keycode) const override;

			void AddDownEvent(const KeyCode& keycode);

			void AddUpEvent(const KeyCode& keycode);
		};

		/// <summary>
		/// XBox�R���g���[���[���͏��\����
		/// </summary>
		struct XInputGamePadThumbState
		{
			static constexpr SHORT INPUT_MAX_VALUE = 0x7FFF;

			float x;
			float y;

			/// <summary>
			/// ���͏��̍X�V
			/// </summary>
			/// <param name="x">X����</param>
			/// <param name="y">Y����</param>
			/// <param name="deadzone">�������l</param>
			void UpdateState(const float x, const float y,const int deadzone);
		};

		class I_XInputEventGetter : public I_InputEventGetter<XInputCode>
		{
		public:
			/// <summary>
			/// ���X�e�B�b�N���͂��擾����
			/// </summary>
			/// <returns>���X�e�B�b�N���͏��</returns>
			virtual const XInputGamePadThumbState& GetLeftThumb() const = 0;

			/// <summary>
			/// �E�X�e�B�b�N���͂��擾����
			/// </summary>
			/// <returns>�E�X�e�B�b�N���͏��</returns>
			virtual const XInputGamePadThumbState& GetRightThumb() const = 0;
		};
		/// <summary>
		/// XBox�R���g���[���[���̓f�[�^�Ǘ��N���X
		/// </summary>
		class XInputGamePadState : public I_XInputEventGetter
		{
			/// <summary>
			/// �P��Ăяo���O�̃Q�[���p�b�h���
			/// </summary>
			XINPUT_GAMEPAD m_beforeGamepad;
			/// <summary>
			/// ���݂̃Q�[���p�b�h���
			/// </summary>
			XINPUT_GAMEPAD m_nowGamepad;

			/// <summary>
			/// ���X�e�B�b�N���͏��
			/// </summary>
			XInputGamePadThumbState m_leftThumState;
			/// <summary>
			/// �E�X�e�B�b�N���͏��
			/// </summary>
			XInputGamePadThumbState m_rightThumState;

		public:
			/// <summary>
			///	�Q�[���p�b�h���͂̍X�V
			/// </summary>
			/// <param name="padNum">�Q�[���p�b�h�ԍ�</param>
			void UpdateGamePadState(const int& padNum);

			/// <summary>
			/// �R�[�h�ɑΉ�����{�^���������ꂽ�u�Ԃ��𔻕ʂ���֐�
			/// </summary>
			/// <param name="xinputCode">���ʗp�R�[�h</param>
			/// <returns>�����ꂽ�u�ԂȂ�true</returns>
			bool IsInputDown(const XInputCode& xinputCode) const override;

			/// <summary>
			/// �R�[�h�ɑΉ�����{�^����������Ă��邩�𔻕ʂ���֐�
			/// </summary>
			/// <param name="xinputCode">���ʗp�R�[�h</param>
			/// <returns>������Ă���Ȃ�true</returns>
			bool IsInputPush(const XInputCode& xinputCode) const override;

			/// <summary>
			/// �R�[�h�ɑΉ�����{�^���������ꂽ�u�Ԃ��𔻕ʂ���֐�
			/// </summary>
			/// <param name="xinputCode">���ʗp�R�[�h</param>
			/// <returns>�����ꂽ�u�ԂȂ�true</returns>
			bool IsInputUp(const XInputCode& xinputCode) const override;

			/// <summary>
			/// ���X�e�B�b�N���͂��擾����
			/// </summary>
			/// <returns>���X�e�B�b�N���͏��</returns>
			const XInputGamePadThumbState& GetLeftThumb() const override;

			/// <summary>
			/// �E�X�e�B�b�N���͂��擾����
			/// </summary>
			/// <returns>�E�X�e�B�b�N���͏��</returns>
			const XInputGamePadThumbState& GetRightThumb() const override;
		};

		/// <summary>
		/// XBox�R���g���[���[�̔ԍ��ƃR�[�h�̃y�A�\����
		/// </summary>
		struct XInputCodePair
		{
			/// <summary>
			/// �R���g���[���[�ԍ�
			/// </summary>
			int num;
			/// <summary>
			/// �R�[�h
			/// </summary>
			XInputCode xinputCode;

			/// <summary>
			/// �R���X�g���N�^
			/// </summary>
			/// <param name="num">�R���g���[���[�ԍ�</param>
			/// <param name="xinputCode">XBox�R���g���[���[�{�^���R�[�h</param>
			XInputCodePair(const int num, const XInputCode& xinputCode);

			bool operator==(const XInputCodePair& codePair) const noexcept;

			bool operator!=(const XInputCodePair& codePair) const noexcept;
		};

		/// <summary>
		/// ���͗p�R�[�h�\����
		/// </summary>
		struct CodeData
		{
			/// <summary>
			/// �L�[�{�[�h�R�[�h�z��
			/// </summary>
			std::vector<KeyCode> keycodes;
			/// <summary>
			/// Xbox�R���g���[���[�R�[�h�i�ԍ��t���j�z��
			/// </summary>
			std::vector<XInputCodePair> xinputCodePairs;

			/// <summary>
			/// ���̓R�[�h������ݒ肳��Ă��Ȃ���
			/// </summary>
			/// <returns>�R�[�h���Ȃ����true</returns>
			bool IsEmptyCode();
		};

		/// <summary>
		/// ���̓C�x���g�f�[�^�\����
		/// </summary>
		struct InputEventData
		{
			/// <summary>
			/// �Ă΂��C�x���g
			/// </summary>
			Utility::Delegate<void()> inputEvent;

			/// <summary>
			/// �C�x���g�Ή��R�[�h
			/// </summary>
			CodeData codedata;
		};

		/// <summary>
		/// �R���g���[���[�N���X
		/// </summary>
		class InputerBase
		{
			friend class InputDevice;

			/// <summary>
			/// �����C�x���g�z��
			/// </summary>
			static std::vector<InputEventData> m_downEventDatas;
			/// <summary>
			/// �������C�x���g�z��
			/// </summary>
			static std::vector<InputEventData> m_upEventDatas;

			/// <summary>
			/// �L�[�{�[�h���̓C�x���g
			/// </summary>
			/// <param name="keycode">���̓L�[�R�[�h</param>
			/// <param name="eventDatas">�Ή��C�x���g�z��</param>
			void OnKeyEvent(const KeyCode& keycode, std::vector<InputEventData>& eventDatas);

			/// <summary>
			/// XBox�R���g���[���[���̓C�x���g
			/// </summary>
			/// <remarks>
			/// �C�x���g�f�[�^�̃R�[�h����Ȃ��AnyKey�Ƃ���
			/// </remarks>
			/// <param name="codePair">����XBox�R�[�h</param>
			/// <param name="eventDatas">�Ή��C�x���g�z��</param>
			void OnXInputEvent(const XInputCodePair& codePair, std::vector<InputEventData>& eventDatas);

			/// <summary>
			/// �L�[�{�[�h�������ꂽ���̓C�x���g
			/// </summary>
			/// <param name="keycode">�L�[�R�[�h</param>
			void OnKeyDown(const KeyCode& keycode);
			/// <summary>
			/// XBox�R���g���[���[�������ꂽ���̓C�x���g
			/// </summary>
			/// <param name="num">�R���g���[���[�ԍ�</param>
			/// <param name="xinputCode">XBox�R���g���[���[�{�^���R�[�h</param>
			void OnXInputDown(const int num, const XInputCode& xinputCode);

			/// <summary>
			/// �L�[�{�[�h�������ꂽ���̓C�x���g
			/// </summary>
			/// <param name="keycode">�L�[�R�[�h</param>
			void OnKeyUp(const KeyCode& keycode);
			/// <summary>
			/// XBox�R���g���[���[�������ꂽ���̓C�x���g
			/// </summary>
			/// <param name="num">�R���g���[���[�ԍ�</param>
			/// <param name="xinputCode">�{�^���R�[�h</param>
			void OnXInputUp(const int num, const XInputCode& xinputCode);

		protected:
			/// <summary>
			/// �p���p�R���X�g���N�^
			/// </summary>
			/// <returns></returns>
			InputerBase() noexcept = default;

			/// <summary>
			/// �����ꂽ�C�x���g�ǉ��֐�
			/// </summary>
			/// <param name="eventData">�C�x���g�f�[�^</param>
			static void AddDownEvent(const InputEventData& eventData);

			/// <summary>
			/// �����ꂽ�C�x���g�ǉ��֐�
			/// </summary>
			/// <param name="eventData">�C�x���g�f�[�^</param>
			static void AddUpEvent(const InputEventData& eventData);
		};

		/// <summary>
		/// �f�o�C�X���͊Ǘ��N���X
		/// </summary>
		class InputDevice
		{
			/// <summary>
			/// �}�E�X�̏�ԕϐ�
			/// </summary>
			MouseState m_mouseState;

			/// <summary>
			/// �L�[�{�[�h�̏�ԕϐ�
			/// </summary>
			KeyBoardState m_keyBoardState;

			/// <summary>
			/// �ő�XBox�R���g���[���[�Ǘ���
			/// </summary>
			static constexpr int MAX_GAMEPAD_NUM = 4;

			/// <summary>
			/// XBox�R���g���[���[4�����z��
			/// </summary>
			std::array<XInputGamePadState, MAX_GAMEPAD_NUM> m_gamePadState;

			/// <summary>
			/// �R���g���[���[�z��
			/// </summary>
			std::vector<std::unique_ptr<InputerBase>> m_inputers;

			/// <summary>
			/// XBox�R���g���[���[�̓��̓C�x���g���ĂԊ֐�
			/// </summary>
			void XInputGamePadInputEvent();
		public:
			/// <summary>
			/// ���̓f�o�C�X�̍X�V
			/// </summary>
			/// <param name="hwnd">�E�B���h�E�̃n���h��</param>
			void UpdateDevice(const HWND& hwnd);

			/// <summary>
			/// �L�[�����C�x���g
			/// </summary>
			/// <param name="vk_keycode">�����������z�L�[�R�[�h</param>
			void OnKeyDown(const UINT8 vk_keycode);

			/// <summary>
			/// �L�[�𗣂����C�x���g
			/// </summary>
			/// <param name="vk_keycode">���������z�L�[�R�[�h</param>
			void OnKeyUp(const UINT8 vk_keycode);

			const MouseState& GetMouseState() const noexcept;

			/// <summary>
			/// �L�[�{�[�h�̏�Ԃ�Ԃ��֐�
			/// </summary>
			/// <returns>�L�[�{�[�h�̏��</returns>
			const I_KeyBoardInputEventGetter& GetKeyBoard() const noexcept;

			/// <summary>
			/// XBox�R���g���[���[�̏�Ԃ�Ԃ��֐�
			/// </summary>
			/// <param name="num">�R���g���[���[�ԍ�</param>
			/// <returns>�R���g���[���[�̏��</returns>
			const I_XInputEventGetter& GetXInputGamePad(const int& num = 0) const noexcept;

			/// <summary>
			/// XBox�R���g���[���[�̏�Ԃ̔z���Ԃ��֐�
			/// </summary>
			/// <returns>�R���g���[���[�̏�Ԃ̔z��</returns>
			const std::array<XInputGamePadState, MAX_GAMEPAD_NUM>& GetXInputGamePads() const noexcept;

			/// <summary>
			/// �Ǘ�����R���g���[���[��o�^����֐�
			/// </summary>
			/// <param name="inputer">�o�^����R���g���[���[</param>
			void AddInputer(InputerBase* inputer);

			void MessageChecker(const UINT message, const WPARAM wParam, const LPARAM lParam);
		};

		class I_BasicInputer
		{
		public:
			virtual bool IsDesitionDown() const = 0;

			virtual bool IsCancelDown() const = 0;

			virtual bool IsUpDown() const = 0;

			virtual bool IsUp() const = 0;

			virtual bool IsDownDown() const = 0;

			virtual bool IsDown() const = 0;

			virtual bool IsLeftDown() const = 0;

			virtual bool IsLeft() const = 0;

			virtual bool IsRightDown() const = 0;

			virtual bool IsRight() const = 0;
		};
	}
}