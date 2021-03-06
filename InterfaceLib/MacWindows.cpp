//
// MacWindows.cpp
// Classix
//
// Copyright (C) 2013 Félix Cloutier
//
// This file is part of Classix.
//
// Classix is free software: you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option) any later
// version.
//
// Classix is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
// A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with
// Classix. If not, see http://www.gnu.org/licenses/.
//

#include <CoreGraphics/CoreGraphics.h>
#include <sstream>
#include "Prototypes.h"
#include "InterfaceLib.h"
#include "ResourceTypes.h"
#include "NotImplementedException.h"
#include "Todo.h"

using namespace OSEnvironment;
using namespace InterfaceLib;
using namespace InterfaceLib::Resources;

void InterfaceLib_BeginUpdate(InterfaceLib::Globals* globals, MachineState* state)
{
	UGrafPort& port = *globals->allocator.ToPointer<UGrafPort>(state->r3);
	globals->grafPorts.BeginUpdate(port);
}

void InterfaceLib_BringToFront(InterfaceLib::Globals* globals, MachineState* state)
{
	throw PPCVM::NotImplementedException(__func__);
}

void InterfaceLib_CalcVis(InterfaceLib::Globals* globals, MachineState* state)
{
	throw PPCVM::NotImplementedException(__func__);
}

void InterfaceLib_CalcVisBehind(InterfaceLib::Globals* globals, MachineState* state)
{
	throw PPCVM::NotImplementedException(__func__);
}

void InterfaceLib_CheckUpdate(InterfaceLib::Globals* globals, MachineState* state)
{
	throw PPCVM::NotImplementedException(__func__);
}

void InterfaceLib_ClipAbove(InterfaceLib::Globals* globals, MachineState* state)
{
	throw PPCVM::NotImplementedException(__func__);
}

void InterfaceLib_DisposeWindow(InterfaceLib::Globals* globals, MachineState* state)
{
	uint32_t windowKey = state->r3;
	globals->ipc().PerformAction<void>(IPCMessage::CloseWindow, windowKey);
	UGrafPort& port = *globals->allocator.ToPointer<UGrafPort>(windowKey);
	globals->grafPorts.DestroyGrafPort(port);
	globals->allocator.Deallocate(&port);
}

void InterfaceLib_DragGrayRgn(InterfaceLib::Globals* globals, MachineState* state)
{
	throw PPCVM::NotImplementedException(__func__);
}

void InterfaceLib_DragTheRgn(InterfaceLib::Globals* globals, MachineState* state)
{
	throw PPCVM::NotImplementedException(__func__);
}

void InterfaceLib_DragWindow(InterfaceLib::Globals* globals, MachineState* state)
{
	uint32_t windowKey = state->r3;
	// we don't need the point in state->r4
	InterfaceLib::Rect& dragBounds = *globals->allocator.ToPointer<InterfaceLib::Rect>(state->r5);
	
	globals->ipc().PerformAction<void>(IPCMessage::DragWindow, windowKey, dragBounds);
}

void InterfaceLib_DrawGrowIcon(InterfaceLib::Globals* globals, MachineState* state)
{
	throw PPCVM::NotImplementedException(__func__);
}

void InterfaceLib_DrawNew(InterfaceLib::Globals* globals, MachineState* state)
{
	throw PPCVM::NotImplementedException(__func__);
}

void InterfaceLib_EndUpdate(InterfaceLib::Globals* globals, MachineState* state)
{
	uint32_t key = state->r3;
	UGrafPort& port = *globals->allocator.ToPointer<UGrafPort>(key);
	CGRect dirtyRect = globals->grafPorts.EndUpdate(port);
	globals->ipc().PerformAction<void>(IPCMessage::SetDirtyRect, key, dirtyRect);
}

void InterfaceLib_FrontWindow(InterfaceLib::Globals* globals, MachineState* state)
{
	state->r3 = globals->ipc().PerformAction<uint32_t>(IPCMessage::FindFrontWindow);
}

void InterfaceLib_GetAuxWin(InterfaceLib::Globals* globals, MachineState* state)
{
	throw PPCVM::NotImplementedException(__func__);
}

