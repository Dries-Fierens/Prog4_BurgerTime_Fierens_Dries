#pragma once
#include <glm/glm.hpp>
#include <memory>

namespace dae
{
	class Controller final
	{
	public:
		explicit Controller(unsigned int controllerIndex);
		~Controller();
		Controller(const Controller& other) = delete;
		Controller& operator=(const Controller& rhs) = delete;
		Controller(Controller&& other) = delete;
		Controller& operator=(Controller&& rhs) = delete;

		void Update();

		unsigned int GetIndex() const { return m_controllerIndex; }
		glm::vec2 GetLeftStickPos() const;

		enum class ButtonState
		{
			Up = 0x0001,
			Down = 0x0002,
			Left = 0x0004,
			Right = 0x0008,
			Start = 0x0010,
			Back = 0x0020,
			LeftStickPress = 0x0040,
			RightStickPress = 0x0080,
			LeftShoulder = 0x0100,
			RightShoulder = 0x0200,
			A = 0x1000,
			B = 0x2000,
			X = 0x4000,
			Y = 0x8000,
			LeftStick
		};

		bool IsDown(ButtonState button) const;
		bool IsUp(ButtonState button) const;
		bool IsPressed(ButtonState button) const;

	private:
		class ControllerImpl;
		std::unique_ptr<ControllerImpl> m_pImpl{};
		unsigned int m_controllerIndex{};
	};
}