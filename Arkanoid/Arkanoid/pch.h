﻿//
// pch.h
// Header for standard system include files.
//

#pragma once

// Use the C++ standard templated min/max
#define NOMINMAX

#include <wrl.h>

#include <d3d11_3.h>
#include <dxgi1_4.h>
#include <DirectXMath.h>
#include <DirectXColors.h>

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <exception>
#include <iterator>
#include <memory>
#include <stdexcept>


#include "BufferHelpers.h"
#include "CommonStates.h"
#include "DDSTextureLoader.h"
#include "SimpleMath.h"
#include "SpriteBatch.h"
#include "WICTextureLoader.h"

#ifdef _DEBUG
#include <dxgidebug.h>
#endif

namespace DX
{
    inline void ThrowIfFailed(HRESULT hr)
    {
        if (FAILED(hr))
        {
            // Set a breakpoint on this line to catch DirectX API errors
            throw std::exception();
        }
    }
}
