#include "headers.h"
#include "Item.h"

void Item::initSprite(sf::Texture* texture)
{
    m_item = new sf::Sprite(*texture);
}

void Item::initVariables()
{
	m_isOnGround = false;
	m_isInHand = true;
	m_speed = 500.0f;
}

//Constructors / Descructors
Item::Item(sf::Texture* texture)
{
	this->initSprite(texture);
	this->initVariables();
	
}

Item::~Item()
{
}

void Item::updateItemPosition(const sf::Vector2i& mousePosition, const sf::Vector2f& position,const sf::Vector2f& creatureSize)
{

	if (m_isInHand == true)
	{
		sf::Vector2f newPosition{
		position.x + creatureSize.x / 3.0f,
		position.y + creatureSize.y / 4.0f
		};
		m_item->setPosition(newPosition);

		this->inHandRotation(mousePosition);
	}
	else if (m_isInHand == false && m_isOnGround == false)
	{
		this->dragItemDown();
	}
}

void Item::inHandRotation(const sf::Vector2i& mousePosition)
{
    m_item->setRotation(sf::degrees(Geometry::getAngleRelativelyToGround(m_item->getPosition(), mousePosition)));
}

void Item::setItemPosition(sf::Vector2f position)
{
	m_itemPosition = position;
	m_item->setPosition(position);
}

void Item::dragItemDown()
{
    m_item->move(sf::Vector2f(0.0f, m_speed * deltaTime::timePerFrame));
}

void Item::itemGroundCollision(Tile& collisionTile)
{
	sf::FloatRect tileBounds{ collisionTile.m_tile.getGlobalBounds() };
	sf::FloatRect itemNextBounds{ m_item->getGlobalBounds() };
    itemNextBounds.position.y += m_speed * deltaTime::timePerFrame;

    if (itemNextBounds.findIntersection(tileBounds) &&
		m_isOnGround == false &&
		collisionTile.m_tileType == Tile::Type::Grass)
	{

        m_item->setPosition(sf::Vector2f(m_item->getPosition().x, tileBounds.position.y - m_item->getGlobalBounds().size.y));
		m_isOnGround = true;
	}
}

const bool& Item::isItemOnGround() const
{
	return m_isOnGround;
}

const bool& Item::isItemEquiped() const
{
	return m_isInHand;
}

const sf::Vector2f Item::getPosition() const
{
	return m_item->getPosition();
}

const Item::Type& Item::itemType() const
{
	return m_itemType;
}

void Item::setPointerToMousePosition(sf::Vector2i& mousePositionMap)
{
	m_mousePositionMapPtr = &mousePositionMap;
}

void Item::setItemType(Type itemType)
{
	m_itemType = itemType;
}

void Item::setScale(float scaleX, float scaleY)
{
    m_item->setScale(sf::Vector2f(scaleX, scaleY));
}
