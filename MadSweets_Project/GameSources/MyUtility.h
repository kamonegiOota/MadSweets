
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
			/// 特定のオブジェクトがRay状に合ったらtrueを返す。
			/// </summary>
			/// <param name="startObj">Rayの開始</param>
			/// <param name="endObj">Rayの終わり</param>
			/// <param name="obstacleObj">間にあるかどうか判断したいオブジェクト</param>
			/// <returns>Ray状に合ったらtrue</returns>
			static bool IsRayObstacle(const std::shared_ptr<GameObject>& startObj, 
				const std::shared_ptr<GameObject>& endObj,
				const std::shared_ptr<GameObject>& obstacleObj);

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
			/// templateで指定されたクラスを覗いて、障害物判定を取る関数。
			/// </summary>
			template<class ExcluteClass>
			static bool IsRayObstacle(const std::shared_ptr<GameObject>& startObj,
				const std::shared_ptr<GameObject>& endObj)
			{
				auto exclutes = maru::MyUtility::GetComponents<ExcluteClass>();
				return IsRayObstacle(startObj, endObj, exclutes);
			}
			
			//対象の障害物が二つのRayの間に合ったらtrue
			static bool IsRayObstacle(const Vec3& startObj, const Vec3& endObj,
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
			template<class T>
			static shared_ptr<T> GetGameObject() {
				auto& app = App::GetApp();
				auto scene = app->GetScene<Scene>();
				auto stage = scene->GetActiveStage();

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
			template<class T>
			static vector<shared_ptr<T>> GetGameObjects() {
				auto& app = App::GetApp();
				auto scene = app->GetScene<Scene>();
				auto stage = scene->GetActiveStage();

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

			template<class T>
			static vector<shared_ptr<T>> GetComponents() {
				auto& app = App::GetApp();
				auto scene = app->GetScene<Scene>();
				auto stage = scene->GetActiveStage();

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

			//ベクター配列から特定のオブジェクトを削除する関数。
			template<class T>
			//static void RemoveVec(vector<shared_ptr<T>>& vec, const shared_ptr<T>& removePtr) {
			static void RemoveVec(vector<T>& vec, const T& removePtr) {
				auto iter = vec.begin();
				while (iter != vec.end()) {
					if (*iter == removePtr) {
						iter = vec.erase(iter);
						break;
					}
					iter++;
				}
			}
		};
	}

	

}

//endbasecross