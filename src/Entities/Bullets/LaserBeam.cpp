#include "precomp.h"
#include "LaserBeam.h"
#include <ResourceIDFrames.h>
#include <RigidBody.h>
#include <BulletType.h>

LaserBeam::LaserBeam(vec2 pos, BulletType bulletType) :
    Bullet(pos,false,vec2(0,0),bulletType,0),
    elapsedTime(0.f)
{ 
    setCollider(vec2(300, 35), vec2(0, 0));
	getAnimationSets() = new AnimationSet[BLaserBeamAnimationSet::BLBe_COUNTS];
	loadGFX();
	setCurrentASIndex(BLaserBeamAnimationSet::BLBe_SHOOT);
	getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()]);
}

LaserBeam::~LaserBeam() {
	delete[] getAnimationSets();
}

void LaserBeam::loadGFX() {
	
    getAnimationSets()[BLaserBeamAnimationSet::BLBe_SHOOT] = AnimationSet(
    1,
    AnimationLayer(ResourceID::ID_LASER_BEAM,
        ResourceIDFrames::IDF_LASER_BEAM,
        100,
        vec2(0, 0),
        vec2(0, 0))
    );


}

void LaserBeam::update(float dt) {
	getAnimator().playAnimation(dt);
    
    elapsedTime += dt;   
    
    if(elapsedTime > 10.f) //small amount
    {
        setDisabled(true);
    }

	if (elapsedTime > MAXTIME){
        setFree(true);
	}

}

void LaserBeam::explodeMap(){
    // explode();
}

void LaserBeam::explode() {

}
