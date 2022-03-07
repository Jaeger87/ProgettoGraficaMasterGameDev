//
// Game.h
//

#pragma once

#include "DeviceResources.h"
#include "ScrollingBackground.h"
#include "StepTimer.h"
#include "Sphere.h"
#include "Paddle.h"
#include "Wall.h"
#include "ScoreManager.h"

using VertexType = DirectX::VertexPositionColor;
using Matrix = DirectX::SimpleMath::Matrix;

// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game final : public DX::IDeviceNotify
{
public:

    Game() noexcept(false);
    ~Game() = default;

    Game(Game&&) = default;
    Game& operator= (Game&&) = default;

    Game(Game const&) = delete;
    Game& operator= (Game const&) = delete;

    // Initialization and management
    void Initialize(IUnknown* window, int width, int height, DXGI_MODE_ROTATION rotation);

    // Basic game loop
    void Tick();

    // IDeviceNotify
    void OnDeviceLost() override;
    void OnDeviceRestored() override;

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowSizeChanged(int width, int height, DXGI_MODE_ROTATION rotation);
    void ValidateDevice();

    // Properties
    void GetDefaultSize( int& width, int& height ) const noexcept;

    

private:
    enum ARKANOIDLEVEL { ONE, TWO };

    ARKANOIDLEVEL m_CurrentLevel;

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();

    void StartGame(int width, int height);
    void initializeLevel1(int width, int height);
    void initializeLevel2(int width, int height);
    void restartGame();
    void nextLevel();
    // Device resources.
    std::unique_ptr<DX::DeviceResources>    m_deviceResources;

    // Rendering loop timer.
    DX::StepTimer                           m_timer;

    Sphere* sphere;
    Paddle* paddle;
    Wall* leftWall;
    Wall* upWall;
    Wall* rightWall;
    ScoreManager* scoreManager;
    Brick** bricks;

    std::unique_ptr<DirectX::Keyboard> m_keyboard;
    std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
    std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_batch;
    std::unique_ptr<DirectX::CommonStates> m_states;
    std::unique_ptr<DirectX::BasicEffect> m_effect;
    Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
    DirectX::SimpleMath::Vector2 m_screenPos;
    DirectX::SimpleMath::Vector2 m_origin;
    std::unique_ptr<ScrollingBackground> m_stars;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_backgroundTex;
    std::unique_ptr<DirectX::SpriteFont> m_font;


    const float paddleMovementDelta = 5.0f;
    const int bricksPerLevel = 90;
    const int bricksPerRow = 18;


    const float startBricksX = 43;
    const float startBricksY = 70;
    const float paddingBrikcs = 5;

    int highScore = 0;

    bool gameOver = false;
    bool levelFinish = false;
};
