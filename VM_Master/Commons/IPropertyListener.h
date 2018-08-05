/*
 * IPropertyListener.h
 *
 *  Created on: 21 Απρ 2018
 *      Author: Synodiporos
 */

#ifndef COMMONS_IPROPERTYLISTENER_H_
#define COMMONS_IPROPERTYLISTENER_H_

class IPropertyListener {
public:
	virtual ~IPropertyListener(){};

	virtual void propertyChanged(
			void* source,
			unsigned short int propertyId,
			const void* oldPropery) = 0;
};

#endif /* COMMONS_IPROPERTYLISTENER_H_ */
