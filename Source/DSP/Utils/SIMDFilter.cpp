/*
  ==============================================================================

    SIMDFilter.cpp
    Created: 9 Sep 2022 5:30:35pm
    Author:  thesp

  ==============================================================================
*/

#include "SIMDFilter.h"

#if !JUCE_USE_SIMD
  #error "SIMD is NOT available"
#endif

namespace xynth
{
void SIMDFilter::reset() noexcept
{
    state[0] = 0.f;
    state[1] = 0.f;
}

SIMDFilter::SimdRegister SIMDFilter::processSample(SimdRegister input) noexcept
{
    const float b0 = coeffs[0];
    const float b1 = coeffs[1];
    const float b2 = coeffs[2];
    const float a1 = coeffs[4];
    const float a2 = coeffs[5];

    const auto output = (input * b0) + state[0];

    state[0] = (input * b1) - (output * a1) + state[1];
    state[1] = (input * b2) - (output * a2);

    return output;
}

} // namespace xynth