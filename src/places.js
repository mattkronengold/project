var type;
var location;
var json;

var xhrRequest = function (url, type, callback) {
  var xhr = new XMLHttpRequest();
  xhr.onload = function () {
    callback(this.responseText);
  };
  xhr.open(type, url);
  xhr.send();
};


function locationSuccess(pos)  {
  
   console.log("Retrieving names from Google API.");
  
  //construct URL
  
  var url = "https://maps.googleapis.com/maps/api/place/nearbysearch/json?location=" +
      pos.coords.latitude + "," + pos.coords.longitude + 
      "&rankby=distance&types=" + type + "&key=AIzaSyAdjwtsTRvZmiPden6haSVlEdIvlQaDmQg";
  
  //console.log("URL1: " + url);
  
  //Send Request to Google
  
  xhrRequest(url, 'GET',
            function(responseText)  {
              
              // responseText contains a JSON object with places
              
              json = JSON.parse(responseText);
              
              //Log Name
              
              var k = 0;
              var numplaces = 0;
              
              var name = [];
              
              while(json.results[k] && k < 10)
                {
                  name.push(json.results[k].name);
                  k++;  
                }
              
              numplaces = k;
              
              while(k < 10)
                {
                  name.push("UNDEFINED");
                  k++;
                }
              
  var dictionary = {
      "KEY_NAME1" : name[0],
      "KEY_NAME2" : name[1],
      "KEY_NAME3" : name[2],
      "KEY_NAME4" : name[3],
      "KEY_NAME5" : name[4],
      "KEY_NAME6" : name[5],
      "KEY_NAME7" : name[6],
      "KEY_NAME8" : name[7],
      "KEY_NAME9" : name[8],
      "KEY_NAME10" : name[9],
      "KEY_NUM_PLACES" : numplaces,

};
  
  //Send to Pebble
Pebble.sendAppMessage(dictionary,
                     function(e)  {
                       console.log("Names sent to Pebble!");
                     },
                     function(e)  {
                       console.log("Error sending names");
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

function getInfo()
{
  console.log("Retrieving details from Google API");
  
  var placeID = json.results[location].place_id;
  //construct URL
  
  var url = "https://maps.googleapis.com/maps/api/place/details/json?placeid=" + placeID + "&key=AIzaSyAdjwtsTRvZmiPden6haSVlEdIvlQaDmQg";
  
  //console.log("URL2: " + url);
  
  
  //Send Request to Google
  
  xhrRequest(url, 'GET',
            function(responseText)  {
              
              // responseText contains a JSON object with places
              
              var json2 = JSON.parse(responseText);
              
              // save info
              
              var address = json2.result.formatted_address;
              var phone = json2.result.formatted_phone_number;
              
              var hours;
              
              hours = "open_";
              
              try
                {
                  hours += json2.result.opening_hours.open_now.valueOf();
                }
              
              catch(err)
                {
                  hours = "no_hours";
                }
                
              
              console.log("Sending Details:");
              console.log(hours);
              console.log(address);
              console.log(phone);
              
  var dictionary = {
    "KEY_ADDRESS" : address,
    "KEY_PHONE" : phone,
    "KEY_HOURS" : hours,
    };
  
  //Send to Pebble
              
Pebble.sendAppMessage(dictionary,
                     function(e)  {
                       console.log("Details sent to Pebble!");
                     },
                     function(e)  {
                       console.log("Error sending details");
                     }
                     );
}
                         
      );
}

Pebble.addEventListener('appmessage',
  function(e) {
    console.log("PebbleKit JS has received message.");
    type = e.payload.KEY_TYPE;
    location = e.payload.KEY_PLACE;
    location--;

    if(e.payload.KEY_TYPE)
      {
      getPlaces();
      }
    
    if(e.payload.KEY_PLACE)
      {
      getInfo();
      }
      
  }
);