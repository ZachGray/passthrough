//-
// ==========================================================================
// Copyright 1995,2006,2008 Autodesk, Inc. All rights reserved.
//
// Use of this software is subject to the terms of the Autodesk
// license agreement provided at the time of installation or download,
// or which otherwise accompanies this software in either electronic
// or hard copy form.
// ==========================================================================
//+

////////////////////////////////////////////////////////////////////////
// DESCRIPTION:
// 
// Produces the dependency graph node "passthrough".
//
// Setup scene
/*
import maya.cmds as mc
passthrough_node = mc.createNode('passthrough')
color_in_node = mc.createNode('colorConstant')
color_out_node = mc.createNode('colorConstant')

mc.connectAttr(f'{color_in_node}.outColor', f'{passthrough_node}.palette[0].color0', force=True)
mc.connectAttr(f'{passthrough_node}.palette[0].color0', f'{color_out_node}.inColor', force=True)

*/


////////////////////////////////////////////////////////////////////////

#include <maya/MPxNode.h>

#include <maya/MString.h> 
#include <maya/MTypeId.h> 
#include <maya/MPlug.h>

#include <maya/MFnTypedAttribute.h>
#include <maya/MFnCompoundAttribute.h>
#include <maya/MFnNumericAttribute.h>

#include <maya/MFnPlugin.h>
#include <maya/MDataBlock.h>
#include <maya/MDataHandle.h>

//#include <string>
#include <maya/MIOStream.h>

class passthrough : public MPxNode
{
public:
					passthrough() {};
					~passthrough() override {}; 

	MStatus		compute( const MPlug& plug, MDataBlock& data ) override;
	static  void*		creator();
	static  MStatus		initialize();

	static  MTypeId     id;
	static MObject aTouchColor0;
	static MObject aColor1;
	static MObject aColor2;
	static MObject aAlpha;
	static MObject aPalette;

	MStatus setDependentsDirty(const MPlug& plugBeingDirtied, MPlugArray& affectedPlugs);
};

MTypeId	passthrough::id( 0x80013 );
MObject passthrough::aTouchColor0 = {};
MObject passthrough::aColor1 = {};
MObject passthrough::aColor2 = {};
MObject passthrough::aAlpha = {};
MObject passthrough::aPalette = {};

void* passthrough::creator()
{
    return new passthrough;
}

#define MAKE_IO(attr) \
	CHECK_MSTATUS(attr.setKeyable(true)); \
	CHECK_MSTATUS(attr.setStorable(true)); \
	CHECK_MSTATUS(attr.setReadable(true)); \
	CHECK_MSTATUS(attr.setWritable(true));

MStatus passthrough::initialize()
{
	MFnNumericAttribute numericFn;
	MFnTypedAttribute typedFn;
	MFnCompoundAttribute compoundFn;

	MStatus				stat;

	aTouchColor0 = numericFn.createColor("color0", "c0");
	MAKE_IO(numericFn);
	CHECK_MSTATUS(numericFn.setDefault(.0, .25, .75));			// Blue

	aColor1 = numericFn.createColor("color1", "c1");
	MAKE_IO(numericFn);
	CHECK_MSTATUS(numericFn.setDefault(.75, .03, .0));			// Red

	aColor2 = numericFn.createColor("color2", "c2");
	MAKE_IO(numericFn);
	CHECK_MSTATUS(numericFn.setDefault(.9, .9, .0));			// Yellow


	aAlpha = numericFn.create("alpha", "alph", MFnNumericData::kFloat, .50f);
	numericFn.setMin(0.0f);
	numericFn.setMax(1.0f);
	MAKE_IO(numericFn);

	aPalette = compoundFn.create("palette", "palette");
	MAKE_IO(compoundFn);
	compoundFn.setArray(true);
	compoundFn.addChild(aTouchColor0);
	compoundFn.addChild(aColor1);
	compoundFn.addChild(aColor2);
	compoundFn.addChild(aAlpha);
	compoundFn.setUsesArrayDataBuilder(true);
	addAttribute(aPalette);


	return MS::kSuccess;
}

MStatus passthrough::compute( const MPlug& plug, MDataBlock& block )
{
    MStatus stat;

	// naughty case, call getValue to force eval
	
	if (plug.isCompound()) {
		//MGlobal::displayInfo("Palette compute");
		//MGlobal::displayInfo(plug.name());
		plug.isDefaultValue(true);
	}
	


	// eval error case, call inputValue to force eval
	/*
	if (plug.attribute() == aPalette) {
		MDataHandle inputValue = block.inputValue(aPalette);
		MArrayDataHandle adh = block.inputArrayValue(aPalette);
	}
	*/

    return MS::kSuccess;
}

MStatus passthrough::setDependentsDirty(const MPlug& plugBeingDirtied, MPlugArray& affectedPlugs) {
	// Stub for dirty
	return MS::kSuccess;
}

MStatus initializePlugin( MObject obj )
{
	MStatus   status;
    MFnPlugin plugin( obj, PLUGIN_COMPANY, "3.0", "Any");

    status = plugin.registerNode( "passthrough", passthrough::id,
						 passthrough::creator, passthrough::initialize );
	if (!status) {
		status.perror("registerNode");
		return status;
	}

    return status;
}

MStatus uninitializePlugin( MObject obj)
{
	MStatus   status;
    MFnPlugin plugin( obj );

    status = plugin.deregisterNode( passthrough::id );
	if (!status) {
		status.perror("deregisterNode");
		return status;
	}

    return status;
}
