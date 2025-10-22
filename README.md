
# Bio-Skin multi-modal tactile sensor

Nice to see you here!

This document will help you to know how to make your own Bio-Skin tactile sensor. If you still don't know what is Bio-Skin, please check our project homepage for more detail: https://williamalexanda.github.io/Bio-Skin/




## About the open source

Hardware of Bio-Skin will be open sourced under the Creative Commons Attribution-NonCommercial 4.0 International License, which means it's open for personal NonCommercial usage only.

Hardware parts include all molds, materials list and code for Esp32. Without software in PC, you can still get the sensor raw data by following this tutorial: https://youtu.be/GShOp8S6hr8

If you want the software which includes super-resolution or GUI or have any other questions, please send a email(haoran.guo@okstate.edu) to get more information.

中文制作教程：https://www.bilibili.com/video/BV1KD8Tz4ERr/
## Open Source List
Hardware folder: including all molds, Sensor PCB and single MUX PCB. All electronic components are directly marked in the figure.

Software folder: The code for ESP32-S3, which includes control, sample and data transmission function.

Material list: All the material you need to make the Bio-Skin.


## License

This project is released under a split licensing model to ensure both the hardware designs and the software code remain open and reciprocal.

| Component | License | Copyleft Strength | Full Text |
| :--- | :--- | :--- | :--- |
| **Hardware Designs** (Schematics, PCB, CAD files) | **CERN Open Hardware Licence v2.0 - Strongly Reciprocal (CERN-OHL-S 2.0)** | Strong | [LICENSE-HARDWARE](./LICENSE-HARDWARE) |
| **Software** (Firmware, Control Code) | **GNU Affero General Public License v3.0 (AGPLv3)** | Strong (Network Usage) | [LICENSE-SOFTWARE](./LICENSE-SOFTWARE) |

**CERN-OHL-S 2.0:** Requires that any modifications to the hardware design files must also be shared under the same license.

**AGPLv3:** Requires that any changes to the software, even if used only as a network service, must have their source code made available to users.
