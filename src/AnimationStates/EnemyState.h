#pragma once

class Enemy;
class RebelSoldier;
enum EnemyAnimationSet : int;

// State machine of the rebel soldier. Each state's update() returns the next EnemyAnimationSet;
// RebelSoldier::update calls enter() on the new state when it changes.
namespace RebelSoldierStates {
    class EnemyState
    {
    public:
        virtual ~EnemyState() = default;
        virtual EnemyAnimationSet update(RebelSoldier& e, float dt, EnemyAnimationSet current) = 0;
        virtual void enter(RebelSoldier&) {}
    protected:
        float duration = 0.f;
        float elapsedTime = 0.f;
        static const int MELEERANGE = 20; // px
        static const int GRANADERANGE = 100; // px, max distance for a grenade throw
        static const int VIEWRANGE = 200; // px, the soldier "sees" the player when closer than this
        static const int MAXCHANCE = 100; // chances are percentages: Rand(100) > MAXCHANCE - CHANCE
    };


    class IdleState final : public EnemyState
    {
    public:
        void enter(RebelSoldier& e) override;
        EnemyAnimationSet update(RebelSoldier& e, float dt, EnemyAnimationSet current)  override;
    private:
        static const int FLIPCHANCE = 25; // % chance to turn around on a check
    };

    class WalkState final : public EnemyState
    {
    public:
        void enter(RebelSoldier& e) override;
        EnemyAnimationSet update(RebelSoldier& e, float dt, EnemyAnimationSet current)  override;
    private:
        static const int FLIPCHANCE = 5;
        static const int JUMPCHANCE = 15;
        static const int GRANADECHANCE = 35;
        static const int MELEECHANCE =  5;
        static const int SCAREDCHANCE =  50;
        static const float JUMPTIMER;
        static const float FLIPTIMER;
        static const float GRENADETIMER;

        float jumpCountdown;
        float flipCountdown;
        float grenadeCountdown;
    };

    class AfterRunState final : public EnemyState
    {
    public:
        void enter(RebelSoldier& e) override;
        EnemyAnimationSet update(RebelSoldier& e, float dt, EnemyAnimationSet current)  override;
    };
    
    class JumpForwardState final : public EnemyState
    {
    public:
        void enter(RebelSoldier& e) override;
        EnemyAnimationSet update(RebelSoldier& e, float dt, EnemyAnimationSet current)  override;
    };
    
    class ScaredState final : public EnemyState
    {
    public:
        void enter(RebelSoldier& e) override;
        EnemyAnimationSet update(RebelSoldier& e, float dt, EnemyAnimationSet current)  override;
    private:
    };
    class ScaredRunState final : public EnemyState
    {
    public:
        void enter(RebelSoldier& e) override;
        EnemyAnimationSet update(RebelSoldier& e, float dt, EnemyAnimationSet current)  override;
    private:
        static const int JUMPTIMER = 500;
        static const int JUMPCHANCE = 30;
        float jumpCountdown;
    };
    
    class FallingState final : public EnemyState
    {
    public:
        void enter(RebelSoldier& e) override;
        EnemyAnimationSet update(RebelSoldier& e, float dt, EnemyAnimationSet current)  override;
    };
    
    class CoverState final : public EnemyState
    {
    public:
        void enter(RebelSoldier& e) override;
        EnemyAnimationSet update(RebelSoldier& e, float dt, EnemyAnimationSet current)  override;
    };
   
    class MeleeAttackState final : public EnemyState
    {
    public:
        void enter(RebelSoldier& e) override;
        EnemyAnimationSet update(RebelSoldier& e, float dt, EnemyAnimationSet current)  override;
    private:
        static const int MSTRIGGER = 500; // ms into the attack when the knife hit lands
        bool attacked; // the hit already happened during this attack
    };
    
    class GrandadeAttackState final : public EnemyState
    {
    public:
        void enter(RebelSoldier& e) override;
        EnemyAnimationSet update(RebelSoldier& e, float dt, EnemyAnimationSet current)  override;
    private:
        static const int MSTRIGGER = 500; // ms into the attack when the grenade is thrown
        bool thrown;
    };
    
    class DeathState final : public EnemyState
    {
    public:
        void enter(RebelSoldier& e) override;
        EnemyAnimationSet update(RebelSoldier& e, float dt, EnemyAnimationSet current)  override;
    private:
    };
    
    class DeathStillState final : public EnemyState
    {
    public:
        void enter(RebelSoldier& e) override;
        EnemyAnimationSet update(RebelSoldier& e, float dt, EnemyAnimationSet current)  override;
    private:
    };

    EnemyState* getEnemyState(EnemyAnimationSet index);

}