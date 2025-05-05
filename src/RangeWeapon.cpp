#include "headers.h"
#include "RangeWeapon.h"

void RangeWeapon::initVariables()
{
	m_ammunition = 1000;

	m_cooldown.setMAXtime(100.0f);

	m_mousePositionMapPtr = nullptr;
}

RangeWeapon::RangeWeapon(sf::Texture* texture)
	: Item{texture}
{
	this->initVariables();

}

RangeWeapon::~RangeWeapon()
{
}

void RangeWeapon::update(const float& timePerFrame)
{
	this->shootBullet();
	this->updateBullets();
}

void RangeWeapon::updateBullets()
{
	for (auto bullet : m_bullets)
	{
		bullet->updatePosition();
	}
	m_cooldown.update(deltaTime::timePerFrame);
}

void RangeWeapon::shootBullet()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_cooldown.getElapsedTime() > m_cooldown.getTimeMAX())
	{
		m_bullets.push_back(new Bullet{});

		this->giveBulletDirection();

		this->giveBulletPosition();

		m_cooldown.restart();
	}
}

void RangeWeapon::render(sf::RenderTarget* target)
{
	target->draw(*m_item);
	this->renderBullets(target);
}

void RangeWeapon::renderBullets(sf::RenderTarget* target)
{
	for (auto bullet : m_bullets)
		target->draw(bullet->m_bullet);
}

bool RangeWeapon::bulletTileMapCollision(Tile& collisionTile, int bulletIndex)
{
	if (collisionTile.m_tile.getGlobalBounds().intersects(m_bullets[bulletIndex]->m_bullet.getGlobalBounds()) &&
		collisionTile.isObsticle == true)
	{

		delete m_bullets[bulletIndex];
		m_bullets.erase(m_bullets.begin() + bulletIndex);
		return true;
	}
	return false;
}

void RangeWeapon::giveBulletDirection()
{
	sf::Vector2f directionVector{
			m_mousePositionMapPtr->x - m_item->getPosition().x,
			m_mousePositionMapPtr->y - m_item->getPosition().y
	};
	float vectorLength{ sqrt(directionVector.x * directionVector.x + directionVector.y * directionVector.y) };

	float normalizeVector{ 1 / vectorLength };

	directionVector.x *= normalizeVector;
	directionVector.y *= normalizeVector;

	m_bullets.back()->m_direction = directionVector;

	m_bullets.back()->m_velocity.x = directionVector.x * m_bullets.back()->m_speed;
	m_bullets.back()->m_velocity.y = directionVector.y * m_bullets.back()->m_speed;

}

void RangeWeapon::giveBulletPosition()
{
	sf::Vector2f bulletDir{ m_bullets.back()->m_direction };

	m_bullets.back()->m_bullet.setPosition(
		m_item->getPosition().x + bulletDir.x*40.0f,
		m_item->getPosition().y + bulletDir.y*40.0f
	);
}

const int& RangeWeapon::firedBullets() const
{
	return m_bullets.size();
}

const RangeWeapon::Bullet& RangeWeapon::getBullet(int index) const
{
	return *m_bullets[index];
}

std::vector<RangeWeapon::Bullet*>& RangeWeapon::getFiredBulletsVector()
{
	return m_bullets;
}

void RangeWeapon::deleteBullet(int bulletIndex)
{
	delete m_bullets[bulletIndex];
	m_bullets.erase(m_bullets.begin() + bulletIndex);
}








//Bullet class
RangeWeapon::Bullet::Bullet()
{
	m_gravity = 400;
	m_speed = 1700;
	
	m_bullet.setRadius(6.0f);
	m_bullet.setFillColor(sf::Color::Black);
	
}

RangeWeapon::Bullet::~Bullet()
{

}

void RangeWeapon::Bullet::dragDown()
{
	m_velocity.y += m_gravity * deltaTime::timePerFrame;
}

void RangeWeapon::Bullet::updatePosition()
{
	this->dragDown();

	m_bullet.move(
		m_velocity.x * deltaTime::timePerFrame,
		m_velocity.y * deltaTime::timePerFrame
	);
	//Debug::showVelocity(m_velocity.x, m_velocity.y);
}

void RangeWeapon::Bullet::renderBullet(sf::RenderTarget* target)
{
	target->draw(m_bullet);
}
