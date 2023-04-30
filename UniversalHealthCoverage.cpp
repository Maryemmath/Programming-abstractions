#include <iostream>
#include <string>
#include <fstream>
#include "set.h"
#include "map.h"
#include "console.h"
#include "simpio.h"
#include "strlib.h"
using namespace std;

using namespace std;


/* Function: canOfferUniversalCoverage(Set<string>& cities,
 *                                     Vector< Set<string> >& locations,
 *                                     int numHospitals,
 *                                     Vector< Set<string> >& result);
 * Usage: if (canOfferUniversalCoverage(cities, locations, 4, result)
 * ==================================================================
 * Given a set of cities, a list of what cities various hospitals can
 * cover, and a number of hospitals, returns whether or not it's
 * possible to provide coverage to all cities with the given number of
 * hospitals.  If so, one specific way to do this is handed back in the
 * result parameter.
 */

// this method checks whether hospitals will cover all cities or not
bool coversAll(Vector< Set<string> >& result, Set<string> & cities) {
	for(int i = 0; i < result.size(); i++) {
		foreach(string city in result[i]) {
			if(cities.contains(city)) {
				cities.remove(city);
			}
		}
	}
	if(cities.isEmpty()) {
		return true;
	} else {
		return false;
	}
}

bool canOfferUniversalCoverage(Set<string>& cities, Vector< Set<string> >& locations,
                               int numHospitals, Vector< Set<string> >& result) {
	if(numHospitals == 0) {
		return false;
	} else if (locations.isEmpty()) {
		return false;
	} else {
		Set<string> element = locations[0];
		locations.remove(0);
		result += element;
		canOfferUniversalCoverage(cities, locations, numHospitals - 1, result);
		if(coversAll(result, cities)) {
			return true;
		}
		result.remove(result.size() - 1);
		canOfferUniversalCoverage(cities, locations, numHospitals, result);
		if(coversAll(result, cities)) {
			return true;
		}
		locations.insert(0, element);
		return false;
	}
}

int main() {
    return 0;
}

