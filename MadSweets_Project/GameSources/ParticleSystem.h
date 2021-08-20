#pragma once
#include"Bezier.h"

namespace basecross
{
	/// <summary>
	/// パーティクルに使う値のインターフェース
	/// </summary>
	class I_ParticleValue
	{
	public:
		/// <summary>
		/// 時間に対する値を返す
		/// </summary>
		/// <param name="time">時間</param>
		/// <returns>時間に対する値</returns>
		virtual float GetValueToTime(const float time) const = 0;
	};

	/// <summary>
	/// 時間に関係なく定数を返す値クラス
	/// </summary>
	class ParticleValueConstant : public I_ParticleValue
	{
		/// <summary>
		/// 返す値
		/// </summary>
		float m_value = 0.0f;

	public:
		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="value">返す値</param>
		ParticleValueConstant(const float value);
		/// <summary>
		/// 返す値を設定する
		/// </summary>
		/// <param name="value">返す値</param>
		void SetValue(const float value);
		/// <summary>
		/// 時間に対する値を返す
		/// </summary>
		/// <param name="time">時間</param>
		/// <returns>時間に対する値</returns>
		float GetValueToTime(const float time) const override;
	};

	/// <summary>
	/// ベジェ曲線を使ったカーブで時間に対する値を返すクラス
	/// </summary>
	class ParticleValueCurve : public I_ParticleValue
	{
		/// <summary>
		/// 時間に対する値を持ったベジェ曲線
		/// </summary>
		itbs::Math::BezierManager m_bezier;

	public:
		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="bezier">時間に対する値を持ったベジェ曲線</param>
		ParticleValueCurve(const itbs::Math::BezierManager& bezier);
		/// <summary>
		/// 使用するベジェ曲線を設定する
		/// </summary>
		/// <param name="bezier">時間に対する値を持ったベジェ曲線</param>
		void SetCurve(const itbs::Math::BezierManager& bezier);
		/// <summary>
		/// 時間に対する値を返す
		/// </summary>
		/// <param name="time">時間</param>
		/// <returns>時間に対する値</returns>
		float GetValueToTime(const float time) const override;
	};

	/// <summary>
	/// 二つの値の間をランダムで値を返すクラス
	/// </summary>
	class ParticleValueRandomBitweenConstants : public I_ParticleValue
	{
		/// <summary>
		/// ランダム最小値
		/// </summary>
		float m_minValue = 0.0f;
		/// <summary>
		/// ランダム最大値
		/// </summary>
		float m_maxValue = 0.0f;

	public:
		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="minValue">ランダム最小値</param>
		/// <param name="maxValue">ランダム最大値</param>
		ParticleValueRandomBitweenConstants(const float minValue, const float maxValue);
		/// <summary>
		/// ランダムに使う最小値と最大値を設定する
		/// </summary>
		/// <param name="minValue">ランダムに使う最小値</param>
		/// <param name="maxValue">ランダムに使う最大値</param>
		void SetValue(const float minValue, const float maxValue);
		/// <summary>
		/// 時間に対する値を返す
		/// </summary>
		/// <param name="time">時間</param>
		/// <returns>時間に対する値</returns>
		float GetValueToTime(const float time) const override;
	};

	/// <summary>
	/// 二つのベジェ曲線から得た値の間をランダムに返すクラス
	/// </summary>
	class ParticleValueRandomBitweenCurves : public I_ParticleValue
	{
		/// <summary>
		/// 一つ目のベジェ曲線
		/// </summary>
		itbs::Math::BezierManager m_bezier1;
		/// <summary>
		/// 二つ目のベジェ曲線
		/// </summary>
		itbs::Math::BezierManager m_bezier2;

	public:
		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="bezier1">一つ目のベジェ曲線</param>
		/// <param name="bezier2">二つ目のベジェ曲線</param>
		ParticleValueRandomBitweenCurves(const itbs::Math::BezierManager& bezier1, const itbs::Math::BezierManager& bezier2);
		/// <summary>
		/// 使用するベジェ曲線を設定する
		/// </summary>
		/// <param name="bezier1">一つ目のベジェ曲線</param>
		/// <param name="bezier2">二つ目のベジェ曲線</param>
		void SetCurves(const itbs::Math::BezierManager& bezier1, const itbs::Math::BezierManager& bezier2);
		/// <summary>
		/// 時間に対する値を返す
		/// </summary>
		/// <param name="time">時間</param>
		/// <returns>時間に対する値</returns>
		float GetValueToTime(const float time) const override;
	};

