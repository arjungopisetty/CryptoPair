function sett() {
  console.log("#Set method called");
  
  var url = new XMLHttpRequest();
  url.open('GET', 'http://www.cryptocoincharts.info/v2/api/listCoins', true);
  url.onload = function(e) {
    console.log("in onload");
    if(url.readyState == 4 && url.status == 200) {
      var response = JSON.parse(url.responseText);
      //var exchange = response.USD.averages.keys().length;
      //console.log("thisisreal " + exchange);
      
      var result = response[2].name;
      console.log("name " + result);
    }
  }
  url.send(null);
}

Pebble.addEventListener("ready",
  function(e) {
    console.log("JavaScript app ready and running!");
    
    sett();
  }
);