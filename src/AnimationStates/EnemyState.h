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
        static const int MELEERANGE = 50;
        static const int GRANADERANGE = 150;
        static const int VIEWRANGE = 200;
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
        static const float JUMPTIMER;
        static const float FLIPTIMER;

        float jumpCountdown;
        float flipCountdown;
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
   
    class MeleeAttackState final : public EnemyState
    {
    public:
        void enter(Enemy& e) override;
        EnemyAnimationSet update(Enemy& e, float dt, EnemyAnimationSet current)  override;
    private:
        static const int MSTRIGGER = 500;
    };
    
    class GrandadeAttackState final : public EnemyState
    {
    public:
        void enter(Enemy& e) override;
        EnemyAnimationSet update(Enemy& e, float dt, EnemyAnimationSet current)  override;
    private:
        static const int MSTRIGGER = 500;
        bool thrown;
    };

    EnemyState* getEnemyState(EnemyAnimationSet index);

}