	/// <summary>
	/// パーティクルに使うベクトルのインターフェース
	/// </summary>
	class I_ParticleVec3
	{
	public:
		/// <summary>
		/// 時間に対する値を返す
		/// </summary>
		/// <param name="time">時間</param>
		/// <returns>時間に対するベクトル</returns>
		virtual Vec3 GetVec3ToTime(const float time) const = 0;
	};

	/// <summary>
	/// 時間に関係なく固定値を返すクラス
	/// </summary>
	class ParticleVec3Constant : public I_ParticleVec3
	{
		/// <summary>
		/// 返すベクトル
		/// </summary>
		Vec3 m_vec3;

	public:
		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="vec3">返す固定値</param>
		ParticleVec3Constant(const Vec3& vec3);
		/// <summary>
		/// 返す固定値を設定する
		/// </summary>
		/// <param name="vec3">返す固定値</param>
		void SetValue(const Vec3& vec3);
		/// <summary>
		/// 時間に対する値を返す
		/// </summary>
		/// <param name="time">時間</param>
		/// <returns>時間に対するベクトル</returns>
		Vec3 GetVec3ToTime(const float time) const override;
	};

	/// <summary>
	/// 時間に対する値を持ったベジェ曲線を使って値を返すクラス
	/// </summary>
	class ParticleVec3Curve : public I_ParticleVec3
	{
		/// <summary>
		/// X軸の情報を持ったベジェ曲線
		/// </summary>
		itbs::Math::BezierManager m_bezierX;
		/// <summary>
		/// Y軸の情報を持ったベジェ曲線
		/// </summary>
		itbs::Math::BezierManager m_bezierY;
		/// <summary>
		/// Z軸の情報を持ったベジェ曲線
		/// </summary>
		itbs::Math::BezierManager m_bezierZ;

	public:
		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="bezierX">X軸の情報を持ったベジェ曲線</param>
		/// <param name="bezierY">Y軸の情報を持ったベジェ曲線</param>
		/// <param name="bezierZ">Z軸の情報を持ったベジェ曲線</param>
		ParticleVec3Curve(const itbs::Math::BezierManager& bezierX, const itbs::Math::BezierManager& bezierY, const itbs::Math::BezierManager& bezierZ);
		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="bezierSize">X,Y,Z軸で使うベジェ曲線</param>
		ParticleVec3Curve(const itbs::Math::BezierManager& bezierSize);

		/// <summary>
		/// 時間に対するベクトルを持ったベジェ曲線を設定する
		/// </summary>
		/// <param name="bezierX">X軸の情報を持ったベジェ曲線</param>
		/// <param name="bezierY">Y軸の情報を持ったベジェ曲線</param>
		/// <param name="bezierZ">Z軸の情報を持ったベジェ曲線</param>
		void SetCurves(const itbs::Math::BezierManager& bezierX, const itbs::Math::BezierManager& bezierY, const itbs::Math::BezierManager& bezierZ);
		/// <summary>
		/// 時間に対するベクトルを持ったベジェ曲線を設定する
		/// </summary>
		/// <param name="bezierSize">X,Y,Z軸の情報を持ったベジェ曲線</param>
		void SetCurve(const itbs::Math::BezierManager& bezierSize);

		/// <summary>
		/// 時間に対する値を返す
		/// </summary>
		/// <param name="time">時間</param>
		/// <returns>時間に対するベクトル</returns>
		Vec3 GetVec3ToTime(const float time) const override;
	};

	/// <summary>
	/// パーティクルで使用する色のインターフェース
	/// </summary>
	class I_ParticleColor
	{
	public:
		/// <summary>
		/// 時間に対する値を返す
		/// </summary>
		/// <param name="time">時間</param>
		/// <returns>時間に対するベクトル</returns>
		virtual Col4 GetColorToTime(const float time) const = 0;
	};

	/// <summary>
	/// 時間に関係なく固定値を返すクラス
	/// </summary>
	class ParticleColorConstant : public I_ParticleColor
	{
		/// <summary>
		/// 返す色
		/// </summary>
		Col4 m_color = Col4(1.0f, 1.0f, 1.0f, 1.0f);

	public:
		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="color">返す色</param>
		ParticleColorConstant(const Col4& color);

