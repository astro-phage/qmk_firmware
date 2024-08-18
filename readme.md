## Disclaimer

- **Fork of**: [https://github.com/Keychron/qmk_firmware](https://github.com/Keychron/qmk_firmware).
- **Use at Your Own Risk**: Proceed with caution. Consult the documentation and recommendations of the manufacturers.
- **VIA Compatibility**: Using this custom QMK firmware will disable direct adjustments with VIA.
- **Keymap Adjustment**: The keymap has been specifically adjusted for the Keychron Q5 Max, but many changes may be adaptable to other keyboards.

## Functionalities

- **Umlauts on Q5 Max ANSI Layout**: Outputs German umlauts (äöü) using the standard US layout on Windows, without needing the US international layout.
- **LED Color Customization**: Changes the LED color of all customized keys when switching layers.
- **Shift Key Behavior**: Double-tapping the Shift key activates Caps Lock.
- **TAP Hold for Umlauts**: Holding down the Umlaut key (250ms) outputs the original key (i.E `ä -> '`) without having to switching back to the base layer while being in "writing" mode.

For detailed changes, refer to the *comments* in  [Keymap.c](https://github.com/astro-phage/qmk_firmware/blob/wireless_playground/keyboards/keychron/q5_max/ansi_encoder/keymaps/default/keymap.c#L19).


## Firmware modifications

- [Keymap.c](https://github.com/astro-phage/qmk_firmware/blob/wireless_playground/keyboards/keychron/q5_max/ansi_encoder/keymaps/default/keymap.c)
- [Rules.mk](https://github.com/astro-phage/qmk_firmware/blob/wireless_playground/keyboards/keychron/q5_max/rules.mk)

## Prerequisites

- **QMK MSYS**: Ensure QMK MSYS is installed on your system.


## Clone the Repository: 

    git clone https://github.com/astro-phage/qmk_firmware.git
    git checkout wireless_playground
*The branch `wireless_playground` contains keymaps for Keychron's wireless keyboards and therefore the modifications.*

## Build and Flash Firmware:

Open QMK MSYS and navigate to the qmk_firmware directory.
Run the following command:

`make keychron/q5_max/ansi_encoder:default:flash`

**Enter Flash Mode**: Unplug the keyboard and then plug it back in while holding the <ESC> key.

### Why Not US-International Layout?

Alternatively, you could use the US-International layout with an ANSI keyboard and type umlauts using key combinations like RALT + P for ö. For more information, see [this Reddit post](https://www.reddit.com/r/MechanicalKeyboards/comments/i4ybk6/using_german_umlaute_on_ansi_layout_via/).
However, this approach has some drawbacks. It includes dead keys, and for example, pressing the *quote* key may produce two *quote*, which can be particularly annoying, especially for coding.
Instead, you can use alt codes (see [Alt-Codes](https://www.alt-codes.net/german_alt_codes/)) to type umlauts while using the standard US layout.


### Notes
The current code is a quick solution and may require significant refactoring. It is provided in its current state to assist with creating your own custom keymap.
Partial code adaptations are from: https://gist.github.com/itspngu/9159f06153b440a754b33c6d65c5f302
