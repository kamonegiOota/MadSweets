#include"HandySounder.h"

namespace basecross
{
	HandySounder::HandySounder(std::shared_ptr<GameObject>& owner) :
		Component(owner),
		m_walkSoundClip(L"HandyWalkSE1", false, 1.0f)
	{

	}

	void HandySounder::WalkSound()
	{
		m_soundEmitter->PlaySoundClip(m_walkSoundClip);
	}

	void HandySounder::OnStart()
	{
		m_soundEmitter = GetGameObject()->GetComponent<SoundEmitter>();
	}
}