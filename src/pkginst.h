//  pkginst.h
//
//  Copyright (c) 2015 by NuTyX team (http://nutyx.org)
// 
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, 
//  USA.
//
#ifndef PKGINST_H
#define PKGINST_H

#include "pkgdbh.h"
#include "pkgrepo.h"

class Pkginst : public Pkgdbh, public Pkgrepo {
public:
//	Pkginst(){}
	Pkginst(const std::string& commandName,const std::string& configFileName );
	void generateDependencies(const std::string& packageName);
	void generateDependencies();
	void addPackage(const bool& installed);
	void addPackagesList();

private:
	bool m_force;
	string m_packageName;
	string m_packageFileName;
	vector<string> m_dependenciesList;
};
#endif /* PKGINST_H */
// vim:set ts=2 :