		/// <summary>
		/// 返す色を設定する
		/// </summary>
		/// <param name="color">返す色</param>
		void SetColor(const Col4& color);

		/// <summary>
		/// 時間に対する値を返す
		/// </summary>
		/// <param name="time">時間</param>
		/// <returns>時間に対するベクトル</returns>
		Col4 GetColorToTime(const float time) const override;
	};

	/// <summary>
	/// 二つの色の間をランダムに返すクラス
	/// </summary>
	class ParticleColorRandomBitweenColors : public I_ParticleColor
	{
		/// <summary>
		/// 一つ目の色
		/// </summary>
		Col4 m_color1;
		/// <summary>
		/// 二つ目の色
		/// </summary>
		Col4 m_color2;

	public:

		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="color1">一つ目の色</param>
		/// <param name="color2">二つ目の色</param>
		ParticleColorRandomBitweenColors(const Col4& color1, const Col4& color2);

		/// <summary>
		/// 使用する色を設定する
		/// </summary>
		/// <param name="color1">一つ目の色</param>
		/// <param name="color2">二つ目の色</param>
		void SetColors(const Col4& color1, const Col4& color2);

		/// <summary>
		/// 時間に対する値を返す
		/// </summary>
		/// <param name="time">時間</param>
		/// <returns>時間に対するベクトル</returns>
		Col4 GetColorToTime(const float time) const override;
	};

	/// <summary>
	/// 時間によるパーティクルのバーストに使うデータ構造体
	/// </summary>
	class ParticleBurst
	{
		/// <summary>
		/// バーストが開始したか
		/// </summary>
		bool m_isBurst = false;
		/// <summary>
		/// バースト開始時間
		/// </summary>
		float m_time = 0.0f;
		/// <summary>
		/// バーストした際に発生する個数
		/// </summary>
		int m_count = 0;
		/// <summary>
		/// 何回バーストするか
		/// </summary>
		int m_cycles = 1;
		/// <summary>
		/// 何回バーストしたか
		/// </summary>
		int m_cycleCount = 0;
		/// <summary>
		/// バーストインターバル
		/// </summary>
		float m_interval = 0.01f;
		/// <summary>
		/// パーティクルが発生する確率
		/// </summary>
		float m_probabil = 1.0f;

	public:
		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="time">発火する時間</param>
		/// <param name="count">発火したときに発生するパーティクル数</param>
		/// <param name="cycles">何回繰り返すか</param>
		/// <param name="interval">クリアS時にどれぐらいの秒数開けるか</param>
		/// <param name="probabil">放出する確率</param>
		ParticleBurst(const float time, const int count, const int cycles, const float interval = 0.01f, const float probabil = 1.0f);

		/// <summary>
		/// バースト開始前にリセットする
		/// </summary>
		/// <param name="duration">パーティクル再生時間</param>
		void Reset(const float duration);
		/// <summary>
		/// バーストしたかどうかを取得する
		/// </summary>
		/// <param name="time">現在時間</param>
		/// <returns>バーストしたかどうか</returns>
		bool IsBurst(const float time);
		/// <summary>
		/// 何個パーティクルが発生するか取得する
		/// </summary>
		/// <returns></returns>
		int GetCount() const;
		/// <summary>
		/// 確率を取得する
		/// </summary>
		/// <returns>発生する確率</returns>
		float GetProbabil() const;
	};

	/// <summary>
	/// パーティクル発生範囲インターフェース
	/// </summary>
	class I_ParticleShape
	{
	public:
		/// <summary>
		/// パーティクル発生情報を作成する
		/// </summary>
		/// <param name="position">発生個所</param>
		/// <param name="direction">発生時のベクトル</param>
		virtual void CreateEmission(Vec3& position,Vec3& direction) const = 0;
	};

	/// <summary>
	/// 球のパーティクル発生範囲クラス
	/// </summary>
	class ParticleShapeSphere : public I_ParticleShape
	{
		/// <summary>
		/// 球の半径
		/// </summary>
		float m_radius = 1.0f;

	public:
		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="radius">球の半径</param>
		ParticleShapeSphere(const float radius = 1.0f);
		/// <summary>
		/// 球の半径を設定する
		/// </summary>
		/// <param name="radius">球の半径</param>
		void SetRadius(const float radius);
		/// <summary>
		/// パーティクル発生情報を作成する
		/// </summary>
		/// <param name="position">発生個所</param>
		/// <param name="direction">発生時のベクトル</param>
		void CreateEmission(Vec3& position,Vec3& direction) const override;
	};

