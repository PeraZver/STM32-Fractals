/*
 * fractals.c
 *
 *  Created on: May 8, 2020
 *      Author: Pero
 */

#include "fractals.h"

/*
 * Julia Set is generated in such a way that every pixel is treated as an initial complex number Z_0, and c
 * is a constant defined in fractals.h. This function iterates formula Zn+1 = Zn^2 + c until either RADIUS or
 * ITERATION value is reached. This way, every pixel is assigned a value that corresponds to color intesity
 * and represents as a part of a Julia set.
 */
void GenerateJulia_fpu(uint16_t size_x, uint16_t size_y, uint16_t offset_x,
					   uint16_t offset_y, uint16_t zoom, uint8_t * buffer)
{
	 float tmp1, tmp2;
	 float num_real, num_img;
	 float radius;
	 uint8_t i;
	 uint16_t x,y;

	 for (y=0; y<size_y; y++) {
		 for (x=0; x<size_x; x++) {
			 num_real = y - offset_y;
			 num_real = num_real / zoom;
			 num_img = x - offset_x;
			 num_img = num_img / zoom;
			 i=0;
			 radius = 0;
			 while ((i<ITERATION-1) && (radius < RADIUS)) {
				 tmp1 = num_real * num_real;
				 tmp2 = num_img * num_img;
				 num_img = 2*num_real*num_img + IMG_CONSTANT;
				 num_real = tmp1 - tmp2 + REAL_CONSTANT;
				 radius = tmp1 + tmp2;
				 i++;
			 }
			 /* Store the value in the buffer */
			 buffer[x+y*size_x] = i;
		}
	}
}
/*
* Mandelbrot Set is generated in such a way that every pixel is treated as a complex number c, while complex
* number Zn is run iterated from inital 0-value. This function iterates formula Zn+1 = Zn^2 + c until either RADIUS or
* ITERATION value is reached. This way, every pixel is assigned a value that corresponds to color intesity
* and represents as a part of a Mandelbrot set.
*/
void GenerateMandelbrot_fpu(uint16_t size_x, uint16_t size_y, uint16_t offset_x,
							uint16_t offset_y, uint16_t zoom, uint8_t * buffer)
{
	 float tmp1, tmp2;
	 float num_real, num_img;
	 float radius;
	 uint8_t i;
	 int x,y;

	 for (y=0; y<size_y; y++) {
		 for (x=0; x<size_x; x++) {      // Run through all the pixels
			 num_img = y - offset_y;    // Zoom in a proper scale
			 num_img = num_img / zoom;
			 num_real = x - offset_x - MANDELBROT_OFFSET; // Original Mandelbrot  has that funny offset
			 num_real = num_real / zoom;
			 i=0;
			 radius = 0;
			 float Zx = 0;
			 float Zy = 0;
			 while ((i<ITERATION-1) && (radius < RADIUS)) {
				 tmp1 = Zx * Zx;
				 tmp2 = Zy * Zy;
				 Zy = 2*Zx*Zy + num_img;
				 Zx = tmp1 - tmp2 + num_real;
				 radius = tmp1 + tmp2;
				 i++;
			 }
			 /* Store the value in the buffer */
			 buffer[x+y*size_x] = i;
		}
	}
 }
