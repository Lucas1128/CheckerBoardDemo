/*
  ==============================================================================

   This file is part of the JUCE examples.
   Copyright (c) 2020 - Raw Material Software Limited

   The code included in this file is provided under the terms of the ISC license
   http://www.isc.org/downloads/software-support-policy/isc-license. Permission
   To use, copy, modify, and/or distribute this software for any purpose with or
   without fee is hereby granted provided that the above copyright notice and
   this permission notice appear in all copies.

   THE SOFTWARE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL WARRANTIES,
   WHETHER EXPRESSED OR IMPLIED, INCLUDING MERCHANTABILITY AND FITNESS FOR
   PURPOSE, ARE DISCLAIMED.

  ==============================================================================
*/

/*******************************************************************************
 The block below describes the properties of this PIP. A PIP is a short snippet
 of code that can be read by the Projucer and used to generate a JUCE project.

 BEGIN_JUCE_PIP_METADATA

 name:             GridDemo
 version:          1.0.0
 vendor:           JUCE
 website:          http://juce.com
 description:      Responsive layouts using Grid.

 dependencies:     juce_core, juce_data_structures, juce_events, juce_graphics,
                   juce_gui_basics
 exporters:        xcode_mac, vs2019, linux_make, androidstudio, xcode_iphone

 moduleFlags:      JUCE_STRICT_REFCOUNTEDPOINTER=1

 type:             Component
 mainClass:        GridDemo

 useLocalCopy:     1

 END_JUCE_PIP_METADATA

*******************************************************************************/

#pragma once

#include "DemoUtilities.h"
#include <iostream>  
#include <string>
#include <math.h> 

using namespace std;

//==============================================================================
struct GridDemo : public Component
{
    int checkerboardsize = 16;

    GridDemo()
    {
        int colloumncount = sqrt (checkerboardsize);

        bool state = false;
        /*Sets Grid Item Color*/
        for (int i = 0; i < checkerboardsize; i++)
        {
            if (i % colloumncount == 0 && state == false)
            {
                state = true;
            }

            else if (i % colloumncount == 0 && state == true)
            {
                state = false;
            }


            if (state == true)
            {
                addGridItemPanel (Colours::black, "");
                state = false;
            }
            else
            {
                addGridItemPanel (Colours::white, "");
                state = true;
            }            
        }
        
        setSize (750, 750);
    }

    void addGridItemPanel (Colour colour, const char* text)
    {
        /*Makes each box visible as a GridItemPanel*/
        addAndMakeVisible (items.add (new GridItemPanel (colour, text)));
    }

    void paint (Graphics& g) override
    {
        /*Background Color*/
        g.fillAll (Colours::black);
    }

    void resized() override
    {
        Grid grid;

        /* Space Between Boxes*/
        grid.rowGap    = 0_px;
        grid.columnGap = 0_px;

        using Track = Grid::TrackInfo;

        /*Sets Number of rows/collumns, each gets equal share of space*/
        grid.templateRows = { Track (1_fr), Track (1_fr), Track (1_fr) , Track(1_fr)};

        grid.templateColumns = { Track (1_fr),
                                 Track (1_fr),
                                 Track (1_fr),
                                 Track (1_fr) };


        grid.autoColumns = Track (1_fr);
        grid.autoRows    = Track (1_fr);

        grid.autoFlow = Grid::AutoFlow::column;

        /*Adds grid items to array*/
        for (int i = 0; i < checkerboardsize; i++)
        {
            grid.items.addArray({ GridItem(items[i]) });
        }

        grid.performLayout (getLocalBounds());
    }

    //==============================================================================
    struct GridItemPanel  : public Component
    {
        GridItemPanel (Colour colourToUse, const String& textToUse)
            : colour (colourToUse),
              text (textToUse)
        {}

        void paint (Graphics& g) override
        {
            g.fillAll (colour.withAlpha (1.0f));

            g.setColour (Colours::black);
            g.drawText (text, getLocalBounds().withSizeKeepingCentre (100, 100), Justification::centred, false);
        }

        Colour colour;
        String text;
    };

    OwnedArray<GridItemPanel> items;
};
