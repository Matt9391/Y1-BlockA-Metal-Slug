#include "precomp.h"
#include "CannonBall.h"
#include <ResourceIDFrames.h>
#include <RigidBody.h>
#include <BulletType.h>
#include <myMath.h>

CannonBall::CannonBall(vec2 pos, bool needsRigidBody, vec2 dir, BulletType bulletType, float duration_, float width_) :
    Bullet(pos,needsRigidBody,dir,bulletType,0),
    elapsedTime(0.f),
    duration(duration_),
    startPos(pos),
    arcWidth(width_),
    peakHeight(70.f),
    frameAngle(22.f)
{ 
	setDir(dir);
    setCollider(vec2(10, 10), vec2(0, 15));
	getAnimationSets() = new AnimationSet[BCannonBallAnimationSet::BCB_COUNTS];
	loadGFX();
	setCurrentASIndex(BCannonBallAnimationSet::BCB_SHOOT);
	getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()]);
	getRigidBody()->setSpeed(0);
}

CannonBall::~CannonBall() {
	delete[] getAnimationSets();
}

void CannonBall::loadGFX() {
	
    getAnimationSets()[BCannonBallAnimationSet::BCB_SHOOT] = AnimationSet(
    1,
    AnimationLayer(ResourceID::ID_CANNON_BALL,
        ResourceIDFrames::IDF_CANNON_BALL,
        100,
        vec2(-15, -5),
        vec2(-15, -5))
    );
    
    getAnimationSets()[BCannonBallAnimationSet::BCB_BOOM] = AnimationSet(
    1,
    AnimationLayer(ResourceID::ID_MISSLE_BOOM,
        ResourceIDFrames::IDF_MISSLE_BOOM,
        30,
        vec2(0, -10),
        vec2(0, -10))
    );

}

void CannonBall::update(float dt) {
	setColliderSprite();
	

	if (getAnimator().isAnimationEnded() && getCurrentASIndex() == BCB_BOOM) {
		setFree(true);
	}

	if (getDisabled()) return;

	elapsedTime += dt;

    float x = fminf(elapsedTime / duration, 1.f);
    float y = 1.f - powf(2.f * x - 1.f, 2.f);

    float worldX = startPos.x + arcWidth * x * getDir().x;
    float worldY = startPos.y - peakHeight * y + 100.f * x;
   
    float dx = worldX - getPos().x;
    float dy = worldY - getPos().y;

    setPos(vec2(worldX, worldY));

    if(getCurrentASIndex() == BCB_BOOM){ //if boom
        getAnimator().playAnimation(dt);
        return;
    }



    // --- frame selection if not boom ---


    // The strip is drawn for a LEFTWARD arc, so measure the angle as if moving left
    int frame = -1;
    if (dx != 0.f || dy != 0.f) { //if it has moved

        float angle = atan2f(dy, -abs(dx)) * 180.f / PI; //I just do the arc tan of a vector which return the angle and converto to degrees
                                                         //-abs(dx) because the sprite face left so we work like it's always going left 
        if (angle < 0.f) angle += 360.f;
        frame = static_cast<int>(myMath::constrain(
                                roundf((270.f - angle) / frameAngle), 
                                0.f, 
                                static_cast<float>(ResourceIDFrames::IDF_CANNON_BALL)));
    }

    if(frame != -1){
        getAnimator().setFrame(frame);
    }
}

void CannonBall::explodeMap(){
    explode();
}

void CannonBall::explode() {

   setFree(true);

}
