/*!
@file I_Chase.h
@brief I_Chase
担当者：丸山 裕喜
*/

#pragma once

namespace basecross {

	class I_Chase
	{
	public:
		virtual void StartChase() = 0;  //追いかける処理に変更する時
		virtual void EndChase() = 0;  //ターゲットを見失ったときの処理
	};
}

//endbasecross