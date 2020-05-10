/*
 * fractals.c
 *
 *  Created on: May 8, 2020
 *      Author: Pero
 */

#include "fractals.h"

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

void drawMandelbrot_Double(float centre_X, float centre_Y, float Zoom,
						   uint16_t IterationMax)
{
	 double X_Min = centre_X - 1.0/Zoom;
	 double X_Max = centre_X + 1.0/Zoom;
	 double Y_Min = centre_Y - (YSIZE_PHYS-CONTROL_SIZE_Y) / (XSIZE_PHYS * Zoom);
	 double Y_Max = centre_Y + (YSIZE_PHYS-CONTROL_SIZE_Y) / (XSIZE_PHYS * Zoom);
	 double dx = (X_Max - X_Min) / XSIZE_PHYS;
	 double dy = (Y_Max - Y_Min) / (YSIZE_PHYS-CONTROL_SIZE_Y) ;

	 double y = Y_Min;

	 double c;
	 for (uint16_t j = 0; j < (YSIZE_PHYS-CONTROL_SIZE_Y); j++)	{
		 double x = X_Min;
		 for (uint16_t i = 0; i < XSIZE_PHYS; i++) {
			 double Zx = x;
			 double Zy = y;
			 int n = 0;
			 while (n < IterationMax) {
				 double Zx2 = Zx * Zx;
				 double Zy2 = Zy * Zy;
				 double Zxy = 2.0 * Zx * Zy;
				 Zx = Zx2 - Zy2 + x;
				 Zy = Zxy + y;
				 if(Zx2 + Zy2 > 16.0) {
					 break;
				 }
				 n++;
			 }
			 x += dx;
		 }
		 y += dy;
	 }
 }
