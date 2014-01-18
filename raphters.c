/*
    Copyright (C) 2011 Raphters authors,
    
    This file is part of Raphters.
    
    Raphters is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Raphters is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <sys/types.h>
#include "raphters.h"
#include "backtrace.h"

void serve_forever() {
	(void)install_segfault_handler();
	int uid = (int) geteuid();
	if(uid = 0){
		// never run webapp as root, its a security risk
		uid = 1;
	}
	// set uid to non-root user
	setuid(uid);
	seteuid(uid);
    init_handlers();
    while(FCGI_Accept() >= 0) {
        dispatch();
    }
    cleanup_handlers();
}
