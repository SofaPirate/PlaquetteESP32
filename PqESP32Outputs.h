/*
 * PqESP32Outputs.h
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

#ifndef PQ_ESP32_OUTPUTS_H_
#define PQ_ESP32_OUTPUTS_H_

#include <Plaquette.h>

/// A generic class representing a simple PWM output.
class SigmaDeltaOut : public PqPutter {
public:
  /// Constructor.
  SigmaDeltaOut(uint8_t channel=0, float freq=312500, uint8_t mode=SOURCE);
  virtual ~SigmaDeltaOut() {}

  /**
   * Attaches a pin on the ESP32 board to this output. This is normally
   * done in the begin() function.
   */
  void attach(uint8_t pin);

  /// Detaches a pin on the ESP32 board to ALL outputs.
  static void detach(uint8_t pin);

  /// Pushes value into the component and returns its (possibly filtered) value.
  virtual float put(float value);

  /// Returns reading in [0, 1].
  virtual float get() { return _value; }

	/// Inverts value by setting it to (1-get()).
	virtual void invert() { put(1-get()); }

  /// Returns the frequency of the sigma delta output.
  float freq() const { return float(_freq); };

  /// Returns the channel this component is attached to.
  uint8_t channel() const { return _channel; }

  /// Returns the mode of the component.
  uint8_t mode() const { return _mode; }

  // Current value.
  float _value;

  // Frequency.
  uint32_t _freq;

  // The attached channel.
  uint8_t _channel;

  // The mode (varies according to context).
  uint8_t _mode;

  // Writes value to output and returns it.
  virtual float write(float value);

protected:
  virtual void setup();
};

#endif
