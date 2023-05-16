#ifndef IIMUSENSORCALIBRATION_H
#define IIMUSENSORCALIBRATION_H

template <typename T>
class IIMUSensorCalibration
{
public:
    virtual ~IIMUSensorCalibration() {}
    virtual bool initialize() = 0;
    virtual bool isFullyCalibrated() = 0;
    virtual void retrieveOffsets(T &calibrationData) = 0;
};

#endif
