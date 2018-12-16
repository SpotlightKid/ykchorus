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

#ifndef DISTRHO_PLUGIN_INFO_H
#define DISTRHO_PLUGIN_INFO_H

#define DISTRHO_PLUGIN_BRAND "chrisarndt.de"
#define DISTRHO_PLUGIN_NAME  "YK Chorus"
#define DISTRHO_PLUGIN_URI   "https://chrisarndt.de/plugins/ykchorus"

#define DISTRHO_PLUGIN_HAS_UI       1
#define DISTRHO_PLUGIN_IS_RT_SAFE   1
#define DISTRHO_PLUGIN_NUM_INPUTS   2
#define DISTRHO_PLUGIN_NUM_OUTPUTS  2
#define DISTRHO_PLUGIN_WANT_TIMEPOS 0
#define DISTRHO_PLUGIN_WANT_PROGRAMS 1

#endif // DISTRHO_PLUGIN_INFO_H
