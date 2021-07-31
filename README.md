# # Ds2vJoy
DualShock™ and DualSense™ to vJoy or ViGEm for Windows 64 bits only

Fork from @090 DS4vJoy and DS5vJoy projects
- Bluetooth compatible
- Vibration compatible (If you select vJoy or ViGEm from the game, the operation of DS4 will be reflected)
- Combinations, macros and time based operations allowed
- Control complex mouse operations
- HidGuardian included to let the game only see the needed vJoy or ViGEm joystick

## How to use
1. Install vJoy (https://sourceforge.net/projects/vjoystick/)
   * or not if you plan to use ViGEm
2. Open 'Configure vJoy' and select Axes, up to 128 Buttons and up to 4 continuous POV and effects
   * It may result in a PC restart.
3. Launch Ds2vJoy.exe
   * an .ini file will be created, to save parameters, with some examples already filled
   * and needed .dll, whose will be destroyed when you'll exit
4. Connect your PC and DS4/DS5 via USB or Bluetooth 
5. Configure as you wish (you have 3 profiles accessible by system tray)

- It is okay to connect DS4 after starting the game. VJoy and ViGEm are always visible in the game
- When you change a setting, Ds2vJoy.ini is automatically and instantly saved
- Ds2vJoy is portable, you can use multiple copy in different  directories with different parameters
- Install for ViGEm, HidGuardian and HidCerberus are included, they will use subdirectories of C:\Program Files\Ds2vJoy removed as soon as you chose to uninstall them from Ds2vJoy menu tabs, the same for C:\Program Files\Ds2vJoy itself when no required anymore
- You can see which button is pressed by launching Monitor vJoy but when under vJoy and ViGEm tabs, you can see them directly in status bar to easily test quick configurations

## Log
![Log](Doc/1.png)

## Settings
![Settings](Doc/2.png)

- Choose between preferred Sony® joypad, vJoy device in use
  - but for example if you chosen DS5 and only DS4 is connected this one will be in used
  - You may have to restart the program to change apply
- Usual Configurations
- Triggers mode (only works with DS5)
  - May be used only for touch pleasure
  - But in conjunction with L2, L2LOW, L2HIGH, L2FULL (same for R2),
  - you may use distinctly 2 or 3 separate actions on the same trigger
- You can specify a serial if you have multiples DS connected
  - or/and multiple copies of Ds2vJoy running
- You can fix threshold of sticks, and set times more accurate to your senses
  - Simultaneous is R1L1 or R2L2 the same time (with this 40ms as default delta)
- Multiple touchpad divide in multiple buttons,
  - But for more simple uses, there is multiple special buttons (see vJoy)
- Led is calm wave fluctuating, and can color be stopped on exit

## vJoy
![vJoy](Doc/3.png)

Each line correspond to a different mapping

Order, add, delete, copy or edit (double click or menu)

Mappings are treated in order,
- Then you can decide for complex actions or shifts
- For example you can use L1, and even L1R1 or more complex situations
- to determine which action square button will launch

DS Button:
- '+' Indicate combination
- '-' Indicate this mapping won't be launched if this button is pressed
- Already configured vJoy buttons can be used as source, in conjunctions with DS buttons

vJoy Button:
- See a brief of what will be launched like vJoy, mouse action (different from mouse) 

Tags:
  * I: if mouse is actually in use
  * F: force this mapping even if a source button has been disabled by another
  * S: short press
  * D: double press
  * L: long press
  * T: this is a toggle mapping
  * R: an action will be effected on release
  * M: if Mouse will be in used

## vJoy editing
![vJoy Editing](Doc/4.png)

- First row is source
- Solo is central led and battery status
- Eight ones are destination
- Group of checkboxes is for mouse
- Group of numbers is either for special mouse actions,
  - or to use mouse in a grid (divided or not) and not the full screen

Over first source you can find special requirements
- If mouse, if a mouse is already in use
- And Force, to ignore if a button has been disabled by a precedent mapping
  - double, this will work only if this mapping is already working

Over two next sources you'll find or/xor conditions instead of simple combination

Over two last sources you'll find not condition,
- The mapping won't be launched if this button is pressed
  - double, except if this mapping is already running

Destinations can be effected with time stamps for tricky actions, macros or combos
- Enter start (if not as soon as) or/and end (of not when release)
- If you enter an odd number, 0-9 milliseconds will be added, different each time
- Middle check box, is to begin the action on release
  - double, only the up press, even if some other timestamps are finished
  
Under each source and destination, you'll find disabling
- this button will be disabled for next mappings if this mapping is running (except with Force)
  - double (only destination), if time stamp is in use, disabling will be effective until whole mapping is finished instead this destination only

Under first source you'll find 3 checkboxes which determine the method
Checkboxes    | Method
------------- | --------------------------------------------------------------------
None          | Simple:        start when pressed, stop when release
First         | Short*:        you have to press and release quickly
Second        | Double:        you'll have to double press in a limited time
Third         | Long:          you have to stay pressed from a certain time
1 & 2         | Double short*: second press acting like short
2 & 2         | Double long:   second press acting like long
1 & 3         | Medium long:   like long but after double long
All           | Very long

  `* you'll have to use timestamp, otherwise you can simply use on release or go to timestamp too

In terms of time:
Method        | Press times
------------- | --------------------------------------------------------------------
Simple        | Immediate
Short         | found in settings
Double        | ~first press and second press < long
Long          | found in settings
Double        | ~first press and second press < long + second press duration < short
Double short* | ~first press and second press < long + second press duration > long
Medium long   | ~press > twice the time as long
Very long     | found in settings

Under central led, you'll find 2 checkboxes
- Macro: Interrupt macros on release (even if timestamp not finished)
  - double, pause this mapping while a not condition instead of interrupting
- Toggle: satisfy mapping conditions one time to start, second one to stop
  - double, destinations states begin activated at program launch
  - can be used to time based mouse actions too,
  - and for mouse if ACTIVE_MOUSE mouse action is used (see below)

At the left of first 4 destinations, you'll find special mouse actions
- ACTIVE_MOUSE: use to bring the chosen mouse
  - from the bottom group of checkboxes into the timestamp
  - and/or make it responsive to the toggle
- SAVE_POSITION: save the mouse position
- MOVE_BACK: return to saved point
- MOVE_TO_XY/MOVE_TO_WH: go to x,y/w,h (two left/central numbers of the grid)
- SAVE_AND_MOVE_TO_XY/SAVE_AND_MOVE_TO_WH: both
- LEFT_CLICK, MIDDLE_CLICK, RIGHT_CLICK, X1_CLICK, X2_CLICK, CROLL_UP, SCROLL_DOWN
- LEFT_DOUBLE_CLICK, MIDDLE_DOUBLE_CLICK, RIGHT_DOUBLE_CLICK, X1_DOUBLE_CLICK, X2_DOUBLE_CLICK, SCROLL_UP_x5, SCROLL_DOWN_x5
- LEFT_DOWN, MIDDLE_DOWN, RIGHT_DOWN, X1_DOWN, X2_DOWN
  - (long press, can use timestamp and on release)
- SCROLL_UP_VARIABLE, SCROLL_DOWN_VARIABLE
  - if on trigger, variable speed following the pressure force, otherwise exponential
	
The mouse group of checkboxes at the bottom, let you use mouse
- With left stick (left column)
- With the touchpad (central column)
- With the right stick (right column)

There is different modes for each
- Absolute, you move at a point which correspond to the coordinates of the stick or touchpad
- Mouse, as a normal mouse with acceleration
- Move (stick) or slow (touchpad), the same but adapted for game movements, or precise mouse
- Sniper (stick) or accuracy (touchpad), extreme precision
- Raid (stick) or grid (touchpad), move inside a zone whom coordinates are entered in numbers group at the right
- Last solo checkbox is for when you have together raid/grid and another mouse mode active, to determine which one is the default one

In this numbers group at the right
- left ones are for first points, central ones for second point,
- two last ones are to divide the zone in a grid, then you are always docked to a point of this grid (or whole screen)
 
A lot of buttons type has been added, for DS and for vJoy

RAW NAMES: LX, LY, RX, RY, L3, DPAD_LEFT, DPAD_UP, DPAD_RIGHT, DPAD_DOWN, SHARE, OPTIONS, SQUARE, TRIANGLE, CIRCLE, CROSS, R3, PS, TOUCH, MUTE, L1, R1, L2, R2, L2TRIGGER, R2TRIGGER, EMPTY, MIDDLE, FULL, LXINV, LYINV, RXINV, RYINV, AXISL_LEFT, AXISL_UP_LEFT, AXISL_UP, AXISL_UP_RIGHT, AXISL_RIGHT, AXISL_DOWN_RIGHT, AXISL_DOWN, AXISL_DOWN_LEFT, AXISR_LEFT, AXISR_UP_LEFT, AXISR_UP, AXISR_UP_RIGHT, AXISR_RIGHT, AXISR_DOWN_RIGHT, AXISR_DOWN, AXISR_DOWN_LEFT, TOUCHUP, TOUCHPAD, TOUCH1, TOUCH2, TOUCH3, TOUCH4, TOUCHL, TOUCHR, L2TRIGGER_33, R2TRIGGER_33, L2TRIGGER_66, R2TRIGGER_66, L2TRIGGER_100, R2TRIGGER_100, L1R1, L2R2, BATTERY
- Usual DS buttons classed by MMORPG action bar order
- Inversed Axis
- Multiple level Triggers (Normal L2 R2, Normal Triggers, ~33, 66 and 100% according to Proactive Triggers mode
- Different parts of the touchpad (all, Up, Only touch part, Left, Right and 4 corners)
- Cardinal Axis (for old games for example, instead of Dpad)
- Simultaneous presses, L1R1 L2R2 (you have a short - configurable - time to press both buttons same time, and will be released only when both will)
- Null, 50% value and full value, for your macros and tips (always on)
- Battery level

RAW NAMES: X, Y, Z, RX, RY, RZ, SL0, SL1, XTR, YTR, ZTR, RXTR, RYTR, RZTR, SL0TR, SL1TR, XINV, YINV, ZINV, RXINV, RYINV, RZINV, SL0INV, SL1INV, DPAD1_LEFT, DPAD1_UP_LEFT, DPAD1_UP, DPAD1_UP_RIGHT, DPAD1_RIGHT, DPAD1_DOWN_RIGHT, DPAD1_DOWN, DPAD1_DOWN_LEFT, DPAD2_LEFT, DPAD2_UP_LEFT, DPAD2_UP, DPAD2_UP_RIGHT, DPAD2_RIGHT, DPAD2_DOWN_RIGHT, DPAD2_DOWN, DPAD2_DOWN_LEFT, DPAD3_LEFT, DPAD3_UP_LEFT, DPAD3_UP, DPAD3_UP_RIGHT, DPAD3_RIGHT, DPAD3_DOWN_RIGHT, DPAD3_DOWN, DPAD3_DOWN_LEFT, DPAD4_LEFT, DPAD4_UP_LEFT, DPAD4_UP, DPAD4_UP_RIGHT, DPAD4_RIGHT, DPAD4_DOWN_RIGHT, DPAD4_DOWN, DPAD4_DOWN_LEFT
- Usual vJoy buttons
- Inversed Axis
- Triggered Axis (to transform lower start point to middle stability)
- Splitted Dpad, then you have unlimited capabilities instead of 1 to 1 Dpad affectation
  - Dpad use a mathematical medium function, then you can attribute other sources than normal ones
  - And instead having the result of for example Left + Up > Up Left
  - You can have it for Left + Up + UpRight + Right (which is mmm... let the program do it itself...)

An example of a simple advanced script for mouse:
```
  1st mapping: DS L2R2 + DS R2 activate right stick mouse
  2nd mapping: DS L2R2 - DS R2 activate right stick sniper
  Then as soon as you enter L2R2 your right stick is activated for mouse
    if you release only R2 you enter sniper mode,
    if you press back R2 you get again quick mouse
    until both L2 and R2 are released,
    which can therefore be used for usual actions
    (you may differ them 40ms and add -(simple)L2R2
```

An example of advanced script for targeting:
```
  1st mapping: DS L2R2 -(double) DS R2 active vJoy 128
    when you first press L2R2 nothing happen as R2 is pressed
    as soon as you release only R2, the conditions is respected, and then button 128 is pressed
    as R2 is double checked, it doesn't stop the mapping while already running,
    so until you release both L2 and R2, 128 stay pressed
    (you could even press R2 and release only L2 for other actions and come back after to only L2)
  2nd mapping: vJoy 128 + DS R2 do target forward target (you place on the button you wish)
  Do the same for the left, with button 127 and target backward target (you place on the button you wish)
    and then until you release Both L2 & R2, you can easily swap target
    and individual L2 and R2 stay free to be affected to usual actions
    (you may differ them 40ms and add -(simple)L2R2
```

![vJoy Help](Doc/5.png)

You can find this help directly in Ds2vJoy by pressing help below grid entries

## RapidFire
![RapidFire](Doc/6.png)

You can set repeated hits with the assigned vJoy button

Order, add, delete, copy or edit (double click or menu)

After the first time has passed, release and press repeatedly
- If you specify the simultaneous press condition,
- you can also enable repeated hits of the cross key and □ △ × ○, 
- for example, only when L2 or R2 is pressed

## RapidFire editing
![RapidFire Editing](Doc/7.png)

Removed DS4vJoy/DS5vJoy limits of time

## Keymap
![Keymap](Doc/8.png)

You can send a keydown when the button is pressed and a keyup when it is released

Order, add, delete, copy or edit (double click or menu)

## Keymap editing
![Keymap Editing](Doc/9.png)

- You can enter directly keys in the Enter Keycode part, or use Send Keycode choices (for advanced use)
- Send to, permit you to specify the process, and will ungrey (disabled)Find button
- If you check last checkbox, this will activate the window first (if post method is unsupported)

![Keymap Window Post](Doc/10.png)

You will find.

## ViGEm
![ViGEm](Doc/11.png)

Install, remove and use @nefarius &co ViGEm separately or jointly to vJoy
- Then you can have a fully remapped DS4 or X360
- Or a simple copy of DS4/DS5 to X360, to simplify compatibility problems
- Checkboxes are made to swap between DS or vJoy as source individually for each button

## Guardian
![Guardian](Doc/12.png)

Install, remove and use @nefarius &co HidGuardian and HidCerberus (and stop/start this service)
- A restart may be necessary after installing Guardian to have it properly running
- You can find link to manual configuration of Cerberus,
- In which you can verify the HID\ to enter in the blacklist section
- Then you can hide your DS4/DS5 and let see only the remapped DS4/X360 or vJoy to the system
- Whitelist section, bypass the guardian for programs you need to achieve this

## Links
![Links](Doc/13.png)

You'll find source of inspiration for this project

And you can enter from 1 to 5 programs name and location which can be launched after that through systray menu

## Tray
![Tray](Doc/14.png)

Picture talk by itself

## Efficiency
![Efficiency](Doc/15.png)

There is no resize but some other stuff

## Thanks
* https://github.com/090 (a lot)
* https://sourceforge.net/projects/vjoystick
* https://github.com/ViGEm/ViGEmBus
* https://github.com/ViGEm/ViGEmClient
* https://github.com/ViGEm/HidGuardian
* https://github.com/ViGEm/HidCerberus
* https://github.com/Jays2Kings/DS4Windows
* https://www.inputmapper.com
* http://www.wischik.com/lu/programmer/zip_utils.html
* https://github.com/stbrumme/crc32
* https://notepad-plus-plus.org
* http://www.planetpointy.co.uk/joystick-test-application
* https://github.com/microsoft/Windows-driver-samples/tree/master/setup/devcon

## Development environment
- Win10 64bit + Visual Studio 2019 (Community is fine)
- Sony® DualShock™ and DualSense™
- Intel® Wireless Bluetooth from Asus ROG
