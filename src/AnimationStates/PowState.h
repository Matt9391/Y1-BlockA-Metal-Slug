#pragma once

enum PowAnimationSet;
class Pow;

namespace PowStates {

    class PowState
    {
    public:
        virtual ~PowState() = default;
        virtual PowAnimationSet update(Pow& pow, float dt, PowAnimationSet current) = 0;
        virtual void enter(Pow& pow) {}
    };



    class IdleState final : public PowState
    {
    public:
        void enter(Pow& pow) override;
        PowAnimationSet update(Pow& pow, float dt, PowAnimationSet current) override;
    private:
    };
   
    class ReleasingState final : public PowState
    {
    public:
        void enter(Pow& pow) override;
        PowAnimationSet update(Pow& pow, float dt, PowAnimationSet current) override;
    private:
    };
   
    class WalkWaitState final : public PowState
    {
    public:
        void enter(Pow& pow) override;
        PowAnimationSet update(Pow& pow, float dt, PowAnimationSet current) override;
    private:
        float elapsedTime;
        static const float TRIGGERMINTIME;
        static const int FLIPMS;
    };
   
    class PantsState final : public PowState
    {
    public:
        void enter(Pow& pow) override;
        PowAnimationSet update(Pow& pow, float dt, PowAnimationSet current) override;
    private:
    };
   
    class ByeState final : public PowState
    {
    public:
        void enter(Pow& pow) override;
        PowAnimationSet update(Pow& pow, float dt, PowAnimationSet current) override;
    private:
    };
   
    class RunAwayState final : public PowState
    {
    public:
        void enter(Pow& pow) override;
        PowAnimationSet update(Pow& pow, float dt, PowAnimationSet current) override;
    private:
    };


    PowState* getPowState(PowAnimationSet index);

}