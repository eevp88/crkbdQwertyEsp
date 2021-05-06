# Denna custom CRKBD Layout

My take on the 40% layout with programming in mind. Do read about the layers, it helps with forming a mental model to remember the keymap better than just memorization.

## Layers
- QWERTY: Base layer. The idea is to reduce thumb movement by placing commonly used keys and layers on resting thumb positions (center thumb keys). You might need to play around with TAPPING_TERM to find your perfect setting. Also, both Lower and Raise buttons appear on both halves for easy access (think of it as: middle thumb key is Lower, outer thumb key is Raise).


## Custom OLED
This keymap includes custom OLED font and code. The font contains some logos and status indidcators for some of the features I use (RGB and Audio). Enable OLED in rukes.mk to check it out. Feel free to reuse the font or parts of it.
__KNOWN BUG:__ When the computer sleeps, one of the OLEDs is always on (they don't turn off on their own, and the timeout doesn't work). I haven't been able to figure out what's going on there and am open to suggestions/PRs.

## Flashing
Flash using `make crkbd:danna:avrdude` for Pro Micro and `make crkbd:danna:dfu` for Elite-C.
