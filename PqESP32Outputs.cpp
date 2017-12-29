/*
 * PqESP32Outputs.cpp
 *
 * (c) 2017 Sofian Audry        :: info(@)sofianaudry(.)com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "PqESP32Outputs.h"

uint8_t SigmaDeltaOut::_nextChannel = 0;

SigmaDeltaOut::SigmaDeltaOut(uint8_t pin_, uint8_t mode_, float freq_)
  : PqPinComponent(pin_, mode_), PqPutter(),
    _value(0),
    _freq(round(freq_))
{
  // Channels are only valid 0..7; after this it will stop working.
  _channel = _nextChannel++;
}

void SigmaDeltaOut::attach(uint8_t pin)
{
  sigmaDeltaDetachPin(pin); // just to be sure
  sigmaDeltaAttachPin(pin, _channel);
}

float SigmaDeltaOut::put(float value) {
  return (_value = write(value));
}

float SigmaDeltaOut::write(float value) {
  // Make sure value is in [0, 1] and remap to [0, 255].
  value = constrain(value, 0, 1) * 255;
  int rawValue = round(value);
  // Write to channel (inverting if needed).
  sigmaDeltaWrite(_channel, (_mode == SOURCE ? rawValue : 255 - rawValue));
  return value;
}

void SigmaDeltaOut::setup() {
  // Initialize channel with appropriate frequency.
  sigmaDeltaSetup(_channel, _freq);

  // Initialize channel to 0.
  sigmaDeltaWrite(_channel, 0);

  // Attach pin.
  attach(_pin);
}
