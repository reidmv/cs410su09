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

# This makefile will populate a postgresql database with the Broke schema.
# Just fill out the following variables with the appropriate information.

DB_HOST       = db.cecs.pdx.edu
DB_USER       = reidmv
DB_NAME       = reidmv
DB_PASS       = cs410oss
DB_SCRIPT_DIR = .

# Available targets are:
# `drop`   - drop all broke tables from the database.
# `create` - create all broke tables in the database.
# `insert` - insert broke sample/structural data into the database.

# Optionally, you may generate your own SchemaSpy visualization using the 
# schemaspy target. You'll need to specify the location of a directory
# containing the schemaSpy_4.1.1.jar and postgresql-8.3-604.jdbc3.jar
# files SchemaSpy is authored by John Currier and released under the LGPL.

SCHEMASPY_DIR = ../schemaspy
SCHEMA_OUTDIR = ../doc/schema

all : drop create insert

drop :
	export PGPASSWORD=${DB_PASS};	\
	psql -h ${DB_HOST} -d ${DB_NAME} -U ${DB_USER} -f ${DB_SCRIPT_DIR}/0_drop.postgresql;

create : drop
	export PGPASSWORD=${DB_PASS};	\
	psql -h ${DB_HOST} -d ${DB_NAME} -U ${DB_USER} -f ${DB_SCRIPT_DIR}/1_create.postgresql;

insert : create
	export PGPASSWORD=${DB_PASS};	\
	{ \
	  psql -h ${DB_HOST} -d ${DB_NAME} -U ${DB_USER} -f ${DB_SCRIPT_DIR}/2_insert_sizes.postgresql; \
		psql -h ${DB_HOST} -d ${DB_NAME} -U ${DB_USER} -f ${DB_SCRIPT_DIR}/2_insert_plants.postgresql; \
	};

schemaspy :
	[ -d "${SCHEMA_OUTDIR}" ] || mkdir "${SCHEMA_OUTDIR}"; \
	java -jar ${SCHEMASPY_DIR}/schemaSpy_4.1.1.jar -t pgsql -host ${DB_HOST} -db ${DB_NAME} -s public -u ${DB_USER} -p ${DB_PASS} -o ${SCHEMA_OUTDIR}/ -dp ${SCHEMASPY_DIR}/postgresql-8.3-604.jdbc3.jar -hq; \
	chmod -R a+r ${SCHEMA_OUTDIR};
