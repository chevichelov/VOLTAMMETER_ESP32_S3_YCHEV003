#pragma once
#include <Arduino.h>

//CSS файл
const char style_css[] PROGMEM = R"rawliteral(
    @media screen and (max-width:600px) {
      #download{
        margin-top:0;
      }
    }
    @media screen and (min-width:600px) {
      #download{
        margin-top:2rem;
      }
    }
    #menu {
      text-align: right;
      
    }
    #menu a{
      margin-top:1rem;
      font-family: 'Open Sans', sans-serif;
      font-size: 1rem;
      line-height: 1.5;
      color: #000;
      font-weight: 100;
      -webkit-font-smoothing: antialiased;
      -webkit-text-size-adjust: 100%;
      bottom: 10px;
      letter-spacing: 4px;
      font-size: 12px;
      text-transform: uppercase;
      text-decoration: none;
    }
    #menu a {
      display: inline-block;
      position: relative;
      padding: 0 1rem 0 1rem;
      transition: color .35s ease;
    }
    #menu a:before {
      content: '';
      display: block;
      position: absolute;
      left: 0;
      bottom: 0;
      height: 2px;
      width: 0;
      transition: width 0s ease, background .35s ease;
    }
    #menu a:after {
      content: '';
      display: block;
      position: absolute;
      right: 0;
      bottom: 0;
      height: 2px;
      width: 0;
      background: #000;
      transition: width .35s ease;
    }
    #menu a:hover:before {
      width: 100%;
      background: #000;
      transition: width .35s ease;
    }
    #menu a:hover:after {
      width: 100%;
      background: transparent;
      transition: all 0s ease;
    }
    h2 {
      font-size: 26px;
      margin: 20px 0;
      text-align: center;
      small {
      font-size: 0.5em;
      }
    }
    li {
      border-radius: 3px;
      padding: 25px 30px;
      display: flex;
      justify-content: space-between;
      margin-bottom: 25px;
    }
    .table-header {
      background-color: #95A5A6;
      font-size: 14px;
      text-transform: uppercase;
      letter-spacing: 0.03em;
    }
    .table-row {
      background-color: #ffffff;
      box-shadow: 0px 0px 9px 0px rgba(0,0,0,0.1);
    }
    .col-1 {
      flex-basis: 40%;
    }
    .col-2 {
      flex-basis: 10%;
    }
    .col-3 {
      flex-basis: 25%;
    }
    .col-4 {
      flex-basis: 25%;
    }
    .col-4 a{
      color: #000;
    }
    @media all and (max-width: 767px) {
      .table-header {
        display: none;
      }
      .table-row{
      }
      li {
        display: block;
      }
      .col {
        flex-basis: 100%;
      }
      .col {
        display: flex;
        padding: 10px 0;
        &:before {
        color: #6C7A89;
        padding-right: 10px;
        content: attr(data-label);
        flex-basis: 50%;
        text-align: right;
        }
      }
    }
    .container_settings{
      display: flex;
      justify-content: center;
    })rawliteral";


