var xhrRequest = function (url, type, callback) {
  var xhr = new XMLHttpRequest();
  xhr.onload = function () {
    callback(this.responseText);
  };
  xhr.open(type, url);
  xhr.send();
};

function locationSuccess(pos)  {
  
  //construct URL
  
  var url = "https://maps.googleapis.com/maps/api/place/nearbysearch/json?location=" +
      pos.coords.latitude + "," + pos.coords.longitude + 
      "&rankby=distance&types=restaurant&key=AIzaSyAdjwtsTRvZmiPden6haSVlEdIvlQaDmQg";
  
  console.log(url);
  
  //Send Request to Google
  
  xhrRequest(url, 'GET',
            function(responseText)  {
              
              // responseText contains a JSON object with places
              
              var json = JSON.parse(responseText);
              console.log(JSON.parse(responseText));
              
              
              //Log Name
              
              var name = json.results[0].name;
              console.log("Name is " + name);
              

  
  var dictionary = {
  "KEY_NAME" : name
};
  
  //Send to Pebble
Pebble.sendAppMessage(dictionary,
                     function(e)  {
                       console.log("Info sent to Pebble!");
                     },
                     function(e)  {
                       console.log("Error sending info");
                     }
                     );
}
                         
      );
}


function locationError(err)  {
  console.log("Error requesting location!");
}

function getPlaces()  {
  navigator.geolocation.getCurrentPosition(
  locationSuccess,
  locationError,
    {timeout: 15000, maximumAge: 60000}
  );
}


// Listen for when the watchface is opened
Pebble.addEventListener('ready', 
  function(e) {
    console.log("PebbleKit JS ready!");
    
    getPlaces();
  }
);

// Listen for when an AppMessage is received
Pebble.addEventListener('appmessage',
  function(e) {
    console.log("AppMessage received!");
  }                     
);