#include "precomp.h"
#include "BombShell.h"
#include <ResourceIDFrames.h>
#include <RigidBody.h>
#include <BulletType.h>

BombShell::BombShell(vec2 pos, bool needsRigidBody, vec2 dir, BulletType bulletType, float duration_, float width_) :
    Bullet(pos, needsRigidBody, dir, bulletType, 0),
    elapsedTime(0.f),
    duration(duration_),
    startPos(pos),
    arcWidth(width_),
    peakHeight(70.f),
    frameAngle(11.25f)   // 360 / 32 frames
{
    setDir(dir);
    // (The sprite is drawn at offset -8,-8, so this 8x8 collider at (0,0) covers its lower-right quarter.)
    setCollider(vec2(8, 8), vec2(0, 0));   // 16x16 shell drawn centred on pos
    getAnimationSets() = new AnimationSet[BBS_COUNT];
    loadGFX();
    setCurrentASIndex(BBS_FLY);
    getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()]);
    getRigidBody()->setSpeed(0);
}

BombShell::~BombShell() {
    delete[] getAnimationSets();
}

void BombShell::loadGFX() {

    getAnimationSets()[BBS_FLY] = AnimationSet(
        1,
        AnimationLayer(ResourceID::ID_BOMB_SHELL,
            ResourceIDFrames::IDF_BOMB_SHELL,        // 32
            100,
            vec2(-8, -8),
            vec2(-8, -8))
    );

    // Note: IDF_BOMB_SHELL_BOOM is currently 1 (the "// 30" below is outdated).
    getAnimationSets()[BBS_BOOM] = AnimationSet(
        1,
        AnimationLayer(ResourceID::ID_BOMB_SHELL_BOOM,
            ResourceIDFrames::IDF_BOMB_SHELL_BOOM,   // 30
            30,
            vec2(-8, -8),
            vec2(-8, -8))
    );
}

void BombShell::update(float dt) {
	setColliderSprite();

    if (getAnimator().isAnimationEnded() && getCurrentASIndex() == BBS_BOOM) {
        setFree(true);
    }

    if (getCurrentASIndex() == BBS_BOOM) { // if boom: stay where it hit and play the explosion
        getAnimator().playAnimation(dt);
        return;
    }

    if (getDisabled()) return;

    // Same arc as the CannonBall: parabola + "+ 100 * x" drop; x is clamped to 1 at the end of the arc.
    elapsedTime += dt;

    float x = fminf(elapsedTime / duration, 1.f);
    float y = 1.f - powf(2.f * x - 1.f, 2.f);

    float worldX = startPos.x + arcWidth * x * getDir().x;
    float worldY = startPos.y - peakHeight * y + 100.f * x;

    float dx = worldX - getPos().x;
    float dy = worldY - getPos().y;

    setPos(vec2(worldX, worldY));


    if (dx != 0.f || dy != 0.f) { // if it has moved

        // Rotate the sprite: 32 frames for 360 degrees, frame 0 = pointing right, going clockwise on screen.
        float angle = atan2f(dy, dx) * 180.f / PI;
        if (angle < 0.f) angle += 360.f;

        int frame = static_cast<int>(roundf(angle / frameAngle)) % static_cast<int>(ResourceIDFrames::IDF_BOMB_SHELL); // 360 deg wraps to frame 0

        getAnimator().setFrame(frame);
    } 
}

void BombShell::explodeMap() {
    explode();
}

void BombShell::explode() {
    // The shell is not disabled here, so the explosion keeps hitting enemies while it plays.
    setCurrentASIndex(BBS_BOOM);
    getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()]);
}