//Главная страница
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="ru">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="icon" href="data:image/x-icon;base64,AAABAAEAEBAAAAEAIABoBAAAFgAAACgAAAAQAAAAIAAAAAEAIAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAADf9f7/3/T+/+D1/f/g9f3/4PX9/+D1/f/G8d7/wfDY/8Dx2P/I8uH/w/LX/8jy3P/l+P7/5fj+/+f6/v/V7vz/4fb+/+H2/v/h9v7/3/b7/7/w1f/C8dj/3Pb3/+H2/v/h9/3/2/b0/8Ty1/+88c3/wPLP/9/48//i9v7/e6Xb/+L3/v/i9/7/2PXx/73x0v/i9v3/4vf+/+L3/v/i9/7/4vj+/+L4/v/l+P7/5fj7/8Hyzv++8sr/pc7q/z5lmv/k9/7/4ff8/73x0f/j9/7/5Pf+/+T3/v/k+P7/5fj+/+T4///k+P//5fj//+b5/v/o+f7/xfPP/6Lbxf9kj8b/5Pf+/8Py1v/k9/z/5ff+/+X4///m+P7/3uXk/9jX0v/c4+H/4Orr/+X2+//m+f//6fr+/+j6+P/A8sr/uuTe/+T3/f/D8tf/5ff9/+X3/v/m+P7/5vj+/+Dp6f/W0sj/1M7E/827qv/c4t//5vn+/+n6/v/p+/7/yfTW/9P22v/S9Of/wuTt/5u++f+Lsfn/ss/7/77Z+//P5vz/3PH8/+P2/f/n+f3/5/n9/+f6/v/p+v//6vv+/9L24P/q+vX/xvLb/9Xr/P+bvfn/ZpT6/5G1+f+Tt/r/gar5/5G1+f+PtPn/mbz5/6TE+v+kxfv/sc77/9Dm/P/p+vn/0vbe/8by2v/m+P7/5vj+/93x/P/M5Pz/xN77/67N/P+uzPr/m736/57A+v+QtPn/qMf6/2+b+f9/p/r/0un0/9X34f/Y9ev/0fTm/+b5/v/n+f7/6Pn+/+f5/v/n+f//5/n//+n4/f/p+f3/4vT9/9/y/f++2Pz/v9r7/7bi2f/u+/v/xfLW/8Xy1f/n+f7/6Pn//+n5///o+f//6Pn//+j5///p+f//6fn//+n5///q+v//7Pv+/+z7/v/L9Nb/8Pz+/9L15P+98cv/4Pf0/+j5///p+f//6vn//+n5///p+f//6fn//+n5///q+v//6vr//+z7/v/g+e//1vbj//D8/v/q+P7/wvLQ/8Hyz//n+Pz/6vn//+v5///q+f//6fn//+n5///p+f//6vr//+v6/v/o+vj/yfTT/+77/v/w/P7/6vn+/+b4+/+98cr/wvLP/9/38P/s+v7/6/r//+v6///r+f//6vn//+r6/v/c9+3/yfPT/+/7/v/v+/7/8Pz+/+v4///q+P//6fn8/8Xy0v++8cn/yvPW/8v02f/V9uT/1Pbk/8v02P/K89f/2Pbl/+76/v/v+///7/v+//D8/v/s+f//6/n//+z5/v/s+v7/3ffr/8702v/t+f3/4/jx/+P48//t+v7/7fn+/+76/v/u+v7/7/v//+/7/v/w/P7/AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA==" type="image/x-icon">
    <link rel="stylesheet" href="/css/styles.css" type="text/css" />
</head>
<body>
  <div id="menu">
    <a href="/">Логи</a> 
    <a href="/settings">Настройки</a>
  </div>
  <div class="container">
    <h2>Логи</h2>
    <ul class="responsive-table">
    <li class="table-header">
      <div class="col col-1">Файл</div>
      <div class="col col-2">Размер</div>
      <div class="col col-3">Дата</div>
      <div class="col col-4">Открыть</div>
    </li>
    <div id="files"></div>
    </ul>
  </div>
  <script type="application/javascript">
    function load() {
      var HTML = '';
      var trueRequest = new XMLHttpRequest();
      trueRequest.open('GET', '/log', true);
      trueRequest.onload = function() {
        JSON.parse(this.response, function (key, value) {
          if (key == 'NAME'){
            HTML += '<li class="table-row">';
            HTML += '<div class="col col-1" data-label="Файл">' + value + '</div>';
          }
          if (key == 'SIZE'){
            HTML += '<div class="col col-2" data-label="Размер">' + value + '</div>';
          }
          if (key == 'DATE'){
            HTML += '<div class="col col-3" data-label="Дата">' + value + '</div>';
          }
          if (key == 'DOWNLOAD'){
            HTML += '<div class="col col-4" data-label="Открыть"><a href="/files?file=' + value + '">' + value + '</a></div>';
            HTML += '</li>';
          }
        });
        document.getElementById("files").innerHTML = HTML;
      };
      trueRequest.send();
    }
    load();
  </script>
</body>
</html>)rawliteral";

