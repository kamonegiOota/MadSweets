
#pragma once
/*!
@file AutoRotation.h
@brief AutoRotationクラス
担当：丸山裕喜
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	struct LiveMoveParam {
		Vec3 startPos;
		Vec3 endPos;
		float speed;

		LiveMoveParam() :
			startPos(Vec3(0.0f)), endPos(Vec3(0.0f)), speed(0.0f)
		{}
		LiveMoveParam(const Vec3& startPos,
			const float& speed = 1.0f
		) :
			startPos(startPos),
			endPos(startPos),
			speed(speed)
		{}

		LiveMoveParam(const Vec3& startPos,
			const Vec3& endPos,
			const float& speed = 1.0f
		) :
			startPos(startPos),
			endPos(endPos),
			speed(speed)
		{}
	};

	struct LiveParam
	{
		LiveMoveParam eye;
		LiveMoveParam at;

		wstring animation;

		float lookTime;
		bool isLookCamera;
		bool isParticle;

		LiveParam() :
			LiveParam(LiveMoveParam(),LiveMoveParam(),L"Appeal")
		{}

		LiveParam(const LiveMoveParam& eye,
			const LiveMoveParam& at,
			const wstring& animation,
			const bool isLookCamera = true,
			bool isParticle = true
		):
			LiveParam(eye,at,animation,0.0f,isLookCamera,isParticle)
		{}

		LiveParam(const LiveMoveParam& eye,
			const LiveMoveParam& at,
			const wstring& animation,
			const float lookTime,
			const bool isLookCamera = true,
			const bool isParticle = true
		) :
			eye(eye),
			at(at),
			animation(animation),
			lookTime(lookTime),
			isLookCamera(isLookCamera),
			isParticle(isParticle)
		{}
	};

	class LiveCamera : public Camera {

		std::shared_ptr<GameObject> m_targetArea;  //アピール中のターゲット

		vector<LiveParam> m_params;
		int m_index;

		float m_timeElapsed;

		void CreateParticle();
		void CreateSuperChat();

		std::shared_ptr<GameStage> GetGameStage();

		void EyeMove();  //カメラ本体の移動
		void AtMove(); //見ている場所の移動

		void NextIndex();
		void PlayAnimation();
		void TargetLookForward();

		void EndProcess();    //カメラ切り替え時に行いたい処理
		void ChangeCamera();  //Cameraを変更する。

		void AnimationWait(); //アニメーションが終了するまで待機する。
		void TimeMgr();  //時間管理

		bool IsEnd() { //終了判断
			return m_params.size() <= m_index;
		}

	public:

		LiveCamera():
			Camera(),
			m_index(0),
			m_timeElapsed(0.0f)
		{}

		void OnUpdate() override;

		void LiveStart(const vector<LiveParam>& params,const std::shared_ptr<GameObject>& targetArea);
	};

}


//endbasecross