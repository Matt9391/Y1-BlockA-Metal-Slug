#include "precomp.h"
#include "Tank.h"
#include <TankAnimationSet.h>
#include <RigidBody.h>
#include <ResourceIDFrames.h>
#include <Player.h>
#include <Renderer.h>
#include <Bullets/BombShell.h>
#include <Bullets/SlugBullet.h>
#include <myMath.h>




Tank::Tank(vec2 pos, const InputManager& inputManager_) :
    Entity(pos, true, EntityType::ET_TANK),
    inputManager(inputManager_),
    player(nullptr),
    gotHit(false),
    dead(false),
    hp(5),
    playerOffset(vec2(30,15)),
    shootOffset{50,10},
    shooterOffset{10,5},
    shootBulletOffset{25,25},
    bulletsCount(0),
	bulletSpeed(0.5f),
    shootDir(0,0),
    angle(0),
    angleFrame((360.f / static_cast<float>(ResourceIDFrames::IDF_TANK_SHOOTER_IDLE))),
    angleIncr(0.5f),
	bullets{nullptr},
    shooterRs{RenderData(AnimationSet(
        1,
        AnimationLayer(
            ResourceID::ID_TANK_SHOOTER_IDLE,
            ResourceIDFrames::IDF_TANK_SHOOTER_IDLE,
            150,
            vec2(0, 0),
            vec2(0, 0))
    ), pos + shooterOffset, 2)},
    aimUp(true),
    shootBulletTimer(0.f),
    shootBombTimer(0.f),
    shootMuzzleTimer(0.f)
{
    setCollider(vec2(60, 50), vec2(15, 10));
	//setCollider(vec2(20, 7), vec2(3, 30));
	getAnimationSets() = new AnimationSet[TankAnimationSet::TAS_COUNTS];
	loadGFX();
	setCurrentASIndex(TankAnimationSet::TAS_IDLE);
	state = TankStates::getTankState(static_cast<TankAnimationSet>(getCurrentASIndex()));
	getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()]);

	getRigidBody()->setSpeed(0.05f);

}

Tank::~Tank(){
	delete[] getAnimationSets();
    for (int i = 0; i < MAXBULLETS; i++) {
		delete bullets[i];
		bullets[i] = nullptr;
	}
}

void Tank::loadGFX() {
    // TAS_IDLE -> idle.png
    getAnimationSets()[TankAnimationSet::TAS_IDLE] = AnimationSet(
        1,
        AnimationLayer(
            ResourceID::ID_TANK_IDLE,
            ResourceIDFrames::IDF_TANK_IDLE,
            150,
            vec2(0, 0),
            vec2(0, 0))
    );
 
    // TAS_WALK -> walk.png
    getAnimationSets()[TankAnimationSet::TAS_WALK] = AnimationSet(
        1,
        AnimationLayer(
            ResourceID::ID_TANK_WALK,
            ResourceIDFrames::IDF_TANK_WALK,
            100,
            vec2(0, 0),
            vec2(0, 0))
    );
 
    // TAS_SHOOT -> shoot.png
    getAnimationSets()[TankAnimationSet::TAS_SHOOT] = AnimationSet(
        1,
        AnimationLayer(
            ResourceID::ID_TANK_SHOOT,
            ResourceIDFrames::IDF_TANK_SHOOT,
            50,
            vec2(0, 0),
            vec2(0, 0))
    );
    
    getAnimationSets()[TankAnimationSet::TAS_HIT] = AnimationSet(
        1,
        AnimationLayer(
            ResourceID::ID_TANK_HIT,
            ResourceIDFrames::IDF_TANK_HIT,
            50,
            vec2(0, 0),
            vec2(0, 0))
    );
 
    // TAS_EXPLOSION -> hit.png
    getAnimationSets()[TankAnimationSet::TAS_EXPLOSION] = AnimationSet(
        1,
        AnimationLayer(
            ResourceID::ID_TANK_EXPLOSION,
            ResourceIDFrames::IDF_TANK_EXPLOSION,
            100,
            vec2(0, 0),
            vec2(0, 0))
    );
 
    // TAS_EXPLOSION_STILL -> hit_still.png (single frame, still to be created)
    getAnimationSets()[TankAnimationSet::TAS_EXPLOSION_STILL] = AnimationSet(
        1,
        AnimationLayer(
            ResourceID::ID_TANK_EXPLOSION_STILL,
            ResourceIDFrames::IDF_TANK_EXPLOSION_STILL,
            100,
            vec2(0, 0),
            vec2(0, 0))
    );
}

