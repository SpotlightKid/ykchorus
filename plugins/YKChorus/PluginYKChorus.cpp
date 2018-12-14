/*
 * YK Chorus audio effect based on DISTRHO Plugin Framework (DPF)
 * Copyright (C) 2018 Christopher Arndt <chris@chrisarndt.de>
 *
 * This file may be licensed under the terms of of the
 * GNU General Public License Version 2 (the ``GPL'').
 *
 * Software distributed under the License is distributed
 * on an ``AS IS'' basis, WITHOUT WARRANTY OF ANY KIND, either
 * express or implied. See the GPL for the specific language
 * governing rights and limitations.
 *
 * You should have received a copy of the GPL along with this
 * program. If not, go to http://www.gnu.org/licenses/gpl.html
 * or write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include <math.h>

#include "PluginYKChorus.hpp"

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

PluginYKChorus::PluginYKChorus()
    : Plugin(paramCount, 3, 0)  // paramCount params, 3 program(s), 0 states
{
    for (uint i = 0; i < paramCount; i++) {
        fParams[i] = 0.0f;
    }
    fSampleRate = -1;
    cengine = new ChorusEngine(getSampleRate());
    loadProgram(0);
}

PluginYKChorus::~PluginYKChorus() {
    delete cengine;
}

// -----------------------------------------------------------------------
// Init

void PluginYKChorus::initParameter(uint32_t index, Parameter& parameter) {
    if (index >= paramCount)
        return;

    parameter.ranges.min = 0.0f;
    parameter.ranges.max = 1.0f;
    parameter.ranges.def = 0.0f;
    parameter.hints = kParameterIsAutomable;

    switch (index) {
        case paramChorus1Enable:
            parameter.name = "Chorus Type 1";
            parameter.symbol = "chorus_1_enable";
            parameter.hints |= kParameterIsBoolean;
            break;
        case paramChorus2Enable:
            parameter.name = "Chorus Type 2";
            parameter.symbol = "chorus_2_enable";
            parameter.hints |= kParameterIsBoolean;
            break;
    }
}

/**
  Set the name of the program @a index.
  This function will be called once, shortly after the plugin is created.
*/
void PluginYKChorus::initProgramName(uint32_t index, String& programName) {
    switch (index) {
        case 0:
            programName = "Type 1";
            break;
        case 1:
            programName = "Type 2";
            break;
        case 2:
            programName = "Type 1+2";
            break;
    }
}

// -----------------------------------------------------------------------
// Internal data

/**
  Optional callback to inform the plugin about a sample rate change.
*/
void PluginYKChorus::sampleRateChanged(double newSampleRate) {
    if (newSampleRate != fSampleRate) {
        fSampleRate = newSampleRate;
        cengine->setSampleRate(newSampleRate);
        cengine->setEnablesChorus(fParams[paramChorus1Enable], fParams[paramChorus2Enable]);
    }
}

/**
  Get the current value of a parameter.
*/
float PluginYKChorus::getParameterValue(uint32_t index) const {
    return fParams[index];
}

/**
  Change a parameter value.
*/
void PluginYKChorus::setParameterValue(uint32_t index, float value) {
    fParams[index] = value;

    switch (index) {
        case paramChorus1Enable:
            // fall through!
        case paramChorus2Enable:
            cengine->setEnablesChorus(fParams[paramChorus1Enable], fParams[paramChorus2Enable]);
            break;
    }
}

/**
  Load a program.
  The host may call this function from any context,
  including realtime processing.
*/
void PluginYKChorus::loadProgram(uint32_t index) {
    switch (index) {
        case 0:
            setParameterValue(paramChorus1Enable, 1.0f);
            setParameterValue(paramChorus2Enable, 0.0f);
            break;
        case 1:
            setParameterValue(paramChorus1Enable, 0.0f);
            setParameterValue(paramChorus2Enable, 1.0f);
            break;
        case 2:
            setParameterValue(paramChorus1Enable, 1.0f);
            setParameterValue(paramChorus2Enable, 1.0f);
            break;
    }
}

// -----------------------------------------------------------------------
// Process

void PluginYKChorus::activate() {
    // plugin is activated
    sampleRateChanged(fSampleRate);
}

void PluginYKChorus::run(const float** inputs, float** outputs, uint32_t frames) {
    // get the left and right audio inputs
    const float* const inpL = inputs[0];
    const float* const inpR = inputs[1];

    // get the left and right audio outputs
    float* const outL = outputs[0];
    float* const outR = outputs[1];

    // apply effect on all samples
    for (uint32_t i = 0; i < frames; ++i) {
        outL[i] = inpL[i];
        outR[i] = inpR[i];
        cengine->process(&outL[i], &outR[i]);
    }
}

// -----------------------------------------------------------------------

Plugin* createPlugin() {
    return new PluginYKChorus();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO
