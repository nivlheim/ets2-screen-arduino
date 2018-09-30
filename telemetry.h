struct fuelDataStruct {
  int current;
  int max;
  int range;
};

struct engineDataStruct {
  bool enabled;
  int rpm;
  int maxRpm;
};

struct speedDataStruct {
  int speed;
  int cruiseControlSpeed;
};

struct telemetryDataStruct {
  engineDataStruct engine;
  fuelDataStruct fuel;
  speedDataStruct speed;
};

void saveTelemetryData(telemetryDataStruct& telemetryData, JsonObject& root) {
  telemetryData.engine.enabled = root["engine"]["enabled"];
  telemetryData.engine.rpm = root["engine"]["rpm"];
  telemetryData.engine.maxRpm = root["engine"]["maxRpm"];

  telemetryData.fuel.current = root["fuel"]["current"];
  telemetryData.fuel.max = root["fuel"]["max"];
  telemetryData.fuel.range = root["fuel"]["range"];

  telemetryData.speed.speed = root["speed"]["speed"];
  telemetryData.speed.cruiseControlSpeed = root["speed"]["cruiseControlSpeed"];
}
