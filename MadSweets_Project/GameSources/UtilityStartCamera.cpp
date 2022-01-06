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
				StartCamera::ShowParam(
					LiveMoveParam(Vec3(-21.0f, +1.0f, -21.0f),Vec3(-21.0f, +1.0f, -21.0f)),
					LiveMoveParam(Vec3(-17.0f, +2.0f, -17.0f),Vec3(-19.0f, +2.0f, -13.0f), 1.0f),
					3.0f),

				StartCamera::ShowParam(
					LiveMoveParam(Vec3(-21.0f, +1.0f, -21.0f),Vec3(-21.0f, +1.0f, -21.0f)),
					LiveMoveParam(Vec3(-19.0f, +2.0f, -13.0f),Vec3(-13.0f, +2.0f, -19.0f), 0.5f),
					4.5f)
			},
		},
		{L"Stage2.csv",
			{
				
			},
		},
		{L"Stage3.csv",
			{
				//StartCamera::ShowParam(
				//	LiveMoveParam(Vec3(2.0f,0.0f,0.0f),Vec3(+4.0f,+0.0f,+0.0f)),
				//	LiveMoveParam(Vec3(0.0f,0.0f,0.0f),Vec3(-3.0f,-3.0f,-3.0f)))
			},
		},
	};

}

//endbasecross