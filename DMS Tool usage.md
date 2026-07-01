# General

DMS Tool is a utility from daktronics for display setup and diagnostics for windows. We will use it for uploading new configuration and fonts to the display.

The tool can be downloaded from [ Daktronics](https://dakfiles.daktronics.com/downloads/Transportation/Utilities/DMS%20Tool.zip) . Extract the zip to a directory, the tool doesn't need installing. You will need a usb-rs232 adapter or hardware rs232 port on the computer. It might be possible to just bridge the rs232 connection over tcp but I haven't tried it yet.

If you want to update the fonts grab the [Rev 2.5.zip](https://dakfiles.daktronics.com/downloads/Transportation/Firmware/AF-670x%20Controller%20(236-237)/Rev%202_5.zip) from Daktronics and find the fonts in `Fonts/Fonts 2/AF\ Bold\ FF1002-0004` and `Fonts/Fonts 3/AF Fixed FF1003-0004`. The new fixed config is at `config/new-config.hex`. The config fixes the definition for the upper corner line, sets frame rate to 300Hz and defaults the display protocol to 1.
# Display setup

Open the dms tool application and press the `Add Displays` button:
![[add_displays.png]]

Enter the display details and click `Done` 
![[display_settings.png]]

Click the `Add` button to add a unit:
![[add_display.png]]

You should see the new display unit:
![[created_display.png]]

Right click it and choose `Edit` from the context menu:
![[context_menu_not_connected.png]]

Set the address, set the connection type to serial and select the correct serial port and baud-rate:
![[unit_settings.png]]

Click `Connect` and `Done` when done. The display should now be connected and show something like this:
![[connected_unit.png]]

Right-click and from the context menu choose `Upload firmware`:
![[context_menu_connected.png]]

Select the files you want to send to the display:
![[upload_firmware.png]]

Click on the `Upload` button and then wait...
![[uploading.png]]