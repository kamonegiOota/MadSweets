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
		/// L[{[hÌL[ñ^
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
		/// XBoxQ[pbhÌ{^ñ^
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
		/// }EXf[^ÇNX
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
		/// L[{[hüÍf[^ÇNX
		/// </summary>
		class KeyBoardState : public I_KeyBoardInputEventGetter
		{
			/// <summary>
			/// L[R[hÅå
			/// </summary>
			static constexpr int MAX_KEYCODE = 256;

			/// <summary>
			/// GetAsyncKeyStateÅæ¾µ½L[îñÌ³êÄ¢é©Ç¤©ÌtOrbg
			/// </summary>
			static constexpr unsigned short GET_ASYNC_KEY_PUSH_BIT = 0x8000;

			/// <summary>
			/// PñÄÑoµOÌüÍ³ê½L[e[u
			/// </summary>
			std::array<bool, MAX_KEYCODE> m_beforeKeycodeTable;
			/// <summary>
			/// »ÝÌt[ÉüÍ³ê½L[e[u
			/// </summary>
			std::array<bool, MAX_KEYCODE> m_nowKeycodeTable;

			std::queue<KeyCode> m_downEventQueue;

			std::queue<KeyCode> m_upEventQueue;
		public:
			/// <summary>
			/// L[{[hüÍÌXV
			/// </summary>
			void UpdateInputKeyState();

			/// <summary>
			/// L[R[hÉÎ·éL[ª³ê½uÔ©ð»Ê·éÖ
			/// </summary>
			/// <param name="keycode">»ÊpL[R[h</param>
			/// <returns>³ê½uÔÈçtrue</returns>
			bool IsInputDown(const KeyCode& keycode) const override;

			/// <summary>
			/// L[R[hÉÎ·éL[ª³êÄ¢é©ð»Ê·éÖ
			/// </summary>
			/// <param name="keycode">»ÊpL[R[h</param>
			/// <returns>³êÄ¢éÈçtrue</returns>
			bool IsInputPush(const KeyCode& keycode) const override;

			/// <summary>
			/// L[R[hÉÎ·éL[ª£³ê½uÔ©ð»Ê·éÖ
			/// </summary>
			/// <param name="keycode">»ÊpL[R[h</param>
			/// <returns>£³ê½uÔÈçtrue</returns>
			bool IsInputUp(const KeyCode& keycode) const override;

			void AddDownEvent(const KeyCode& keycode);

			void AddUpEvent(const KeyCode& keycode);
		};

		/// <summary>
		/// XBoxRg[[üÍîñ\¢Ì
		/// </summary>
		struct XInputGamePadThumbState
		{
			static constexpr SHORT INPUT_MAX_VALUE = 0x7FFF;

			float x;
			float y;

			/// <summary>
			/// üÍîñÌXV
			/// </summary>
			/// <param name="x">XüÍ</param>
			/// <param name="y">YüÍ</param>
			/// <param name="deadzone">µ«¢l</param>
			void UpdateState(const float x, const float y,const int deadzone);
		};

		class I_XInputEventGetter : public I_InputEventGetter<XInputCode>
		{
		public:
			/// <summary>
			/// ¶XeBbNüÍðæ¾·é
			/// </summary>
			/// <returns>¶XeBbNüÍîñ</returns>
			virtual const XInputGamePadThumbState& GetLeftThumb() const = 0;

			/// <summary>
			/// EXeBbNüÍðæ¾·é
			/// </summary>
			/// <returns>EXeBbNüÍîñ</returns>
			virtual const XInputGamePadThumbState& GetRightThumb() const = 0;
		};
		/// <summary>
		/// XBoxRg[[üÍf[^ÇNX
		/// </summary>
		class XInputGamePadState : public I_XInputEventGetter
		{
			/// <summary>
			/// PñÄÑoµOÌQ[pbhîñ
			/// </summary>
			XINPUT_GAMEPAD m_beforeGamepad;
			/// <summary>
			/// »ÝÌQ[pbhîñ
			/// </summary>
			XINPUT_GAMEPAD m_nowGamepad;

			/// <summary>
			/// ¶XeBbNüÍîñ
			/// </summary>
			XInputGamePadThumbState m_leftThumState;
			/// <summary>
			/// EXeBbNüÍîñ
			/// </summary>
			XInputGamePadThumbState m_rightThumState;

		public:
			/// <summary>
			///	Q[pbhüÍÌXV
			/// </summary>
			/// <param name="padNum">Q[pbhÔ</param>
			void UpdateGamePadState(const int& padNum);

			/// <summary>
			/// R[hÉÎ·é{^ª³ê½uÔ©ð»Ê·éÖ
			/// </summary>
			/// <param name="xinputCode">»ÊpR[h</param>
			/// <returns>³ê½uÔÈçtrue</returns>
			bool IsInputDown(const XInputCode& xinputCode) const override;

			/// <summary>
			/// R[hÉÎ·é{^ª³êÄ¢é©ð»Ê·éÖ
			/// </summary>
			/// <param name="xinputCode">»ÊpR[h</param>
			/// <returns>³êÄ¢éÈçtrue</returns>
			bool IsInputPush(const XInputCode& xinputCode) const override;

			/// <summary>
			/// R[hÉÎ·é{^ª£³ê½uÔ©ð»Ê·éÖ
			/// </summary>
			/// <param name="xinputCode">»ÊpR[h</param>
			/// <returns>£³ê½uÔÈçtrue</returns>
			bool IsInputUp(const XInputCode& xinputCode) const override;

			/// <summary>
			/// ¶XeBbNüÍðæ¾·é
			/// </summary>
			/// <returns>¶XeBbNüÍîñ</returns>
			const XInputGamePadThumbState& GetLeftThumb() const override;

			/// <summary>
			/// EXeBbNüÍðæ¾·é
			/// </summary>
			/// <returns>EXeBbNüÍîñ</returns>
			const XInputGamePadThumbState& GetRightThumb() const override;
		};

		/// <summary>
		/// XBoxRg[[ÌÔÆR[hÌyA\¢Ì
		/// </summary>
		struct XInputCodePair
		{
			/// <summary>
			/// Rg[[Ô
			/// </summary>
			int num;
			/// <summary>
			/// R[h
			/// </summary>
			XInputCode xinputCode;

			/// <summary>
			/// RXgN^
			/// </summary>
			/// <param name="num">Rg[[Ô</param>
			/// <param name="xinputCode">XBoxRg[[{^R[h</param>
			XInputCodePair(const int num, const XInputCode& xinputCode);

			bool operator==(const XInputCodePair& codePair) const noexcept;

			bool operator!=(const XInputCodePair& codePair) const noexcept;
		};

		/// <summary>
		/// üÍpR[h\¢Ì
		/// </summary>
		struct CodeData
		{
			/// <summary>
			/// L[{[hR[hzñ
			/// </summary>
			std::vector<KeyCode> keycodes;
			/// <summary>
			/// XboxRg[[R[hiÔt«jzñ
			/// </summary>
			std::vector<XInputCodePair> xinputCodePairs;

			/// <summary>
			/// üÍR[hªêÂàÝè³êÄ¢È¢©
			/// </summary>
			/// <returns>R[hªÈ¯êÎtrue</returns>
			bool IsEmptyCode();
		};

		/// <summary>
		/// üÍCxgf[^\¢Ì
		/// </summary>
		struct InputEventData
		{
			/// <summary>
			/// ÄÎêéCxg
			/// </summary>
			Utility::Delegate<void()> inputEvent;

			/// <summary>
			/// CxgÎR[h
			/// </summary>
			CodeData codedata;
		};

		/// <summary>
		/// Rg[[NX
		/// </summary>
		class InputerBase
		{
			friend class InputDevice;

			/// <summary>
			/// ºCxgzñ
			/// </summary>
			static std::vector<InputEventData> m_downEventDatas;
			/// <summary>
			/// £µ½Cxgzñ
			/// </summary>
			static std::vector<InputEventData> m_upEventDatas;

			/// <summary>
			/// L[{[hüÍCxg
			/// </summary>
			/// <param name="keycode">üÍL[R[h</param>
			/// <param name="eventDatas">ÎCxgzñ</param>
			void OnKeyEvent(const KeyCode& keycode, std::vector<InputEventData>& eventDatas);

			/// <summary>
			/// XBoxRg[[üÍCxg
			/// </summary>
			/// <remarks>
			/// Cxgf[^ÌR[hªóÈçÎAnyKeyÆ·é
			/// </remarks>
			/// <param name="codePair">üÍXBoxR[h</param>
			/// <param name="eventDatas">ÎCxgzñ</param>
			void OnXInputEvent(const XInputCodePair& codePair, std::vector<InputEventData>& eventDatas);

			/// <summary>
			/// L[{[hª³ê½üÍCxg
			/// </summary>
			/// <param name="keycode">L[R[h</param>
			void OnKeyDown(const KeyCode& keycode);
			/// <summary>
			/// XBoxRg[[ª³ê½üÍCxg
			/// </summary>
			/// <param name="num">Rg[[Ô</param>
			/// <param name="xinputCode">XBoxRg[[{^R[h</param>
			void OnXInputDown(const int num, const XInputCode& xinputCode);

			/// <summary>
			/// L[{[hª£³ê½üÍCxg
			/// </summary>
			/// <param name="keycode">L[R[h</param>
			void OnKeyUp(const KeyCode& keycode);
			/// <summary>
			/// XBoxRg[[ª£³ê½üÍCxg
			/// </summary>
			/// <param name="num">Rg[[Ô</param>
			/// <param name="xinputCode">{^R[h</param>
			void OnXInputUp(const int num, const XInputCode& xinputCode);

		protected:
			/// <summary>
			/// p³pRXgN^
			/// </summary>
			/// <returns></returns>
			InputerBase() noexcept = default;

			/// <summary>
			/// ³ê½CxgÇÁÖ
			/// </summary>
			/// <param name="eventData">Cxgf[^</param>
			static void AddDownEvent(const InputEventData& eventData);

			/// <summary>
			/// £³ê½CxgÇÁÖ
			/// </summary>
			/// <param name="eventData">Cxgf[^</param>
			static void AddUpEvent(const InputEventData& eventData);
		};

		/// <summary>
		/// foCXüÍÇNX
		/// </summary>
		class InputDevice
		{
			/// <summary>
			/// }EXÌóÔÏ
			/// </summary>
			MouseState m_mouseState;

			/// <summary>
			/// L[{[hÌóÔÏ
			/// </summary>
			KeyBoardState m_keyBoardState;

			/// <summary>
			/// ÅåXBoxRg[[Ç
			/// </summary>
			static constexpr int MAX_GAMEPAD_NUM = 4;

			/// <summary>
			/// XBoxRg[[4ÂðÂzñ
			/// </summary>
			std::array<XInputGamePadState, MAX_GAMEPAD_NUM> m_gamePadState;

			/// <summary>
			/// Rg[[zñ
			/// </summary>
			std::vector<std::unique_ptr<InputerBase>> m_inputers;

			/// <summary>
			/// XBoxRg[[ÌüÍCxgðÄÔÖ
			/// </summary>
			void XInputGamePadInputEvent();
		public:
			/// <summary>
			/// üÍfoCXÌXV
			/// </summary>
			/// <param name="hwnd">EBhEÌnh</param>
			void UpdateDevice(const HWND& hwnd);

			/// <summary>
			/// L[ºCxg
			/// </summary>
			/// <param name="vk_keycode">ºµ½¼zL[R[h</param>
			void OnKeyDown(const UINT8 vk_keycode);

			/// <summary>
			/// L[ð£µ½Cxg
			/// </summary>
			/// <param name="vk_keycode">£µ½¼zL[R[h</param>
			void OnKeyUp(const UINT8 vk_keycode);

			const MouseState& GetMouseState() const noexcept;

			/// <summary>
			/// L[{[hÌóÔðÔ·Ö
			/// </summary>
			/// <returns>L[{[hÌóÔ</returns>
			const I_KeyBoardInputEventGetter& GetKeyBoard() const noexcept;

			/// <summary>
			/// XBoxRg[[ÌóÔðÔ·Ö
			/// </summary>
			/// <param name="num">Rg[[Ô</param>
			/// <returns>Rg[[ÌóÔ</returns>
			const I_XInputEventGetter& GetXInputGamePad(const int& num = 0) const noexcept;

			/// <summary>
			/// XBoxRg[[ÌóÔÌzñðÔ·Ö
			/// </summary>
			/// <returns>Rg[[ÌóÔÌzñ</returns>
			const std::array<XInputGamePadState, MAX_GAMEPAD_NUM>& GetXInputGamePads() const noexcept;

			/// <summary>
			/// Ç·éRg[[ðo^·éÖ
			/// </summary>
			/// <param name="inputer">o^·éRg[[</param>
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