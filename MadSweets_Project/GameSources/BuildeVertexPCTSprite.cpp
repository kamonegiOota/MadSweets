
#pragma once
/*!
@file BuildeVertexPCT.cpp
@brief BuildeVertexPCT���̃N���X
�S���F�ێR�T��
*/


#include "stdafx.h"
#include "Project.h"
#include "BuildeVertexPCTSprite.h"

namespace basecross {

	void BuildeVertexPCTSprite::OnCreate()
	{

		CreateVertices();  //���_�f�[�^�̐���

		m_indices = {  //�C���f�B�Z�X�̐���
			0, 1, 2,
			2, 1, 3
		};

	}

	void BuildeVertexPCTSprite::CreateVertices()
	{
		float width = m_param.width;
		float height = m_param.height;
		float depth = m_param.depth;
		const float size = m_param.size;

		const Col4& color = m_param.color;

		const auto& pivot = m_param.pivot;

		auto useUV = CreateUseUV();

		switch (pivot)
		{
		case UIPivot::Center: //���S
			m_vertices = {
				{Vec3(-width,+height,+depth) * size, color, useUV[0]},
				{Vec3(+width,+height,+depth) * size, color, useUV[1]},
				{Vec3(-width,-height,+depth) * size, color, useUV[2]},
				{Vec3(+width,-height,+depth) * size, color, useUV[3]},
			};

			break;

		case UIPivot::Up:  //���
			height *= 2.0f;

			m_vertices = {
				{Vec3(-width,+0.0f,+depth) * size, color, useUV[0]},
				{Vec3(+width,+0.0f,+depth) * size, color, useUV[1]},
				{Vec3(-width,-height,+depth) * size, color, useUV[2]},
				{Vec3(+width,-height,+depth) * size, color, useUV[3]},
			};

			break;

		case UIPivot::Down:  //����
			height *= 2.0f;

			m_vertices = {
				{Vec3(-width,+height,+depth) * size, color, useUV[0]},
				{Vec3(+width,+height,+depth) * size, color, useUV[1]},
				{Vec3(-width,+0.0f,+depth) * size, color, useUV[2]},
				{Vec3(+width,+0.0f,+depth) * size, color, useUV[3]},
			};

			break;

		case UIPivot::Left:  //����
			//���S�ɂ����ꍇ������width�ōςނ���A
			//�t�ɍ��悹�œ����傫������邽�߂ɂ́A��{�ɂ��Ȃ���΂Ȃ�Ȃ�
			width *= 2.0f;

			m_vertices = {
				{Vec3(+0.0f ,+height,+depth) * size, color, useUV[0]},
				{Vec3(+width,+height,+depth) * size, color, useUV[1]},
				{Vec3(+0.0f ,-height,+depth) * size, color, useUV[2]},
				{Vec3(+width,-height,+depth) * size, color, useUV[3]},
			};

			break;

		case UIPivot::LeftUp:  //�����

			width *= 2.0f;
			height *= 2.0f;

			m_vertices = {
				{Vec3(+0.0f ,+0.0f  ,+depth) * size, color, useUV[0]},
				{Vec3(+width,+0.0f  ,+depth) * size, color, useUV[1]},
				{Vec3(+0.0f ,-height,+depth) * size, color, useUV[2]},
				{Vec3(+width,-height,+depth) * size, color, useUV[3]},
			};

			break;

		case UIPivot::LeftDown:  //������

			width *= 2.0f;
			height *= 2.0f;

			m_vertices = {
				{Vec3(+0.0f ,+height  ,+depth) * size, color, useUV[0]},
				{Vec3(+width,+height  ,+depth) * size, color, useUV[1]},
				{Vec3(+0.0f ,+0.0f,+depth) * size, color, useUV[2]},
				{Vec3(+width,+0.0f,+depth) * size, color, useUV[3]},
			};

			break;

		case UIPivot::Right:  //�E��

			width *= 2.0f;

			m_vertices = {
				{Vec3(+0.0f ,+height,+depth) * size, color, useUV[0]},
				{Vec3(-width,+height,+depth) * size, color, useUV[1]},
				{Vec3(+0.0f ,-height,+depth) * size, color, useUV[2]},
				{Vec3(-width,-height,+depth) * size, color, useUV[3]},
			};

			break;

		case UIPivot::RightUp:  //�E���

			width *= 2.0f;
			height *= 2.0f;

			m_vertices = {
				{Vec3(+0.0f ,+0.0f,+depth) * size, color, useUV[0]},
				{Vec3(-width,+0.0f,+depth) * size, color, useUV[1]},
				{Vec3(+0.0f ,-height,+depth) * size, color, useUV[2]},
				{Vec3(-width,-height,+depth) * size, color, useUV[3]},
			};

			break;

		case UIPivot::RightDown:  //�E����

			width *= 2.0f;
			height *= 2.0f;

			m_vertices = {
				{Vec3(+0.0f ,+height,+depth) * size, color, useUV[0]},
				{Vec3(-width,+height,+depth) * size, color, useUV[1]},
				{Vec3(+0.0f ,+0.0f,+depth) * size, color, useUV[2]},
				{Vec3(-width,+0.0f,+depth) * size, color, useUV[3]},
			};

			break;
		}
	}

	vector<Vec2> BuildeVertexPCTSprite::CreateUseUV()
	{

		const auto xRange = m_param.useUVRange_X;
		const auto yRange = m_param.useUVRange_Y;
		const Vec2& size = m_param.useSpriteSize;

		const vector<Vec2> useUV = {
			{xRange.start / size.x , yRange.start / size.y},
			{xRange.end   / size.x , yRange.start / size.y},
			{xRange.start / size.x , yRange.end   / size.y},
			{xRange.end   / size.x , yRange.end   / size.y}
		};

		return useUV;
	}

}

//endbasecross