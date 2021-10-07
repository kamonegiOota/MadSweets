/*!
@file MainCamera.cpp
@brief MainCameraのクラス実体
担当：丸山裕喜
*/

#include "stdafx.h"
#include "Project.h"
#include "LiveCamera.h"


namespace basecross {

	void LiveCamera::CreateParticle() {

	}

	void LiveCamera::CreateSuperChat() {

	}

	std::shared_ptr<GameStage> LiveCamera::GetGameStage() {
		auto& app = App::GetApp(); // アプリケーションオブジェクトを取得
		auto scene = app->GetScene<Scene>(); // アプリオブジェからシーンを取得
		auto stage = dynamic_pointer_cast<GameStage>(scene->GetActiveStage());

		if (stage) {
			return stage;
		}
		else {
			return nullptr;
		}
	}

	void LiveCamera::EyeMove() {
		auto delta = App::GetApp()->GetElapsedTime();

		auto pos = GetEye();
		const auto& endPos = m_params[m_index].eye.endPos;
		const float speed = m_params[m_index].eye.speed;

		auto newPos = Lerp::CalculateLerp(pos, endPos, 0.0f, 1.0f, delta * speed, Lerp::rate::Linear);

		SetEye(newPos);
	}

	void LiveCamera::AtMove() {
		auto delta = App::GetApp()->GetElapsedTime();

		auto at = GetAt();
		const auto& endAt = m_params[m_index].at.endPos;
		const float speed = m_params[m_index].at.speed;

		auto newAt = Lerp::CalculateLerp(at, endAt, 0.0f, 1.0f, delta * speed, Lerp::rate::Linear);

		SetAt(newAt);
	}

	void LiveCamera::NextIndex() {
		m_timeElapsed = 0.0f;
		m_index++;  //インデックスをインクリメント

		if (IsEnd()) {  //だったら
			EndProcess();
			ChangeCamera();
		}
		else {
			SetEye(m_params[m_index].eye.startPos);
			SetAt(m_params[m_index].at.startPos);
			PlayAnimation();

			if (m_params[m_index].isParticle) {
				//パーティクルの生成
				CreateParticle();
			}
		}
	}

	void LiveCamera::PlayAnimation() {

	}

	//ターゲットがステージの正面の方向を向く
	void LiveCamera::TargetLookForward() {

	}

	void LiveCamera::EndProcess() {

	}

	void LiveCamera::ChangeCamera() {

	}

	void LiveCamera::AnimationWait() {

	}

	void LiveCamera::TimeMgr() {
		auto delta = App::GetApp()->GetElapsedTime();

		if (m_params[m_index].lookTime == 0.0f) {
			AnimationWait();
			return;
		}

		m_timeElapsed += delta;
		if (m_timeElapsed >= m_params[m_index].lookTime)  //時間が経過したら
		{
			NextIndex();
		}
	}

	void LiveCamera::OnUpdate()
	{
		//終了のお知らせ
		if (m_params.size() <= m_index) {
			return;
		}

		AtMove();
		EyeMove();

		TimeMgr();  //時間管理

	}

	void LiveCamera::LiveStart(const vector<LiveParam>& params, const std::shared_ptr<GameObject>& targetArea) {
		m_params = params;
		m_targetArea = targetArea;
		SetEye(m_params[m_index].eye.startPos);
		SetAt(m_params[m_index].at.startPos);
		PlayAnimation();
	}

}

//endbasecross