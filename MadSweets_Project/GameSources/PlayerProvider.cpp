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
		MessageBox(0, L"����ɌĂ΂ꂽ", L"�ǂ����悤", 0);
	}
}