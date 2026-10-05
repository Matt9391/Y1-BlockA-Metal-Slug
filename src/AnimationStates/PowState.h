#pragma once

enum PowAnimationSet : int;
class Pow;

namespace PowStates {

    class PowState
    {
    public:
        virtual ~PowState() = default;
        virtual PowAnimationSet update(Pow& pow, float dt, PowAnimationSet current) = 0;
        virtual void enter(Pow&) {}
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
        float flipElapsedTime;
        static const float TRIGGERMINTIME;
        static const float FLIPMS;
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