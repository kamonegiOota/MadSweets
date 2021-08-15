
/*!
@file MyUtility.h
@brief MyUtilityクラス
担当：丸山裕喜
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	namespace maru{

		class MyUtility
		{

		public:

			static constexpr float FOWARD_ADJUST = -XM_PIDIV2;

			static std::shared_ptr<Stage> GetStage();

			//対象が正面にいるかどうか
			static bool IsTargetInFront(const std::shared_ptr<GameObject>& target, const std::shared_ptr<GameObject>& self);

			//一つ目の引数の方向に向く
			//※y軸に対応してないため、yは0で渡してください。
			//対応次第コメ書き消します。
			static void SetLookDirect(const Vec3& direct, const std::shared_ptr<GameObject>& objPtr);

			/// <summary>
			/// ターゲットに向かうベクトルを計算してくれる。
			/// </summary>
			/// <param name="self">自分自身のポインタ</param>
			/// <param name="target">ターゲットのポインタ</param>
			/// <returns>ターゲットに向かうベクトル</returns>
			static Vec3 CalucToTargetVec(const std::shared_ptr<GameObject>& self, const std::shared_ptr<GameObject>& target);

			/// <summary>
			/// Rayを飛ばしたとき、障害物があったらtrueを返す。
			/// </summary>
			/// <param name="startObj">Rayのスタートポジション</param>
			/// <param name="endObj">Rayのエンドポジション</param>
			/// <returns>障害物があったらtrue</returns>
			static bool IsRayObstacle(const std::shared_ptr<GameObject>& startObj, const std::shared_ptr<GameObject>& endObj);
			static bool IsRayObstacle(const Vec3& startPos, const Vec3& endPos);

			/// <summary>
			/// 対象のオブジェクトまでに障害物があるかどうか
			/// </summary>
			/// <param name="startObj">Rayのスタート</param>
			/// <param name="endObj">Rayを飛ばす対象</param>
			/// <param name="excluteObj">障害物として省く対象</param>
			/// <returns>障害物が合ったらtrue</returns>
			static bool IsRayObstacle(const std::shared_ptr<GameObject>& startObj,
				const std::shared_ptr<GameObject>& endObj,
				const vector<shared_ptr<GameObject>>& excluteObjs);

			/// <summary>
			/// 対象のオブジェクトまでに障害物があるかどうか
			/// </summary>
			/// <param name="startPos">Rayのスタート</param>
			/// <param name="endPos">Rayを飛ばす対象</param>
			/// <param name="excluteObjs">障害物として省く対象</param>
			/// <returns>障害物が合ったらtrue</returns>
			static bool IsRayObstacle(const Vec3& startPos, const Vec3& endPos,
				const vector<shared_ptr<GameObject>>& excluteObjs);

			/// <summary>
			/// 対象オブジェクトまでに障害物があるかどうか
			/// </summary>
			/// <param name="startObj">Rayのスタート</param>
			/// <param name="endObj">対象オブジェクト</param>
			/// <param name="obstacleObjs">障害物の対象になるオブジェクト</param>
			/// <param name="excluteObjs">障害物の対象になるオブジェクトの中でも特定のオブジェクトを対象外にしたい場合に記述</param>
			/// <returns>障害物が合ったらtrue</returns>
			static bool IsRayObstacle(const std::shared_ptr<GameObject>& startObj, const std::shared_ptr<GameObject>& endObj,
				const vector<shared_ptr<GameObject>>& obstacleObjs, const vector<shared_ptr<GameObject>>& excluteObjs);

			/// <summary>
			/// 対象オブジェクトまでに障害物があるかどうか
			/// </summary>
			/// <param name="startPos">Rayのスタート</param>
			/// <param name="endPos">対象オブジェクト</param>
			/// <param name="obstacleObjs">障害物の対象になるオブジェクト</param>
			/// <param name="excluteObjs">障害物の対象になるオブジェクトの中でも特定のオブジェクトを対象外にしたい場合に記述</param>
			/// <returns>障害物が合ったらtrue</returns>
			static bool IsRayObstacle(const Vec3& startPos, const Vec3& endPos,
				const vector<shared_ptr<GameObject>>& obstacleObjs, const vector<shared_ptr<GameObject>>& excluteObjs);

			/// <summary>
			/// templateで指定されたクラスを覗いて、障害物判定を取る関数。
			/// </summary>
			template<class ExcluteClass>
			static bool IsRayObstacleExclute(const std::shared_ptr<GameObject>& startObj,
				const std::shared_ptr<GameObject>& endObj)
			{
				auto exclutes = maru::MyUtility::GetComponents<ExcluteClass>();
				return IsRayObstacle(startObj, endObj, exclutes);
			}

			/// <summary>
			/// Templateで指定したコンポーネントのついているオブジェクトを指定障害物判定して探す。
			/// </summary>
			template<class ObstacleClass>
			static bool IsRayObstacle(const std::shared_ptr<GameObject>& startObj,
				const std::shared_ptr<GameObject>& endObj)
			{
				auto obstacleObjs = maru::MyUtility::GetComponents<ObstacleClass>();

				return IsRayObstacle(startObj, endObjs, obstacleObjs, vector<shared_ptr<GameObject>>());
			}

			/// <summary>
			/// 特定のオブジェクトがRay状に合ったらtrueを返す。
			/// </summary>
			/// <param name="startObj">Rayの開始</param>
			/// <param name="endObj">Rayの終わり</param>
			/// <param name="obstacleObj">間にあるかどうか判断したいオブジェクト</param>
			/// <returns>Ray状に合ったらtrue</returns>
			static bool IsRayObstacle(const std::shared_ptr<GameObject>& startObj,
				const std::shared_ptr<GameObject>& endObj,
				const std::shared_ptr<GameObject>& obstacleObj);
			
			//対象の障害物が二つのRayの間に合ったらtrue
			static bool IsRayObstacle(const Vec3& startPos, const Vec3& endPos,
				const std::shared_ptr<GameObject>& obstacleObj);

			/// <summary>
			/// 対象のオブジェクトが対象外かどうか判断する
			/// </summary>
			/// <param name="targetObj">対象のオブジェクト</param>
			/// <param name="excluteObjs">対象外となる配列オブジェクト</param>
			/// <returns>対象外ならtrue</returns>
			static bool IsExclute(const shared_ptr<GameObject>& targetObj ,const vector<shared_ptr<GameObject>>& excluteObjs);


			//ゲームオブジェクトVecから指定のオブジェクトのみ取得
			//最初に取得できたものだけ返す。
			template<class T,
				enable_if_t<is_base_of_v<GameObject, T>, std::nullptr_t> = nullptr >
			static shared_ptr<T> GetGameObject() {
				auto stage = GetStage();

				auto objs = stage->GetGameObjectVec();
				for (auto& obj : objs) {
					auto t = dynamic_pointer_cast<T>(obj);
					if (t) {
						return t;
					}
				}

				return nullptr;
			}

			//ゲームオブジェクトVecから指定のオブジェクトのみ取得
			//ベクター配列として見つけたもの全て返す。
			template<class T,
				enable_if_t<is_base_of_v<GameObject, T>, std::nullptr_t> = nullptr >
			static vector<shared_ptr<T>> GetGameObjects() {
				auto stage = GetStage();

				vector<shared_ptr<T>> returnObjs;

				auto objs = stage->GetGameObjectVec();
				for (auto& obj : objs) {
					auto t = dynamic_pointer_cast<T>(obj);
					if (t) {
						returnObjs.push_back(t);
					}
				}

				return returnObjs;
			}

			template<class T,
				enable_if_t<is_base_of_v<Component, T>, std::nullptr_t> = nullptr >
			static shared_ptr<T> GetComponent() {
				auto stage = GetStage();

				auto objs = stage->GetGameObjectVec();
				for (auto& obj : objs) {
					auto t = obj->GetComponent<T>(false);
					if (t) {
						return t;
					}
				}

				return nullptr;
			}

			template<class T,
				enable_if_t<is_base_of_v<Component, T>, std::nullptr_t> = nullptr >
			static vector<shared_ptr<T>> GetComponents() {
				auto stage = GetStage();

				vector<shared_ptr<T>> returnObjs;

				auto objs = stage->GetGameObjectVec();
				for (auto& obj : objs) {
					auto t = obj->GetComponent<T>(false);
					if (t) {
						returnObjs.push_back(t);
					}
				}

				return returnObjs;
			}

			/// <summary>
			/// 渡された配列にtemplateで指定したオブジェクト型のオブジェクトを追加する。
			/// </summary>
			template<class T,
				enable_if_t<is_base_of_v<GameObject, T>, std::nullptr_t> = nullptr >
			static void AddObjects(vector<shared_ptr<GameObject>>& addVec) {
				auto stage = GetStage();

				auto objs = stage->GetGameObjectVec();
				for (auto& obj : objs) {
					auto t = dynamic_pointer_cast<T>(obj);
					if (t) {
						addVec.push_back(t);  //オブジェクトの追加
					}
				}
			}

			/// <summary>
			/// 渡された配列にtemplateで指定したコンポーネントを持つオブジェクトを追加する。
			/// </summary>
			template<class T ,
				enable_if_t<is_base_of_v<Component, T>, std::nullptr_t> = nullptr >
			static void AddComponents(vector<shared_ptr<GameObject>>& addVec) {
				auto stage = GetStage();

				auto objs = stage->GetGameObjectVec();
				for (auto& obj : objs) {
					auto t = obj->GetComponent<T>(false);
					if (t) {
						addVec.push_back(obj);  //オブジェクトの追加
					}
				}
			}

			//ベクター配列から特定のオブジェクトを削除する関数。
			template<class T>
			//static void RemoveVec(vector<shared_ptr<T>>& vec, const shared_ptr<T>& removePtr) {
			static bool RemoveVec(vector<T>& vec, const T& removePtr) {
				auto iter = vec.begin();
				while (iter != vec.end()) {
					if (*iter == removePtr) {
						iter = vec.erase(iter);
						return true;
						//break;
					}
					iter++;
				}

				return false;
			}

		};
	}

	

}

//endbasecross