//Страница настроек
const char settings_html[] PROGMEM = R"rawliteral(<!DOCTYPE html>
<html lang="ru">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="icon" href="data:image/x-icon;base64,AAABAAEAEBAAAAEAIABoBAAAFgAAACgAAAAQAAAAIAAAAAEAIAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAADf9f7/3/T+/+D1/f/g9f3/4PX9/+D1/f/G8d7/wfDY/8Dx2P/I8uH/w/LX/8jy3P/l+P7/5fj+/+f6/v/V7vz/4fb+/+H2/v/h9v7/3/b7/7/w1f/C8dj/3Pb3/+H2/v/h9/3/2/b0/8Ty1/+88c3/wPLP/9/48//i9v7/e6Xb/+L3/v/i9/7/2PXx/73x0v/i9v3/4vf+/+L3/v/i9/7/4vj+/+L4/v/l+P7/5fj7/8Hyzv++8sr/pc7q/z5lmv/k9/7/4ff8/73x0f/j9/7/5Pf+/+T3/v/k+P7/5fj+/+T4///k+P//5fj//+b5/v/o+f7/xfPP/6Lbxf9kj8b/5Pf+/8Py1v/k9/z/5ff+/+X4///m+P7/3uXk/9jX0v/c4+H/4Orr/+X2+//m+f//6fr+/+j6+P/A8sr/uuTe/+T3/f/D8tf/5ff9/+X3/v/m+P7/5vj+/+Dp6f/W0sj/1M7E/827qv/c4t//5vn+/+n6/v/p+/7/yfTW/9P22v/S9Of/wuTt/5u++f+Lsfn/ss/7/77Z+//P5vz/3PH8/+P2/f/n+f3/5/n9/+f6/v/p+v//6vv+/9L24P/q+vX/xvLb/9Xr/P+bvfn/ZpT6/5G1+f+Tt/r/gar5/5G1+f+PtPn/mbz5/6TE+v+kxfv/sc77/9Dm/P/p+vn/0vbe/8by2v/m+P7/5vj+/93x/P/M5Pz/xN77/67N/P+uzPr/m736/57A+v+QtPn/qMf6/2+b+f9/p/r/0un0/9X34f/Y9ev/0fTm/+b5/v/n+f7/6Pn+/+f5/v/n+f//5/n//+n4/f/p+f3/4vT9/9/y/f++2Pz/v9r7/7bi2f/u+/v/xfLW/8Xy1f/n+f7/6Pn//+n5///o+f//6Pn//+j5///p+f//6fn//+n5///q+v//7Pv+/+z7/v/L9Nb/8Pz+/9L15P+98cv/4Pf0/+j5///p+f//6vn//+n5///p+f//6fn//+n5///q+v//6vr//+z7/v/g+e//1vbj//D8/v/q+P7/wvLQ/8Hyz//n+Pz/6vn//+v5///q+f//6fn//+n5///p+f//6vr//+v6/v/o+vj/yfTT/+77/v/w/P7/6vn+/+b4+/+98cr/wvLP/9/38P/s+v7/6/r//+v6///r+f//6vn//+r6/v/c9+3/yfPT/+/7/v/v+/7/8Pz+/+v4///q+P//6fn8/8Xy0v++8cn/yvPW/8v02f/V9uT/1Pbk/8v02P/K89f/2Pbl/+76/v/v+///7/v+//D8/v/s+f//6/n//+z5/v/s+v7/3ffr/8702v/t+f3/4/jx/+P48//t+v7/7fn+/+76/v/u+v7/7/v//+/7/v/w/P7/AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA==" type="image/x-icon">
    <link rel="stylesheet" href="/css/styles.css" type="text/css" />