void InterfaceLib_GetCWMgrPort(InterfaceLib::Globals* globals, MachineState* state)
{
	throw PPCVM::NotImplementedException(__func__);
}

void InterfaceLib_GetGrayRgn(InterfaceLib::Globals* globals, MachineState* state)
{
	throw PPCVM::NotImplementedException(__func__);
}

void InterfaceLib_GetNewCWindow(InterfaceLib::Globals* globals, MachineState* state)
{
	uint16_t resourceId = static_cast<uint16_t>(state->r3);
	WIND* window = globals->resources().GetResource<WIND>(resourceId);
	
	uint32_t portAddress = state->r4;
	UGrafPort* port;
	std::string title = window->title;
	const InterfaceLib::Rect& rect = window->windowRect;
	
	Palette* palette = nullptr;
	if (ResourceEntry* entry = globals->resources().GetRawResource("pltt", resourceId))
	{
		palette = reinterpret_cast<Palette*>(entry->begin());
	}
	
	if (portAddress == 0)
	{
		std::stringstream ss;
		ss << "Window: \"" << title << "\"";
		port = &globals->grafPorts.AllocateColorGrafPort(rect, palette, title);
		portAddress = globals->allocator.ToIntPtr(port);
	}
	else
	{
		port = globals->allocator.ToPointer<UGrafPort>(portAddress);
		assert(port->IsColor() && "Not a Color QuickDraw port");
	}
	
	bool visible = window->visible;
	uint32_t createBehind = state->r5;
	uint32_t surfaceId = globals->grafPorts.SurfaceOfGrafPort(*port);
	
	globals->ipc().PerformAction<void>(IPCMessage::CreateWindow, portAddress, surfaceId, rect, visible, title, createBehind);
	state->r3 = portAddress;
}

void InterfaceLib_GetNewWindow(InterfaceLib::Globals* globals, MachineState* state)
{
	throw PPCVM::NotImplementedException(__func__);
}

void InterfaceLib_GetWindowPic(InterfaceLib::Globals* globals, MachineState* state)
{
	throw PPCVM::NotImplementedException(__func__);
}

void InterfaceLib_GetWMgrPort(InterfaceLib::Globals* globals, MachineState* state)
{
	throw PPCVM::NotImplementedException(__func__);
}

void InterfaceLib_GetWRefCon(InterfaceLib::Globals* globals, MachineState* state)
{
	throw PPCVM::NotImplementedException(__func__);
}

void InterfaceLib_GetWTitle(InterfaceLib::Globals* globals, MachineState* state)
{
	throw PPCVM::NotImplementedException(__func__);
}

void InterfaceLib_GetWVariant(InterfaceLib::Globals* globals, MachineState* state)
{
	throw PPCVM::NotImplementedException(__func__);
}

void InterfaceLib_GrowWindow(InterfaceLib::Globals* globals, MachineState* state)
{
	throw PPCVM::NotImplementedException(__func__);
}

void InterfaceLib_HideWindow(InterfaceLib::Globals* globals, MachineState* state)
{
	throw PPCVM::NotImplementedException(__func__);
}

void InterfaceLib_HiliteWindow(InterfaceLib::Globals* globals, MachineState* state)
{
	throw PPCVM::NotImplementedException(__func__);
}

void InterfaceLib_InitWindows(InterfaceLib::Globals* globals, MachineState* state)
{
	// nothing to do here
}

void InterfaceLib_InvalRect(InterfaceLib::Globals* globals, MachineState* state)
{
	throw PPCVM::NotImplementedException(__func__);
}

void InterfaceLib_InvalRgn(InterfaceLib::Globals* globals, MachineState* state)
{
	throw PPCVM::NotImplementedException(__func__);
}

