/**
   @file orientationdata.h
   @brief Datatypes for different filters

   <p>
   Copyright (C) 2009-2010 Nokia Corporation

   @author Joep van Gassel <joep.van.gassel@nokia.com>
   @author Timo Rongas <ext-timo.2.rongas@nokia.com>
   @author Ustun Ergenoglu <ext-ustun.ergenoglu@nokia.com>

   This file is part of Sensord.

   Sensord is free software; you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License
   version 2.1 as published by the Free Software Foundation.

   Sensord is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with Sensord.  If not, see <http://www.gnu.org/licenses/>.
   </p>

  @todo Split datatypes into separate files or rename this to something more
        generic.<br>
        Drop out unnecessary typedefs.
 */

#ifndef ORIENTATIONDATA_H
#define ORIENTATIONDATA_H

#include <QMetaType>

#include <datatypes/genericdata.h>

typedef TimedXyzData AccelerationData;
typedef TimedXyzData MagneticFieldData;
typedef TimedXyzData AngularVelocityData;

typedef TimedXyzData OrientationData;
typedef TimedXyzData MagnetometerData;

/**
 * @brief Container for calibrated magnetic field measurements.
 *
 */
class CalibratedMagneticFieldData : public TimedData {
public:
    CalibratedMagneticFieldData() : TimedData(0),
                                    x_(0), y_(0), z_(0),
                                    rx_(0), ry_(0), rz_(0),
                                    level_(0) {}

    CalibratedMagneticFieldData(quint64 timestamp, int x, int y, int z, int rx, int ry, int rz, int level) :
        TimedData(timestamp),
        x_(x), y_(y), z_(z),
        rx_(rx), ry_(ry), rz_(rz),
        level_(level) {}

    CalibratedMagneticFieldData(TimedXyzData magData, int level) :
        TimedData(magData.timestamp_),
        x_(0), y_(0), z_(0),
        rx_(magData.x_), ry_(magData.y_), rz_(magData.z_),
        level_(level) {}

    int x_;
    int y_;
    int z_;
    int rx_;
    int ry_;
    int rz_;

    int level_;                   /**< Magnetometer calibration level */
};

/**
 * @brief Container for Compass measurements.
 *
 * Holds measurement timestamp, compass direction and magnetometer calibration
 * level.
 */
class CompassData : public TimedData {
public:
    CompassData() : TimedData(0), degrees_(0), level_(0) {}

    CompassData(quint64 timestamp, int degrees, int level) :
        TimedData(timestamp), degrees_(degrees), level_(level) {}

    int degrees_; /**< Angle to north */
    int level_;   /**< Magnetometer calibration level */
};

#endif // ORIENTATIONDATA_H