</head>
<body>
  <div id="menu">
    <a href="/">Логи</a> 
    <a href="/settings">Настройки</a>
  </div>
  <div class="container_settings">
    <table>
      <tbody>
        <tr>
          <td colspan="2" align="center" id="notification" style="background-color:#FFFFFF;height:30px;">
          </td>
        <tr>
        <tr>
          <td>
            Пароль от WI-FI сети:
          </td>
          <td>
            <input id="password" />
          </td>
        </tr>
        <tr>
          <td>
            Текущее время:
          </td>
          <td>
            <input id="time" /><input type="checkbox" id="is_time" checked />
          </td>
        </tr>
        <tr>
          <td>
            Коррекция амперметра CH1:
          </td>
          <td>
            <input id="ch1" />
          </td>
        </tr>
        <tr>
          <td>
            Коррекция амперметра CH2:
          </td>
          <td>
            <input id="ch2" />
          </td>
        </tr>
        <tr>
          <td>
            Коррекция амперметра CH3:
          </td>
          <td>
            <input id="ch3" />
          </td>
        </tr>
        <tr>
          <td style="text-align:right;">
            <input type="submit" id="save" value="Сохранить" />
          </td>
          <td>
          </td>
        </tr>
      </tbody>
    </table>
  </div>
  <script type="application/javascript">
  function add_zero(namber) {
    if (namber < 10) {
      return "0" + namber;
    }
    return namber;
  }
  let date = new Date();
  document.getElementById("time").value = "" + date.getFullYear() + "-" + add_zero(date.getMonth()) + "-" + add_zero(date.getDate()) + " " + add_zero(date.getHours()) + ":" + add_zero(date.getMinutes()) + ":" + add_zero(date.getSeconds());
  setInterval(() => { 
    if (document.getElementById("is_time").checked) {
      date = new Date(); 
      document.getElementById("time").value = "" + date.getFullYear() + "-" + add_zero(date.getMonth()) + "-" + add_zero(date.getDate()) + " " + add_zero(date.getHours()) + ":" + add_zero(date.getMinutes()) + ":" + add_zero(date.getSeconds()); 
    }
  }, 1000);
    
  function clear() {
    document.getElementById('notification').innerHTML       = '';
    document.getElementById('notification').style.background  = '#FFFFFF';
  }

  document.getElementById('save').onclick = function()
  {
    var PASSWORD  = document.getElementById("password").value,
      TIME        = document.getElementById("time").value.replace(' ', '_'),
      CH1         = document.getElementById("ch1").value.replace(/,/, '.'),
      CH2         = document.getElementById("ch2").value.replace(/,/, '.'),
      CH3         = document.getElementById("ch3").value.replace(/,/, '.');

    if (PASSWORD.length < 8 || PASSWORD.length > 63)
    {
      document.getElementById('notification').innerHTML       = '<div>Длина пароля должна быть больше или равна 8, но меньше или ровна 63 символам!</div>';
      document.getElementById('notification').style.background  = '#FF0000';
      return false;
    }
    var trueRequest = new XMLHttpRequest();
    trueRequest.open('GET', '/setting?password=' + PASSWORD + '&time=' + TIME + '&ch1=' + CH1 + '&ch2=' + CH2 + '&ch3=' + CH3, true);
    trueRequest.onload = function() {
      if (this.status == 200){
        document.getElementById('notification').innerHTML       = '<div>Сохранено!</div>';
        document.getElementById('notification').style.background  = '#00FF00';
        setTimeout(() => {
          clear();
        }, 1000);
      }
      if (this.status == 400){
        document.getElementById('notification').innerHTML       = '<div>Длина пароля более 63 символов!</div>';
        document.getElementById('notification').style.background  = '#FF0000';
        setTimeout(() => {
          clear();
        }, 1000);
      }
    }
    trueRequest.send();
  } 

  const inputs = Array.prototype.slice.call(
    document.querySelectorAll('.ipaddress')
  );

  inputs.forEach((input) => {
    input.addEventListener('keyup', (event) => {
      if (input.value > 255) {
      input.value = 255;
      }
    });
    input.addEventListener('keypress', (event) => {
      if (!(event.keyCode < 48 || event.keyCode > 57)) { // Only allow numbers
      if (input.value.length >= input.maxLength) {
        event.preventDefault();
        focusNext();
      }
      } else {
      event.returnValue = false;
      }
    });
  });

  function focusNext() {
    const currInput     = document.activeElement;
    const currInputIndex  = inputs.indexOf(currInput);
    const nextinputIndex  = (currInputIndex + 1) % inputs.length;
    const input       = inputs[nextinputIndex];
    input.focus();
  }
  function load() {
    var trueRequest = new XMLHttpRequest();
    trueRequest.open('GET', '/loadsetting', true);
    trueRequest.onload = function() {
      JSON.parse(this.response, function (key, value) {
      if (key == 'PASSWORD'){
        document.getElementById("password").value = value;
      } else if (key == 'CH1'){
        document.getElementById("ch1").value = value;
      } else if (key == 'CH2'){
        document.getElementById("ch2").value = value;
      } else if (key == 'CH3'){
        document.getElementById("ch3").value = value;
      }
      });
    };
    trueRequest.send();
  }
  load();
  </script>
</body>
</html>)rawliteral";
