/*!
@file EscapeEnemy.cpp
@brief EscapeEnemy�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

#include "EscapeEnemy.h"

#include "EnState_Plowling.h"
#include "EnState_EscapeMove.h"
#include "EnState_LoseTarget.h"

#include "EyeSearchRange.h"
#include "AstarCtrl.h"

#include "I_Escape.h"
#include "AshiStator.h"

namespace basecross {

	void EscapeEnemy::OnCreate() {
		//ChangeStateMachine<EnState_Plowling>();
	}

	void EscapeEnemy::OnUpdate() {
		BaseEnemy::OnUpdate();

		//EyeSearch();
	}

	//void EscapeEnemy::StartEscape(const std::shared_ptr<GameObject>& target) {
	//	//auto stator = GetGameObject()->GetComponent<AshiStator>(false);
	//	//if (stator) {
	//	//	stator->GetTransitionMemeber().escapeTrigger.Fire();
	//	//}

	//	//ChangeStateMachine<EnState_EscapeMove>(target);
	//}

	//void EscapeEnemy::SuccessEscape() {
	//	//auto stator = GetGameObject()->GetComponent<AshiStator>(false);
	//	//if (stator) {
	//	//	stator->GetTransitionMemeber().loseTrigger.Fire();
	//	//}

	//	//ChangeStateMachine<EnState_LoseTarget>();
	//}

	//void EscapeEnemy::EyeSearch() {
	//	//auto obj = GetGameObject();
	//	//auto eye = obj->GetComponent<EyeSearchRange>(false);
	//	//if (!eye) {  //�����Ă��Ȃ������珈�������Ȃ�
	//	//	return;
	//	//}

	//	//if(eye->IsLookTarget(obj)) {  //�������Ȃ�
	//	//	auto astar = obj->GetComponent<AstarCtrl>(false);
	//	//	if (astar) {
	//	//		//astar->SearchAstarEscapeStart();
	//	//	}
	//	//	//�X�e�[�g�ύX
	//	//	ChangeStateMachine<EnState_EscapeMove>();
	//	//}
	//}
}