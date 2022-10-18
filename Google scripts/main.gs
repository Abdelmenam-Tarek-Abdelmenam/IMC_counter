const sheetID = "1pO78v_U0dzZnKo3HkPSkXrltO0F5510lzsbcmMpYbLk"
const ss = SpreadsheetApp.openByUrl("https://docs.google.com/spreadsheets/d/" + sheetID + "/edit");
const database = ss.getSheets()[0];
const logs = ss.getSheets()[1];


function doGet(e) {
  if (e != null) {

    mode = e.parameters.mode


    if (mode == "neWCount") {
      var dateTime = new Date();
      var row = logs.getLastRow() + 1;
      logs.getRange("A" + row).setValue(dateTime.toLocaleDateString());
      logs.getRange("B" + row).setValue("New count begin");

      return ContentService.createTextOutput("New count values begin now");
    }
    else if (mode == "count") {

      id = e.parameters.id;
      if (id != null) {
        var result = countId(id);
        return ContentService.createTextOutput(result).setMimeType(ContentService.MimeType.JSON);

      } else {

        return ContentService.createTextOutput("-1");
      }
    } else if (mode == "store") {
      ids = e.parameters.ids;
      model = e.parameters.model;
      if (ids != null && model != null) {
        ids = ids.toString().split(",");
        storeIds(ids, model);
        return ContentService.createTextOutput("Strore " + ids.length + " ids  With model " + model);
      } else {
        return ContentService.createTextOutput("-1");
      }
    } else {
      return ContentService.createTextOutput("-1");
    }
  }
  else {
    Logger.log("No parameters to excute code");
  }
}

