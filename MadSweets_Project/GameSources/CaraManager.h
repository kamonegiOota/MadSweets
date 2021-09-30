/*!
@file CaraManager.h
@brief CaraManager
担当者：丸山 裕喜
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	class CaraManager : public Component, public I_Chase, public I_Probe, public I_Ear, public I_ReturnPlowling
	{

	public:
		CaraManager(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override {}
		void OnUpdate() override {}

		//Interfaceの実装-------------------------------------------------------------

				//追従スタート
		void StartChase() override;
		void EndChase() override;  //ターゲットを見失ったときの処理

		//捜索スタート
		void StartProbe() override;
		void EndProbe() override;
		void HideSearchAnimationStart() override;

		//音を聞いた
		void Listen() override;
		void EndListen() override;

		//元の場所に戻る行為スタート
		void StartReturnPlowling() override;
		void EndReturnPlowling() override;

		//アクセッサ-------------------------------------------------------------------

	};

}

//endbasecross