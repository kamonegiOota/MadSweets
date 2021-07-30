/*!
@file GraphNode.cpp
@brief GraphNode�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

#include "PNTPointDraw.h"

namespace basecross {

	void PNTPointDraw::OnCreate() {
		SetLightingEnabled(true);
		//�}���`���C�g�̐ݒ�
		for (int i = 0; i < GetMaxDirectionalLights(); i++) {
			SetLightEnabled(i, true);
		}
	}

	void PNTPointDraw::OnDraw() {

		if (GetGameObject()->GetAlphaActive()) {
			if (!(GetBlendState() == BlendState::AlphaBlend || GetBlendState() == BlendState::Additive)) {
				SetBlendState(BlendState::AlphaBlend);
			}
			SetRasterizerState(RasterizerState::DoubleDraw);
		}
		
		//���b�V�����\�[�X�̎擾
		auto PtrMeshResource = GetMeshResource();
		if (PtrMeshResource) {
			//�V�F�[�_�̐ݒ�
			if (IsPerPixelLighting()) {
				//�s�N�Z�����C�e�B���O
				DrawStatic<VSPNTPoint, PSPNTPoint>(PtrMeshResource->GetMashData());
			}
			else {
				//���_���C�e�B���O
				DrawStatic<VSPNTPoint, PSPNTPoint>(PtrMeshResource->GetMashData());
			}
		}

		//�}���`���b�V�����\�[�X�̎擾
		auto PtrMultiMeshResource = GetMultiMeshResource();
		if (PtrMultiMeshResource) {
			size_t count = PtrMultiMeshResource->GetMeshVecCount();
			auto& vec = PtrMultiMeshResource->GetMeshVec();
			for (size_t i = 0; i < count; i++) {
				if (GetMultiMeshIsDraw(i)) {
					//�V�F�[�_�̐ݒ�
					if (IsPerPixelLighting()) {
						//�s�N�Z�����C�e�B���O
						DrawStatic<VSPNTPoint, PSPNTPoint>(vec[i]);
					}
					else {
						//���_���C�e�B���O
						DrawStatic<VSPNTPoint, PSPNTPoint>(vec[i]);
					}
				}
			}
		}

		//��n��
		auto Dev = App::GetApp()->GetDeviceResources();
		Dev->InitializeStates();
	}

}

//endbasecross