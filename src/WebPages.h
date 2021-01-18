const char CONFIG_PAGE[] PROGMEM = R"=====(
<HTML>
 <HEAD>
   <TITLE>Lossnay Controller v2</TITLE>
 </HEAD>
 <BODY>
  <form action="/settings" method="get">
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
 "in_temp":%.1f,
 "in_humidity":%.1f,
 "in_abs_humidity":%.2f,
 "out_temp":%.1f,
 "out_humidity":%.1f,
 "out_abs_humidity":%.2f,
 "bypass":%s,
 "power":%s,
 "fan_speed":%d
})=====";
