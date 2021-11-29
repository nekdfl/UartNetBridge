# Network bridge to uart on ESP chips

I did find chip ESP8266 is very intresting. It enouth of RAM and ROM to make network bridge from UART to network and have some WEB user interface for configure it.
It will be usfull for CNC GBRL machines and 3D printers and other projects.

### Worked fuatures

Telnet communication with LASERGRBL [https://github.com/arkypita/LaserGRBL](https://github.com/arkypita/LaserGRBL)

### Target fuatures

* Telnet support for LaserWeb [https://laserweb.yurl.ch/](https://laserweb.yurl.ch/)
* WebSocket support for LaserWeb
* WebSocket support for LaserGRBL

### Some code part got from here

[https://github.com/arkypita/ESP8266-SerialTelnet](https://github.com/arkypita/ESP8266-SerialTelnet).
<br>
### Programmer intrumments:

For develop this project used Microsoft VSCode (Visual Studio Code do not confused with Microsoft Visual Studio) with Platformio plugin.
After open project from platformio home (plagin) run build operation to download all required librarries
<br>
## This project provided as is without warranty of work

But we are doing hard work to make it work excelent