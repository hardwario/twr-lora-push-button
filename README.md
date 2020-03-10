<a href="https://www.hardwario.com/"><img src="https://www.hardwario.com/ci/assets/hw-logo.svg" width="200" alt="HARDWARIO Logo" align="right"></a>

# Firmware for HARDWARIO Lora Push Button

[![Travis](https://img.shields.io/travis/bigclownlabs/bcf-lora-push-button/master.svg)](https://travis-ci.org/bigclownlabs/bcf-lora-push-button)
[![Release](https://img.shields.io/github/release/bigclownlabs/bcf-lora-push-button.svg)](https://github.com/bigclownlabs/bcf-lora-push-button/releases)
[![License](https://img.shields.io/github/license/bigclownlabs/bcf-lora-push-button.svg)](https://github.com/bigclownlabs/bcf-lora-push-button/blob/master/LICENSE)
[![Twitter](https://img.shields.io/twitter/follow/hardwario_en.svg?style=social&label=Follow)](https://twitter.com/hardwario_en)

This repository contains firmware for LoraWan push button

## Description

The unit measures the temperature and count events button click and button hold.
Values is sent every 60 minutes over LoRaWAN. Values are the arithmetic mean of the measured values since the last send.

Measure interval for temperature is 60s. The battery is measured during transmission.

## Buffer
big endian

| Byte   | Name        | Type   | Factor   | Unit
| -----: | ----------- | ------ | -------- | -------
|      0 | HEADER      | uint8  |          |
|      1 | BATTERY     | uint8  | x 0.1    | V
|      2 | ORIENTATION | uint8  |          |
|  3 - 4 | TEMPERATURE | int16  | x 0.1    | °C
|  5 - 6 | CLICK COUNT | uint16 |          |
|  7 - 8 | HOLD COUNT  | uint16 |          |

### Header

* 0 - bool
* 1 - update
* 2 - button click
* 3 - button hold

## AT

```sh
picocom -b 115200 --omap crcrlf  --echo /dev/ttyUSB0
```

## License

This project is licensed under the [MIT License](https://opensource.org/licenses/MIT/) - see the [LICENSE](LICENSE) file for details.

---

Made with &#x2764;&nbsp; by [**HARDWARIO s.r.o.**](https://www.hardwario.com/) in the heart of Europe.
