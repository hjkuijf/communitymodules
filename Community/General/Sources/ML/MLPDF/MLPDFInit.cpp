//----------------------------------------------------------------------------------
//! Dynamic library and runtime type system initialization.
/*!
// \file    MLPDFInit.cpp
// \author  Axel Newe (axel.newe@fau.de)
// \date    2014-02-06
*/
//----------------------------------------------------------------------------------


// Local includes
#include "MLPDFSystem.h"

// Include definition of ML_INIT_LIBRARY.
#include "mlLibraryInitMacros.h"

// Include all module headers ...
#include "PDFUtils/PDFUtils.h"
#include "LoadPointLineGeometry/LoadPointLineGeometry.h"
#include "SavePDF/SavePDF.h"
#include "Save3DFigurePDF/Save3DFigurePDF.h"
#include "SaveU3D/SaveU3D.h"
#include "SavePRC/SavePRC.h"
#include "LoadU3D/LoadU3D.h"

ML_START_NAMESPACE

//----------------------------------------------------------------------------------
//! Calls init functions of all modules to add their types to the runtime type
//! system of the ML.
//----------------------------------------------------------------------------------
int MLPDFInit()
{
  PDFUtils::initClass();
  LoadPointLineGeometry::initClass();

  SavePDF::initClass();
  Save3DFigurePDF::initClass();
  SaveU3D::initClass();
  SavePRC::initClass();

  LoadU3D::initClass();

  return 1;
}

ML_END_NAMESPACE


//! Calls the init method implemented above during load of shared library.
ML_INIT_LIBRARY(MLPDFInit)