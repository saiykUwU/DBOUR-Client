//**********************************************************************
//
// Copyright (c) 2004
// PathEngine
// Lyon, France
//
// All Rights Reserved
//
//**********************************************************************

#ifndef SURFACE_TYPE_COSTS_INCLUDED
#define SURFACE_TYPE_COSTS_INCLUDED

#include "libs/Mesh3D/interface/tMesh_3D_Header.h"
#include "libs/Geometry/interface/tPoint_Header.h"
#include "libs/ParseXML/interface/iXMLHandler.h"
#include "common/STL/vector.h"

class cTranslationToOverlapped;
class iMovementCostCalculator;
class cCornerProvider;
class iOutputStream;
class iXMLOutputStream;

class cSurfaceTypeCosts
{
    const std::vector<long>* _surfaceTypesVector;
    long _topSurfaceType;
    std::vector<float> _costs;
    std::vector<tPoint> _costDirections;
    long _numberSet;

public:

    // the surface types vector and mesh pair must be constant over the lifetime of this object
    cSurfaceTypeCosts(const std::vector<long>* surfaceTypesVector, long topSurfaceType);
    cSurfaceTypeCosts(const std::vector<long>* surfaceTypesVector); // this version finds the top surface type
                        
    void save(iXMLOutputStream& os) const;

    bool empty() const
    {
        return _numberSet == 0;
    }

    void setCost(long surfaceType, float value);
    void setCostDirection(long surfaceType, const tPoint& value);

    void buildCornersAndCostCalculator(
                    tMesh_3D& mesh3D,
                    const cTranslationToOverlapped& translation,
                    iMovementCostCalculator*& calculator,
                    cCornerProvider& corners);

    void checksum(iOutputStream& os) const;
};

class cSurfaceTypeCostsLoader : public iXMLHandler
{
    cSurfaceTypeCosts* _target;

public:

    cSurfaceTypeCostsLoader()
    {
        _target = 0;
    }
    void setTarget(cSurfaceTypeCosts* target)
    {
        _target = target;
    }

// interface for iXMLHandler
    iXMLHandler* element(const char* el, const char *const* attributes);
};

class cSurfaceTypeCostsVectorLoader : public iXMLHandler
{
    std::vector<long>*& _surfaceTypesVector;
    std::vector<cSurfaceTypeCosts*>& _target;
    cSurfaceTypeCostsLoader _targetLoader;

public:

    cSurfaceTypeCostsVectorLoader(
                        std::vector<long>*& surfaceTypesVector,
                        std::vector<cSurfaceTypeCosts*>& target
                        ) :
      _surfaceTypesVector(surfaceTypesVector),
      _target(target)
    {
    }

// interface for iXMLHandler
    iXMLHandler* element(const char* el, const char *const* attributes);
};


#endif
