/*!
@file EnState_LoseTarget.cpp
@brief EnState_LoseTargetなど実体
*/

#include "stdafx.h"
#include "Project.h"

#include "EnState_LoseTarget.h"
#include "PlowlingMove.h"
#include "ReturnPlowlingPosition.h"
#include "AstarCtrl.h"
#include "TargetChase.h"
#include "TargetEscape.h"
#include "TargetProbe.h"
#include "Velocity.h"
#include "EyeSearchRange.h"
#include "I_Escape.h"

namespace basecross {

    void EnState_LoseTarget::ChangeState() {
        auto object = GetOwner()->GetGameObject();
        
        auto escape = object->GetComponent<I_Escape>(false);
        if (escape) {
            escape->StartEscape();
        }
    }

    void EnState_LoseTarget::OnStart() {
        auto obj = GetOwner()->GetGameObject();
        auto returnPlow = obj->GetComponent<ReturnPlowlingPosition>(false);
        if (returnPlow) {
            returnPlow->StartReturn();
        }

        AddChangeComp(returnPlow, true, false);

        AddChangeComp(obj->GetComponent<TargetChase>(false), false, false);
        AddChangeComp(obj->GetComponent<TargetEscape>(false), false, false);
        AddChangeComp(obj->GetComponent<TargetProbe>(false), false, false);

        StartChangeComps();

        //DebugObject::sm_wss << L"Lose" << endl;
    }

    void EnState_LoseTarget::OnUpdate() {
        auto object = GetOwner()->GetGameObject();
        auto targetManager = object->GetComponent<TargetManager>(false);
        auto eyeSearch = object->GetComponent<EyeSearchRange>(false);

        //nullCheck
        if (targetManager == nullptr || eyeSearch == nullptr) {
            DebugObject::AddString(L"EnState_LoseTarget:: コンポーネントが足りません。");
            return;
        }

        //視界にターゲットが存在したら、Chaseに切替
        auto target = targetManager->GetTarget();
        if (target) {
            if (eyeSearch->IsInEyeRange(target)) {
                ChangeState();
            }
        }

        //DebugObject::sm_wss << L"Lose";
    }

    void EnState_LoseTarget::OnExit() {
        ExitChangeComps();
    }

}

//endbasecross