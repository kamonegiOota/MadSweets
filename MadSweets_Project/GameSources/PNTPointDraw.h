/*!
@file EnemyStateMachine.h
@brief EnemyStateMachine
担当者：丸山 裕喜
*/

#pragma once

#include "stdafx.h"
#include "Project.h"
#include "PointLight.h"

namespace basecross {

	struct PointConstants {
		Col4 diffuseColor;
		Col4 emissiveColor;
		Col4 specularColorAndPower;

		Col4 lightDirection[3];
		Col4 lightDiffuseColor[3];
		Col4 lightSpecularColor[3];

		Vec4 eyePosition;

		Col4 fogColor;
		Vec4 fogVector;

		Mat4x4 world;
		Vec4 worldInverseTranspose[3];
		Mat4x4 worldViewProj;
		//汎用フラグ
		XMUINT4 activeFlg;
		//以下影
		Vec4 lightPos;
		Vec4 eyePos;
		Mat4x4 lightView;
		Mat4x4 lightProjection;

		int usePointLightNum;
		XMUINT3 null;
		PointLightParam pointLightParams[256];

		Vec4 bones[3 * 72];
		//PointLightParam poitnLightParam[256];
	};

	//コンスタントバッファの実装
	DECLARE_DX11_CONSTANT_BUFFER(PointBuffer, PointConstants)

	class PNTPointDraw :public BcBaseDraw
	{
		struct Impl;
		unique_ptr<Impl> pImpl;

	public :
		PNTPointDraw(const std::shared_ptr<GameObject>& objPtr);

		void OnCreate() override;
		void OnUpdate() override{}

		void OnDraw() override;


	private:
		
		void DrawStatic2(const MeshPrimData& data);
		void SetPointConstants(PointConstants& pointCb, const MeshPrimData& data);
	};

}

//endbasecross