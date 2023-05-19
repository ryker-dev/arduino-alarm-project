# arduino-alarm-project
A group project for the embedded systems course.

## Building projects
The solution consists of multiple projects. You can build projects individually by clicking the project name (alarm-mega or alarm-uno) in the solution viewer on the right side of the Microchip UI. Then go to the top toolbar and select Build -> Build alarm-uno. After this use a custom external tool command preset to send the build to the board.

## Sending the build to the boards
To send the build to a board, you must create an external tool preset in Microchip Studio. Go to the top toolbad and select Tools -> External Tools and add a new command preset.

- Insert a name for the preset in the *Title* field.
- Add path to AVRDUDE in the *Command* field. `.\avrdude\avrdude.exe` AVRDUDE is included in the repository files for ease of use and is taken from an open source project under the GPL 2.0 license.
- Add the command arguments to the *Arguments* field. This depends on the board you are using:

UNO:  `-C ".\avrdude\avrdude.conf" -p atmega328p -c arduino -P COM3 -b 115200 -U flash:w:"$(ProjectDir)Debug\$(TargetName).hex":i`

MEGA: `-v -C ".\avrdude\avrdude.conf" -p atmega2560 -c wiring -P COM4 -b 115200 -D -U flash:w:$(TargetDir)$(TargetName).hex:i`

❗ Make sure to change the COM port to the right one. This may change depending the computer you are using ❗

- Finally tick the *Use Output window* box to see the possible errors through the Microchip terminal.
