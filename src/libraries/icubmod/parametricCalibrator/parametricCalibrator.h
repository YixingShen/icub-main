// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/**
 * @ingroup icub_calibrators
 * \defgroup parametricCalibrator
 *
 * Implement calibration routines for the iCub arm(s) (version 1.2).
 *
 * Copyright (C) 20014 iCub Facility, Istituto Italiano di Tecnologia
 *
 * Authors: Alberto Cardellino, Marco Randazzo, Valentina Gaggero
 *
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#ifndef __ICUB_PARAMETRIC_CALIBRATOR__
#define __ICUB_PARAMETRIC_CALIBRATOR__

#include <string>
#include <list>
#include <yarp/dev/DeviceDriver.h>
#include <yarp/os/Semaphore.h>
#include <yarp/dev/CalibratorInterfaces.h>
#include <yarp/dev/ControlBoardInterfaces.h>

namespace yarp {
    namespace dev
    {
        class parametricCalibrator;
    }
}

/**
 * \file eo_iCubArmCalibratorJ8.h
 * A device driver to implement the calibration of the Arm of iCub.
 */

/**
 * @ingroup dev_impl
 * 
 * A calibrator interface implementation for the Arm of the robot iCub.
 */
class yarp::dev::parametricCalibrator : public ICalibrator, public DeviceDriver, public IRemoteCalibrator
{
public:
    /**
     * Default constructor.
     */
    parametricCalibrator();

    /**
     * Destructor.
     */
    ~parametricCalibrator();

    /**
     * Calibrate method. Call this to calibrate the complete device.
     * @param dd is a pointer to the DeviceDriver to calibrate which must implement
     * the position control interfaces of the standard control board devices.
     * @return true if calibration was successful, false otherwise.
     */
    bool calibrate(DeviceDriver *dd);

    /**
     * Open the device driver.
     * @param config is a reference to a Searchable object which contains the initialization
     * parameters.
     * @return true/false on success/failure.
     */
    virtual bool open (yarp::os::Searchable& config);

    /**
     * Close the device driver.
     * @return true/false on success/failure.
     */
    virtual bool close ();

    virtual bool park(DeviceDriver *dd, bool wait=true);

    virtual bool quitPark();

    virtual bool quitCalibrate();

    // IRemoteCalibrator

    yarp::dev::IRemoteCalibrator *getCalibratorDevice();

    bool calibrateSingleJoint(int j);

    bool calibrateWholePart();

    bool homingSingleJoint(int j);

    bool homingWholePart();

    bool parkSingleJoint(int j, bool _wait=true);

    bool parkWholePart();

private:
    yarp::os::Semaphore calibMutex;

    bool calibrate();
    bool calibrateJoint(int j);
    bool goToZero(int j);
    bool checkCalibrateJointEnded(std::list<int> set);
    bool checkGoneToZero(int j);
    bool checkGoneToZeroThreshold(int j);
    bool checkHwFault(int j);

    yarp::dev::PolyDriver *dev2calibrate;
    IControlCalibration2 *iCalibrate;
    IPidControl *iPids;
    IEncoders *iEncoders;
    IPositionControl *iPosition;
    IControlMode2 *iControlMode;
    IAmplifierControl *iAmp;

    std::list<std::list<int> > joints;

    int n_joints;
    unsigned char *type;
    double *param1;
    double *param2;
    double *param3;
    int    *maxPWM;
    double *currPos;
    double *currVel;
    double *original_max_pwm;
    double *limited_max_pwm;
    double *zeroVel;
    double *zeroPos;
    double *homeVel;
    double *homePos;
    double *zeroPosThreshold;
    bool    abortCalib;
    bool    abortParking;
    bool    isCalibrated;
    bool    skipCalibration;
    bool    clearHwFault;

    std::string deviceName;
};
#endif
