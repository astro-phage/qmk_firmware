# Custom Keychron Q5 Max Firmware (ANSI Encoder)

## ✨ Features & Changes

### 1. The "Control Switch" (Caps Lock) Layer

The physical Caps Lock key has been repurposed into a Momentary Layer Toggle (`MO(WIN_CTRL)`). Holding Caps Lock activates a custom layer with the following features:

- **Umlauts (Swiss Style):**
    - `Caps Lock` + `[` = **ü** (or **Ü** if holding Shift)
    - `Caps Lock` + `;` = **ö** (or **Ö** if holding Shift)
    - `Caps Lock` + `'` = **ä** (or **Ä** if holding Shift)

- **Media Knob:** Turning the encoder wheel while holding Caps Lock skips to the Previous/Next track.
- **Sleep:** Pressing the 2nd key to the left of the knob puts the computer to sleep.

---

### 2. Standard Layer Tweaks

- **Calculator:** The 3rd key to the left of the knob opens the Calculator on Windows.
- **Volume Knob:** The encoder wheel handles volume up/down by default.
- **Play/Pause:** Pressing the encoder knob plays or pauses media.
- **Num Pad:** Press **Fn + ESC (Num PAD key)** to toggle Num Pad on and off.

---

### 3. Escape Hatch: Real Caps Lock

Because Caps Lock is now a layer modifier, standard Caps Lock functionality was moved to the `WIN_FN` layer.

- Press **Fn + Caps Lock** to toggle standard ALL CAPS on and off.

---

## 🛠 Prerequisites (Windows Setup)

To compile and flash this firmware on Windows, you need the QMK CLI toolchain installed.

1. Download and install **QMK MSYS** from the official GitHub releases:
   https://github.com/qmk/qmk_distro_msys/releases

2. Open the QMK MSYS terminal.

3. Run the setup command to pull down the required compilers:

Navigate to your firmware folder (for example):

```bash
cd /c/Repos/qmk_firmware
```

Ensure submodules are up to date (fixes the ChibiOS "No such file or directory" error):

```bash
make git-submodule
```

---

## 🚀 Building & Flashing the Keyboard

1. Open your QMK MSYS terminal and navigate to your `qmk_firmware` directory.

2. Run the flash command:

```bash
qmk flash -kb keychron/q5_max/ansi_encoder -km via
```

The terminal will compile the code and eventually pause, waiting for a bootloader.

### Put the keyboard into DFU/Flash mode:

1. Unplug the USB cable.
2. Press and hold the **Esc** key.
3. Plug the USB cable back in while still holding Esc.
4. Release the Esc key after 1–2 seconds.

The terminal will automatically detect the keyboard, erase the old firmware, and install this custom build.  
**Do not unplug the keyboard during this process.**

Wait for the keyboard to restart and the RGB lights to turn back on.

---

## 📁 File Structure & Modifications

If you need to edit this layout later, the modified files are located in:

```
keyboards/keychron/q5_max/ansi_encoder/keymaps/via/
```

### Modified Files

- **keymap.c**  
  Contains the layer arrays, custom C logic for the Umlaut macros, and the updated encoder press for play/pause.

- **rules.mk**  
  Enabled:
    - `VIA_ENABLE`
    - `ENCODER_ENABLE`
    - `ENCODER_MAP_ENABLE`

- **config.h**  
  Custom file created specifically to:

```c
#define DYNAMIC_KEYMAP_LAYER_COUNT 5
```

This allows the firmware to use the additional `WIN_CTRL` layer.
