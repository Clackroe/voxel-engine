#include "../../vendor/stb_image.h"

/*
Texture Location(x, y) "In The Main Texture File"

 -------------------
 | (0, 1) | (1, 1) |
 | ----------------|
 | (0, 0) | (1, 0) |
 -------------------


Texture Coords To Load In Shader
(LB, TB), (RB, TB)
(LB, BB), (RB, BB)

Combined:Txtr Ratio 'R' = WidthOfFile / WidthOfTexture

LB = x * R      BB = y * R
RB = LB + R     TB = BB + R
*/



