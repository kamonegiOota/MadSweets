#include"MenuButtonSounder.h"

namespace basecross
{
	MenuButtonSounder::MenuButtonSounder(std::shared_ptr<GameObject>& stage) :
		Component(stage)
	{

	}

	void MenuButtonSounder::SetOutSelectSoundKey(const std::wstring& selectSoundKey)
	{
		m_selectSoundKey = selectSoundKey;
	}

	void MenuButtonSounder::SetPushSoundKey(const std::wstring& pushSoundKey)
	{
		m_pushSoundKey = pushSoundKey;
	}


	void MenuButtonSounder::OnOutSelectSoundPlay()
	{
		if (m_selectSoundKey == L"")
		{
			return;
		}

		SimpleSoundManager::OnePlaySE(m_selectSoundKey);
	}

	void MenuButtonSounder::OnPushSoundPlay()
	{
		if (m_pushSoundKey == L"")
		{
			return;
		}

		SimpleSoundManager::OnePlaySE(m_pushSoundKey);
	}

	void MenuButtonSounder::OnCreate()
	{

	}
}