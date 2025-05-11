#pragma once
#include "BaseState.h"
#include "Button.h"
#include "Level.h"
#include "CaveLevel.h"
#include "BossLevel.h"
#include "PauseMenu.h"
#include "ValleyLevel.h"
#include "ParkourValleyLevel.h"
#include "Player.h"
#include "Item.h"
#include "RangeWeapon.h"
#include <map>
#include <stack>

class StateGame : public BaseState
{
public:
    StateGame(StateManager* stateManager);
    virtual void OnCreate() override;
    virtual void OnDestroy() override;
    virtual void Activate() override;
    virtual void Deactivate() override;
    virtual void Update(const sf::Time &time) override;
    virtual void Draw() override;
    virtual void HandlePlayerInput(const std::optional<sf::Event> &event) override;

    void moveBackgroundProportionallyToMap();
    void updateMousePositions(sf::View& camera);

    //void update(sf::RenderWindow* window) override;
    void updateInput();
    void levelDependentUpdate();
    void isLevelCompleted();
    void caveLevelUpdate();
    void valleyLevelUpdate();
    void parkourLevelUpdate();
    void bossLevelUpdate();


    //Buttons
    void updateButtons(sf::RenderWindow* window);
    void updateButtonsHover(sf::RenderWindow* window);
    void updateButtonsClickDetection(sf::RenderWindow* window);

    void updatePauseMenuButtons(sf::RenderWindow* window);
    void updateAfterDeathMenuButtons(sf::RenderWindow* window);
    void deleteAllEnemies();

    //Items
    void updateItems(const float& timerPerFrame);
    void updateItemsCollision(Item* item);
    void bulletsCollision(Item* item);
    void bulletsTileMapCollision(Item* item);
    void bulletEnemyCollision(Item* item);
    void playerEnemyCollision();

    //Creatures
    void updateCreatures(const float& timePerFrame);
    void updatePlayerCamera();
    void updateEnemyAI();

    void updateEnemySpawn();

    //Collision
    void updateTilesMapCollision(Creature* creature);
    void updateRenderBounds();
    void calculateCollisionBounds(sf::Vector2f point, int& fromX, int& toX, int& fromY, int& toY);
    void updateCollision(Creature* creature);

    void checkTileMapBounds(int& fromX, int& toX, int& fromY, int& toY);
    void checkPlayerCameraBounds();
    void CheckXaxis(float leftCameraBound, float rightCameraBound);
    void CheckYaxis(float upCameraBound, float downCameraBound);
    bool isPlayerDead();
    void deleteDeadEnemy();
    void resetLevel();
    void setLevelAfterBoss();
private:
    //Levels
    std::stack<Level*> m_levels;
    Level* m_currentLevel;
    bool m_isLevelCompleted;
    sf::RectangleShape m_nextLevelDoors;
    CaveLevel* m_caveLevel;
    ValleyLevel* m_valleyLevel;
    BossLevel* m_bossLevel;


    //GUI
    std::map<sf::String, Button*> m_buttons;
    PauseMenu* m_pauseMenu;
    PauseMenu* m_afterDeathMenu;
    ParkourValleyLevel* m_parkourValleyLevel;

    //Creatures
    std::vector<Creature*> m_creatures;
    std::vector<Enemy*> m_enemies;
    Player* m_player;
    sf::View m_playerCamera;
    bool m_isCameraOnLeftBound;
    bool m_isCameraOnRightBound;


    sf::Texture m_backgroundTexture;
    sf::RectangleShape m_background;

    Timer m_enemySpawnTimer;

    //Items
    std::vector<Item*> m_items;
    RangeWeapon* m_rifle;

    //Render and collision bounds
    int m_renderFromX;
    int m_renderToX;
    int m_renderFromY;
    int m_renderToY;

    //TileMap
    TileMap* m_tileMap;

    sf::Vector2i m_mousePositionWindow;
    sf::Vector2f m_mousePositionView;
    sf::Vector2u m_mouseGridPosition;
    sf::Vector2i m_mousePositionMap;

    //Initialize Functions
    void initButtons();
    void initPauseMenu();
    void initPlayer();
    void initBackground();
    void initTileMap();
    void initVariables();
    void initLevels();

    //void render(sf::RenderTarget* target = nullptr) override;
    void renderButtons(sf::RenderTarget* target);
    void renderCreatures(sf::RenderTarget* target, bool addBlendMode = false);
    void renderGUI(sf::RenderTarget* target);
    void renderItems(sf::RenderTarget* target);
    void caveLevelRender(sf::RenderTarget* target);
    void valleyLevelRender(sf::RenderTarget* target);
    void parkourValleyLevelRender(sf::RenderTarget* target);
    void bossLevelRender(sf::RenderTarget* target);
};