void Tank::update(float dt){
    getAnimator().playAnimation(dt);
	setColliderSprite();
    
    RigidBody* rb = getRigidBody();

    if (!rb->isGrounded()) {
		addVelocity(vec2(0, rb->getGravity() * dt));
	}
	else {
		setVelocityY(0.f);
	}

    shooterRs.pos = getPos() + shooterOffset;


    if (player != nullptr) {
        player->setPos(getPos() + playerOffset);
    }
    else if (!dead) {
        gotHit = false;
        rb->setVelocityX(0);
        setDir(vec2(0, 0));
        this->addToPos(rb->getVelocity() * dt);
        return;
    }

    shootBombTimer += dt;
    shootBulletTimer += dt;
    shootMuzzleTimer += dt;

    const TankStates::TankInput tInput = getTankInput();

    if(getCurrentASIndex() == TankAnimationSet::TAS_EXPLOSION && tInput.onAnimationEnd){
        setFree(true);
    }

    TankAnimationSet nextState = state->handleInput(tInput, static_cast<TankAnimationSet>(getCurrentASIndex()));
    setCurrentASIndex(nextState);
    state = TankStates::getTankState(static_cast<TankAnimationSet>(getCurrentASIndex()));


	if (getDir().x != 0)
		setLastDir(getDir());
	setDir(vec2(0, 0));

	//Movement
	if (tInput.inputRight) {
		setDir(vec2(1, 0));
	}
	else if (tInput.inputLeft) {
		setDir(vec2(-1, 0));
	}

	rb->setVelocityX(rb->getSpeed() * getDir().x);

	this->addToPos(rb->getVelocity() * dt);

	const bool reset = tInput.isShooting && getCurrentASIndex() != TankAnimationSet::TAS_HIT && !tInput.isDead;

	getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()], false, reset);

    //reset bools
    gotHit = false;

    if (tInput.isShooting && !tInput.isDead && shootBombTimer > SHOOTBOMBCOUNTDOWN) {
        shoot(BulletType::BT_BOMB_SHELL);
    }else if(tInput.isShootingBullet && !tInput.isDead && shootBulletTimer > SHOOTBULLETCOUNTDOWN){
        shoot(BulletType::BT_SLUG_BULLET);
    }

    for (int i = 0; i < MAXBULLETS; i++) {
		if (bullets[i] == nullptr) continue;
		bullets[i]->update(dt);
	}

     if(tInput.isShootingBullet){ // DONE: fix tank shooter sprite
         shooterRs.animationSet.layers[0] = AnimationLayer(
             ResourceID::ID_TANK_SHOOTER_SHOOT,
             ResourceIDFrames::IDF_TANK_SHOOTER_SHOOT,
             150,
             vec2(-31, -31),
             vec2(-31, -31));
     }else if(shootMuzzleTimer > SHOOTMUZZLETIMER){
        shooterRs.animationSet.layers[0] = AnimationLayer(
            ResourceID::ID_TANK_SHOOTER_IDLE,
            ResourceIDFrames::IDF_TANK_SHOOTER_IDLE,
            150,
            vec2(0, 0),
            vec2(0, 0));
     }


    if (player != nullptr) {
        if (tInput.inputUp && !aimUp) { aimUp = true;  angle = 360.f - angle; }
        if (tInput.inputDown &&  aimUp) { aimUp = false; angle = 360.f - angle; }
    }

    float rot = 0.f;
    if (tInput.inputRight)     rot = -1.f;
    else if (tInput.inputLeft) rot =  1.f;
    if (!aimUp) rot = -rot;      // lower half runs 180 -> 360, so D must increase the angle

    angle += rot * angleIncr * dt;

    const float minAngle = aimUp ? 0.f   : 180.f;
    const float maxAngle = aimUp ? 180.f : 360.f;
    angle = myMath::constrain(angle, minAngle, maxAngle);
    float x = cos(angle * (PI / 180.f));
    float y = -sin(angle * (PI / 180.f));

    shootDir = vec2(x,y);

    int frame = static_cast<int>(roundf(angle / angleFrame)) % static_cast<int>(ResourceIDFrames::IDF_TANK_SHOOTER_IDLE); // 360 deg wraps to frame 0

    shooterRs.animationSet.layers[0].currentFrame = frame;

    
}

