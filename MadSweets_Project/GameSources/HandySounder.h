#pragma once
#include "SoundHelper.h"

namespace basecross
{
	class HandySounder : public Component
	{
		ex_weak_ptr<SoundEmitter> m_soundEmitter;

		SoundClip m_walkSoundClip;
	public:
		HandySounder(std::shared_ptr<GameObject>& owner);

		void WalkSound();

		void OnStart() override;
	};
}