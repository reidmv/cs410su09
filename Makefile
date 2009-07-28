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

DB_HOST   = db.cecs.pdx.edu
DB_USER   = reidmv
DB_NAME   = reidmv
DB_PASS   = cs410oss

SCHEMASPY_DIR = documentation/SchemaSpy
DB_SCRIPT_DIR = db_creation_scripts

all :

drop :
	export PGPASSWORD=${DB_PASS};	\
	psql -h ${DB_HOST} -d ${DB_NAME} -U ${DB_USER} -f ${DB_SCRIPT_DIR}/0_drop.postgresql;

create :
	export PGPASSWORD=${DB_PASS};	\
	psql -h ${DB_HOST} -d ${DB_NAME} -U ${DB_USER} -f ${DB_SCRIPT_DIR}/1_create.postgresql;

insert :
	export PGPASSWORD=${DB_PASS};	\
	psql -h ${DB_HOST} -d ${DB_NAME} -U ${DB_USER} -f ${DB_SCRIPT_DIR}/2_insert.postgresql;


clean .SILENT .IGNORE :
	rm -rf ${SCHEMASPY_DIR}/html/*;

schemaspy :
	java -jar ${SCHEMASPY_DIR}/schemaSpy_4.1.1.jar -t pgsql -host ${DB_HOST} -db ${DB_NAME} -s public -u ${DB_USER} -p ${DB_PASS} -o ${SCHEMASPY_DIR}/html/ -dp ${SCHEMASPY_DIR}/postgresql-8.3-604.jdbc3.jar -hq;
