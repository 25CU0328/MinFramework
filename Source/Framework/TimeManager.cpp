

#include "TimeManager.h"

//QueryPerformanceCounterを使うためにインクルード
#include <windows.h>

// コンストラクタ
TimeManager::TimeManager()
	: m_updateFrequency(0.0)
	, m_deltaTime(0.0)
	, m_currentTime()
	, m_previousTime()
{


}

// 初期化処理
void TimeManager::Init()
{
	std::int64_t counterPerSecond;
	QueryPerformanceFrequency((LARGE_INTEGER*)&counterPerSecond);
	m_updateFrequency = 1.0 / (double)counterPerSecond;
}

// 毎フレームの更新処理
void TimeManager::Update()
{
	std::int64_t currentTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
	m_currentTime = currentTime;

	m_deltaTime = (DOUBLE)(m_currentTime - m_previousTime) * m_updateFrequency;

	m_previousTime = m_currentTime;

}

// DeltaTimeを取得する
double TimeManager::GetDeltaTime()
{
	return m_deltaTime;
}

// 秒間フレーム数を取得する
int TimeManager::GetFPS()
{
	return (int)(1.0 / m_deltaTime);
}