
#pragma once
/*!
@file BuildeVertexPCT.cpp
@brief BuildeVertexPCT実体クラス
担当：丸山裕喜
*/


#include "stdafx.h"
#include "Project.h"
#include "BuildeVertexPCTSprite.h"

namespace basecross {

	void BuildeVertexPCTSprite::OnCreate()
	{

		CreateVertices();  //頂点データの生成

		m_indices = {  //インディセスの生成
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
		case UIPivot::Center: //中心
			m_vertices = {
				{Vec3(-width,+height,+depth) * size, color, useUV[0]},
				{Vec3(+width,+height,+depth) * size, color, useUV[1]},
				{Vec3(-width,-height,+depth) * size, color, useUV[2]},
				{Vec3(+width,-height,+depth) * size, color, useUV[3]},
			};

			break;

		case UIPivot::Up:  //上寄せ
			height *= 2.0f;

			m_vertices = {
				{Vec3(-width,+0.0f,+depth) * size, color, useUV[0]},
				{Vec3(+width,+0.0f,+depth) * size, color, useUV[1]},
				{Vec3(-width,-height,+depth) * size, color, useUV[2]},
				{Vec3(+width,-height,+depth) * size, color, useUV[3]},
			};

			break;

		case UIPivot::Down:  //下寄せ
			height *= 2.0f;

			m_vertices = {
				{Vec3(-width,+height,+depth) * size, color, useUV[0]},
				{Vec3(+width,+height,+depth) * size, color, useUV[1]},
				{Vec3(-width,+0.0f,+depth) * size, color, useUV[2]},
				{Vec3(+width,+0.0f,+depth) * size, color, useUV[3]},
			};

			break;

		case UIPivot::Left:  //左寄せ
			//中心にした場合半分のwidthで済むから、
			//逆に左よせで同じ大きさを作るためには、二倍にしなければならない
			width *= 2.0f;

			m_vertices = {
				{Vec3(+0.0f ,+height,+depth) * size, color, useUV[0]},
				{Vec3(+width,+height,+depth) * size, color, useUV[1]},
				{Vec3(+0.0f ,-height,+depth) * size, color, useUV[2]},
				{Vec3(+width,-height,+depth) * size, color, useUV[3]},
			};

			break;

		case UIPivot::LeftUp:  //左上寄せ

			width *= 2.0f;
			height *= 2.0f;

			m_vertices = {
				{Vec3(+0.0f ,+0.0f  ,+depth) * size, color, useUV[0]},
				{Vec3(+width,+0.0f  ,+depth) * size, color, useUV[1]},
				{Vec3(+0.0f ,-height,+depth) * size, color, useUV[2]},
				{Vec3(+width,-height,+depth) * size, color, useUV[3]},
			};

			break;

		case UIPivot::LeftDown:  //左下寄せ

			width *= 2.0f;
			height *= 2.0f;

			m_vertices = {
				{Vec3(+0.0f ,+height  ,+depth) * size, color, useUV[0]},
				{Vec3(+width,+height  ,+depth) * size, color, useUV[1]},
				{Vec3(+0.0f ,+0.0f,+depth) * size, color, useUV[2]},
				{Vec3(+width,+0.0f,+depth) * size, color, useUV[3]},
			};

			break;

		case UIPivot::Right:  //右寄せ

			width *= 2.0f;

			m_vertices = {
				{Vec3(+0.0f ,+height,+depth) * size, color, useUV[0]},
				{Vec3(-width,+height,+depth) * size, color, useUV[1]},
				{Vec3(+0.0f ,-height,+depth) * size, color, useUV[2]},
				{Vec3(-width,-height,+depth) * size, color, useUV[3]},
			};

			break;

		case UIPivot::RightUp:  //右上寄せ

			width *= 2.0f;
			height *= 2.0f;

			m_vertices = {
				{Vec3(+0.0f ,+0.0f,+depth) * size, color, useUV[0]},
				{Vec3(-width,+0.0f,+depth) * size, color, useUV[1]},
				{Vec3(+0.0f ,-height,+depth) * size, color, useUV[2]},
				{Vec3(-width,-height,+depth) * size, color, useUV[3]},
			};

			break;

		case UIPivot::RightDown:  //右下寄せ

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