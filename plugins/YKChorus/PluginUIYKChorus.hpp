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

#ifndef PLUGIN_UI_YKCHORUS_H
#define PLUGIN_UI_YKCHORUS_H

#include "DistrhoUI.hpp"
#include "ImageWidgets.hpp"

#include "PluginArtworkYKChorus.hpp"

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

class PluginUIYKChorus : public UI,
                         public ImageSwitch::Callback,
                         public ImageKnob::Callback
{
public:
    PluginUIYKChorus();

protected:
    // -------------------------------------------------------------------
    // DSP Callbacks

    void parameterChanged(uint32_t index, float value) override;
    void programLoaded(uint32_t index) override;

    // -------------------------------------------------------------------
    // Widget Callbacks

    void imageSwitchClicked(ImageSwitch* sw, bool down) override;
    void imageKnobDragStarted(ImageKnob* knob) override;
    void imageKnobDragFinished(ImageKnob* knob) override;
    void imageKnobValueChanged(ImageKnob* knob, float value) override;

    void onDisplay() override;

private:
    Image fImgBackground;

    ScopedPointer<ImageSwitch> fSwitchChorus1Enable, fSwitchChorus2Enable;
    ScopedPointer<ImageKnob> fKnobRate1, fKnobRate2;

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginUIYKChorus)
};

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO

#endif // PLUGIN_UI_YKCHORUS_H