	/// <summary>
	/// 半球のパーティクル発生範囲クラス
	/// </summary>
	class ParticleShapeHemisphere : public I_ParticleShape
	{
		/// <summary>
		/// 半球の半径
		/// </summary>
		float m_radius = 1.0f;

	public:
		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="radius">半球の半径</param>
		ParticleShapeHemisphere(const float radius = 1.0f);
		/// <summary>
		/// 半球の半径を設定する
		/// </summary>
		/// <param name="radius">半球の半径</param>
		void SetRadius(const float radius);
		/// <summary>
		/// パーティクル発生情報を作成する
		/// </summary>
		/// <param name="position">発生個所</param>
		/// <param name="direction">発生時のベクトル</param>
		void CreateEmission(Vec3& position, Vec3& direction) const override;
	};

	/// <summary>
	/// 円錐台のパーティクル発生範囲クラス
	/// </summary>
	class ParticleShapeCone : public I_ParticleShape
	{
		/// <summary>
		/// 円錐台の角度
		/// </summary>
		float m_angle;
		/// <summary>
		/// 円錐台の上面の半径
		/// </summary>
		float m_radius;
		/// <summary>
		/// 円錐台の高さ
		/// </summary>
		float m_length;

		/// <summary>
		/// 円錐台の底面の半径
		/// </summary>
		float m_angleToRadius;
		/// <summary>
		/// ローカル座標
		/// </summary>
		Vec3 m_localPosition;
		/// <summary>
		/// ローカル回転
		/// </summary>
		Quat m_localRotation;

		/// <summary>
		/// 円錐台の角度から底面の半径を設定する
		/// </summary>
		void SetAngleToRadius();

	public:
		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="angle">円錐台の角度</param>
		/// <param name="radius">円錐台の上面の半径</param>
		/// <param name="length">円錐台の高さ</param>
		ParticleShapeCone(const float angle = XMConvertToRadians(25), const float radius = 1.0f, const float length = 5.0f);

		/// <summary>
		/// 円錐台の角度を設定する
		/// </summary>
		/// <param name="angle">円錐台の角度</param>
		void SetAngle(const float angle);
		/// <summary>
		/// 円錐台の上面の半径の設定する
		/// </summary>
		/// <param name="radius">円錐台の上面の半径</param>
		void SetRadius(const float radius);
		/// <summary>
		/// 円錐台の高さを設定する
		/// </summary>
		/// <param name="length">円錐台の高さ</param>
		void SetLength(const float length);
		/// <summary>
		/// ローカル座標を設定する
		/// </summary>
		/// <param name="localPosition">ローカル座標</param>
		void SetLocalPosition(const Vec3& localPosition);
		/// <summary>
		/// ローカル回転を設定する
		/// </summary>
		/// <param name="localRotation">ローカル回転</param>
		void SetLocalRotation(const Vec3& localRotation);

		/// <summary>
		/// パーティクル発生情報を作成する
		/// </summary>
		/// <param name="position">発生個所</param>
		/// <param name="direction">発生時のベクトル</param>
		void CreateEmission(Vec3& position, Vec3& direction) const override;
	};

	/// <summary>
	/// パーティクル管理コンポーネント
	/// </summary>
	class ParticleSystem : public Component
	{
		/// <summary>
		/// パーティクル生成時のデータ構造体
		/// </summary>
		struct StartSpriteData : public ParticleSprite
		{
			/// <summary>
			/// 重力のスケール
			/// </summary>
			float gravityScale;
			/// <summary>
			/// カメラの向きを軸とした回転
			/// </summary>
			float rotation;

			/// <summary>
			/// コンストラクタ
			/// </summary>
			StartSpriteData();
			/// <summary>
			/// コンストラクタ
			/// </summary>
			/// <param name="particleSprite">パーティクルスプライト</param>
			/// <param name="gravityScale">重力のスケール</param>
			/// <param name="rotation">カメラの向きを軸とした回転</param>
			StartSpriteData(const ParticleSprite& particleSprite, const float gravityScale,const float rotation);
		};

		/// <summary>
		/// パーティクル管理用データ
		/// </summary>
		struct ParticleData
		{
			/// <summary>
			/// パーティクルのポインタ
			/// </summary>
			ex_weak_ptr<Particle> particle;
			/// <summary>
			/// パーティクル発生時のデータ
			/// </summary>
			std::vector<StartSpriteData> startDatas;
			/// <summary>
			/// パーティクルに対して流れた時間
			/// </summary>
			float nowTime = 0.0f;
		};

		/// <summary>
		/// デフォルトでパーティクルに使う画像のキー
		/// </summary>
		static const std::wstring DEFAULT_TEXTURE_KEY;

		/// <summary>
		/// パーティクルにかかる重力の標準
		/// </summary>
		static constexpr float DEFAULT_GRAVITY_VALUE = 0.98f;

		/// <summary>
		/// カメラポインタ
		/// </summary>
		const ex_weak_ptr<Camera const> m_camera;

		/// <summary>
		/// マルチパーティクルポインタ
		/// </summary>
		ex_weak_ptr<MultiParticle> m_multiParticle;

		/// <summary>
		/// パーティクル管理用配列
		/// </summary>
		std::vector<ParticleData> m_particleDatas;

		/// <summary>
		/// パーティクルが終了した際にオブジェクトを削除するか
		/// </summary>
		bool m_isFinishedDestroy = false;
		/// <summary>
		/// 再生時間に対しての現在の時間
		/// </summary>
		float m_particleTimer = 0.0f;
		/// <summary>
		/// RateOverLifeTime用の時間
		/// </summary>
		float m_emissionTimer = 0.0f;
		/// <summary>
		/// パーティクル再生時間
		/// </summary>
		float m_duration = 1.0f;
		/// <summary>
		/// ループさせるかどうか
		/// </summary>
		bool m_isLooping = true;
		/// <summary>
		/// 開始時のパーティクル寿命
		/// </summary>
		std::shared_ptr<I_ParticleValue> m_startLifeTime = std::make_shared<ParticleValueConstant>(5.0f);
		/// <summary>
		/// パーティクル放出時の開始速度
		/// </summary>
		std::shared_ptr<I_ParticleValue> m_startSpeed = std::make_shared<ParticleValueConstant>(5.0f);
		/// <summary>
		/// パーティクル放出時のサイズ
		/// </summary>
		std::shared_ptr<I_ParticleVec3> m_startSize = std::make_shared<ParticleVec3Constant>(Vec3(1.0f));
		/// <summary>
		/// パーティクル放出時のカメラの向きに対しての回転
		/// </summary>
		std::shared_ptr<I_ParticleValue> m_startRotation = std::make_shared<ParticleValueConstant>(0.0f);
		/// <summary>
		/// パーティクル放出時の色
		/// </summary>
		std::shared_ptr<I_ParticleColor> m_startColor = std::make_shared<ParticleColorConstant>(Col4(1.0f, 1.0f, 1.0f, 1.0f));
		/// <summary>
		/// パーティクルにかかる重力
		/// </summary>
		std::shared_ptr<I_ParticleValue> m_gravityScale = std::make_shared<ParticleValueConstant>(0.0f);
		/// <summary>
		/// 毎秒いくつパーティクルを発生させるか
		/// </summary>
		std::shared_ptr<I_ParticleValue> m_rateOverTime = std::make_shared<ParticleValueConstant>(0);
		/// <summary>
		/// パーティクルバースト用の配列
		/// </summary>
		std::vector<ParticleBurst> m_particleBursts;
		/// <summary>
		/// パーティクル生成用の形
		/// </summary>
		std::shared_ptr<I_ParticleShape> m_particleShape = std::make_shared<ParticleShapeSphere>();
		/// <summary>
		/// 時間に対するパーティクルに加わる力
		/// </summary>
		std::shared_ptr<I_ParticleVec3> m_ForceOverLifeTime = std::make_shared<ParticleVec3Constant>(Vec3());
		/// <summary>
		/// 時間に対するサイズの倍率
		/// </summary>
		std::shared_ptr<I_ParticleVec3> m_sizeOverLifeTime = std::make_shared<ParticleVec3Constant>(Vec3(1.0f));
		/// <summary>
		/// パーティクルに使う画像のキー
		/// </summary>
		std::wstring m_textureKey = DEFAULT_TEXTURE_KEY;

		/// <summary>
		/// パーティクル作成関数
		/// </summary>
		void CreateParticle();
		/// <summary>
		/// パーティクル更新関数
		/// </summary>
		void UpdateParticle();

