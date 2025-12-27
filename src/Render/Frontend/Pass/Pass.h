#pragma once
#include "Core/Core.h"

namespace PlayGround {

	class Scene;
}

namespace PlayGround::Render { 

	class Pass
	{
	public:

		class Impl
		{
		public:

			Impl() = default;
			virtual ~Impl() = default;
		};

	public:

		Pass();
		virtual ~Pass() = default;

		virtual void OnConstruct() = 0;

		virtual void OnRender(Scene* scene) = 0;

	private:

		SP<Impl> CreatePassImplement();

	private:
	
		SP<Impl> m_Impl = nullptr;

	};
}