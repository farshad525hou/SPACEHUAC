/*
 * Copyright 2013 Daniel Warner <contact@danrw.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#include <CoordTopocentric.h>
#include <CoordGeodetic.h>
#include <Observer.h>
#include <SGP4.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <fstream> 

using namespace std;


int main()
{
	ofstream Out;
	Out.open("out.txt");

    Observer obs(51.507406923983446, -0.12773752212524414, 0.05);
    Tle tle = Tle("ISS (ZARYA)             ",
        "1 25544U 98067A   17195.87565972  .00001417  00000-0  28645-4 0  9994",
        "2 25544  51.6423 260.3080 0005347  36.4034 304.6822 15.54165554 66054");
    SGP4 sgp4(tle);

    std::cout << tle << std::endl;

    for (int i = 0; i < 1000; ++i)
    {
        /*
         * current time
         */
        DateTime now = DateTime::Now(true);
        /*
         * calculate satellite position
         */
        Eci eci = sgp4.FindPosition(now);
        /*
         * get look angle for observer to satellite
         */
        CoordTopocentric topo = obs.GetLookAngle(eci);
        /*
         * convert satellite position to geodetic coordinates
         */
        CoordGeodetic geo = eci.ToGeodetic();
	
        Out << now << " " << topo << " " << geo << std::endl;
	sleep(1);


    };

    return 0;
}
