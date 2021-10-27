
#pragma once
/*!
@file UtilityStartCamera.h
@brief UtilityStartCameraクラス
担当：丸山裕喜
*/

#pragma once
#include "stdafx.h"
#include "LiveCamera.h"
#include "StartCamera.h"

namespace basecross {
	
	class UtilityStartCamera
	{
		static map<wstring, vector<StartCamera::ShowParam>> sm_startCameraParams;

	public:

		static vector<StartCamera::ShowParam> GetStartCameraShowParams(const wstring& name) {
			return sm_startCameraParams.at(name);
		}

	};

}

//endbasecross