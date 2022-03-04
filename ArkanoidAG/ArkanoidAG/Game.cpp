//
// Game.cpp
//

#include "pch.h"
#include "Game.h"

extern void ExitGame() noexcept;

using namespace DirectX;

using Microsoft::WRL::ComPtr;

Game::Game() noexcept(false)
{
    m_deviceResources = std::make_unique<DX::DeviceResources>();
    m_deviceResources->RegisterDeviceNotify(this);
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(IUnknown* window, int width, int height, DXGI_MODE_ROTATION rotation)
{
    StartGame(width, height);

    m_keyboard = std::make_unique<Keyboard>();
    m_keyboard->SetWindow(reinterpret_cast<ABI::Windows::UI::Core::ICoreWindow*>(window));

    m_deviceResources->SetWindow(window, width, height, rotation);

    m_deviceResources->CreateDeviceResources();
    CreateDeviceDependentResources();

    m_deviceResources->CreateWindowSizeDependentResources();
    CreateWindowSizeDependentResources();

    // TODO: Change the timer settings if you want something other than the default variable timestep mode.
    // e.g. for 60 FPS fixed timestep update logic, call:
    /*
    m_timer.SetFixedTimeStep(true);
    m_timer.SetTargetElapsedSeconds(1.0 / 60);
    */

    
}

void Game::StartGame(int width, int height)
{
    sphere = new Sphere(new Vec2(width / 2, height * 0.65f));
    paddle = new Paddle(new Vec2(width * 0.84f / 2 - 32, height * 0.88f),64,16);
    leftWall = new Wall(new Vec2(0, 0), 20, height, Wall::WALLTYPE::LEFT);
    upWall = new Wall(new Vec2(0, 0), width * 0.84f, 20, Wall::WALLTYPE::UP);
    rightWall = new Wall(new Vec2(width * 0.84f - 20, 0), 20, height, Wall::WALLTYPE::RIGHT);
    bricks = new Brick*[bricksPerLevel];

    initializeBricksLevel2();
}

void Game::initializeBricksLevel1()
{
    for (int i = 0; i < bricksPerLevel; i++)
    {
        int x = startBricksX + (i % bricksPerRow) * Brick::BWIDTH + paddingBrikcs;
        int y = startBricksY + (i / bricksPerRow) * Brick::BHEIGHT + paddingBrikcs;
        bricks[i] = new Brick(new Vec2(x, y), Brick::LIFEBRICK::HALF);
    }
}

void Game::initializeBricksLevel2()
{
    for (int i = 0; i < bricksPerLevel; i++)
    {
        int x = startBricksX + (i % bricksPerRow) * Brick::BWIDTH + paddingBrikcs;
        int y = startBricksY + (i / bricksPerRow) * Brick::BHEIGHT + paddingBrikcs;

        Brick::LIFEBRICK life = (i / bricksPerRow) % 2 == 0 ? Brick::LIFEBRICK::FULL : Brick::LIFEBRICK::HALF;

        bricks[i] = new Brick(new Vec2(x, y), life);
    }
}

#pragma region Frame Update
// Executes the basic game loop.
void Game::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

    Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
    PIXBeginEvent(PIX_COLOR_DEFAULT, L"Update");

    float elapsedTime = float(timer.GetElapsedSeconds());

    // TODO: Add your game logic here.
    m_stars->Update(elapsedTime * 200);
    auto kb = m_keyboard->GetState();
    if (kb.Escape)
    {
        ExitGame();
    }

    if (kb.Left)
    {
        paddle->getInput(-paddleMovementDelta, leftWall, rightWall);
    }

    if (kb.Right)
    {
        paddle->getInput(paddleMovementDelta, leftWall, rightWall);
    }

    sphere->update(*paddle, bricks, bricksPerLevel, *leftWall, *upWall, *rightWall);
    elapsedTime;

    PIXEndEvent();
}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
void Game::Render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    Clear();

   

    m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states->NonPremultiplied());
    
    m_stars->Draw(m_spriteBatch.get());

    for (int i = 0; i < bricksPerLevel; i++)
    {
        bricks[i]->display(m_spriteBatch, m_batch);
    }

    sphere->display(m_spriteBatch, m_batch);
    paddle->display(m_spriteBatch, m_batch);
    
    const wchar_t* output = L"Score";

    Vec2 origin = m_font->MeasureString(output) / 2.f;

    Vec2 scaleFont = Vec2(0.4f, 0.4f);

    m_font->DrawString(m_spriteBatch.get(), output,
        m_fontPos, Colors::White, 0.f, origin, scaleFont);

    m_spriteBatch->End();

    auto context = m_deviceResources->GetD3DDeviceContext();
    PIXBeginEvent(context, PIX_COLOR_DEFAULT, L"Render");


    // TODO: Add your rendering code here.

    context->OMSetBlendState(m_states->Opaque(), nullptr, 0xFFFFFFFF);
    context->OMSetDepthStencilState(m_states->DepthNone(), 0);
    context->RSSetState(m_states->CullNone());

    m_effect->Apply(context);
    context->IASetInputLayout(m_inputLayout.Get());

    m_batch->Begin();

    leftWall->display(m_spriteBatch, m_batch);
    upWall->display(m_spriteBatch, m_batch);
    rightWall->display(m_spriteBatch, m_batch);

    m_batch->End();

    PIXEndEvent(context);

    // Show the new frame.
    PIXBeginEvent(PIX_COLOR_DEFAULT, L"Present");
    m_deviceResources->Present();
    PIXEndEvent();
}

