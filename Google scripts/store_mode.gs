function storeIds(ids, model) {
  name = findName(model);

  for (i in ids) {
    Logger.log(ids[i])
    checkId(ids[i]);
    saveData(ids[i], name, model);
  }

  Logger.log("Store ids " + ids + " with model " + model);
}

function saveData(id, name, model) {
  var dateTime = new Date();
  var row = database.getLastRow() + 1;
  // Start Populating the data
  database.getRange("A" + row).setValue(dateTime.toLocaleDateString());
  database.getRange("B" + row).setValue(id);
  database.getRange("C" + row).setValue(model);
  database.getRange("D" + row).setValue(name);

}

function checkId(id) {
  var column = database.getRange("B:B").getValues();
  for (var i = 0; i < column.length; i++) {
    if (column[i][0] == id) {
      database.deleteRow(i+1)
      return ;
    }
  }
}

function findName(model) {
  var column = database.getRange("C:C").getValues();
  var index = null;
  for (var i = 0; i < column.length; i++) {
    if (column[i][0] == model) {
      index = i + 1;
      data = database.getRange(index, 1, 1, 4).getValues()[0]
      var name = data[3]
      return name;
    }
  }
  return "";
}