#include"PlayerProvider.h"

namespace basecross
{
	PlayerProvider::PlayerProvider(std::shared_ptr<GameObject>& owner) :
		Component(owner)
	{
	}

	void PlayerProvider::OnCreate()
	{

	}

	void PlayerProvider::OnUpdate()
	{

	}

	void PlayerProvider::TestFunction()
	{
		MessageBox(0, L"Ÿè‚ÉŒÄ‚Î‚ê‚½", L"‚Ç‚¤‚µ‚æ‚¤", 0);
	}
}