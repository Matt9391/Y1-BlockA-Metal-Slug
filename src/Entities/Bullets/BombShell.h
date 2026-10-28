#pragma once
#include <Bullet.h>

enum BBombShellAnimationSet {
    BBS_FLY = 0,   
    BBS_BOOM,    
    BBS_COUNT
};

// BombShell - tank cannon shell: follows a fixed arc (same idea as the CannonBall) and explodes on contact.
class BombShell : public Bullet {
public:
    BombShell(vec2 pos, bool needsRigidBody, vec2 dir, BulletType bulletType, float duration_, float width_);
    ~BombShell() override;

    void loadGFX() override;
    void update(float dt) override;

    void explode() override;
    void explodeMap() override;

private:
    float elapsedTime;
    float duration;
    vec2  startPos;
    float arcWidth;
    float peakHeight;

    float frameAngle;
    // (SHELL_FRAMES and FRAME_ANGLE are not used: the .cpp uses 'frameAngle' and IDF_BOMB_SHELL.)
    static const int   SHELL_FRAMES = 32;     // frames in the shell sheet
    static constexpr float FRAME_ANGLE = 11.25f; // 360 / 32
};