/**
 * Copyright 2024 University of Oulu
 * Authors:
 *   Elmeri Uotila <roope.uotila@oulu.fi>
 */

#include "canvasitem.h"

CanvasItem::CanvasItem(size_t x, size_t y, Vector2 position, Vector2 scale, RGBAPixel color) {
	resize(x, y);
	RGBAPixel* pixel = (*this)(x, y);
	pixel->alpha = 0;
	pixel->red = color.red;
	pixel->green = color.green;
	pixel->blue = color.blue;
	position_ = position;
	color_ = color;
	scale_ = scale;
}

RGBAPixel CanvasItem::getBlendedPixel(size_t x, size_t y){
	RGBAPixel* p = (*this)(x,y);
	RGBAPixel copy = *p;
	copy.alpha *= color_.alpha / 255;
	copy.red *= color_.red / 255;
	copy.green *= color_.green / 255;
	copy.blue *= color_.blue / 255;
	
	return copy;
}

Vector2 CanvasItem::position(){
	return position_;
}

Vector2 CanvasItem::scale(){
	return scale_;
}

void CanvasItem::SetPosition(Vector2 pos){
	position_ = pos;
}