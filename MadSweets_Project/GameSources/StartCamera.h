
#pragma once
/*!
@file AutoRotation.h
@brief AutoRotationクラス
担当：丸山裕喜
*/

#pragma once
#include "stdafx.h"
#include "LiveCamera.h"

namespace basecross {

	class StartCamera : public Camera
	{
		CONTROLER_STATE GetPad() const
		{
			auto& app = App::GetApp();
			auto device = app->GetInputDevice();
			auto pad = device.GetControlerVec()[0];
			return pad;
		}

		template<class T>
		std::shared_ptr<T> GetStage() {
			auto& app = App::GetApp(); // アプリケーションオブジェクトを取得
			auto scene = app->GetScene<Scene>(); // アプリオブジェからシーンを取得
			auto stage = scene->GetActiveStage();
			auto tStage = dynamic_pointer_cast<T>(stage);
			if (tStage) {
				return tStage;
			}
			else{
				return nullptr;
			}
		}

	public:

		//演出にほしい情報を構造体として受け取る。
		struct ShowParam
		{
			LiveMoveParam eye;
			LiveMoveParam at;
			float lookTime;  //どの位の時間を見るか？

			ShowParam() :
				ShowParam(LiveMoveParam(),
					LiveMoveParam(),
					3.0f)
			{}

			ShowParam(const LiveMoveParam& eye,
				const LiveMoveParam& at,
				const float lookTime = 3.0f
			) :
				eye(eye),
				at(at),
				lookTime(lookTime)
			{}
		};

	private:

		std::vector<ShowParam> m_params;
		int m_index;

		float m_timeElapsed;

		std::shared_ptr<GameStage> GetGameStage();

		void PlayAnimation();
		void StartLock(const bool b);  //スタートカメラ中にロックする項目

		void FadeStart();

	public:

		StartCamera(const vector<ShowParam>& params) : 
			Camera(),m_params(params),m_index(0),m_timeElapsed(0.0f)
		{}

		void OnCreate() override;
		void OnUpdate() override;

		void EyeMove();
		void AtMove();

		void Skip();

		void ChangeCamera();

		bool IsEnd() {  //終了を判断
			return m_params.size() <= m_index;
		}
	};

}

//endbasecross