#pragma once
#include "Core/Core.h"
#include "NativeScript.h"
#include <filesystem>

namespace PlayGround {

	class VideoPlayer : public NativeScript
	{
	public:

		VideoPlayer(const std::filesystem::path path) : m_InFile{ path } {}
		~VideoPlayer() override = default;

		void OnAttached() override;
		void OnTick() override;

	private:

		std::filesystem::path m_InFile;

	};
}