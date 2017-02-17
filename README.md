# sumo_revamp

This repo is for the revamp of the mini sumo robot which placed 1st at the 2015 IEEE Student Activities Conference and 1st at the Pitt Design Expo under the Student Club Category.

The revamped version will compete in the 2016 IEEE Student Activities Conference.

Rules for this competition can be found here: http://media.wix.com/ugd/7fe387_8af9a80701e34a4dbb4a95af3a744282.pdf

You need Quentins encoder mod cloned into your arduinos library folder
https://github.com/QuentinTorg/EncoderMod.git



Definitions of Encoders:
Front Left = 1
Front Right = 2
Back Left = 3
Back Right = 4

## Teensy Setup:

Follow the steps found here: https://www.pjrc.com/teensy/td_download.html

Go here: https://www.pjrc.com/teensy/49-teensy.rules and save as 49-teensy.rules

On linux: run `chmod +x /path/to/TeensyduinoInstall.linux64` to create the executable (replace 32 with 64 or ARM)

Then run the Teensy installer and direct it to the Arduino directory
