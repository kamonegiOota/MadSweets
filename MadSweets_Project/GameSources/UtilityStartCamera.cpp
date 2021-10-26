/*!
@file UtilityStartCamera.cpp
@brief UtilityStartCameraのクラス実体
担当：丸山裕喜
*/

#include "stdafx.h"
#include "Project.h"

#include "UtilityStartCamera.h"

namespace basecross {

	map<wstring, vector<StartCamera::ShowParam>> UtilityStartCamera::sm_startCameraParams = {
		{L"Stage1.csv",
			{
				
			},
		},
		{L"Stage2.csv",
			{

			},
		},
		{L"Stage3.csv",
			{
				StartCamera::ShowParam(
					LiveMoveParam(Vec3(2.0f,0.0f,0.0f),Vec3(+4.0f,+0.0f,+0.0f)),
					LiveMoveParam(Vec3(0.0f,0.0f,0.0f),Vec3(-3.0f,-3.0f,-3.0f)))
			},
		},
	};

}

//endbasecross