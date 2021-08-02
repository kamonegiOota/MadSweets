/*!
@file GraphNode.cpp
@brief GraphNode‚È‚ÇŽÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"

#include "EnState_CheckSoundPos.h"
#include "DebugObject.h"

#include "CheckTargetPos.h"
#include "TargetChase.h"
#include "PlowlingMove.h"
#include "ReturnPlowlingPosition.h"
#include "Velocity.h"

#include "AstarCtrl.h"

namespace basecross {

	void EnState_CheckSoundPos::OnStart() {
		auto obj = GetOwner()->GetGameObject();

		auto astar = obj->GetComponent<AstarCtrl>(false);
		if (astar) {
			astar->SearchAstarStart(m_targetPos);
		}
		
		AddChangeComp(obj->GetComponent<CheckTargetPos>(false), true, false);
		AddChangeComp(obj->GetComponent<PlowlingMove>(false), false, false);
		AddChangeComp(obj->GetComponent<ReturnPlowlingPosition>(false), false, false);

		StartChangeComps();

		auto draw = obj->GetComponent<BcBaseDraw>(false);
		if (draw) {
			draw->SetDiffuse(Col4(1.0f, 0.0f, 0.0f, 1.0f));
		}

		DebugObject::m_wss << L"Listen" << endl;
	}

	void EnState_CheckSoundPos::OnUpdate() {
		//DebugObject::m_wss << L"Chase";
	}

	void EnState_CheckSoundPos::OnExit() {

		ExitChangeComps();
	}

}

//endbasecross