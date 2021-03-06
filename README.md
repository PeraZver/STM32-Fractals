# Fractals on STM32F4

I am trying to generate the fractal images on my TFT LCD touchscreen. 
I'll be using an [application note](https://www.st.com/content/ccc/resource/technical/document/application_note/10/6b/dc/ea/5b/6e/47/46/DM00047230.pdf/files/DM00047230.pdf/jcr:content/translations/en.DM00047230.pdf) from ST, made to demostrate advatages of hardware FPU. 

This is an educational project, so the purpose is only fun and learning.

## Hardware 
 * A NUCLEO-F411RE board with STM32F411RET6 (100 MHz SYSCLK)
 * A TFT-LCD with ILI9341 driver and XPT2046 touchscreen controller from [AliExpress](https://www.aliexpress.com/item/32815224002.html?spm=a2g0s.9042311.0.0.6f9d4c4dv0T4OV), with SPI (100 MHz SCK)

### Wiring

|LCD Board|Nucleo |STM32F411RE|                   |
| ------- |:-----:| ---------:|	--------------:	  |
|VCC      |CN6-4  | -         | 3.3V              |
|GND      |CN6-6  | -         | GND	              |
|CS       |CN5-3  | PB6       | D10, Chip Select  |
|RST      |CN9-5  | PB5       | D4,  LCD Reset    |
|DC       |CN7-21 | PB7       | Data control      |
|MOSI     |CN5-4  | PA7       | D11, MOSI         |
|SCK      |CN5-6  | PA5       | D13, SCK          |
|LED      |CN7-5  | VDD       | 5V                |
|MISO     |CN5-5  | PA6       | D12, MISO         |
|T_CLK    |CN9-7  | PB10      | D6, Touch CLK     |
|T_CS     |CN10-6 | PC5       | Touch Chip Select |
|T_DIN    |CN7-37 | PC3       | Touch Data In  	  |
|T_DO     |CN7-35 | PC2       | Touch Data OUt 	  |
|T_IRQ    |CN10-24| PB1       | Touch Interrupt   |


## Software
 * Standard STM32 HAL Libraries, on the fresh STM32CubeIDE
 * ILI9341 Driver - I'm using an existing library from [this guy](https://github.com/martnak/STM32-ILI9341)
   * Actually, I switched to [this one](https://github.com/afiskon/stm32-ili9341); it has nice GUI. I added a Touchscreen calibration function as well.

## To-Do

 - [x] Touchscreen zoom 
 - [x] Touchscreen centering
 - [ ] Colour mapping
 - [x] Mandelbrot fractals
 - [x] Switch between Julia and Mandelbrot
 - [ ] Touchscreen over SPI instead of bit banging

## Resources

 - [Very well documented example on ESP32/Arduino](https://www.instructables.com/id/Mandelbrot-and-Julia-Sets-on-ESP32/)
 - [Lousy documented app note from ST about FPU](https://www.st.com/content/ccc/resource/technical/document/application_note/10/6b/dc/ea/5b/6e/47/46/DM00047230.pdf/files/DM00047230.pdf/jcr:content/translations/en.DM00047230.pdf)