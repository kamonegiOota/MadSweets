
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

		};
	}

	

}

//endbasecross