#pragma once
#include "Image.h"

class Tile : public Image
{
public:
    Tile(string _strTexturePath) : Image(_strTexturePath) {}
};
