/*!
@file EnState_Plowling.cpp
@brief EnState_Plowlingなど実体
*/

#include "stdafx.h"
#include "Project.h"

#include "TargetEscape.h"
#include "AstarCtrl.h"
#include "EnState_LoseTarget.h"
#include "I_Escape.h"

#include "MyUtility.h"

#include "DebugObject.h"

namespace basecross {

	void TargetEscape::Move() {
		auto astar = GetGameObject()->GetComponent<AstarCtrl>(false);
		if (!astar) {  //Astarが無かったら
			return;
		}

		astar->UpdateMove();
		
		if(astar->IsRouteEnd()) {  //最終場所まで就いたら
			TargetRayCheck();
		}
	}

	void TargetEscape::TargetRayCheck() {
		//障害物が合ったら
		if (maru::MyUtility::IsRayObstacle(GetGameObject(),m_target)) {
			m_outSightCount++;
		}
		else {  //無かったら
			m_outSightCount = 0;
		}

		ChangeStateCheck();
	}

	void TargetEscape::ChangeStateCheck() {
		if (m_outSightCount > m_alertReleaseNum) { //指定回数逃げ切ったら
			SuccessEscape(); //逃げ切り成功
		}
		else {
			//今のノードから一番遠いノードを選択する。
			CalucNextNode();
		}
	}

	void TargetEscape::CalucNextNode() {
		auto astar = GetGameObject()->GetComponent<AstarCtrl>();
		if (astar) {
			astar->SearchAstarEscapeNextRoute(m_target);  //次に逃げるべきノードの検索
		}
	}

	void TargetEscape::SuccessEscape() {
		auto escape = GetGameObject()->GetComponent<I_Escape>();
		if (escape) {
			DebugObject::m_wss << endl << to_wstring(m_outSightCount) <<endl << L"escape";
			escape->SuccessEscape();
		}
	}

	void TargetEscape::OnCreate() {
		SetUpdateActive(false);
	}

	void TargetEscape::OnUpdate() {
		Move();  //ノードまで移動

		//移動したら敵との状態を完治 
				
		//障害物ある状態が一定回数(二回)続いたら元に戻る
		
		//そうでない場合は、今のノードから一番遠いノードを選択して移動
	}

}

//endbasecross