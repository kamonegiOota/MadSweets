#include"HandySounder.h"

namespace basecross
{
	HandySounder::HandySounder(std::shared_ptr<GameObject>& owner) :
		Component(owner),
		m_walkSoundClip(L"HandyWalkSE2", false, 0.25f)
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