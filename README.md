# sumo_revamp

This repo is for the revamp of the mini sumo robot which placed 1st at the 2015 IEEE Student Activities Conference and 1st at the Pitt Design Expo under the Student Club Category.

The revamped version will compete in the 2017 IEEE Student Activities Conference.

Rules for this competition can be found here: https://sac17.rowanieee.org/index.php?p=competitions#tabs-2


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
* [x] Software: dulplicate the battery checking feature that runs at startup to check x periodically while it's running so we don't discharge our batteries too much while we test (would be removed during competition)
* [ ] Hardware: settle on design
* [ ] Hardware: order parts
* [ ] Hardware: kill switch
* [ ] Software: Create modes for display, debug, competition

## DESIGN QUESTIONS
* [ ] With 4 wheels, what is the mechanical effect of losing two wheels
* [x] How much time do we get if we don't have to deploy > Not worth it, bot becomes too small
* [ ] How to arrange sensors
