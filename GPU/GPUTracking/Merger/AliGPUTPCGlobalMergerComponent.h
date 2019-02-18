//-*- Mode: C++ -*-
// $Id$
// ************************************************************************
// This file is property of and copyright by the ALICE HLT Project        *
// ALICE Experiment at CERN, All rights reserved.                         *
// See cxx source for full Copyright notice                               *
//                                                                        *
//*************************************************************************


#ifndef ALIHLTTPCCAGLOBALMERGERCOMPONENT_H
#define ALIHLTTPCCAGLOBALMERGERCOMPONENT_H

/// @file   AliGPUTPCGlobalMergerComponent.h
/// @author Matthias Kretz
/// @date
/// @brief  HLT TPC CA global merger component.
///

#ifndef GPUCA_ALIROOT_LIB
#define GPUCA_ALIROOT_LIB
#endif

#include "AliHLTProcessor.h"
#include "AliHLTComponentBenchmark.h"
#include "AliGPUParam.h"

class AliGPUTPCGMMerger;
class AliGPUReconstruction;
class AliGPUChainTracking;

/**
 * @class AliGPUTPCGlobalMergerComponent
 * The TPC global merger component
 *
 * Interface to the global merger of the CA tracker for HLT.
 */
class AliGPUTPCGlobalMergerComponent : public AliHLTProcessor
{
  public:
    /**
     * Constructs a AliGPUTPCGlobalMergerComponent.
     */
    AliGPUTPCGlobalMergerComponent();

    /**
     * Destructs the AliGPUTPCGlobalMergerComponent
     */
    virtual ~AliGPUTPCGlobalMergerComponent();

    // Public functions to implement AliHLTComponent's interface.
    // These functions are required for the registration process

    /**
     * @copydoc AliHLTComponent::GetComponentID
     */
    const char *GetComponentID();

    /**
     * @copydoc AliHLTComponent::GetInputDataTypes
     */
    void GetInputDataTypes( AliHLTComponentDataTypeList &list );
    int GetOutputDataTypes(AliHLTComponentDataTypeList& tgtList);

    /**
     * @copydoc AliHLTComponent::GetOutputDataType
     */
    AliHLTComponentDataType GetOutputDataType();

    /**
     * @copydoc AliHLTComponent::GetOutputDataSize
     */
    virtual void GetOutputDataSize( unsigned long& constBase, double& inputMultiplier );

    /**
     * @copydoc AliHLTComponent::Spawn
     */
    AliHLTComponent *Spawn();
    
    static const AliGPUTPCGMMerger* GetCurrentMerger();

  protected:

    // Protected functions to implement AliHLTComponent's interface.
    // These functions provide initialization as well as the actual processing
    // capabilities of the component.

    /**
     * @copydoc AliHLTComponent::DoInit
     */
    int DoInit( int argc, const char **argv );

    /**
     * @copydoc AliHLTComponent::DoDeinit
     */
    int DoDeinit();

    /** reconfigure **/
    int Reconfigure( const char* cdbEntry, const char* chainId );

    /**
     * @copydoc @ref AliHLTProcessor::DoEvent
     */
    int DoEvent( const AliHLTComponentEventData &evtData, const AliHLTComponentBlockData *blocks,
                 AliHLTComponentTriggerData &trigData, AliHLTUInt8_t *outputPtr,
                 AliHLTUInt32_t &size, AliHLTComponentBlockDataList &outputBlocks );

    using AliHLTProcessor::DoEvent;

  private:

    static AliGPUTPCGlobalMergerComponent fgAliGPUTPCGlobalMergerComponent;

    // disable copy
    AliGPUTPCGlobalMergerComponent( const AliGPUTPCGlobalMergerComponent & );
    AliGPUTPCGlobalMergerComponent &operator=( const AliGPUTPCGlobalMergerComponent & );

    /** set configuration parameters **/
    void SetDefaultConfiguration();
    int ReadConfigurationString(  const char* arguments );
    int ReadCDBEntry( const char* cdbEntry, const char* chainId );
    int Configure( const char* cdbEntry, const char* chainId, const char *commandLine );

    /** the global merger object */

    double fSolenoidBz;  // magnetic field
    double fClusterErrorCorrectionY; // correction for the cluster error during pre-fit
    double fClusterErrorCorrectionZ; // correction for the cluster error during pre-fit
	int fNWays; //Setting for merger
    char fNWaysOuter; //Store outer param after n-way fit
    bool fNoClear;  //Do not clear memory after processing an event
    static const AliGPUChainTracking* fgCurrentMergerReconstruction; //Pointer to current merger in case memory is not cleared after processing the event
    AliHLTComponentBenchmark fBenchmark;// benchmark
    AliGPUParam fParam; //ca params
    AliGPUReconstruction* fRec; //AliGPUReconstruction
    AliGPUChainTracking* fChain;

    ClassDef( AliGPUTPCGlobalMergerComponent, 0 )
};

#endif //ALIHLTTPCCAGLOBALMERGERCOMPONENT_H
