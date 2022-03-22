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

#ifndef PLUGIN_YKCHORUS_H
#define PLUGIN_YKCHORUS_H

#include "DistrhoPlugin.hpp"
#include "ChorusEngine.h"

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

class PluginYKChorus : public Plugin {
public:
    enum Parameters {
        paramChorus1Enable = 0,
        paramChorus2Enable,
        paramChorus1LfoRate,
        paramChorus2LfoRate,
        paramCount
    };

    PluginYKChorus();

    ~PluginYKChorus();

protected:
    // -------------------------------------------------------------------
    // Information

    const char* getLabel() const noexcept override {
        return "YK Chorus";
    }

    const char* getDescription() const override {
        return "A chorus effect inspired by well-known Japanese analog synthesizers";
    }

    const char* getMaker() const noexcept override {
        return "chrisarndt.de";
    }

    const char* getHomePage() const override {
        return "https://chrisarndt.de/plugins/ykchorus";
    }

    const char* getLicense() const noexcept override {
        return "https://spdx.org/licenses/GPL-2.0-only";
    }

    uint32_t getVersion() const noexcept override {
        return d_version(0, 2, 2);
    }

    // Go to:
    //
    // http://service.steinberg.de/databases/plugin.nsf/plugIn
    //
    // Get a proper plugin UID and fill it in here!
    int64_t getUniqueId() const noexcept override {
        return d_cconst('Y', 'K', 'C', 'h');
    }

    // -------------------------------------------------------------------
    // Init

    void initParameter(uint32_t index, Parameter& parameter) override;
    void initProgramName(uint32_t index, String& programName) override;

    // -------------------------------------------------------------------
    // Internal data

    float getParameterValue(uint32_t index) const override;
    void setParameterValue(uint32_t index, float value) override;
    void loadProgram(uint32_t index) override;

    // -------------------------------------------------------------------
    // Optional

    // Optional callback to inform the plugin about a sample rate change.
    void sampleRateChanged(double newSampleRate) override;

    // -------------------------------------------------------------------
    // Process

    void activate() override;
    void run(const float**, float** outputs, uint32_t frames) override;

    // -------------------------------------------------------------------

private:
    float    fParams[paramCount];
    double   fSampleRate;
    ChorusEngine * cengine;

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginYKChorus)
};

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO

#endif  // #ifndef PLUGIN_YKCHORUS_H
