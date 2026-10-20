/*
  ==============================================================================

    ZeketeHeader.h
    Created: 9 Sep 2022 9:56:09am
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include "../Common/Constants.h"

#include "Dist1.h"
#include "Dist2.h"
#include "Dist3.h"
#include "Dist4.h"
#include "Dist5.h"
#include "Dist6.h"

namespace xynth
{

static std::unique_ptr<DistortionProcessor> distortionFromType(size_t distType)
{
    switch (distType)
    {
        default: jassertfalse; // Invalid distortion type
        case 0: return std::make_unique<Dist1>();
        case 1: return std::make_unique<Dist2>();
        case 2: return std::make_unique<Dist3>();
        case 3: return std::make_unique<Dist4>();
        case 4: return std::make_unique<Dist5>();
        case 5: return std::make_unique<Dist6>();
    }
}

static float distortSampleVisualization(size_t distType, float sample, float amount)
{
    switch (distType)
    {
        default: jassertfalse; // Invalid distortion type
        case 0: return Dist1::distortVisual(sample, amount);
        case 1: return Dist2::distortVisual(sample, amount);
        case 2: return Dist3::distortVisual(sample, amount);
        case 3: return Dist4::distortVisual(sample, amount);
        case 4: return Dist5::distortVisual(sample, amount);
        case 5: return Dist6::distortVisual(sample, amount);
    }
}

static float xAxisFromAmount(size_t distType, float amount)
{
    switch (distType)
    {
        default: jassertfalse; // Invalid distortion type
        case 0: return Dist1::xAxis(amount);
        case 1: return Dist2::xAxis(amount);
        case 2: return Dist3::xAxis(amount);
        case 3: return Dist4::xAxis(amount);
        case 4: return Dist5::xAxis(amount);
        case 5: return Dist6::xAxis(amount);
    }
}

}
