void routesConfiguration() {

  // Example of a 'standard' route
  server.on("/index.html", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html", "text/html");
  });

  // Duplicated serving of index.html route, so the IP can be entered directly to browser.
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html", "text/html");
  });


  // Example of linking to an external file
  server.on("/arduino.css", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/arduino.css", "text/css");
  });


  // Example of a route with additional authentication (popup in browser)
  // And uses the processor function.
  server.on("/dashboard.html", HTTP_GET, [](AsyncWebServerRequest * request) {
    if (!request->authenticate(http_username, http_password))
      return request->requestAuthentication();
    request->send(SPIFFS, "/dashboard.html", "text/html", false, processor);
  });

  // Example of route with authentication, and use of processor
  // Also demonstrates how to have arduino functionality included (turn LED on)
  //turns siren on 
  server.on("/Sirenon", HTTP_GET, [](AsyncWebServerRequest * request) {
    if (!request->authenticate(http_username, http_password))
      return request->requestAuthentication();
   logEvent("Sirenon");
   emergencyservicesActive=true;
    request->send(SPIFFS, "/dashboard.html", "text/html", false, processor);
  });

//turns siren off 
server.on("/Sirenoff", HTTP_GET, [](AsyncWebServerRequest * request) {
    if (!request->authenticate(http_username, http_password))
      return request->requestAuthentication();
    logEvent("Sirenoff");
    emergencyservicesActive=false;
    request->send(SPIFFS, "/dashboard.html", "text/html", false, processor);
  });

  // when someone presses siren off the speaker will stop making the beeping noise.
  
  // Example of route which sets file to download - 'true' in send() command.
  //downloads logevent
  server.on("/logOutput", HTTP_GET, [](AsyncWebServerRequest * request) {
    logEvent("output");
    request->send(SPIFFS, "/logEvents.csv", "text/html", true);
  });
}

//Date and time code
String getDateTime() {
   DateTime rightNow = rtc.now();
  char csvReadableDate[25];
  sprintf(csvReadableDate, "%02d:%02d:%02d %02d/%02d/%02d,",  rightNow.hour(), rightNow.minute(), rightNow.second(),rightNow.day(),rightNow.month(),rightNow.year());
  return csvReadableDate;
}

String processor(const String& var) {
  /*
     Updates the HTML by replacing set variables with return value from here.
     For example:
     in HTML file include %VARIABLEVALUE%.
     In this function, have:
      if (var=="VARIABLEVALUE") { return "5";}
  */
  
if(var == "DATETIME") {
  String datetime= getDateTime();
  return datetime;
}

  // Default "catch" which will return nothing in case the HTML has no variable to replace.
  return String();
}
