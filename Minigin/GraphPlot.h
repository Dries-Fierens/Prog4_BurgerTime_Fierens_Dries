#pragma once
#include <vector>
#include <memory>

namespace dae
{
	class GraphPlot
	{
	public:
		void PlotIntegers() const;
		void PlotGameObject3D() const;

	private:
		template <typename T>
		std::vector<float> GetTimings(int samples) const;
		const int ARR_SIZE{ 10000000 };
		const int MAX_STEPSIZE{ 1024 };
		const int TOTAL_STEPS{ 11 };
		const std::vector<float> TIMESTEPS{ 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024 };
		std::unique_ptr<int> m_samplesInt = std::make_unique<int>(10);
		std::unique_ptr<int> m_samplesGameObject3D = std::make_unique<int>(10);
	};
}