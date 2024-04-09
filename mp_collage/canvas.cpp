/**
 * Copyright 2024 University of Oulu
 * Authors:
 *   Elmeri Uotila <roope.uotila@oulu.fi>
 */

#include "canvas.h"
#include <iostream>

Canvas::Canvas()
{
 items = new CanvasItem*[10];
 itemcount = 0;
}

// Just delete the list, the individual items are handled by main
Canvas::~Canvas()
{
	delete[] items;
}

// Add an item at the end of the list
void Canvas::Add(CanvasItem *item)
{
	if (itemcount == 9)
	{
		std::cout << "Array is full" << std::endl;
		return;
	}

	items[0] = item;
	itemcount++;
}

// Find and remove pointer from list
// But don't free the memory, leave that to main
// If pointer is not found, do nothing
void Canvas::Remove(CanvasItem *item)
{
	for (size_t i = 0; i < itemcount; i++)
	{
		if (item == items[i])
		{
			items[i] = nullptr;
		}
		
	}
}

// Find given items from list and swap their positions
// Swap only if both pointers are found
void Canvas::Swap(CanvasItem *item1, CanvasItem *item2)
{
	CanvasItem* swap1;
	CanvasItem* swap2;
	for (size_t i = 0; i < itemcount; i++)
	{
		if (item1 == items[i])
		{
			swap1 = item1;
		}
		if (item2 == items[i])
		{
			swap2 = item2;
		}
		
		
	}

	if (swap1 != nullptr && swap2 != nullptr)
	{
		CanvasItem* temp;
		temp = swap1;
		swap1 = swap2;
		swap2 = temp;
	}
	
}

// Draws all items in the list in order
// Blends the pixels colors of the items with their item color
// Draws the items in their given position and scales them accordingly
// Blends drawn layers based on alpha channel (transparency)
void Canvas::draw(PNG *canvas) const
{
	for (size_t i = 0; i < itemcount; i++)
	{
		// update this line
		CanvasItem *item = items[i];

		for (size_t x = 0, xmax = item->width(); x < xmax; x++)
		{
			for (size_t y = 0, ymax = item->height(); y < ymax; y++)
			{
				// This gets the pixel color blended with item color
				// Check canvasitem.cpp
				RGBAPixel coli = item->getBlendedPixel(x, y);
				Vector2 sc = item->scale();

				// You should uncomment the below line and use in the section below
				Vector2 pos = item->position();

				// A loop is needed in case it must be scaled up, or we end up with gaps
				for (int xs = 0; xs < std::abs((int)(sc.x() - 0.001)) + 1; xs++)
				{
					for (int ys = 0; ys < std::abs((int)(sc.y() - 0.001)) + 1; ys++)
					{
						// Determine the position on the canvas based on
						// item position, scale, pixel position and adjacent pixel selection
						// x1, y1 should be coordinates of the canvas to draw to
						// So we should add item position and adjacent pixel selection xs, ys
						// Multiply x and y by item scale
						

						// Modify the two lines below
						int x1 = pos.x() * sc.x();
						int y1 = pos.y() * sc.y();
						x1 += xs;
						y1 += ys;

						// Check that it's within bounds
						if (x1 >= 0 && x1 < (int)canvas->width() && y1 >= 0 && y1 < (int)canvas->height())
						{
							// Current color of the canvas
							RGBAPixel *colc = (*canvas)(x1, y1);

							// TODO Blend based on alpha.
							// Multiply item color with alpha, canvas color with 255-alpha
							// Add them and divide by 255
							// In other words 255 = replace old pixel with new. 0 = don't draw.
							// 1-254 = partly new pixel, partly old

							// Modify the three lines below
							colc->alpha = coli.alpha;
							colc->red = coli.red;
							colc->green = coli.green;
							colc->blue = coli.blue;

							// We can keep the canvas opaque, no reason to change it
							colc->alpha = 255;
						}
					}
				}
			}
		}
	}
}
