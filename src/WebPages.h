const char CONFIG_PAGE[] PROGMEM = R"=====(
<HTML>
 <HEAD>
   <TITLE>Lossnay Controller v2</TITLE>
 </HEAD>
 <BODY>
  <form action="/settings" method="get">
   %s<br><br>
   %s<br><br>
   %s<br><br>
   %s<br><br>
   <br><br>
   <input type="submit" value="Save" style='width: 150px;'>
   &nbsp;&nbsp;&nbsp;
   <a href="/reboot">
    <button type="button" style='width: 150px;'>Restart</button>
   </a>
  </form>
 </BODY>
</HTML>
)=====";

const char GET_JSON[] PROGMEM = R"=====({
 "ra_temp":%.1f,
 "ra_humidity":%.1f,
 "ra_pressure":%.0f,
 "ra_abs_humidity":%.2f,
 "sa_temp":%.1f,
 "sa_humidity":%.1f,
 "sa_pressure":%.0f,
 "sa_abs_humidity":%.2f,
 "bypass":%s,
 "power":%s,
 "fan_speed":%d
})=====";

const char HELP_PAGE[] PROGMEM = R"=====(
/settings -> settings page<br>
/get -> get current state<br>
/on -> turn the unit on<br>
/off -> turn the unit off<br>
/mode?[lossnay|bypass] -> set heat recovery/bypass mode<br> 
/speed?[1|2|3|4] -> set the fan speed<br>
/help -> this page
)=====";
