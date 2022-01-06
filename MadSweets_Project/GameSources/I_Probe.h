/*!
@file I_Probe.h
@brief I_Probe
担当者：丸山 裕喜
*/

#pragma once

namespace basecross {

	class I_Probe {

	public:

		virtual void StartProbe() = 0;
		virtual void EndProbe() = 0;

		/// <summary>
		/// 隠れるオブジェクトの中を覗く処理
		/// </summary>
		virtual void HideSearchAnimationStart() = 0;
	};
}

//endbasecross