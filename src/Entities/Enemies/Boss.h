#pragma once
#include <Enemy.h>


class Bullet;
class Renderer;

class Boss : public Enemy{
public:
    Boss(vec2 pos);
    ~Boss() override;

    void loadGFX() override;

	void update(float dt) override;
    // void freeBullet(int i);

    // void addRenderDatas(Renderer& renderer);

    // int getMaxBullets() const;
    

    // Bullet* getBullet(int i) const;

    // void takeHit();
private:
    // bool shoot();

};