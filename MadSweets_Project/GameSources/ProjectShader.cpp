/*!
@file ProjectShader.cpp
@brief プロジェクトで使用するシェーダー実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	IMPLEMENT_DX11_VERTEX_SHADER(VSPNTPoint, App::GetApp()->GetShadersPath() + L"VSPNTPoint.cso")
	IMPLEMENT_DX11_PIXEL_SHADER(PSPNTPoint, App::GetApp()->GetShadersPath() + L"PSPNTPoint.cso")

}
//end basecross


