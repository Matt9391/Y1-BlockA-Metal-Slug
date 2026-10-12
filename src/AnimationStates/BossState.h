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

    class AttackOneState final : public BossState
    {
    public:
        void enter(Boss& b) override;
        BossAnimationSet update(Boss& b, float dt, BossAnimationSet current) override;
    };

    class AttackTwoState final : public BossState
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

    BossState* getBossState(BossAnimationSet index);

}