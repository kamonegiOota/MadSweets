/*!
@file Components.h
@brief コンポーネント
@copyright Copyright (c) 2017 WiZ Tamura Hiroki,Yamanoi Yasushi.
*/
#pragma once
#include "stdafx.h"
#include "ex_weak_ptr.h"

namespace basecross {

	class GameObject;
	class Stage;
	class Transform;

	//--------------------------------------------------------------------------------------
	///	コンポーネント親クラス
	//--------------------------------------------------------------------------------------
	class Component :public ObjectInterface, public ShapeInterface {
	protected:
		itbs::Utility::ex_weak_ptr<Transform> transform;

		//構築と破棄
		//--------------------------------------------------------------------------------------
		/*!
		@brief	プロテクトコンストラクタ
		@param[in]	GameObjectPtr	このコンポーネントを所持するゲームオブジェクト
		*/
		//--------------------------------------------------------------------------------------
		explicit Component(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	プロテクトデストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~Component();
	public:
		//アクセサ
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ゲームオブジェクトの取得
		@return	このコンポーネントを所持するゲームオブジェクト
		*/
		//--------------------------------------------------------------------------------------
		shared_ptr<GameObject> GetGameObject() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ゲームオブジェクトを設定する
		@param[in]	GameObjectPtr	新しいゲームオブジェクト
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void AttachGameObject(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ステージの取得<br />
		ゲームオブジェクトがステージだった場合、そのステージが返る
		@return	このコンポーネントを所持するゲームオブジェクトが所属するステージ
		*/
		//--------------------------------------------------------------------------------------
		shared_ptr<Stage> GetStage() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	Updateがアクティブかどうかを得る
		@return	アクティブならtrue
		*/
		//--------------------------------------------------------------------------------------
		bool IsUpdateActive() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	Updateがアクティブかどうかを得る
		@return	アクティブならtrue
		*/
		//--------------------------------------------------------------------------------------
		bool GetUpdateActive() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	Updateがアクティブかどうかを設定する
		@param[in]	b	アクティブかどうか
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetUpdateActive(bool b);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	Drawがアクティブかどうかを得る
		@return	アクティブならtrue
		*/
		//--------------------------------------------------------------------------------------
		bool IsDrawActive() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	Drawがアクティブかどうかを得る
		@return	アクティブならtrue
		*/
		//--------------------------------------------------------------------------------------
		bool GetDrawActive() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	Drawがアクティブかどうかを設定する
		@param[in]	b	アクティブかどうか
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetDrawActive(bool b);
		//--------------------------------------------------------------------------------------
		/*!
		@brief 初期化を行う（仮想関数<br />
		＊thisポインタが必要なオブジェクトはこの関数を多重定義して、取得できる<br />
		＊ここでは空関数にしておくので、必要な場合は派生クラスで多重定義する
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() {}

		virtual void OnUpdate() {}

		virtual void OnStart() {}

		virtual void OnDraw() override {}

	protected:
		/// <summary>
		/// 一定時間後に呼ばれる関数を登録
		/// </summary>
		/// <param name="object">呼ばれる関数のオブジェクト</param>
		/// <param name="action">呼ばれる関数</param>
		/// <param name="invokeTime">呼ばれるまでの時間</param>
		template<class T>
		void AddAction(const std::shared_ptr<T>& object, void(T::* action)(),const float invokeTime)
		{
			GetGameObject()->AddAction(object, action, invokeTime);
		}

		public:
		
		/// <summary>
		/// 衝突発生時に呼ばれるイベント
		/// </summary>
		/// <param name="other">衝突した相手</param>
		virtual void OnCollisionEnter(std::shared_ptr<GameObject>& other) {}

		/// <summary>
		/// 衝突時に呼ばれるイベント
		/// </summary>
		/// <param name="other">衝突した相手</param>
		virtual void OnCollisionExcute(std::shared_ptr<GameObject>& other) {}

		/// <summary>
		/// 衝突終了時に呼ばれるイベント
		/// </summary>
		/// <param name="other">衝突していた相手</param>
		virtual void OnCollisionExit(std::shared_ptr<GameObject>& other) {}
	private:
		// pImplイディオム
		struct Impl;
		unique_ptr<Impl> pImpl;
	};


	//--------------------------------------------------------------------------------------
	///	変換コンポーネント
	//--------------------------------------------------------------------------------------
	class Transform : public Component {
	public:
		//構築と破棄
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	GameObjectPtr	このコンポーネントを所持するゲームオブジェクト
		*/
		//--------------------------------------------------------------------------------------
		explicit Transform(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~Transform();
		//アクセサ
		//--------------------------------------------------------------------------------------
		/*!
		@brief	1ターン前のスケーリングを得る
		@return	1ターン前のスケーリング
		*/
		//--------------------------------------------------------------------------------------
		bsm::Vec3 GetBeforeScale() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	1つ前の重心を得る
		@return	1つ前の重心
		*/
		//--------------------------------------------------------------------------------------
		bsm::Vec3 GetBeforePivot() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	1ターン前のワールド回転を得る
		@return	1ターン前のワールド回転
		*/
		//--------------------------------------------------------------------------------------
		bsm::Quat GetBeforeQuaternion() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	1ターン前のワールド回転を得る
		@return	1ターン前のワールド回転（ベクトル）
		*/
		//--------------------------------------------------------------------------------------
		bsm::Vec3 GetBeforeRotation() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	1ターン前の位置を得る
		@return	1ターン前の位置
		*/
		//--------------------------------------------------------------------------------------
		bsm::Vec3 GetBeforePosition() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	1ターン前のワールド位置を得る
		@return	1ターン前のワールド位置
		*/
		//--------------------------------------------------------------------------------------
		bsm::Vec3 GetBeforeWorldPosition() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	1つ前のワールド行列と同じかどうかを得る
		@param	mat	調べる行列
		@return	同じならtrue
		*/
		//--------------------------------------------------------------------------------------
		bool IsSameBeforeWorldMatrix(const bsm::Mat4x4& mat) const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	1つ前のワールド行列を得る
		@return	1つ前のワールド行列
		*/
		//--------------------------------------------------------------------------------------
		const bsm::Mat4x4 GetBeforeWorldMatrix() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	スケーリングを得る
		@return	スケーリング
		*/
		//--------------------------------------------------------------------------------------
		bsm::Vec3 GetScale() const;

		/// <summary>
		/// ワールドのスケーリングを得る
		/// </summary>
		/// <returns>ワールドスケーリング</returns>
		bsm::Vec3 GetWorldScale() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	スケーリングを設定する.
		@param	const bsm::Vec3& Scale	スケーリング
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetScale(const bsm::Vec3& Scale);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	スケーリングを設定する.
		@param[in]	x	Xスケーリング
		@param[in]	y	Yスケーリング
		@param[in]	z	Zスケーリング
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetScale(float x, float y, float z);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	重心を得る
		@return	重心
		*/
		//--------------------------------------------------------------------------------------
		bsm::Vec3 GetPivot() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	重心を設定する.
		@param	Pivot	重心
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetPivot(const bsm::Vec3& Pivot);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	重心を設定する.
		@param[in]	x	X重心
		@param[in]	y	Y重心
		@param[in]	z	Z重心
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetPivot(float x, float y, float z);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ワールド回転を得る
		@return	ワールド回転（クオータニオン）
		*/
		//--------------------------------------------------------------------------------------
		bsm::Quat GetQuaternion() const;

		/// <summary>
		/// ワールドのワールド回転を得る
		/// </summary>
		/// <returns>ワールドのワールド回転</returns>
		bsm::Quat GetWorldQuaternion() const;

		void SetWorldQuaternion(const bsm::Quat& quaternion);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ワールド回転を設定する
		@param[in]	quaternion	クオータニオン
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetQuaternion(const bsm::Quat& quaternion);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ワールド回転を得る
		@return	ワールド回転（ベクトル）
		*/
		//--------------------------------------------------------------------------------------
		bsm::Vec3 GetRotation() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ワールド回転を設定する
		@param[in]	Rot	回転ベクトル
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetRotation(const bsm::Vec3& Rot);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ワールド回転を設定する
		@param[in]	x	X回転
		@param[in]	y	Y回転
		@param[in]	z	Z回転
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetRotation(float x, float y, float z);

		/// <summary>
		/// 回転する
		/// </summary>
		/// <param name="rot">回転ベクトル</param>
		void Rotate(const bsm::Vec3& rot);

		/// <summary>
		/// 回転する
		/// </summary>
		/// <param name="x">X回転</param>
		/// <param name="y">Y回転</param>
		/// <param name="z">Z回転</param>
		void Rotate(const float x, const float y, const float z);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	位置を得る
		@return	位置
		*/
		//--------------------------------------------------------------------------------------
		bsm::Vec3 GetPosition() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	位置を設定する
		@param[in]	Position	設定する位置
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetPosition(const bsm::Vec3& Position);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	位置を設定する
		@param[in]	x	X位置
		@param[in]	y	Y位置
		@param[in]	z	Z位置
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetPosition(float x, float y, float z);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	位置と一つ前の位置を設定する
		@param[in]	Position	設定する位置
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void ResetPosition(const bsm::Vec3& Position);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ワールド位置を得る
		@return	ワールド位置
		*/
		//--------------------------------------------------------------------------------------
		bsm::Vec3 GetWorldPosition() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ワールド位置を設定する
		@param[in]	Position	設定する位置
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetWorldPosition(const bsm::Vec3& Position);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ワールド位置と一つ前のワールド位置を設定する
		@param[in]	Position	設定する位置
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void ResetWorldPosition(const bsm::Vec3& Position);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ワールド行列と同じかどうかを得る
		@param	mat	調べる行列
		@return	同じならtrue
		*/
		//--------------------------------------------------------------------------------------
		bool IsSameWorldMatrix(const bsm::Mat4x4& mat) const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ワールド行列を得る
		@return	ワールド行列
		*/
		//--------------------------------------------------------------------------------------
		const bsm::Mat4x4 GetWorldMatrix() const; 
		//--------------------------------------------------------------------------------------
		/*!
		@brief	2D用の計算されたワールド行列を得る
		@return	2D用の計算されたワールド行列
		*/
		//--------------------------------------------------------------------------------------
		const bsm::Mat4x4 Get2DWorldMatrix() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	親オブジェクトを得る
		@return	親オブジェクト（nullptrの場合あり）
		*/
		//--------------------------------------------------------------------------------------
		const shared_ptr<GameObject> GetParent()const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	親オブジェクトを設定する
		@param[in]	Obj	親オブジェクト
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetParent(const shared_ptr<GameObject>& Obj);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	親オブジェクトをクリアする
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void ClearParent();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	Transfoem上で計算した速度を得る
		@return	Transfoem上で計算した速度
		*/
		//--------------------------------------------------------------------------------------
		bsm::Vec3 GetVelocity() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	Transfoem上で計算した移動距離を得る
		@return	Transfoem上で計算した移動距離
		*/
		//--------------------------------------------------------------------------------------
		float GetMoveSize() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief 情報を一つ前に移す<br />
		各情報はターンごとに1つ前のターン時の情報を持つ<br />
		この関数はその処理を行う
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetToBefore();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ローカル進行方向（Z軸の方向）を得る
		@return	ローカルZ軸が変化している方向を得る
		*/
		//--------------------------------------------------------------------------------------
		bsm::Vec3 GetForword() const;

		void SetForward(const bsm::Vec3& forward);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ローカル上方向（Y軸の方向）を得る
		@return	ローカルY軸が変化している方向を得る
		*/
		//--------------------------------------------------------------------------------------
		bsm::Vec3 GetUp() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ローカル右方向（X軸の方向）を得る
		@return	ローカルX軸が変化している方向を得る
		*/
		//--------------------------------------------------------------------------------------
		bsm::Vec3 GetRight() const;
		//操作
		//--------------------------------------------------------------------------------------
		/*!
		@brief	更新処理
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	描画処理。デフォルトは何も行わない
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override {}
	private:
		// pImplイディオム
		struct Impl;
		unique_ptr<Impl> pImpl;
	};

	class StageCellMap;
	//--------------------------------------------------------------------------------------
	///	 経路検索コンポーネント
	//--------------------------------------------------------------------------------------
	class PathSearch : public Component {
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	GameObjectPtr	ゲームオブジェクト
		@param[in]	StageCellMapPtr	セルマップのポインタ
		*/
		//--------------------------------------------------------------------------------------
		explicit PathSearch(const shared_ptr<GameObject>& GameObjectPtr,
			const shared_ptr<StageCellMap>& StageCellMapPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~PathSearch();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	今の位置からターゲットまでのパスを検索
		@param[in]	TargetPosition 相手の位置
		@param[out]	RetCellIndexVec	経路を受け取る参照
		@return	成功したらtrue
		*/
		//--------------------------------------------------------------------------------------
		bool SearchCell(const bsm::Vec3& TargetPosition,vector<CellIndex>& RetCellIndexVec);
		//--------------------------------------------------------------------------------------
		/*!
		@brief 更新処理
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief 描画処理。デフォルトは何も行わない
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override {}
	private:
		// pImplイディオム
		struct Impl;
		unique_ptr<Impl> pImpl;
	};


	//--------------------------------------------------------------------------------------
	///	 重力コンポーネント
	//--------------------------------------------------------------------------------------
	class Gravity : public Component {
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	GameObjectPtr	ゲームオブジェクト
		@param[in]	gravity	重力加速度
		*/
		//--------------------------------------------------------------------------------------
		explicit Gravity(const shared_ptr<GameObject>& GameObjectPtr,
			const bsm::Vec3& gravity = bsm::Vec3(0,-9.8f,0));
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~Gravity();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	重力加速度を得る
		@return	重力加速度
		*/
		//--------------------------------------------------------------------------------------
		bsm::Vec3 GetGravity() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	重力加速度を設定する
		@param[in]	gravity	重力加速度
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetGravity(const bsm::Vec3& gravity);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	重力加速度を0にする
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetGravityZero();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	現在の重力加速度による速度を得る
		@return	重力加速度による速度
		*/
		//--------------------------------------------------------------------------------------
		bsm::Vec3 GetGravityVelocity() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	重力加速度による速度をを設定する
		@param[in]	GravityVerocity	重力加速度による速度
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetGravityVerocity(const bsm::Vec3& GravityVerocity);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	重力加速度による速度を0にする
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetGravityVerocityZero();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ジャンプする
		@param[in]	JumpVerocity	ジャンプによるによる初速度
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void StartJump(const bsm::Vec3& JumpVerocity);
		//--------------------------------------------------------------------------------------
		/*!
		@brief 更新処理
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief 描画処理。デフォルトは何も行わない
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override {}
	private:
		// pImplイディオム
		struct Impl;
		unique_ptr<Impl> pImpl;
	};




}
//end basecross
