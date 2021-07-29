/*!
@file ProjectShader.h
@brief プロジェクトで使用するシェーダー
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	DECLARE_DX11_VERTEX_SHADER(VSPNTPoint, VertexPositionNormalTexture)
	DECLARE_DX11_PIXEL_SHADER(PSPNTPoint)

}
//end basecross

