/*
 * fractals.h
 *
 *  Created on: May 8, 2020
 *      Author: Pero
 */

#ifndef SRC_FRACTALS_FRACTALS_H_
#define SRC_FRACTALS_FRACTALS_H_

#include "main.h"

#define REAL_CONSTANT 0.285
#define IMG_CONSTANT 0.01
#define ITERATION 128
#define RADIUS 4

void GenerateJulia_fpu(uint16_t size_x, uint16_t size_y, uint16_t offset_x,
					   uint16_t offset_y, uint16_t zoom, uint8_t * buffer);



#endif /* SRC_FRACTALS_FRACTALS_H_ */
