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
#include "TargetEscape.h"
#include "Velocity.h"

namespace basecross {

    void EnState_LoseTarget::OnStart() {
        auto obj = GetOwner()->GetGameObject();
        auto returnPlow = obj->GetComponent<ReturnPlowlingPosition>(false);
        if (returnPlow) {
            returnPlow->StartReturn();
        }

        auto velocity = obj->GetComponent<Velocity>();
        if (velocity) {
            velocity->Reset();
        }

        AddChangeComp(returnPlow, true, false);
        AddChangeComp(obj->GetComponent<AstarCtrl>(false), true, false);

        AddChangeComp(obj->GetComponent<TargetChase>(false), false, false);
        AddChangeComp(obj->GetComponent<TargetEscape>(false), false, false);

        StartChangeComps();

        auto draw = obj->GetComponent<SmBaseDraw>(false);
        if (draw) {
            draw->SetDiffuse(Col4(0.0f, 0.0f, 1.0f, 1.0f));
        }

       
    }

    void EnState_LoseTarget::OnUpdate() {

    }

    void EnState_LoseTarget::OnExit() {
        ExitChangeComps();
    }

}

//endbasecross