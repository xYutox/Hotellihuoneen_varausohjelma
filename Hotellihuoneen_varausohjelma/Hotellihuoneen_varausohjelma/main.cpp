// Joel Juntunen

// Include the all needed header files.
#include "Menu.h"
#include "InputChecker.h"
#include "Room.h"
#include <vector>
#include <iostream>

//
using namespace std;

int main() {

	setlocale(LC_ALL, "FI_fi");

	// Initialize the variables.
	const int SENTINEL = -1;			//
	vector<Room> rooms(0);				//
	int reservedRoomsCounter = 0,		//
		numberOfRooms = 0,				//
		userInput = 0;					//
	bool reservationSuccess = false;	//

	// Generate the rooms or read the previous session from the file.
	setupRooms(rooms);

	numberOfRooms = rooms.size();

	for (Room& room : rooms) {
		if (room.reserved) {
			reservedRoomsCounter += 1;
		}
	}

	// Loops until the user enters the SENTINEL value.
	do
	{
		try {

			// Print the menu options.
			printMenu(numberOfRooms - reservedRoomsCounter);

			userInput = inputChecker<int>(1, 4, SENTINEL);

			// Select the action.
			switch (userInput) {

				// Make reservation
				case(1):	
					reservationSuccess = makeReservation(rooms, numberOfRooms);

					if (reservationSuccess == 0) {
						reservedRoomsCounter += 1;
					}
					break;

				case(2):
					// Show all reservations.
					showAllReservations(rooms);
					break;
				case(3):
					// Search for the specific reservations
					searchReservation(rooms);
					break;
				case(4):
					// Delete reservation
					deleteReservation(rooms);
					break;
			}
						
		}
		catch (exception e) {
			cout << "Error: " << e.what();
		}

	} while (!(userInput == SENTINEL) && !(reservedRoomsCounter == numberOfRooms));

	// Write the reservations to the file.
	saveReservationsToFile(rooms);


	return 0;
}
