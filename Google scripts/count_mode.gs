function countId(id) {

  var map = getlastCount()
  items = map.items;
  dataLen = map.lastItem + 1;


  if (!isNaN(id)) id = parseInt(id)
  idModel = findId(id);
  if (idModel != "") {
    var oldVal = items[idModel]
    if (oldVal == null) {
      logs.getRange("B" + dataLen).setValue(idModel);
      logs.getRange("C" + dataLen).setValue(1);
      items[idModel] = new ItemValue(1, dataLen)
    } else {
      items[idModel].value = parseInt(oldVal.value) + 1;
      logs.getRange("C" + items[idModel].index).setValue(items[idModel].value);
    }
  }


  for (i in items) {
    items[i] = items[i].value;
  }
  return JSON.stringify(items);
}


function getlastCount() {
  var len = logs.getLastRow();
  var column = logs.getRange("B:C").getValues();
  for (var i = len - 1; i >= 0; i--) {
    if (column[i][0] == "New count begin") {
      var newList = (column.slice(i + 1, len));
      var newMap = {};
      for (var index in newList) {
        item = newList[index]

        newMap[item[0]] = new ItemValue(item[1], parseInt(index) + parseInt(i) + 2);
      }
      return new returnItems(newMap, len);
    }

  }
}

function findId(id) {
  var column = database.getRange("B:B").getValues();
  for (var i = 0; i < column.length; i++) {
    if (column[i][0] == id) {
      index = i + 1;

      data = database.getRange(index, 1, 1, 5).getValues()[0]
      var model = data[2];
      var date = data[4];
      if (date != null && date != "") {
        return "";
      } else {
        var dateTime = new Date();
        database.getRange("E" + index).setValue(dateTime.toLocaleDateString());
      }
      return model;
    }
  }
  return ""
}

class ItemValue {
  constructor(value, index) {
    this.value = value;
    this.index = index;
  }
}

class returnItems {
  constructor(items, lastItem) {
    this.items = items;
    this.lastItem = lastItem;
  }
}
