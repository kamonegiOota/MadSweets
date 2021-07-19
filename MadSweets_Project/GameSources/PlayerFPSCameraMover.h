#pragma once
#include"PlayerProvider.h"
#include"AnimationHelper.h"
#include"PlayerObject.h"

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

		ex_weak_ptr<Animator<PlayerAnimationMember, PlayerState>> m_playerAnimator;

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

		Vec3 m_standPosition = Vec3(0, 1, 0);
		Vec3 m_crouchPosition = Vec3(0, 0, 0);
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

		void OnUpdate2() override;
	};
}