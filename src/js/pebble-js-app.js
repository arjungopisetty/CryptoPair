function sett() {
  console.log("#Set method called");
  
  /*
  var url = new XMLHttpRequest();
  url.open('GET', 'http://www.cryptocoincharts.info/v2/api/listCoins', true);
  url.onload = function(e) {
    console.log("in onload");
    if(url.readyState == 4 && url.status == 200) {
      var response = JSON.parse(url.responseText);
      
      var name = response[2].name;
      var price = response[2].price_btc;
      var volume = response[2].volume_btc;
      
      Pebble.sendAppMessage({
        "name": name,
         "price": price,
         "volume": volume,
      });
    }
  };
  url.send(null);
  */
  var response = HTTPGET("https://api.bitcoinaverage.com/all");
  
  var json = JSON.parse(response);
  
  var price = json.USD.averages.bid;
  console.log("price: " + price);
  
  var dict = {"KEY_PRICE" : price};
     
  // Send data to watch for display
  Pebble.sendAppMessage(dict);
}

function HTTPGET(url) {
    var req = new XMLHttpRequest();
    req.open("GET", url, false);
    req.send(null);
    return req.responseText;
}

Pebble.addEventListener("ready",
  function(e) {
    console.log("JavaScript app ready and running!");
    sett();
  }
);

Pebble.addEventListener("appmessage",
  function(e) {
	//Watch wants new data!
	sett();
  }
);