const TankStates::TankInput Tank::getTankInput() const {
	bool inputRight = inputManager.isKeyPressed('D');
	bool inputLeft = inputManager.isKeyPressed('A');
	bool inputUp = inputManager.isKeyPressed('W');
	bool inputDown = inputManager.isKeyPressed('S');
	bool isMoving = inputRight || inputLeft;
	bool isGrounded = getRigidBody()->isGrounded();
	bool isShootingBullet = inputManager.isKeyJustPressed('F');
	bool isShooting = inputManager.isKeyJustPressed('G');
	bool isHit = gotHit;
	bool isDead = dead;

    if(player == nullptr){
        inputRight = false;
        inputLeft = false;
        inputUp = false;
        inputDown = false;
        isMoving = false;
        isGrounded = getRigidBody()->isGrounded();
        isShootingBullet = false;
        isShooting = false;
        isHit = false;
        isDead = dead;
    }

	const TankStates::TankInput tankInput = {
		inputRight,
		inputLeft,
		inputUp,
		inputDown,
		isMoving,
		isGrounded,
		isShootingBullet,
		isShooting,
		getAnimator().isAnimationEnded(),
		isHit,
        isDead
	};

	return tankInput;
}


void Tank::enterPlayer(Player* player_){
    if(dead) return;
    this->player = player_;
    this->player->setInTank(true);
}


bool Tank::hasPlayer() const{
    return this->player != nullptr;
}

void Tank::takeHit(){
    gotHit = true;
    this->hp--;
    if(this->hp < 0){
        ejectPlayer();
        dead = true;
    }

}

void Tank::ejectPlayer(){
    if(this->player == nullptr) return;
    player->setPos(getPos() + playerOffset - vec2(0, 80));
    player->setInTank(false);
    this->player = nullptr;
}

void Tank::freeBullet(int i) {
	if (bullets[i]) {
		delete bullets[i];
		bullets[i] = nullptr;
		bulletsCount--;
	}
}

int Tank::getMaxBullets() const{
	return MAXBULLETS;
}

Bullet* Tank::getBullet(int i) const {
	return bullets[i];
}

bool Tank::shoot(BulletType bulletType) {

	int bIndex = -1;
	for (int i = 0; i < MAXBULLETS; i++) {
		if (bullets[i] == nullptr) {
			bIndex = i;
			break;
		}
	}

	if (bIndex == -1) return false;

    switch (bulletType)
    {
    case BT_BOMB_SHELL:
        bullets[bIndex] = new BombShell(getPos() + getCollider().offset + shootOffset,
                                        true, 
                                        vec2(1,0), 
                                        BulletType::BT_BOMB_SHELL,
                                        Rand(150.f) + 1500.f,
                                        400.f);
        shootBombTimer = 0.f;
        break;
    case BT_SLUG_BULLET:
        bullets[bIndex] = new SlugBullet(getPos() + shootBulletOffset, true, shootDir, BT_SLUG_BULLET, bulletSpeed);
        shootMuzzleTimer = 0.f;
        shootBulletTimer = 0.f;
        break;
    
    default:
        break;
    }
	bulletsCount++;

    
	return true;
}

void Tank::addRenderDatas(Renderer& renderer) {
    renderer.addRenderData(shooterRs);
	for (int i = 0; i < MAXBULLETS; i++) {
		if (bullets[i] == nullptr) continue;
		renderer.addRenderData(bullets[i]->getRenderData());
		renderer.addCollider(bullets[i]->getCollider());

	}
}
