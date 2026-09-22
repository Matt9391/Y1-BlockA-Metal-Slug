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
        static const int VIEWRANGE = 160;
        static const int MAXCHANCE = 100;
    };


    class IdleState final : public EnemyState
    {
    public:
        void enter(Enemy& e) override;
        EnemyAnimationSet update(Enemy& e, float dt, EnemyAnimationSet current)  override;
    private:
        static const int FLIPCHANCE = 25;
    };

    class WalkState final : public EnemyState
    {
    public:
        void enter(Enemy& e) override;
        EnemyAnimationSet update(Enemy& e, float dt, EnemyAnimationSet current)  override;
    private:
        static const int FLIPCHANCE = 5;
        static const int JUMPCHANCE = 15;
    };

    class AfterRunState final : public EnemyState
    {
    public:
        void enter(Enemy& e) override;
        EnemyAnimationSet update(Enemy& e, float dt, EnemyAnimationSet current)  override;
    };
    
    class JumpForwardState final : public EnemyState
    {
    public:
        void enter(Enemy& e) override;
        EnemyAnimationSet update(Enemy& e, float dt, EnemyAnimationSet current)  override;
    };
    
    class ScaredState final : public EnemyState
    {
    public:
        void enter(Enemy& e) override;
        EnemyAnimationSet update(Enemy& e, float dt, EnemyAnimationSet current)  override;
    };
    
    class FallingState final : public EnemyState
    {
    public:
        void enter(Enemy& e) override;
        EnemyAnimationSet update(Enemy& e, float dt, EnemyAnimationSet current)  override;
    };
    
    class CoverState final : public EnemyState
    {
    public:
        void enter(Enemy& e) override;
        EnemyAnimationSet update(Enemy& e, float dt, EnemyAnimationSet current)  override;
    };

    EnemyState* getEnemyState(EnemyAnimationSet index);

}