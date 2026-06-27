#pragma once


#include <cstdint>

class TimeManager
{
	// コピーを禁止する
	TimeManager(const TimeManager&) = delete;
	// オペレーターによるコピーを禁止する
	void operator = (const TimeManager&) = delete;
public:
	// コンストラクタ
	TimeManager();

	// 初期化処理
	void Init();

	// 毎フレームの更新処理
	void Update();

	// DeltaTimeを取得する
	double GetDeltaTime();

	// 秒間フレーム数を取得する
	int GetFPS();

private:
	// 更新処理の頻度
	double m_updateFrequency;
	// 前回フレームとの時間差
	double m_deltaTime;

	// 前回の時間
	std::int64_t m_previousTime;
	// 現在の時間
	std::int64_t m_currentTime;
};