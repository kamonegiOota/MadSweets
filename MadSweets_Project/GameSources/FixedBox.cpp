/*!
@file FixedBox.cpp
@brief FixedBox実体
担当：丸山裕喜
*/

#include "stdafx.h"
#include "Project.h"
#include "FixedBox.h"

namespace basecross {

	void FixedBox::OnCreate()
	{
        StageObject::OnCreate();

        auto coll = AddComponent<CollisionObb>();
        coll->SetFixed(true);

        //描画コンポーネントの追加
        auto PtrDraw = AddComponent<PNTStaticDraw>();
        PtrDraw->SetMeshResource(L"DEFAULT_CUBE");
        //描画コンポーネントに形状（メッシュ）を設定
        PtrDraw->SetOwnShadowActive(true);
        //描画コンポーネントテクスチャの設定
        //PtrDraw->SetTextureResource(L"Wall_Tx");
        //タイリング設定
        PtrDraw->SetSamplerState(SamplerState::LinearWrap);

        AddTag(L"FixedBox");
        coll->AddExcludeCollisionTag(L"FixedBox");
	}

    void FixedBox::OnUpdate()
    {

    }

}