#include "PlayerSounder.h"
#include "SoundHelper.h"

namespace basecross
{
	PlayerSounder::PlayerSounder(std::shared_ptr<GameObject>& owner) :
		Component(owner)
	{

	}

	void PlayerSounder::PlayerWalk()
	{
		SimpleSoundManager::OnePlaySE(L"PlayerWalkSE1",1.00f);
	}
}