//----------------------------------------------------------------------------------
//! The ML module class PDFUtils.
/*!
// \file    PDFUtils.h
// \author  Axel Newe (axel.newe@fau.de)
// \date    2015-10-29
//
// Utilities for PDF creation.
*/
//----------------------------------------------------------------------------------


#pragma once


#ifndef _PDFUtils_H
#define _PDFUtils_H


// Local includes
#include "MLPDFSystem.h"
#include "../shared/MLPDF_Tools.h"

// ML includes
#include <mlModuleIncludes.h>
#include <mlXMarkerList.h>
#include <IndexPairList.h>
#include <ColoredMarkerList.h>
#include <mlFiberSet.h>

// WEM includes
#include <WEMBase/WEM.h>
#include <WEMBase/WEMModuleBase/WEMProcessor.h>


ML_START_NAMESPACE


//////////////////////////////////////////////////////////////////////////
//! Utilities for PDF creation.
class MLPDF_EXPORT PDFUtils : public WEMProcessor
{
  //! Implements interface for the runtime type system of the ML.
  ML_MODULE_CLASS_HEADER(PDFUtils)

public:

  //! Constructor.
  PDFUtils (std::string type="PDFUtils");

protected:

  //! Destructor.
  virtual ~PDFUtils();

  //! Initialize module after loading.
  virtual void activateAttachments();

  //! Handle field changes of the field \c field.
  virtual void handleNotification (Field* field);

  //! _process()-routine for correct processing.
  virtual void _process();

  //! Called when the inputWEM has changed
  virtual void _inWEMChanged();

private:

  /* FIELDS */

  // Input fields for point sets and line sets
  BaseField *_inPointPositionsFld;
  BaseField *_inLinePositionsFld;
  BaseField *_inLineConnectionsFld;

  // Output fields (WEM output is for free...)
  BaseField*   _outFibersFld;

  //! Inventor camera fields (needed for calculation of PDF view camera from Inventor camera settings)
  NotifyField*   _calculateCameraFromInventorSceneFld;
  BoolField*     _autoCalculateCameraFromInventorSceneFld;
  Vector3Field*  _inventorCameraPositionFld;
  Vector4Field*  _inventorCameraOrientationFld;
  FloatField*    _inventorCameraFocalDistanceFld;
  FloatField*    _inventorCameraHeightFld;

  //! Fields for SoVertexProperty and SoIndexedLineSet
  StringField*   _vertexListFld;
  StringField*   _coordIndexListFld;

  //! PDF view camera fields
  Vector3Field*  _cameraCenterOfOrbitFld;
  Vector3Field*  _cameraCenterToCameraFld;
  FloatField*    _cameraRadiusOfOrbitFld;
  FloatField*    _cameraRollAngleFld;
  FloatField*    _cameraFOVAngleFld;

  //! Fields for creating views
  StringField*   _viewSpecificationsFld;
  StringField*   _newViewDisplayNameFld;
  ColorField*    _newViewBackgroundColorFld;
  EnumField*     _newViewLightingSchemeFld;
  NotifyField*   _addNewViewFld;
  NotifyField*   _clearViewsFld;

  //! Fields for WEM/mesh handling
  StringField*   _selectedWEMPatchFld;
  IntField*      _selectedWEMPatchIdFld;
  StringField*   _availableWEMPatchesFld;
  StringField*   _selectedWEMPatchNewLabelFld;

  //! Fields for specification generator
  StringField*   _newSpecificationObjectNameFld;
  StringField*   _newSpecificationGroupPathFld;
  EnumField*     _newSpecificationModelVisibilityFld;
  BoolField*     _newSpecificationUseDefaultColorFld;
  ColorField*    _newSpecificationColorFld;
  FloatField*    _newSpecificationColorAlphaFld;
  BoolField*     _newSpecificationUseDefaultSpecularColorFld;
  ColorField*    _newSpecificationSpecularColorFld;

  //! Fields for PointSet/LineSet properties
  IntField*      _pointPositionsMaxTypeIDFld;
  IntField*      _linePositionsMaxTypeIDFld;
  IntField*      _lineConnectionsMaxTypeIDFld;
  IntField*      _lineDefinitionsMaxTypeIDFld;
  IntField*      _pointPositionsNextTypeIDFld;
  IntField*      _linePositionsNextTypeIDFld;
  IntField*      _lineConnectionsNextTypeIDFld;
  IntField*      _lineDefinitionsNextTypeIDFld;

  //! The XMarkerList input for point positions of point clouds
  ml::XMarkerList _inPointPositions;  

  //! The XMarkerList input for node positions of line sets
  ml::XMarkerList _inLinePositions;

  //! The StringList input for connections of line sets
  ml::IndexPairList _inLineConnections;

  //! The fiberset container used for visualizing the line sets
  FiberSetContainer _outFiberSetContainer;

  /* METHODS */

  // Camera methods ==========================================================

  // Calculate PDF camera properties
  void _calculateCameraPropertiesFromInventorCamera();
  void _calculateDefaultCameraProperties();

  // Methods for SoVertexProperty and SoIndexedLineSet =======================

  void _calculateInventorPropertyFields();
  void _calculateInventorVertexList();
  void _calculateInventorCoordIndexList();

  // Methods for cresting views ==============================================

  void _createNewView();
  void _clearViews();

  // Methods for handling meshes =============================================

  void _updateAvailableWEMPatchesFld(WEMPtr wem, std::string defaultEntry = "");
  void _selectedWEMPatchChanged(WEMPtr wem);
  void _selectedWEMPatchIdChanged(WEMPtr wem);
  void _selectedWEMPatchNewLabelChanged();
  void _processPatch(unsigned int patchIndex);


  // Methods for PointSet/LineSet properties =================================

  void _getMaxTypeIDFromList(ml::XMarkerList& list, int& maxTypeID);
  void _getMaxTypeIDFromList(ml::IndexPairList& list, int& maxTypeID);
  void _calculateListPropertyFields();

  // Methods for Fibersets ===================================================

  void _createFibers();


  // Debug, development & test methods =======================================


//////////////////////////////////////////////


};

ML_END_NAMESPACE

#endif // _PDFUtils_H