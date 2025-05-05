#include "headers.h"
#include "Geometry.h"

namespace Geometry
{
	//Cztery prze�adowane funkcje dla r�wnych typ�w (int i float)
	int getAngleRelativelyToGround(const sf::Vector2i& pointOne, const sf::Vector2i& pointTwo)
	{

		int Ydifference{ pointTwo.y - pointOne.y };
		int Xdifference{ pointTwo.x - pointOne.x };

		float angleInRadians{ static_cast<float>(atan2(Ydifference, Xdifference)) };

		float angleInDegrees{ (angleInRadians * 180) / Constants::pi };

		return angleInDegrees;
	}
	int getAngleRelativelyToGround(const sf::Vector2f& pointOne, const sf::Vector2f& pointTwo)
	{
		int Ydifference{ static_cast<int>(pointTwo.y) - static_cast<int>(pointOne.y) };
		int Xdifference{ static_cast<int>(pointTwo.x) - static_cast<int>(pointOne.x) };

		float angleInRadians{ static_cast<float>(atan2(Ydifference, Xdifference)) };

		float angleInDegrees{ (angleInRadians * 180) / Constants::pi };

		return angleInDegrees;
	}
	int getAngleRelativelyToGround(const sf::Vector2f& pointOne, const sf::Vector2i& pointTwo)
	{

		int Ydifference{ std::abs(static_cast<int>(pointTwo.y) - static_cast<int>(pointOne.y)) };
		int Xdifference{ std::abs(static_cast<int>(pointTwo.x) - static_cast<int>(pointOne.x)) };

		if (Xdifference == 0)
		{
			if (pointOne.y > pointTwo.y)
				return 270;
			else
				return 90;
		}

		if (Ydifference == 0)
		{
			if (pointOne.x < pointTwo.x)
				return 0;
			else
				return 180;
		}

		float tangens{ static_cast<float>(Ydifference) / Xdifference };

		float angleInRadians{ static_cast<float>(atan(tangens)) };

		float angleInDegrees{ (angleInRadians * 180) / Constants::pi };

		//Poszczeg�lne �wiartki uk�adu wsp�ednych, gdzie gracz jest pukntem (0,0)
		if (pointOne.x < pointTwo.x && pointOne.y > pointTwo.y)
		{//Je�li myszka jest w pierwszej �wiartce

			angleInDegrees = 360 - angleInDegrees;
		}
		else if (pointOne.x > pointTwo.x && pointOne.y > pointTwo.y)
		{//Je�li myszka jest w �wiartce drugiej
			angleInDegrees = 180 + angleInDegrees;
		}
		else if (pointOne.x > pointTwo.x && pointOne.y < pointTwo.y)
		{//Je�li myszka jest w trzeciej �wiartce

			angleInDegrees = 180 - angleInDegrees;
		}
		else if (pointOne.x < pointTwo.x && pointOne.y < pointTwo.y)
		{//Je�li myszka jest w czwartej �wiartce
			//angleInDegrees = 360 - angleInDegrees;
		}

		

		return angleInDegrees;
	}
	int getAngleRelativelyToGround(const sf::Vector2i& pointOne, const sf::Vector2f& pointTwo)
	{
		int Ydifference{ static_cast<int>(pointTwo.y) - static_cast<int>(pointOne.y) };
		int Xdifference{ static_cast<int>(pointTwo.x) - static_cast<int>(pointOne.x) };

		float angleInRadians{ static_cast<float>(atan2(Ydifference, Xdifference)) };

		float angleInDegrees{ (angleInRadians * 180) / Constants::pi };

		return angleInDegrees;
	}

	float calculateVectorLength(const sf::Vector2f& pointOne, const sf::Vector2f& pointTwo)
	{
		return sqrt((pointTwo.x - pointOne.x)*(pointTwo.x - pointOne.x) + (pointTwo.y - pointOne.y)*(pointTwo.y - pointOne.y));
	}