void InterfaceLib_NewCWindow(InterfaceLib::Globals* globals, MachineState* state)
{
	TODO("NewCWindow has so many parameters it should be verified that they all fit in registers");
	
	// We use storage pointers as window indentifiers in the UI head, since they're guaranteed to be unique
	// for ay given window.
	uint32_t portAddress = state->r3;
	UGrafPort* port;
	
	// We try to get the title first, since we can use it for the allocation name.
	const char* pascalTitle = globals->allocator.ToPointer<const char>(state->r5);
	std::string cppTitle = PascalStringToCPPString(pascalTitle);
	
	const InterfaceLib::Rect& rect = *globals->allocator.ToPointer<const InterfaceLib::Rect>(state->r4);
	
	if (portAddress == 0)
	{
		std::stringstream ss;
		ss << "Window: \"" << cppTitle << "\"";
		port = &globals->grafPorts.AllocateColorGrafPort(rect, nullptr, cppTitle);
		portAddress = globals->allocator.ToIntPtr(port);
	}
	else
	{
		port = globals->allocator.ToPointer<UGrafPort>(portAddress);
		assert(port->IsColor() && "Not a Color QuickDraw port");
	}
	
	bool visible = state->r6 != 0;
	uint32_t createBehind = state->r8;
	uint32_t surfaceId = globals->grafPorts.SurfaceOfGrafPort(*port);
	
	globals->ipc().PerformAction<void>(IPCMessage::CreateWindow, portAddress, surfaceId, rect, visible, cppTitle, createBehind);
	state->r3 = portAddress;
}

void InterfaceLib_NewWindow(InterfaceLib::Globals* globals, MachineState* state)
{
	throw PPCVM::NotImplementedException(__func__);
}

void InterfaceLib_PaintBehind(InterfaceLib::Globals* globals, MachineState* state)
{
	throw PPCVM::NotImplementedException(__func__);
}

void InterfaceLib_PaintOne(InterfaceLib::Globals* globals, MachineState* state)
{
	throw PPCVM::NotImplementedException(__func__);
}

void InterfaceLib_PinRect(InterfaceLib::Globals* globals, MachineState* state)
{
	throw PPCVM::NotImplementedException(__func__);
}

void InterfaceLib_SaveOld(InterfaceLib::Globals* globals, MachineState* state)
{
	throw PPCVM::NotImplementedException(__func__);
}

void InterfaceLib_SelectWindow(InterfaceLib::Globals* globals, MachineState* state)
{
	throw PPCVM::NotImplementedException(__func__);
}

void InterfaceLib_SendBehind(InterfaceLib::Globals* globals, MachineState* state)
{
	throw PPCVM::NotImplementedException(__func__);
}

void InterfaceLib_SetDeskCPat(InterfaceLib::Globals* globals, MachineState* state)
{
	throw PPCVM::NotImplementedException(__func__);
}

void InterfaceLib_SetWinColor(InterfaceLib::Globals* globals, MachineState* state)
{
	throw PPCVM::NotImplementedException(__func__);
}

void InterfaceLib_SetWindowPic(InterfaceLib::Globals* globals, MachineState* state)
{
	throw PPCVM::NotImplementedException(__func__);
}

void InterfaceLib_SetWRefCon(InterfaceLib::Globals* globals, MachineState* state)
{
	throw PPCVM::NotImplementedException(__func__);
}

void InterfaceLib_SetWTitle(InterfaceLib::Globals* globals, MachineState* state)
{
	throw PPCVM::NotImplementedException(__func__);
}

void InterfaceLib_ShowHide(InterfaceLib::Globals* globals, MachineState* state)
{
	throw PPCVM::NotImplementedException(__func__);
}

void InterfaceLib_SizeWindow(InterfaceLib::Globals* globals, MachineState* state)
{
	throw PPCVM::NotImplementedException(__func__);
}

void InterfaceLib_TrackBox(InterfaceLib::Globals* globals, MachineState* state)
{
	throw PPCVM::NotImplementedException(__func__);
}

void InterfaceLib_TrackGoAway(InterfaceLib::Globals* globals, MachineState* state)
{
	throw PPCVM::NotImplementedException(__func__);
}

void InterfaceLib_ValidRect(InterfaceLib::Globals* globals, MachineState* state)
{
	throw PPCVM::NotImplementedException(__func__);
}

void InterfaceLib_ValidRgn(InterfaceLib::Globals* globals, MachineState* state)
{
	throw PPCVM::NotImplementedException(__func__);
}

void InterfaceLib_ZoomWindow(InterfaceLib::Globals* globals, MachineState* state)
{
	throw PPCVM::NotImplementedException(__func__);
}

