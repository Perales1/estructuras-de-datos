/**
 * @author David Fernández Espejo, dfe00004@red.ujaen.es
 * @author David Lorente Wagner, dlw00001@red.ujaen.es
 * @file UTM.cpp
 * @brief Implementación de la clase UTM
 */

#include "UTM.h"

UTM::UTM() : lat(0), lon(0) {}

UTM::UTM(float lat_, float lon_) : lat(lat_), lon(lon_) {}

float UTM::getLat() {
    return lat;
}

void UTM::setLat(float lat_) {
    lat = lat_;
}

float UTM::getLon() {
    return lon;
}

void UTM::setLon(float lon_) {
    lon = lon_;
}

bool UTM::operator==(const UTM &otro) const {
    return this->lat == otro.lat && this->lon == otro.lon;
}

bool UTM::operator!=(const UTM &otro) const {
    return !(*this == otro);
}