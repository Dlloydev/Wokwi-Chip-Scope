# Wokwi-Chip-Scope

## Description

This 4 channel scope chip allows you to graph four analog or digital signals as they vary over time.

- Scope `Sample Time μs` range is 10µs to 10000 ms (default 100 µs).

- Width of plot is 250 samples.

- Trigger Channel selector (0-3) for analog or digital signals, default 0

- `Trigger` modes are Off (`0`) Rising (default) ⬆ and Falling ⬇

- Displays analog volts`Vmax`, and volts `Vmin`

- Displays  Sample Raye `S/s` and Capture Time `ms`

- Displays Trigger Channel selection `>`

- Displays Frequency Hz and Duty of digital signals 

- Default control settings (below) can be changed in `diagram.json` 

  ```json
        "attrs": {
          "mySampleTimeUs": "100",
          "mySampleTimeMs": "0",
          "myTriggerChannel": "0",
          "myTriggerMode": "1"
        }
  ```

  ![image](https://user-images.githubusercontent.com/63488701/225511219-88cb7d44-6541-4598-9401-b627d5cc918f.png)



![image](https://user-images.githubusercontent.com/63488701/225989409-f13bb610-c9eb-4df7-a969-b8c1cd27d1c5.png)

| Name           | Description                                       |
| -------------- | ------------------------------------------------- |
| D0, D1, D2, D3 | Digital INPUTs, located on left side of the chip. |
| A0, A1, A2, A3 | Analog INPUTs, located on right side of the chip. |

If both a digital and analog signal are connected for the same channel, then the analog signal will be shown on the screen if any analog voltage is detected. In this case, the minimum volts may start at 1.0V due to activity of the digital signal. If the analog signal is set to 0.0 volts, then the digital signal will be shown.

For digital signals, the frequency (Hz) and duty (%) is calculated for the selected channel for trigger. Just select each channel for trigger to lock in on its signal and display the calculated parameters.

In the image above, D0 is selected for trigger shown by `>`. The analog voltage for the slide pot is not shown, as it is adjusted to minimum (0V). The signal generator is connected to A3 and the sine wave is displayed, If this analog signal is adjusted to 0.0 volts, then the waveform on channel D3 will be shown.

## Usage

To use this chip in your project, include it as a dependency in your `diagram.json` file:

```json
  "dependencies": {
    "chip-scope": "github:Dlloydev/Wokwi-Chip-scope@1.0.4"
  }
```

Then, add the chip to your circuit by adding a `chip-scope` item to the `parts` section of `diagram.json`:

```json
  "parts": {
    ...,
    {
      "type": "chip-scope",
      "id": "scope1",
      "top": -100.0,
      "left": 100.0,
      "attrs": {
        "mySampleTimeUs": "100",
        "mySampleTimeMs": "0",
        "myTriggerChannel": "0",
        "myTriggerMode": "1"
      }
    },
```

The actual source code for the chip lives in [src/main.c](https://github.com/Dlloydev/Wokwi-Chip-Scope/blob/main/src/main.c), and the pins are described in [chip.json](https://github.com/Dlloydev/Wokwi-Chip-Scope/blob/main/chip.json).

## Example

[![Wokwi_badge](https://user-images.githubusercontent.com/63488701/212449119-a8510897-c860-4545-8c1a-794169547ba1.svg)](https://wokwi.com/projects/359330496025635841) Graph four analog or digital signals as they vary over time.

## License

This project is licensed under the MIT license. See the [LICENSE](https://github.com/Dlloydev/Wokwi-Chip-Scope/blob/main/LICENSE) file for more details.
