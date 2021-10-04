#pragma once
#include"ChoicesComponentBase.h"

namespace basecross
{
	/// <summary>
	/// 隠れるのに使うデータ構造体
	/// </summary>
	struct HideData
	{
		/// <summary>
		/// 隠れる際のワールド座標
		/// </summary>
		Vec3 hideWorldPosition;
		/// <summary>
		/// 隠れる際の向き
		/// </summary>
		Vec3 hideForward;
		//隠れているオブジェクト
		ex_weak_ptr<GameObject> hideObject = nullptr;

		/// <summary>
		/// コンストラクタ
		/// </summary>
		HideData();
		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="hideWorldPosition">隠れる際のワールド座標</param>
		/// <param name="hideForward">隠れる際の向き</param>
		HideData(const Vec3& hideWorldPosition, const Vec3& hideForward);
	};

	/// <summary>
	/// 隠れる動作をするコンポーネントにつけるInterface
	/// </summary>
	class I_HideComponent
	{
	public:
		/// <summary>
		/// 隠れる際に呼ばれる関数
		/// </summary>
		/// <param name="hideData">隠れる際に使うデータ構造体</param>
		virtual void OnHide(HideData& hideData) = 0;

		/// <summary>
		/// 隠れるのを終了したときに呼ばれる関数
		/// </summary>
		/// <param name="hideData">隠れるのに必要なデ－タ構造体</param>
		virtual void OnEndHide(HideData& hideData) = 0;
	};

	/// <summary>
	/// 隠れられるオブジェクトの機能を持ったコンポーネント
	/// </summary>
	class HiddenComponent : public ChoicesComponentBase
	{
		/// <summary>
		/// 隠れるのに必要なデータ
		/// </summary>
		HideData m_hideData;

		std::shared_ptr<ChoicesObjectAndEvent> m_choicesObjectAndEvent;

	public:
		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="owner">ゲームオブジェクト</param>
		/// <param name="hideWorldPosition">隠れるのに使うワールド座標</param>
		/// <param name="hideForward">隠れるときの向き</param>
		HiddenComponent(std::shared_ptr<GameObject>& owner, const Vec3& hideWorldPosition, const Vec3& hideForward);
		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="owner">ゲームオブジェクト</param>
		/// <param name="hiddenWorldPosition">隠れるのに使うデータ構造体</param>
		HiddenComponent(std::shared_ptr<GameObject>& owner,const HideData& hiddenWorldPosition);

		/// <summary>
		/// 隠れるのに必要なデータを取得する
		/// </summary>
		/// <returns>隠れるのに必要なデータ</returns>
		HideData GetHideData() const;

		std::shared_ptr<ChoicesObjectAndEvent const> GetChoicesObjectAndEvent(const std::shared_ptr<GameObject>& selectorObject) override;
	};
}