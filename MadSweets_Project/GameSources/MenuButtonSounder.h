#pragma once
#include"SoundHelper.h"

namespace basecross
{
	class MenuButtonSounder : public Component
	{
		std::wstring m_selectSoundKey;
		std::wstring m_pushSoundKey;
	public:
		MenuButtonSounder(std::shared_ptr<GameObject>& owner);

		void SetOutSelectSoundKey(const std::wstring& selectSoundKey);
		void SetPushSoundKey(const std::wstring& pushSoundKey);

		void OnOutSelectSoundPlay();

		void OnPushSoundPlay();

		void OnCreate() override;

	};
}