/*
 * Fahrzeug.h
 *
 *  Created on: 11.10.2024
 *      Author: marti
 */

#ifndef FAHRZEUG_H_
#define FAHRZEUG_H_

#include <iostream>
#include <string>
class Fahrzeug
{
public:
	Fahrzeug();
	Fahrzeug(std::string name);
	~Fahrzeug();

private:
	static inline int p_maxID = 0;
	std::string p_sName = "";
	const int p_iID = 0;
};
#endif /* FAHRZEUG_H_ */
