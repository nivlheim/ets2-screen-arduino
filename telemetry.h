struct fuelDataStruct {
  int current;
  int max;
  int range;
};

struct telemetryDataStruct {
  bool engineEnabled;
  fuelDataStruct fuel;
};

void saveTelemetryData(telemetryDataStruct& telemetryData, JsonObject& root) {
  telemetryData.engineEnabled = root["engine"]["enabled"];

  telemetryData.fuel.current = root["fuel"]["current"];
  telemetryData.fuel.max = root["fuel"]["max"];
}