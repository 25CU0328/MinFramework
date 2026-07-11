#pragma once

#include <functional>

#include "Framework/Math/Vector.h"
#include "Framework/Collision/CollisionEvent.h"
#include "ColliderType.h"

// 全てのコライダーのベースクラス
class Collider
{
public:
	virtual ~Collider() = default;
    // 衝突が発生する時に呼ばれるメソッド
    virtual void OnCollision(CollisionEvent _collisionEvent);

    // コライダーの種類を取得する
    ColliderType GetColliderType() const;

    // コールバック関数を設定する
    void SetCallback(std::function<void(CollisionEvent)> _callback);

    // 位置を設定する
    void SetPosition(const float _x, const float _y);
    void SetPosition(const Vector2f _newPosition);
    void SetPosition(const float _x, const float _y, const float _z);
    void SetPosition(const Vector3f _newPosition);
    
    // 位置を取得する
    Vector3f GetPosition() const;

    // 衝突レイヤーを追加する
    void AddHitLayer(int _layer);
    // 衝突レイヤーを削除する
    void RemoveHitLayer(int _layer);
    // 衝突レイヤーをリセット
    void ClearHitLayer();
    // 衝突対象レイヤーを取得する
    int GetHitLayer() const;

    // コライダー自身のレイヤーを設定する
    void SetLayer(int _layer);
    // コライダーのレイヤーを取得する
    int GetLayer() const;

protected:
    // コールバック関数を記録するための変数
	std::function<void(CollisionEvent)> m_collisionCallback;
    // コライダーの種類
    ColliderType m_type;
    // 位置
    Vector3f m_position;

    // 衝突のレイヤー(使用者から管理する)
private:
    // コライダーのレイヤー
    int m_layer;
    // 衝突できるレイヤー
    int m_hitLayer;
};