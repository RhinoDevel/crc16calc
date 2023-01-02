This is a CRC-16 generator preconfigured with input values to generate a CRC-16-CCITT (X.25) checksum the way it should be calculated by devices sending SML (Smart Message Language) messages, e.g. so called smart meters (measuring the consumed energy and more) as the Iskra MT175 does.

It is based on source code from Sven Reifegerste (see http://www.zorc.breitbandkatze.de/crc.html).

Please take a look at the (short) function getCrc16ForBytes() that does the calculation (almost everything else is code to make the website work).

There is also a C port in the subfolder called "C", it holds the two library files and a commandline tool to calculate and print the CRC value from a commandline argument.