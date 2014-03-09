function sett() {
  console.log("#Set method called");
  
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
  
  var burl = new XMLHttpRequest();
  burl.open('GET', "https://api.bitcoinaverage.com/all", true);
  burl.onload = function(e) {
    if(burl.readyState == 4 && burl.status == 200) {
      var response = JSON.parse(burl.responseText);
      
      var price = response.USD.averages.bid;
      console.log("price is " + price);
    }
  };
  burl.send(null);
}

Pebble.addEventListener("ready",
  function(e) {
    console.log("JavaScript app ready and running!");
    
    sett();
  }
);