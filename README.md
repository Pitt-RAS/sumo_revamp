# sumo_revamp

This repo is for the revamp of the mini sumo robot which placed 1st at the 2015 IEEE Student Activities Conference and 1st at the Pitt Design Expo under the Student Club Category.

The revamped version will compete in the 2017 IEEE Student Activities Conference.

Rules for this competition can be found here: http://media.wix.com/ugd/7fe387_8af9a80701e34a4dbb4a95af3a744282.pdf


## SETUP:
### Teensy Setup:

Follow the steps found here: https://www.pjrc.com/teensy/td_download.html

Go here: https://www.pjrc.com/teensy/49-teensy.rules and save as 49-teensy.rules before running the udev thing on the previous link

On linux: run `chmod +x /path/to/TeensyduinoInstall.linux64` to create the executable (replace 64 with 32 or ARM)

Then run the Teensy installer and direct it to the Arduino directory

### Encoder:
Clone this mod of encoder into your Arduino library: https://github.com/Pitt-RAS/Encoder

Definitions of Encoders:
Front Left = 1
Front Right = 2
Back Left = 3
Back Right = 4

## TODO
* [x] dulplicate the battery checking feature that runs at startup to check x periodically while it's running so we don't discharge our batteries too much while we test (would be removed during competition)
* [ ] settle on design
* [ ] order parts
