#pragma once
#include <Bullet.h>

enum BBombShellAnimationSet {
    BBS_FLY = 0,   
    BBS_BOOM,    
    BBS_COUNT
};

class BombShell : public Bullet {
public:
    BombShell(vec2 pos, bool needsRigidBody, vec2 dir, BulletType bulletType, float duration_, float width_);
    ~BombShell() override;

    void loadGFX() override;
    void update(float dt) override;

    void explode() override;
    void explodeMap() override;

private:
    vec2 arcPos(float x);                      // position on the arc for x = 0..1
    int  angleToFrame(float dx, float dy) const;

    float elapsedTime;
    float duration;
    vec2  startPos;
    float arcWidth;
    float peakHeight;
    float dropHeight;
    bool  exploding;

    float frameAngle;
    static const int   SHELL_FRAMES = 32;     // frames in the shell sheet
    static constexpr float FRAME_ANGLE = 11.25f; // 360 / 32
};