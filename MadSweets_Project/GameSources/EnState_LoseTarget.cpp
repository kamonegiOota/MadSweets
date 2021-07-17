/*!
@file LoseTarget.cpp
@brief LoseTarget‚È‚ÇŽÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"

#include "EnState_LoseTarget.h"
#include "ReturnPlowlingPosition.h"
#include "AstarCtrl.h"
#include "TargetChase.h"

namespace basecross {

    void EnState_LoseTarget::OnStart() {
        auto obj = GetOwner()->GetGameObject();
        auto returnPlow = obj->GetComponent<ReturnPlowlingPosition>(false);
        if (returnPlow) {
            returnPlow->StartReturn();
        }
        
        AddChangeComp(obj->GetComponent<AstarCtrl>(), true, false);
        AddChangeComp(obj->GetComponent<TargetChase>(), false, false);

        StartChangeComps();
    }

    void EnState_LoseTarget::OnUpdate() {

    }

    void EnState_LoseTarget::OnExit() {
        ExitChangeComps();
    }

}

//endbasecross