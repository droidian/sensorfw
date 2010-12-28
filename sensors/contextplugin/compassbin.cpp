/**
   @file compassbin.cpp
   @brief Compass Bin for ContextFW
   <p>
   Copyright (C) 2009-2010 Nokia Corporation

   @author Marja Hassinen <ext-marja.2.hassinen@nokia.com>
   @author Timo Rongas <ext-timo.2.rongas@nokia.com>

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
*/

#include "compassbin.h"
#include "contextplugin.h"
#include "sensord/sensormanager.h"

CompassBin::CompassBin(ContextProvider::Service& s, bool pluginValid):
    headingProperty(s, "Location.Heading"),
    compassChain(0),
    compassReader(10),
    headingFilter(&headingProperty),
    sessionId(0)
{
    if (pluginValid)
    {
        compassChain = SensorManager::instance().requestChain("compasschain");
        if (!compassChain)
        {
            sensordLogC() << "Unable to access Compass for heading property.";
        }

        add(&compassReader, "compass");
        add(&headingFilter, "headingfilter");

        // Create a branching filter chain
        join("compass", "source", "headingfilter", "sink");

        RingBufferBase* rb = compassChain->findBuffer("truenorth");
        if (!rb)
        {
            sensordLogC() << "Unable to connect to compass direction buffer.";
        }
        else
        {
            rb->join(&compassReader);
        }
    }

    // Listening for context property subscriptions
    connect(&headingProperty, SIGNAL(firstSubscriberAppeared(QString)), this, SLOT(startRun()));
    connect(&headingProperty, SIGNAL(lastSubscriberDisappeared(QString)), this, SLOT(stopRun()));
}

CompassBin::~CompassBin()
{
    RingBufferBase* rb = compassChain->findBuffer("truenorth");
    if (rb)
    {
        rb->unjoin(&compassReader);
    }
}

void CompassBin::startRun()
{
    // Get unique sessionId for this Bin.
    sessionId = SensorManager::instance().requestListenSensor("contextsensor");
    if (sessionId == INVALID_SESSION)
    {
        sensordLogC() << "Failed to get unique id for compass info via context.";
    }

    start();
    if (compassChain) {
        compassChain->start();
    }
}

void CompassBin::stopRun()
{
    if (compassChain) {
        compassChain->stop();
    }
    stop();

    SensorManager::instance().releaseSensor("contextsensor", sessionId);
}
