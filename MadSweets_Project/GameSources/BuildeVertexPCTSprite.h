
#pragma once
/*!
@file BuildeVertexPCT.h
@brief BuildeVertexPCTクラス
担当：丸山裕喜
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	enum class UIPivot {
		Center,
		Up,
		Down,
		Left,
		LeftUp,
		LeftDown,
		Right,
		RightUp,
		RightDown,
	};

	struct UseUVRange
	{
		float start;
		float end;

		UseUVRange(const float start, const float end)
			:start(start),end(end)
		{}

		UseUVRange(const Vec2& range)
			:start(range.x),end(range.y)
		{}
	};

	struct BuildeVertexPCTParam
	{

		float width;
		float height;
		float depth;  //depthは現状使わない
		float size;

		Col4 color;

		UseUVRange useUVRange_X;  //使用したいUV範囲X
		UseUVRange useUVRange_Y;  //使用したいUV範囲Y

		Vec2 useSpriteSize;  //画像の大きさ

		wstring texture;

		UIPivot pivot;

		BuildeVertexPCTParam() :
			width(256.0f),
			height(256.0f),
			depth(0.0f),
			size(1.0f),
			color(Col4(1.0f)),
			useUVRange_X(0.0f,256.0f),
			useUVRange_Y(0.0f,256.0f),
			useSpriteSize(256.0f, 256.0f),
			texture(L""),
			pivot(UIPivot::Center)
		{}

		BuildeVertexPCTParam(const wstring& texture, bool isSprite = true,UIPivot pivot = UIPivot::Center) :
			width(256.0f),
			height(256.0f),
			depth(0.0f),
			size(1.0f),
			color(Col4(1.0f)),
			useUVRange_X(0.0f, 1.0f),
			useUVRange_Y(0.0f, 1.0f),
			useSpriteSize(1.0f, 1.0f),
			texture(texture),
			pivot(pivot)
		{
			if (isSprite) {
				width *= 0.5f;
				height *= 0.5f;
			}
			else {
				width = 0.5f;
				height = 0.5f;
			}
		}

		BuildeVertexPCTParam(const Vec2& useSpriteSize, 
			const wstring& texture, const UIPivot& pivot = UIPivot::Center,
			const bool isSprite = true
		) :
			BuildeVertexPCTParam(
				Vec2(0.0f,useSpriteSize.x), Vec2(0.0f,useSpriteSize.y),
				useSpriteSize, texture, pivot,
				isSprite
			)
		{}

		BuildeVertexPCTParam(const UseUVRange& useRangeX, const UseUVRange& useRangeY,
			const Vec2& useSpriteSize, const wstring& texture, const UIPivot& pivot = UIPivot::Center,
			const bool isSprite = true
		) :
			width(256.0f),
			height(256.0f),
			depth(0.0f),
			size(1.0f),
			color(Col4(1.0f)),
			useUVRange_X(useRangeX),
			useUVRange_Y(useRangeY),
			useSpriteSize(useSpriteSize),
			texture(texture),
			pivot(pivot)
		{
			if (isSprite){  //スプライトだったら
				width = (useRangeX.end - useRangeX.start) / 2.0f;
				height = (useRangeY.end - useRangeY.start) / 2.0f;
			}
			else {
				width = 0.5f;
				height = 0.5f;
			}
		}

		BuildeVertexPCTParam(const float width, const float height,
			const UseUVRange& useRangeX, const UseUVRange& useRangeY,
			const Vec2& useSpriteSize, const wstring& texture, const UIPivot& pivot = UIPivot::Center
		) :
			width(width),
			height(height),
			depth(0.0f),
			size(1.0f),
			color(Col4(1.0f)),
			useUVRange_X(useRangeX),
			useUVRange_Y(useRangeY),
			useSpriteSize(useSpriteSize),
			texture(texture),
			pivot(pivot)
		{}
	};


	struct BuildeVertexPCTSprite
	{
	private:
		
		void CreateVertices();
		vector<Vec2> CreateUseUV();
		void OnCreate();

		BuildeVertexPCTParam m_param;

	public:

		vector<VertexPositionColorTexture> m_vertices;
		vector<uint16_t> m_indices;

		BuildeVertexPCTSprite(const BuildeVertexPCTParam& param)
			:m_param(param)
		{
			OnCreate();
		}

		//vector<VertexPositionColorTexture> CreateVertices(BuildeVertexPCTParam param);
	};

}

