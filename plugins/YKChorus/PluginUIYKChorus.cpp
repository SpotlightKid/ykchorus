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

#include "PluginYKChorus.hpp"
#include "PluginUIYKChorus.hpp"

START_NAMESPACE_DISTRHO

namespace Art = PluginArtworkYKChorus;

// -----------------------------------------------------------------------

PluginUIYKChorus::PluginUIYKChorus()
    : UI(Art::backgroundWidth, Art::backgroundHeight),
      fImgBackground(Art::backgroundData, Art::backgroundWidth, Art::backgroundHeight, GL_BGRA)
{
    // Knobs
    Image knobImage(Art::knobData, Art::knobWidth, Art::knobHeight);

    // Knob Chorus 1 LFO Rate
    fKnobRate1 = new ImageKnob(this, knobImage, ImageKnob::Vertical);
    fKnobRate1->setId(PluginYKChorus::paramChorus1LfoRate);
    fKnobRate1->setImageLayerCount(30);
    fKnobRate1->setAbsolutePos(10, 170);
    fKnobRate1->setRange(0.0f, 10.0f);
    fKnobRate1->setDefault(5.0f);
    fKnobRate1->setCallback(this);

    // Knob Chorus 2 LFO Rate
    fKnobRate2 = new ImageKnob(this, knobImage, ImageKnob::Vertical);
    fKnobRate2->setId(PluginYKChorus::paramChorus2LfoRate);
    fKnobRate2->setImageLayerCount(30);
    fKnobRate2->setAbsolutePos(110, 170);
    fKnobRate2->setRange(0.0f, 10.0f);
    fKnobRate2->setDefault(5.0f);
    fKnobRate2->setCallback(this);

    // Switches

    // Switch Chorus 1 On/Off
    Image switchImageUp(Art::switch_upData, Art::switch_upWidth, Art::switch_upHeight);
    Image switchImageDown(Art::switch_downData, Art::switch_downWidth, Art::switch_downHeight);
    fSwitchChorus1Enable = new ImageSwitch(this, switchImageUp, switchImageDown);
    fSwitchChorus1Enable->setId(PluginYKChorus::paramChorus1Enable);
    fSwitchChorus1Enable->setAbsolutePos(22, 82);
    fSwitchChorus1Enable->setCallback(this);

    // Switch Chorus 2 On/Off
    fSwitchChorus2Enable = new ImageSwitch(this, switchImageUp, switchImageDown);
    fSwitchChorus2Enable->setId(PluginYKChorus::paramChorus2Enable);
    fSwitchChorus2Enable->setAbsolutePos(122, 82);
    fSwitchChorus2Enable->setCallback(this);

    // set default values
    programLoaded(0);
}

// -----------------------------------------------------------------------
// DSP Callbacks

void PluginUIYKChorus::parameterChanged(uint32_t index, float value) {
    switch (index) {
        case PluginYKChorus::paramChorus1Enable:
            fSwitchChorus1Enable->setDown(value);
            break;
        case PluginYKChorus::paramChorus2Enable:
            fSwitchChorus2Enable->setDown(value);
            break;
        case PluginYKChorus::paramChorus1LfoRate:
            fKnobRate1->setValue(value);
            break;
        case PluginYKChorus::paramChorus2LfoRate:
            fKnobRate2->setValue(value);
            break;
    }
}

void PluginUIYKChorus::programLoaded(uint32_t index) {
    switch (index) {
        case 0:
            fSwitchChorus1Enable->setDown(true);
            fSwitchChorus2Enable->setDown(false);
            fKnobRate1->setValue(5.0f);
            fKnobRate2->setValue(8.3f);
            break;
        case 1:
            fSwitchChorus1Enable->setDown(false);
            fSwitchChorus2Enable->setDown(true);
            fKnobRate1->setValue(5.0f);
            fKnobRate2->setValue(8.3f);
            break;
        case 2:
            fSwitchChorus1Enable->setDown(true);
            fSwitchChorus2Enable->setDown(true);
            fKnobRate1->setValue(5.0f);
            fKnobRate2->setValue(8.3f);
            break;
    }
}

// -----------------------------------------------------------------------
// Widget Callbacks

void PluginUIYKChorus::imageSwitchClicked(ImageSwitch* sw, bool down) {
    if (sw == fSwitchChorus1Enable || sw == fSwitchChorus2Enable) {
        sw->setDown(down);
        setParameterValue(sw->getId(), down);
    }
}

void PluginUIYKChorus::imageKnobDragStarted(ImageKnob* knob) {
    editParameter(knob->getId(), true);
}

void PluginUIYKChorus::imageKnobDragFinished(ImageKnob* knob) {
    editParameter(knob->getId(), false);
}

void PluginUIYKChorus::imageKnobValueChanged(ImageKnob* knob, float value) {
    setParameterValue(knob->getId(), value);
}

void PluginUIYKChorus::onDisplay() {
    fImgBackground.draw();
}

// -----------------------------------------------------------------------

UI* createUI() {
    return new PluginUIYKChorus();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO
