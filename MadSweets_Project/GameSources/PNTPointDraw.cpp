/*!
@file GraphNode.cpp
@brief GraphNodeなど実体
*/

#include "stdafx.h"
#include "Project.h"

#include "PNTPointDraw.h"

namespace basecross {

	void PNTPointDraw::OnCreate() {
		SetLightingEnabled(true);
		//マルチライトの設定
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
		
		//メッシュリソースの取得
		auto PtrMeshResource = GetMeshResource();
		if (PtrMeshResource) {
			//シェーダの設定
			if (IsPerPixelLighting()) {
				//ピクセルライティング
				DrawStatic<VSPNTPoint, PSPNTPoint>(PtrMeshResource->GetMashData());
			}
			else {
				//頂点ライティング
				DrawStatic<VSPNTPoint, PSPNTPoint>(PtrMeshResource->GetMashData());
			}
		}

		//マルチメッシュリソースの取得
		auto PtrMultiMeshResource = GetMultiMeshResource();
		if (PtrMultiMeshResource) {
			size_t count = PtrMultiMeshResource->GetMeshVecCount();
			auto& vec = PtrMultiMeshResource->GetMeshVec();
			for (size_t i = 0; i < count; i++) {
				if (GetMultiMeshIsDraw(i)) {
					//シェーダの設定
					if (IsPerPixelLighting()) {
						//ピクセルライティング
						DrawStatic<VSPNTPoint, PSPNTPoint>(vec[i]);
					}
					else {
						//頂点ライティング
						DrawStatic<VSPNTPoint, PSPNTPoint>(vec[i]);
					}
				}
			}
		}

		//後始末
		auto Dev = App::GetApp()->GetDeviceResources();
		Dev->InitializeStates();
	}

}

//endbasecross