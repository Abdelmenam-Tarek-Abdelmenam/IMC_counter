#include <HTTPClient.h>

const String GOOGLE_SCRIPT_ID = "AKfycbw0velOfw9bhtoK1cBaKzN1Ph5c-A6urNqmB4_ciW2izKNhL_Weq8MRI2Mv3LSnS4wYFQ";


/*
  @berif  perform http get request to the google app script 
  @params request paramaters 
  @retVal the request payload  
*/
static String sendData(String params);


/*
  @berif  tell google script to enter new count mode
  @params  
  @retVal error state 
*/
bool startCountMode() {
  String payload = sendData("mode=neWCount");
  Serial.println(payload);
  return payload != "-1" ;
}


/*
  @berif  send the scanned id to google script to start count it 
  @params scanned id
  @retVal error state 
*/
bool countId(String id) {
  String payload = sendData("mode=count&id="  + id);
  Serial.println(payload);
  return payload != "-1" ;
}


/*
  @berif  send the id list to google script to store count it 
  @params ids : scanned id list 
          idsLen : lenght scanned id list 
          model : user define model for products with this id
  @retVal error state 
*/
bool storeIds(String ids[] , int idsLen , int model) {
  String idsStr = ids[0];
  for (int i = 1 ; i < idsLen ; i++) {
    idsStr += ("," + ids[i]) ;
  }

  String payload = sendData("mode=store&ids="  + idsStr + "&model=" + String(model));
  Serial.println(payload);
  return payload != "-1" ;
}


static String sendData(String params)
{
  HTTPClient http;
  int now = millis() ;
  String url = "https://script.google.com/macros/s/" + GOOGLE_SCRIPT_ID + "/exec?" + params;
  Serial.println("Making a request");
  Serial.println(url);
  http.begin( url );
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);

  int httpCode = http.GET();

  Serial.println(": done " + String(httpCode));
  Serial.print("Time taken is :"); Serial.println(millis() - now);

  String payload = http.getString();

  http.end();

  if (httpCode == HTTP_CODE_OK) {
    Serial.println(":OK ");
    return payload ;
  } else {
    return "-1";
  }

}
