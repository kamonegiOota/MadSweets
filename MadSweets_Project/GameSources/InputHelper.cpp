#include"InputHelper.h"

namespace itbs
{
	namespace Input
	{
		// CursorSetting -------------------------------------
		
		bool CursorSetting::m_isLock = false;
		bool CursorSetting::m_isDraw = true;

		void CursorSetting::SetIsLock(const bool isLock)
		{
			m_isLock = isLock;
		}

		void CursorSetting::SetIsDraw(const bool isDraw)
		{
			m_isDraw = isDraw;
			ShowCursor(m_isDraw);
		}

		bool CursorSetting::GetIsLock()
		{
			return m_isLock;
		}

		bool CursorSetting::GetIsDraw()
		{
			return m_isDraw;
		}

		// MouseState ----------------------------------------
		
		void MouseState::UpdateMouseState()
		{
			POINT point;
			GetCursorPos(&point);

			m_mouseMoveRange.x = point.x - m_mousePosition.x;
			m_mouseMoveRange.y = point.y - m_mousePosition.y;

			m_mousePosition = point;
		}

		POINT MouseState::GetMouseMove() const
		{
			return m_mouseMoveRange;
		}

		// KeyBoardState -------------------------------------

		void KeyBoardState::UpdateInputKeyState()
		{
			m_beforeKeycodeTable.swap(m_nowKeycodeTable);

			for (int i = 0; i < MAX_KEYCODE; i++)
			{
				m_nowKeycodeTable[i] = (GetAsyncKeyState(i) & GET_ASYNC_KEY_PUSH_BIT) != 0;
			}
		}

		bool KeyBoardState::IsKeyDown(const KeyCode& keycode) const noexcept
		{
			UINT8 tableCode = static_cast<UINT8>(keycode);
			return m_nowKeycodeTable[tableCode] && !m_beforeKeycodeTable[tableCode];
		}

		bool KeyBoardState::IsKeyPush(const KeyCode& keycode) const noexcept
		{
			UINT8 tableCode = static_cast<UINT8>(keycode);
			return m_nowKeycodeTable[tableCode];
		}

		bool KeyBoardState::IsKeyUp(const KeyCode& keycode) const noexcept
		{
			UINT8 tableCode = static_cast<UINT8>(keycode);
			return !m_nowKeycodeTable[tableCode] && m_beforeKeycodeTable[tableCode];
		}


		// XInputGamePadThumbState ----------------------------

		void XInputGamePadThumbState::UpdateState(const float x,const float y,const int deadzone)
		{
			if ((deadzone > x && x > -deadzone) &&
				(deadzone > y && y > -deadzone))
			{
				this->x = 0;
				this->y = 0;
				return;
			}

			this->x = x / INPUT_MAX_VALUE;
			this->y = y / INPUT_MAX_VALUE;
		}

		// XInputGamePadState --------------------------------

