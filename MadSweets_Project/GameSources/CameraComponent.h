#pragma once

namespace basecross
{
	/// <summary>
	/// カメラ用コンポーネント
	/// </summary>
	class CameraComponent : public Component
	{
		/// <summary>
		/// カメラのポインタ
		/// </summary>
		ex_weak_ptr<Camera> m_camera;

		/// <summary>
		/// カメラの視点を常に前にする
		/// </summary>
		void SetCameraAtForward();

		/// <summary>
		/// 今ターゲットにされているかどうか
		/// </summary>
		bool m_isTarget = false;
	public:
		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="owner">ゲームオブジェクト</param>
		CameraComponent(std::shared_ptr<GameObject>& owner);

		void OnCreate() override;

		void OnUpdate2() override;

		void OnEnable() override;

		void OnDisable() override;

	};
}