// Helper method to clear the back buffers.
void Game::Clear()
{
    auto context = m_deviceResources->GetD3DDeviceContext();
    PIXBeginEvent(context, PIX_COLOR_DEFAULT, L"Clear");

    // Clear the views.
    auto renderTarget = m_deviceResources->GetRenderTargetView();
    auto depthStencil = m_deviceResources->GetDepthStencilView();

    context->ClearRenderTargetView(renderTarget, Colors::CornflowerBlue);
    context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    context->OMSetRenderTargets(1, &renderTarget, depthStencil);

    // Set the viewport.
    auto viewport = m_deviceResources->GetScreenViewport();
    context->RSSetViewports(1, &viewport);

    PIXEndEvent(context);
 }
#pragma endregion

#pragma region Message Handlers
// Message handlers
void Game::OnActivated()
{
    // TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
    auto context = m_deviceResources->GetD3DDeviceContext();
    context->ClearState();

    m_deviceResources->Trim();

    // TODO: Game is being power-suspended.
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed.
}

void Game::OnWindowSizeChanged(int width, int height, DXGI_MODE_ROTATION rotation)
{
    if (!m_deviceResources->WindowSizeChanged(width, height, rotation))
        return;

    CreateWindowSizeDependentResources();

    // TODO: Game window is being resized.
}