		void XInputGamePadState::UpdateGamePadState(const int& padNum)
		{
			XINPUT_STATE state;
			DWORD result = XInputGetState(padNum, &state);

			m_beforeGamepad = m_nowGamepad;

			// パッド情報の取得に成功したならば
			if (result == ERROR_SUCCESS)
			{
				m_nowGamepad = state.Gamepad;

				m_leftThumState.UpdateState(m_nowGamepad.sThumbLX, m_nowGamepad.sThumbLY, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
				m_rightThumState.UpdateState(m_nowGamepad.sThumbRX, m_nowGamepad.sThumbRY, XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
			}
		}

		bool XInputGamePadState::IsButtonDown(const XInputCode& xinputCode) const noexcept
		{
			WORD buttonCode = static_cast<WORD>(xinputCode);
			return (m_nowGamepad.wButtons & buttonCode) && !(m_beforeGamepad.wButtons & buttonCode);
		}

		bool XInputGamePadState::IsButtonPush(const XInputCode& xinputCode) const noexcept
		{
			WORD buttonCode = static_cast<WORD>(xinputCode);
			return m_nowGamepad.wButtons & buttonCode;
		}

		bool XInputGamePadState::IsButtonUp(const XInputCode& xinputCode) const noexcept
		{
			WORD buttonCode = static_cast<WORD>(xinputCode);
			return !(m_nowGamepad.wButtons & buttonCode) && (m_beforeGamepad.wButtons & buttonCode);
		}

		const XInputGamePadThumbState& XInputGamePadState::GetLeftThumb() const
		{
			return m_leftThumState;
		}

		const XInputGamePadThumbState& XInputGamePadState::GetRightThumb() const
		{
			return m_rightThumState;
		}

		// XInputCodePair --------------------------------------

		XInputCodePair::XInputCodePair(const int num, const XInputCode& xinputCode) :
			num(num),
			xinputCode(xinputCode)
		{
			
		}

		bool XInputCodePair::operator==(const XInputCodePair& codePair) const noexcept
		{
			return num == codePair.num && xinputCode == codePair.xinputCode;
		}

		bool XInputCodePair::operator!=(const XInputCodePair& codePair) const noexcept
		{
			return !(*this == codePair);
		}

		// CodeData --------------------------------------

		bool CodeData::IsEmptyCode()
		{
			return keycodes.empty() && xinputCodePairs.empty();
		}

		// InputerBase -----------------------------------------

		std::vector<InputEventData> InputerBase::m_downEventDatas;
		std::vector<InputEventData> InputerBase::m_upEventDatas;

		void InputerBase::OnKeyEvent(const KeyCode& keycode, std::vector<InputEventData>& eventDatas)
		{
			for (auto& eventData : eventDatas)
			{
				// イベントコードが登録されていなければAnyKeyとして扱う
				if (eventData.codedata.IsEmptyCode())
				{
					eventData.inputEvent();
					continue;
				}

				auto& keycodes = eventData.codedata.keycodes;
				auto result = std::find(keycodes.begin(), keycodes.end(), keycode);
				if (result != keycodes.end())
				{
					eventData.inputEvent();
				}
			}
		}

		void InputerBase::OnXInputEvent(const XInputCodePair& codePair, std::vector<InputEventData>& eventDatas)
		{
			for (auto& eventData : eventDatas)
			{
				// イベントコードが登録されていなければAnyKeyとして扱う
				if (eventData.codedata.IsEmptyCode())
				{
					eventData.inputEvent();
					continue;
				}

				auto& codePairs = eventData.codedata.xinputCodePairs;
				auto result = std::find(codePairs.begin(), codePairs.end(), codePair);
				if (result != codePairs.end())
				{
					eventData.inputEvent();
				}
			}
		}

		void InputerBase::OnKeyDown(const KeyCode& keycode)
		{
			OnKeyEvent(keycode, m_downEventDatas);
		}

		void InputerBase::OnXInputDown(const int num, const XInputCode& xinputCode)
		{
			XInputCodePair pair = { num,xinputCode };
			OnXInputEvent(pair, m_downEventDatas);
		}

		void InputerBase::OnKeyUp(const KeyCode& keycode)
		{
			OnKeyEvent(keycode, m_upEventDatas);
		}

		void InputerBase::OnXInputUp(const int num, const XInputCode& xinputCode)
		{
			XInputCodePair pair = { num,xinputCode };
			OnXInputEvent(pair, m_upEventDatas);
		}

		void InputerBase::AddDownEvent(const InputEventData& eventData)
		{
			m_downEventDatas.push_back(eventData);
		}

		void InputerBase::AddUpEvent(const InputEventData& eventData)
		{
			m_upEventDatas.push_back(eventData);
		}

		// InputDevice -----------------------------------------

		void InputDevice::XInputGamePadInputEvent()
		{
			for (int i = 0; i < MAX_GAMEPAD_NUM; ++i)
			{
				// 1ビットずつずらしながら、ボタンの対応ビットを作成し、それと比較してボタンイベントを調べる

				WORD buttonCode = 1;

				auto& gamePad = m_gamePadState[i];

				while (buttonCode != 0)
				{
					XInputCode xinputCode = static_cast<XInputCode>(buttonCode);
					if (gamePad.IsButtonDown(xinputCode))
					{
						for (auto& inputer : m_inputers)
						{
							inputer->OnXInputDown(i, xinputCode);
						}
					}

					if (gamePad.IsButtonUp(xinputCode))
					{
						for (auto& inputer : m_inputers)
						{
							inputer->OnXInputUp(i, xinputCode);
						}
					}

					buttonCode <<= 1;
				}
			}
		}

		void InputDevice::UpdateDevice()
		{
			m_mouseState.UpdateMouseState();

			m_keyBoardState.UpdateInputKeyState();

			for (int i = 0; i < MAX_GAMEPAD_NUM; ++i)
			{
				m_gamePadState[i].UpdateGamePadState(i);
			}

			XInputGamePadInputEvent();
		}

		void InputDevice::OnKeyDown(const UINT8 vk_keycode)
		{
			for (auto& inputer : m_inputers)
			{
				inputer->OnKeyDown(static_cast<KeyCode>(vk_keycode));
			}
		}

		void InputDevice::OnKeyUp(const UINT8 vk_keycode)
		{
			for (auto& inputer : m_inputers)
			{
				inputer->OnKeyUp(static_cast<KeyCode>(vk_keycode));
			}
		}

		const MouseState& InputDevice::GetMouseState() const noexcept
		{
			return m_mouseState;
		}

		const KeyBoardState& InputDevice::GetKeyBoard() const noexcept
		{
			return m_keyBoardState;
		}

		const XInputGamePadState& InputDevice::GetXInputGamePad(const int& num) const noexcept
		{
			return m_gamePadState[num];
		}

		const std::array<XInputGamePadState,InputDevice::MAX_GAMEPAD_NUM>& InputDevice::GetXInputGamePads() const noexcept
		{
			return m_gamePadState;
		}

		void InputDevice::AddInputer(InputerBase* inputer)
		{
			m_inputers.push_back(std::unique_ptr<InputerBase>(inputer));
		}
	}
}