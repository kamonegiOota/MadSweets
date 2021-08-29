
/*!
@file MyUtility.cpp
@brief MyUtility�N���X����
�S���F�ێR�T��
*/

#include "stdafx.h"
#include "Project.h"

#include "EatenObject.h"
#include "EatenComponent.h"
#include "SoundHelper.h"

#include "BuildeVertexPCTSprite.h"
#include "BillBoard.h"

namespace basecross {

	void EatenObject::OnCreate() {
		StageObject::OnCreate();

		auto builde = BuildeVertexPCTSprite(m_param);

		auto draw = AddComponent<PCTStaticDraw>();
		draw->CreateOriginalMesh(builde.m_vertices, builde.m_indices);
		draw->SetOriginalMeshUse(true);
		if (m_param.texture != L"") {
			draw->SetTextureResource(m_param.texture);
			m_name = m_param.texture;  //�e�N�X�`�����l�[���Ƃ��Ĉ���
		}
		SetAlphaActive(true);

		AddComponent<BillBoard>();

		auto col = AddComponent<CollisionObb>();

		AddComponent<EatenComponent>(EatenData(10, 10));
		AddComponent<SoundEmitter>();
	}

}

//endbasecross