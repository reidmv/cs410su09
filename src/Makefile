#=============================================================================
# Copyright (C) 2009 Reid Vandewiele                                       
# ALL RIGHTS RESERVED                                                      
#                                                                          
# This file is part of Broke.                                              
#                                                                          
# Broke is free software: you can redistribute it and/or modify it under the 
# terms of the GNU General Public License as published by the Free Software 
# Foundation, either version 3 of the License, or (at your option) any later
# version.                                               
#                                                                          
# Broke is distributed in the hope that it will be useful, but WITHOUT ANY 
# WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS 
# FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more 
# details.                                                        
#                                                                          
# You should have received a copy of the GNU General Public License along  
# with Broke in a file named COPYING.  If not, see     
# <http://www.gnu.org/licenses/>.                                          
#=============================================================================

CC         = gcc
CFLAGS     = -x c -g -Wall `pkg-config --cflags gtk+-2.0`
COMPILE    = $(CC) $(CFLAGS) -c
LD         = $(CC)
LDFLAGS    = `pkg-config --libs gtk+-2.0` -export-dynamic

BROKE_OBJS = broke.o event_handlers.o 
BROKE_HDRS = 

bunny_rabbits : broke

broke : $(BROKE_OBJS) $(BROKE_HDRS)
	$(LD) $(LDFLAGS) $(BROKE_OBJS) -o $@

%.o : %.c
	$(COMPILE) $< -o $@

clean .IGNORE .SILENT : 
	rm broke *.o 2> /dev/null

