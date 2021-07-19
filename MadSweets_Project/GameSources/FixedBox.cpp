/*!
@file FixedBox.cpp
@brief FixedBox����
�S���F�ێR�T��
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

        //�`��R���|�[�l���g�̒ǉ�
        auto PtrDraw = AddComponent<PNTStaticDraw>();
        PtrDraw->SetMeshResource(L"DEFAULT_CUBE");
        //�`��R���|�[�l���g�Ɍ`��i���b�V���j��ݒ�
        PtrDraw->SetOwnShadowActive(true);
        //�`��R���|�[�l���g�e�N�X�`���̐ݒ�
        //PtrDraw->SetTextureResource(L"Wall_Tx");
        //�^�C�����O�ݒ�
        PtrDraw->SetSamplerState(SamplerState::LinearWrap);

        AddTag(L"FixedBox");
        coll->AddExcludeCollisionTag(L"FixedBox");
	}

    void FixedBox::OnUpdate()
    {

    }

}