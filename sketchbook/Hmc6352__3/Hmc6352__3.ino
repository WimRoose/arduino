/*
 * hmc6352example.pde
 * 
 * Copyright (c) 2009 Ruben Laguna <ruben.laguna at gmail.com>. All rights reserved.
 * 
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

 
#include <hmc6352.h>
#include <Wire.h>


//set up hmc6352
Hmc6352 hmc6352;

  
void setup()  {  
  Serial.begin(9600);
  delay(100);
  
  Serial.print("RST\r\n");delay(100);  
}


void loop() 
{ 
  hmc6352.wake();
  float a = hmc6352.getHeading();
  hmc6352.sleep();
 
  Serial.print((int)a,DEC);
  Serial.print("\r\n");
  delay(1000);
  
}
