/*
 * fahrzeug.h
 *
 *  Created on: 11.10.2024
 *      Author: marti
 */

#ifndef FAHRZEUG_H_
#define FAHRZEUG_H_

#include <string>

class Fahrzeug
{
public:
	Fahrzeug(std::string name);
	Fahrzeug();

private:
	static int p_maxID = 0;
	std::string p_sName = "";
	int p_iID = 0;
};
#endif /* FAHRZEUG_H_ */