	bool isPointOutsideScreen(const sf::Vector2f& pointToCheck, const sf::Vector2f& viewCenter)
	{
		sf::Vector2f leftUpCorner{ viewCenter.x - Constants::WindowWidth / 2.0f, viewCenter.y - Constants::WindowHeigth / 2.0f };
		sf::Vector2f leftDownCorner{ leftUpCorner.x, leftUpCorner.y + Constants::WindowHeigth };
		sf::Vector2f rightUpCorner{ leftUpCorner.x + Constants::WindowWidth , leftUpCorner.y };
		sf::Vector2f rightDownCorner{ leftUpCorner.x + Constants::WindowWidth, leftUpCorner.y + Constants::WindowHeigth };

		if (pointToCheck.x < leftUpCorner.x || pointToCheck.x > rightUpCorner.x)
		{
			return true;
		}
		else if (pointToCheck.y < leftUpCorner.y || pointToCheck.y > leftDownCorner.y)
		{
			return true;
		}


		return false;
	}
	bool isVectorOutsideScreen(const sf::Vector2f& pointOne, const sf::Vector2f& pointTwo, const sf::Vector2f& viewCenter)
	{
		sf::Vector2f leftUpCorner{ viewCenter.x - Constants::WindowWidth / 2.0f, viewCenter.y - Constants::WindowHeigth / 2.0f };
		sf::Vector2f leftDownCorner{ leftUpCorner.x, leftUpCorner.y + Constants::WindowHeigth };
		sf::Vector2f rightUpCorner{ leftUpCorner.x + Constants::WindowWidth , leftUpCorner.y };
		sf::Vector2f rightDownCorner{ leftUpCorner.x + Constants::WindowWidth, leftUpCorner.y + Constants::WindowHeigth };

		if (!isPointOutsideScreen(pointOne, viewCenter) || !isPointOutsideScreen(pointTwo, viewCenter))
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	bool get_line_intersection(const sf::Vector2f& pointOne, const sf::Vector2f& pointTwo,
		const sf::Vector2f& pointThree, const sf::Vector2f& pointFour)
	{
		float s1_x, s1_y, s2_x, s2_y;
		s1_x = pointTwo.x - pointOne.x;     s1_y = pointTwo.y - pointOne.y;
		s2_x = pointFour.x - pointThree.x;     s2_y = pointFour.y - pointThree.y;

		float s, t;
		s = (-s1_y * (pointOne.x - pointThree.x) + s1_x * (pointOne.y - pointThree.y)) / (-s2_x * s1_y + s1_x * s2_y);
		t = (s2_x * (pointOne.y - pointThree.y) - s2_y * (pointOne.x - pointThree.x)) / (-s2_x * s1_y + s1_x * s2_y);

		if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
		{
			// Collision detected
			return true;
		}

		return false; // No collision
	}
}

namespace Algorithms
{
	Tile* getShortestPathFirstTile(std::vector<std::vector<Tile*>>& tileMap,
		const sf::Vector2f& startPosition, const sf::Vector2f& endPosition, const sf::Vector2i& tileMapSize)
	{
		setTilesDefaultValues(tileMap, tileMapSize);


		sf::Vector2i startGridPosition{ (int)(startPosition.x / Constants::gridSizeU), (int)(startPosition.y / Constants::gridSizeU) };
		if (isOutsideMap(startGridPosition, tileMapSize))
		{ return nullptr; }

		Tile* currentTile{ tileMap[startGridPosition.y][startGridPosition.x] };
		Tile* startTile{ currentTile };

		sf::Vector2i endGridPosition{ (int)(endPosition.x / Constants::gridSizeU), (int)(endPosition.y / Constants::gridSizeU) };
		if (isOutsideMap(endGridPosition, tileMapSize))
		{ return nullptr; }

		Tile* endTile{ tileMap[endGridPosition.y][endGridPosition.x] };


		startTile->globalGoal = twoPointsDistance(startPosition, endPosition);
		startTile->distanceToStart = 0.0f;

		std::vector<Tile*> tilesToTest{};
		tilesToTest.push_back(startTile);

		if (startGridPosition.x == endGridPosition.x && startGridPosition.y == endGridPosition.y) 
		{ return nullptr; }

		while (!tilesToTest.empty() && currentTile != endTile)
		{

			std::sort(tilesToTest.begin(), tilesToTest.end(),
				[](const Tile* a, const Tile* b)
				{
					return a->globalGoal < b->globalGoal;
				});

			while (!tilesToTest.empty() && tilesToTest[0]->isVisited == true)
			{
				tilesToTest.erase(tilesToTest.begin() + 0);
			}

			if (tilesToTest.empty())
			{
				break;
			}

			currentTile = tilesToTest[0];
			currentTile->isVisited = true;

			for (int iii{ 0 }; iii < currentTile->neighbors.size(); ++iii)
			{
				Tile* neighbourTile{ currentTile->neighbors[iii] };

				if (neighbourTile->isVisited == false && neighbourTile->isObsticle == false)
					tilesToTest.push_back(neighbourTile);

				float lowestLocalGoal{currentTile->distanceToStart +
					twoPointsDistance(currentTile->m_tile.getPosition(), neighbourTile->m_tile.getPosition())};

				if (lowestLocalGoal < neighbourTile->distanceToStart)
				{
					neighbourTile->parentTile = currentTile;
					neighbourTile->distanceToStart = lowestLocalGoal;
					neighbourTile->globalGoal = neighbourTile->distanceToStart +
						twoPointsDistance(neighbourTile->m_tile.getPosition(), endTile->m_tile.getPosition());
				}


			}

		}

		Tile* firstShortestPathTile{ endTile };


		while (firstShortestPathTile->parentTile != nullptr && firstShortestPathTile->parentTile->parentTile != nullptr)
		{
			firstShortestPathTile = firstShortestPathTile->parentTile;
		}

		return firstShortestPathTile;
	}

	void setTilesDefaultValues(std::vector<std::vector<Tile*>>& tileMap, const sf::Vector2i& tileMapSize)
	{
		for (int iii{ 0 }; iii < tileMapSize.y; ++iii)
		{
			for (int kkk{ 0 }; kkk < tileMapSize.x; ++kkk)
			{
				tileMap[iii][kkk]->isVisited = false;
				tileMap[iii][kkk]->globalGoal = INFINITY;
				tileMap[iii][kkk]->distanceToStart = INFINITY;
				tileMap[iii][kkk]->parentTile = nullptr;
			}
		}
	}

	float twoPointsDistance(sf::Vector2f startPoint, sf::Vector2f endPoint)
	{
		sf::Vector2f vector{ endPoint.x - startPoint.x, endPoint.y - startPoint.y };

		float length{ sqrt(vector.x * vector.x + vector.y * vector.y) };

		return length;
	}

	bool isOutsideMap(const sf::Vector2i& gridPosition, const sf::Vector2i& tileMapSize)
	{
		if (gridPosition.x > tileMapSize.x)
			return true;

		if (gridPosition.x < 0)
			return true;

		if (gridPosition.y > tileMapSize.y)
			return true;

		if (gridPosition.y < 0)
			return true;

		return false;
	}
}