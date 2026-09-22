#pragma once

class Enemy;
enum EnemyAnimationSet;

namespace RebelSoldierStates {
    class EnemyState
    {
    public:
        virtual ~EnemyState() = default;
        virtual EnemyAnimationSet update(Enemy& e, float dt, EnemyAnimationSet current) = 0;
        virtual void enter(Enemy& e) {}
    protected:
        float duration = 0.f;
        float elapsedTime = 0.f;
        static const int ATTACKRANGE = 50;
    };


    class IdleState final : public EnemyState
    {
    public:
        void enter(Enemy& e) override;
        EnemyAnimationSet update(Enemy& e, float dt, EnemyAnimationSet current)  override;
    private:
    };

    class WalkState final : public EnemyState
    {
    public:
        void enter(Enemy& e) override;
        EnemyAnimationSet update(Enemy& e, float dt, EnemyAnimationSet current)  override;
    };

    class AfterRunState final : public EnemyState
    {
    public:
        void enter(Enemy& e) override;
        EnemyAnimationSet update(Enemy& e, float dt, EnemyAnimationSet current)  override;
    };

    EnemyState* getEnemyState(EnemyAnimationSet index);

}