#include "GraphPlot.h"
#include <imgui.h>
#include <chrono>
#include <algorithm>
#include <string>

using namespace std::chrono;

struct transform {
	float matrix[16] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
};

class GameObject3D {
public:
	transform local;
	int id{};
};

class GameObject3DAlt {
public:
	transform* local;
	int id;
};

static void PlotTimingsLines(const char* label, const std::vector<float>& timings)
{
	if (timings.empty())
		return;

	auto [minIt, maxIt] = std::minmax_element(timings.begin(), timings.end());
	const float minV = *minIt;
	const float maxV = *maxIt;

	std::string overlay = "min=" + std::to_string(minV) + "  max=" + std::to_string(maxV);

	ImGui::PlotLines(
		label,
		timings.data(),
		static_cast<int>(timings.size()),
		0,
		overlay.c_str(),
		minV,
		maxV,
		ImVec2(200, 100)
	);
}

void dae::GraphPlot::PlotIntegers() const
{
	ImGui::Begin("Exercise 1");

	static std::vector<float> timings;

	ImGui::InputInt("Samples", m_samplesInt.get());

	if (ImGui::Button("Thrash the cache"))
		timings = GetTimings<int>(*m_samplesInt.get());

	if (!timings.empty())
		PlotTimingsLines("Integers", timings);

	ImGui::End();
}

void dae::GraphPlot::PlotGameObject3D() const
{
	ImGui::Begin("Exercise 2");

	static std::vector<float> timingsGameObject3D;
	static std::vector<float> timingsGameObject3DAlt;

	ImGui::InputInt("Samples", m_samplesGameObject3D.get());

	if (ImGui::Button("Thrash the cache with GameObject3D"))
		timingsGameObject3D = GetTimings<GameObject3D>(*m_samplesGameObject3D.get());

	if (!timingsGameObject3D.empty())
		PlotTimingsLines("GameObject3D", timingsGameObject3D);

	if (ImGui::Button("Thrash the cache with GameObject3DAlt"))
		timingsGameObject3DAlt = GetTimings<GameObject3DAlt>(*m_samplesGameObject3D.get());

	if (!timingsGameObject3DAlt.empty())
		PlotTimingsLines("GameObject3DAlt", timingsGameObject3DAlt);

	ImGui::End();
}

template <typename T>
std::vector<float> dae::GraphPlot::GetTimings(int samples) const
{
	T* arr = new T[ARR_SIZE]{};
	std::vector<float> elapsedTimes;
	std::vector<std::vector<float>> allTimings(TOTAL_STEPS, std::vector<float>(samples));

	for (int sample = 0; sample < samples; ++sample) {
		for (int stepsize = 1, index = 0; stepsize <= MAX_STEPSIZE; stepsize *= 2, ++index) {
			auto start = high_resolution_clock::now();

			if constexpr (std::is_same_v<T, int>) {
				for (int i = 0; i < ARR_SIZE; i += stepsize) arr[i] *= 2;
			}
			else if constexpr (std::is_same_v<T, GameObject3D>) {
				for (int i = 0; i < ARR_SIZE; i += stepsize) arr[i].id *= 2;
			}
			else if constexpr (std::is_same_v<T, GameObject3DAlt>) {
				for (int i = 0; i < ARR_SIZE; i += stepsize) arr[i].id *= 2;
			}

			auto end = high_resolution_clock::now();
			float elapsedTime = static_cast<float>(duration_cast<microseconds>(end - start).count());
			allTimings[index][sample] = elapsedTime;
		}
	}

	for (const auto& timings : allTimings) {
		std::vector<float> sortedTimings = timings;
		std::sort(sortedTimings.begin(), sortedTimings.end());
		elapsedTimes.push_back(sortedTimings[sortedTimings.size() / 2]);
	}

	delete[] arr;
	return elapsedTimes;
}