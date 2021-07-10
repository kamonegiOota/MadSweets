#pragma once
#include<memory>
#include<vector>

namespace itbs
{
	namespace Utility
	{
		/// <summary>
		/// �֐��|�C���^���b�v�N���X
		/// </summary>
		template<class T, class... Types>
		class I_Func
		{
		public:
			virtual T operator()(Types... args) = 0;
			virtual bool IsValid() const = 0;
		};

		/// <summary>
		/// �����o�֐��|�C���^���b�v�N���X
		/// </summary>
		template<class Object, class T, class... Args>
		class MemberFunction : public I_Func<T, Args...>
		{
		public:
			using func_type = T(Object::*)(Args...);

		private:
			std::weak_ptr<Object> ptr;
			func_type fn;

		public:
			/// <summary>
			/// �R���X�g���N�^
			/// </summary>
			/// <param name="ptr">�֐����ĂԃI�u�W�F�N�g</param>
			/// <param name="fn">�֐��|�C���^</param>
			MemberFunction(const std::shared_ptr<Object>& ptr, func_type fn) :
				ptr(ptr),
				fn(fn)
			{

			}

			T operator()(Args... args) override
			{
				auto* objectPtr = ptr.lock().get();
				return (objectPtr->*fn)(args...);
			}

			bool IsValid() const override
			{
				return !ptr.expired();
			}
		};

		/// <summary>
		/// �O���[�o�� or static�֐��|�C���^���b�v�N���X
		/// </summary>
		template<class T, class... Args>
		class GlobalFunction : public I_Func<T, Args...>
		{
		public:
			using func_type = T(*)(Args...);

		private:
			func_type fn;

		public:
			GlobalFunction(func_type fn) :
				fn(fn)
			{

			}

			T operator()(Args... args) override
			{
				return (*fn)(args...);
			}

			bool IsValid() const override
			{
				return true;
			}
		};

		/// <summary>
		/// �f���Q�[�g�N���X
		/// </summary>
		template<class T>
		class Delegate;

		/// <summary>
		/// �f���Q�[�g�N���X
		/// </summary>
		template<class T, class... Args>
		class Delegate<T(Args...)>
		{
			using I_func = I_Func<T, Args...>;
			std::vector<std::shared_ptr<I_func>> functions;
		public:

			/// <summary>
			/// �����o�֐��|�C���^�o�^�֐�
			/// </summary>
			/// <param name="object">�֐����ĂԃI�u�W�F�N�g��shard�|�C���^</param>
			/// <param name="fn">�����o�֐��|�C���^</param>
			template<class Obj>
			void AddFunc(const std::shared_ptr<Obj>& object, T(Obj::* fn)(Args...))
			{
				auto memberFunc = std::make_shared<MemberFunction<Obj, T, Args...>>(object, fn);
				functions.push_back(memberFunc);
			}

			/// <summary>
			/// �O���[�o�� or static�֐��|�C���^�o�^�֐�
			/// </summary>
			/// <param name="fn">�֐��|�C���^</param>
			void AddFunc(T(*fn)(Args...))
			{
				auto globalFunc = std::make_shared<GlobalFunction<T, Args...>>(fn);
				functions.push_back(globalFunc);
			}

			void RemoveAll()
			{
				functions.clear();
			}

			void operator()(Args... args)
			{
				auto it = functions.begin();

				while (it != functions.end())
				{
					auto& func = (*it);
					if (!func->IsValid())
					{
						it = functions.erase(it);
						continue;
					}

					(*func)(args...);
					it++;
				}
			}
		};

	}
}