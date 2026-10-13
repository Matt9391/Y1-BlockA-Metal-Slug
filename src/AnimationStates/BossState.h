#pragma once

class Enemy;
class Boss;
enum BossAnimationSet : int;

namespace BossStates {
    class BossState
    {
    public:
        virtual ~BossState() = default;
        virtual BossAnimationSet update(Boss& b, float dt, BossAnimationSet current) = 0;
        virtual void enter(Boss&) {}
    protected:
        float duration = 0.f;
        float elapsedTime = 0.f;
    };

    class AttackOneHighState final : public BossState
    {
    public:
        void enter(Boss& b) override;
        BossAnimationSet update(Boss& b, float dt, BossAnimationSet current) override;
    private:
        int shootCount;
        static const int FIRSTSHOOT = 800; 
        static const int SECONDSHOOT = 1200; 
        static const int THIRDSHOOT = 1600; 
    };

    class AttackOneLowState final : public BossState
    {
    public:
        void enter(Boss& b) override;
        BossAnimationSet update(Boss& b, float dt, BossAnimationSet current) override;
    private:
        int shootCount;
        static const int FIRSTSHOOT = 800; 
        static const int SECONDSHOOT = 1200; 
        static const int THIRDSHOOT = 1600;
    };

    class AttackTwoHighState final : public BossState
    {
    public:
        void enter(Boss& b) override;
        BossAnimationSet update(Boss& b, float dt, BossAnimationSet current) override;
    };

    class AttackTwoLowState final : public BossState
{
    public:
        void enter(Boss& b) override;
        BossAnimationSet update(Boss& b, float dt, BossAnimationSet current) override;
    };

    class MoveUpState final : public BossState
    {
    public:
        void enter(Boss& b) override;
        BossAnimationSet update(Boss& b, float dt, BossAnimationSet current) override;
    };

    class MoveDownState final : public BossState
    {
    public:
        void enter(Boss& b) override;
        BossAnimationSet update(Boss& b, float dt, BossAnimationSet current) override;
    };

    class DeathState final : public BossState
    {
    public:
        void enter(Boss& b) override;
        BossAnimationSet update(Boss& b, float dt, BossAnimationSet current) override;
    };
    
    class DeathStillState final : public BossState
    {
    public:
        void enter(Boss& b) override;
        BossAnimationSet update(Boss& b, float dt, BossAnimationSet current) override;
    };

    BossState* getBossState(BossAnimationSet index);

}