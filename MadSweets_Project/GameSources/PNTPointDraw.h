/*!
@file EnemyStateMachine.h
@brief EnemyStateMachine
�S���ҁF�ێR �T��
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	struct PointLightParam {
		Vec3 m_Directional;	//���C�g�̌���
		Col4 m_DiffuseColor;	//�f�B�t�B�[�Y�F
		Col4 m_SpecularColor;	//�X�y�L�����[�F
		Vec3 position = Vec3(0.0f);
		float power = 1.0f;
		bool isActive = false;
	};

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
		//�ėp�t���O
		XMUINT4 activeFlg;
		//�ȉ��e
		Vec4 lightPos;
		Vec4 eyePos;
		Mat4x4 lightView;
		Mat4x4 lightProjection;

		Vec4 poitnLightPositions[256];

		Vec4 bones[3 * 72];
		//PointLightParam poitnLightParam[256];
	};

	//�R���X�^���g�o�b�t�@�̎���
	DECLARE_DX11_CONSTANT_BUFFER(PointBuffer, PointConstants)

	class PNTPointDraw :public BcBaseDraw
	{
		struct Impl;
		unique_ptr<Impl> pImpl;

		void DrawStatic2(const MeshPrimData& data);
		void SetPointConstants(PointConstants& pointCb, const MeshPrimData& data);

	public :
		PNTPointDraw(const std::shared_ptr<GameObject>& objPtr);

		void OnCreate() override;
		void OnUpdate() override{}

		void OnDraw() override;

	};

}

//endbasecross