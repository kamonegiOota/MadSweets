#pragma once
#include"PlayerProvider.h"
#include"PlayerStanceManager.h"

namespace basecross
{
	/// <summary>
	/// プレイヤー一人称カメラの動きを担当するコンポーネント
	/// </summary>
	class PlayerFPSCameraMover : public Component
	{
		/// <summary>
		/// カメラの向き用の子オブジェクト
		/// </summary>
		ex_weak_ptr<GameObject> m_lookAtObject;

		/// <summary>
		/// ステージのカメラ
		/// </summary>
		ex_weak_ptr<Camera> m_targetCamera;

		ex_weak_ptr<PlayerProvider> m_playerProvider;

		ex_weak_ptr<PlayerStanceManager> m_playerStanceManager;

		/// <summary>
		/// 現在のY回転
		/// </summary>
		float m_rotY = 0.0f;

		/// <summary>
		/// 最大Y回転角度
		/// </summary>
		float m_maxRotY =  XM_PIDIV2;
		/// <summary>
		/// 最小Y回転角度
		/// </summary>
		float m_minRotY = -XM_PIDIV2;
	public:
		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="owner">ゲームオブジェクト</param>
		PlayerFPSCameraMover(std::shared_ptr<GameObject>& owner);

		/// <summary>
		/// 最大Y回転角度を設定する
		/// </summary>
		/// <param name="rotY">Y回転角度</param>
		void SetMaxRotY(const float rotY);
		/// <summary>
		/// 最小Y回転角度を設定する
		/// </summary>
		/// <param name="rotY">Y回転角度</param>
		void SetMinRotY(const float rotY);

		/// <summary>
		/// 最大Y回転角度を取得する
		/// </summary>
		/// <returns>Y回転角度</returns>
		float GetMaxRotY() const;
		/// <summary>
		/// 最小Y回転角度を取得する
		/// </summary>
		/// <returns>Y回転角度</returns>
		float GetMinRotY() const;

		void OnCreate() override;

		void OnUpdate() override;

		void OnDraw() override {}
	};
}