void Game::ValidateDevice()
{
    m_deviceResources->ValidateDevice();
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const noexcept
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    width = 800;
    height = 600;
}
#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Game::CreateDeviceDependentResources()
{
    auto device = m_deviceResources->GetD3DDevice();

    // TODO: Initialize device dependent objects here (independent of window size).

    m_font = std::make_unique<SpriteFont>(device, L"Assets/myfile.spritefont");

    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>* m_textureSphere = new Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>();
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>* m_texturePaddle = new Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>();
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>* m_textureBrickHalf = new Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>();
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>* m_textureBrickFull = new Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>();

    auto context = m_deviceResources->GetD3DDeviceContext();
    m_spriteBatch = std::make_unique<SpriteBatch>(context);
    
    m_states = std::make_unique<CommonStates>(device);
    m_effect = std::make_unique<BasicEffect>(device);

    m_effect->SetVertexColorEnabled(true);
    m_batch = std::make_unique<PrimitiveBatch<DirectX::VertexPositionColor>>(context);

    DX::ThrowIfFailed(
        CreateInputLayoutFromEffect<VertexType>(device, m_effect.get(),
            m_inputLayout.ReleaseAndGetAddressOf())
    );

    auto size = m_deviceResources->GetOutputSize();

    Matrix proj = Matrix::CreateScale(2.f / float(size.right),
        -2.f / float(size.bottom), 1.f)
        * Matrix::CreateTranslation(-1.f, 1.f, 0.f);
    m_effect->SetProjection(proj);



    ComPtr<ID3D11Resource> resourceSphere;
    DX::ThrowIfFailed(
        CreateWICTextureFromFile(device, L"Assets/Sphere.png",
            resourceSphere.GetAddressOf(),
            m_textureSphere->ReleaseAndGetAddressOf()));

    ComPtr<ID3D11Texture2D> sphereTex;
    DX::ThrowIfFailed(resourceSphere.As(&sphereTex));

    CD3D11_TEXTURE2D_DESC sphereDesc;
    sphereTex->GetDesc(&sphereDesc);

    

    Sphere::setupTexture(m_textureSphere);


    ComPtr<ID3D11Resource> resourcePaddle;
    DX::ThrowIfFailed(
        CreateWICTextureFromFile(device, L"Assets/Paddle.png",
            resourcePaddle.GetAddressOf(),
            m_texturePaddle->ReleaseAndGetAddressOf()));

    ComPtr<ID3D11Texture2D> paddleTex;
    DX::ThrowIfFailed(resourcePaddle.As(&paddleTex));

    CD3D11_TEXTURE2D_DESC paddleDesc;
    paddleTex->GetDesc(&paddleDesc);

    Paddle::setupTexture(m_texturePaddle);


    ComPtr<ID3D11Resource> resourceBrickHalf;
    DX::ThrowIfFailed(
        CreateWICTextureFromFile(device, L"Assets/BrickHalf.png",
            resourceBrickHalf.GetAddressOf(),
            m_textureBrickHalf->ReleaseAndGetAddressOf()));

    ComPtr<ID3D11Texture2D> brickHalfTex;
    DX::ThrowIfFailed(resourceBrickHalf.As(&brickHalfTex));

    CD3D11_TEXTURE2D_DESC brickHalfDesc;
    brickHalfTex->GetDesc(&brickHalfDesc);

    ComPtr<ID3D11Resource> resourceBrickFull;
    DX::ThrowIfFailed(
        CreateWICTextureFromFile(device, L"Assets/BrickFull.png",
            resourceBrickFull.GetAddressOf(),
            m_textureBrickFull->ReleaseAndGetAddressOf()));

    ComPtr<ID3D11Texture2D> brickFullTex;
    DX::ThrowIfFailed(resourceBrickFull.As(&brickFullTex));

    CD3D11_TEXTURE2D_DESC brickFullDesc;
    brickFullTex->GetDesc(&brickFullDesc);

    Brick::setupTexture(m_textureBrickFull, m_textureBrickHalf);

    DX::ThrowIfFailed(CreateWICTextureFromFile(device, L"Assets/starfield.png",
        nullptr, m_backgroundTex.ReleaseAndGetAddressOf()));

    m_stars = std::make_unique<ScrollingBackground>();
    m_stars->Load(m_backgroundTex.Get());

    
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
    // TODO: Initialize windows-size dependent objects here.

    auto size = m_deviceResources->GetOutputSize();
    m_screenPos.x = float(size.right) / 2.f;
    m_screenPos.y = float(size.bottom) / 2.f;

    m_stars->SetWindow(size.right - 120, size.bottom);

    m_fontPos.x = float(size.right) * 0.92;
    m_fontPos.y = float(size.bottom) * 0.20;
}



void Game::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here.
    m_spriteBatch.reset();
    m_font.reset();
    m_batch.reset();
    m_effect.reset();
    m_states.reset();
    m_inputLayout.Reset();
    m_stars.reset();
    m_backgroundTex.Reset();
    sphere->Reset();
    paddle->Reset();

    for (int i = 0; i < bricksPerLevel; i++)
        bricks[i]->Reset();
}

void Game::OnDeviceRestored()
{
    CreateDeviceDependentResources();

    CreateWindowSizeDependentResources();
}
#pragma endregion
