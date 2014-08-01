// cards_create.cc
//
//  Copyright (c) 2014 by NuTyX team (http://nutyx.org)
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

#include "cards_create.h"
using namespace std;

CardsCreate::CardsCreate(const CardsArgumentParser& argParser)
	: m_argParser(argParser)
{
}
void CardsCreate::run(int argc, char** argv)
{
}
void CardsCreate::printHelp() const
{
	cout << endl
			<< "  This command is mainly used to finally check the quality of the port" << endl
			<< " The compilation should go through without problems and " << endl
			<< " all the dependencies should be availables" << endl;
}
// vim:set ts=2 :

