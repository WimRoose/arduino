/*
HMC5843_basic.pde - Basic reading example for the HMC5843 library
Copyright (C) 2011 Fabio Varesano <fabio at varesano dot net>


This program is free software: you can redistribute it and/or modify
it under the terms of the version 3 GNU General Public License as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

//#include <Wire.h>
//#include <DebugUtils.h>
//#include <.h>




void getKompas() { 
  
  int ix,iy,iz;
  magn.getValues(&ix,&iy,&iz);


  if (ix < minx) minx=ix;
  if (ix > maxx) maxx=ix;
  if (iy < miny) miny=iy;
  if (iy > maxy) maxy=iy;
  
   ix -= calibratex;
   iy -= calibratey;
  
  heading = atan2(iy, ix);
  if(heading < 0) {
    heading += 2 * M_PI;  
  }
  heading = heading * 180/M_PI;
  
  
  // x and y axis are swapped above with respect to the above paper as our Z axis points to the sky while in the paper it points to the bottom
}
