#include"PlayerChoicesListObject.h"

namespace basecross
{
	PlayerChoicesListObject::PlayerChoicesListObject(std::shared_ptr<Stage>& stage) :
		UIObject(stage)
	{

	}

	void PlayerChoicesListObject::OnCreate()
	{
		GetComponent<RectTransform>()->SetPosition(300, 0);

		auto mo = AddComponent<ChoicesList>();

		GetStage()->SetSharedGameObject(L"PlayerChoicesList", GetThis<PlayerChoicesListObject>());
	}
}