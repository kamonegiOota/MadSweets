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
		MessageBox(0, L"勝手に呼ばれた", L"どうしよう", 0);
	}
}