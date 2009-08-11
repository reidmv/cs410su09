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

brokedir=../

broke_PROGRAMS=\
	broke

broke_SOURCES=\
	main.c \
	broke_ui.c \
	common.h \
	broke_ui.h

broke_LDFLAGS=\
	-export-dynamic

INCLUDES=\
	@GTK_CFLAGS@ \
	@LIBGDA_CFLAGS@ \
	@LIBGNOMEDB_CFLAGS@

broke_LDADD=\
	@GTK_LIBS@ \
	@LIBGDA_LIBS@ \
	@LIBGNOMEDB_LIBS@

