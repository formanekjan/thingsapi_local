#include "License.h"

LicenseProperty::LicenseProperty() {
  
}

LicenseProperty::LicenseProperty(String type, String owner, String metadata) {
  this->type = type;
  this->owner = owner;
  this->metadata = metadata;
}

LicenseProperty::toJSONObject(JsonObject& root) {
  root["type"] = type;
  root["owner"] = owner;
  root["metadata"] = metadata;
}