		/// <summary>
		/// ビルボード用クォータニオンを作成する
		/// </summary>
		/// <returns>ビルボード用クォータニオン</returns>
		Quat CreateBillBoardQuat() const;
		/// <summary>
		/// カメラの向きを軸とした回転を表すクォータニオンを作成する
		/// </summary>
		/// <param name="rotation">回転</param>
		/// <returns>カメラの向きを軸とした回転を表すクォータニオン</returns>
		Quat CreateRotationQuat(const float rotation) const;

	public:
		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="owner">ゲームオブジェクト</param>
		ParticleSystem(std::shared_ptr<GameObject>& owner);

		/// <summary>
		/// パーティクル再生時間を設定する
		/// </summary>
		/// <param name="duration">パーティクル再生時間</param>
		void SetDuration(const float duration);
		/// <summary>
		/// ループするかどうかを設定する
		/// </summary>
		/// <param name="isLooping">ループするかどうか</param>
		void SetIsLooping(const bool isLooping);
		/// <summary>
		/// 開始時のパーティクル寿命を設定する
		/// </summary>
		/// <param name="startLifeTime">パーティクル寿命の値</param>
		void SetStartLifeTime(const std::shared_ptr<I_ParticleValue>& startLifeTime);
		/// <summary>
		/// 開始時のパーティクル速度を設定する
		/// </summary>
		/// <param name="startSpeed">開始時のパーティクル速度</param>
		void SetStartSpeed(const std::shared_ptr<I_ParticleValue>& startSpeed);
		/// <summary>
		/// パーティクル放出時のサイズを設定する
		/// </summary>
		/// <param name="startSize">パーティクル放出時のサイズ</param>
		void SetStartSize(const std::shared_ptr<I_ParticleVec3>& startSize);
		/// <summary>
		/// パーティクル放出時のカメラの向きに対しての回転を設定する
		/// </summary>
		/// <param name="startRotation">パーティクル放出時のカメラの向きに対しての回転</param>
		void SetStartRotation(const std::shared_ptr<I_ParticleValue>& startRotation);
		/// <summary>
		/// パーティクル放出時の色を設定する
		/// </summary>
		/// <param name="startColor">放出時の色</param>
		void SetStartColor(const std::shared_ptr<I_ParticleColor>& startColor);
		/// <summary>
		/// パーティクルにかかる重力を設定する
		/// </summary>
		/// <param name="gravityScale">パーティクルにかかる重力</param>
		void SetGravityScale(const std::shared_ptr<I_ParticleValue>& gravityScale);
		/// <summary>
		/// 秒あたりに生成するパーティクル数を設定する
		/// </summary>
		/// <param name="rateOverTime">秒あたりに生成するパーティクル数</param>
		void SetRateOverTime(const std::shared_ptr<I_ParticleValue>& rateOverTime);
		/// <summary>
		/// パーティクルバースト情報を追加する
		/// </summary>
		/// <param name="particleBurst">パーティクルバースト情報</param>
		void AddEmissionBurst(const ParticleBurst& particleBurst);
		/// <summary>
		/// パーティクルを放出する範囲の形を設定する
		/// </summary>
		/// <param name="particleShape">パーティクルを放出する範囲の形</param>
		void SetShape(const std::shared_ptr<I_ParticleShape>& particleShape);
		/// <summary>
		/// 寿命に対する加える力を設定する
		/// </summary>
		/// <param name="forceOverLifeTime">寿命に対する加える力</param>
		void SetForceOverLifeTime(const std::shared_ptr<I_ParticleVec3>& forceOverLifeTime);
		/// <summary>
		/// 寿命に対するサイズの倍率を設定する
		/// </summary>
		/// <param name="sizeOverLifeTime">寿命に対するサイズの倍率</param>
		void SetSizeOverLifeTime(const std::shared_ptr<I_ParticleVec3>& sizeOverLifeTime);
		/// <summary>
		/// パーティクルの画像を設定する
		/// </summary>
		/// <param name="textureKey">画像のキー</param>
		void SetTextureKey(const std::wstring& textureKey);
		/// <summary>
		/// パーティクルが終了した際にオブジェクトを削除するかを設定する
		/// </summary>
		/// <param name="isFinishedDestroy">パーティクルが終了した際にオブジェクトを削除するか</param>
		void SetIsFinishedDestroy(const bool isFinishedDestroy);

		void OnPreCreate() override;

		void OnUpdate() override;
	};
}