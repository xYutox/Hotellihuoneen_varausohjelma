#pragma once
#include "InputChecker.h"
#include "Room.h"
#include <random>
#include <string>

using namespace std;

// 
int makeReservation(vector<Room>& rooms, int numberOfRooms) {

	try {

		// Initialize the variables.
		Room tempRoom;
		char c = ' ';
		char confirm = ' ';
		bool reservationNumCheck = false;
		int roomSize = 0,
			randomRoomIndex = 0,
			minRoomIndex = 0,
			maxRoomIndex = 0,
			discountPercentage = 0;

		// Reservation info
		string name = "";
		int roomNumberIndex = 0,
			reservationNum = 0,
			nights = 0;
		double price = 0.0;

		// Initialize the random number generator.
		random_device rnd;
		mt19937 gen(rnd());
		uniform_int_distribution<> reservationDist(10000, 99999);
		uniform_int_distribution<> discountDist(1, 3);

		// Generate a unique reservation number.
		do {
			reservationNum = reservationDist(gen);
			reservationNumCheck = false;

			// Checks if the generated reservation number already exists.
			for (auto& room : rooms) {

				if (room.reservationNumber == reservationNum) {
					reservationNumCheck = true;
				}
			}
		} while (reservationNumCheck == true);

		system("cls");
		cout << "=====================\n"
			<< "Make reservation.\n"
			<< "=====================\n\n";

		/*
		* Asks the name.
		*/

		name = inputChecker<string>();

		for (char& c : name) {
			c = tolower(c);
		}

		/*
		* Select the room number.
		*/

		//Asks for the room number.
		cout << "\n=====================\n\nDo you want to rent room for 1 or 2 persons. (1/2): ";
		roomSize = inputChecker<int>(1, 2);

		// Select rooms for one or two people.
		if (roomSize == 1) {
			minRoomIndex = 0;
			maxRoomIndex = (rooms.size() / 2) - 1;
		}
		else if (roomSize == 2) {
			minRoomIndex = rooms.size() / 2;
			maxRoomIndex = numberOfRooms - 1;
		}

		// Check are there any room available.
		for (int i = minRoomIndex; i <= maxRoomIndex; i++) {
		
				
		}

		cout << "\n=====================\n\n"
			<< "Recommend available room?\n\n";

		// 
		c = toupper(inputChecker<char>(c));

		// 
		if (c == 'Y') {

			// Generate random room numbers until a free one is found.
			do {
				// Get a random room with selected room size.
				uniform_int_distribution<> roomDist(minRoomIndex, maxRoomIndex);
				randomRoomIndex = roomDist(gen);

				// Checks if the generated room is already reserved.
			} while (isRoomReserved(rooms, randomRoomIndex) == true);

			roomNumberIndex = randomRoomIndex;
		}
		// Prints the rooms from the vector of the selected size.
		else if (c == 'N') {
			cout << "\n\n=====================\n\n"
				<< "Select a room and enter room number."
				<< "\n\n=====================\n\n"
				<< "Room number: \tRoom size: \tPrize per night (e):" << endl;
			for (int i = minRoomIndex; i <= maxRoomIndex; i++) {
				cout << rooms[i].roomNum
					<< " \t\t" << rooms[i].roomType << " person(s)"
					<< " \t" << rooms[i].cost << endl;
			}
			cout << "\n=====================\n\n"
				<< "Enter the number of a room: ";

			roomNumberIndex = inputChecker<int>(minRoomIndex + 1, maxRoomIndex + 1) - 1;

			// Checks if the selected rooms is already reserved.
			while (isRoomReserved(rooms, roomNumberIndex) == true) {
				cout << "Sorry this room is already reserved! Enter an another room: ";
				roomNumberIndex = inputChecker<int>(minRoomIndex + 1, maxRoomIndex + 1) - 1;
			}
		}

		/*
		* Number of nights
		*/

		// Asks how many night to reserve.
		cout << "\n=====================\n\n"
			<< "How many night you will stay?: ";
		nights = inputChecker<int>(1);

		/*
		* Discount percentage
		*/

		// Calculate the possible discount.
		switch (discountDist(gen)) {
		case(1):
			discountPercentage = 0;
			break;
		case(2):
			discountPercentage = 10;
			break;
		case(3):
			discountPercentage = 20;
		}

		// Calculates the price to the reservation.
		price = calculateReservationPrice(nights, rooms[roomNumberIndex].cost, discountPercentage);

		cout << "\n\n=====================\n\n" 
			<< "Price for the reservation is " << price << " (e).";

		cout << "\n\nConfirm reservation? ";

		confirm = toupper(inputChecker<char>(confirm));

		// Save the reservation.
		if (confirm == 'Y') {

			tempRoom.roomNum = roomNumberIndex + 1;
			tempRoom.roomType = roomSize;
			tempRoom.cost = rooms[roomNumberIndex].cost;
			tempRoom.reservationNumber = reservationNum;
			tempRoom.name = name;
			tempRoom.numberOfNights = nights;
			tempRoom.reserved = true;
			tempRoom.discount = discountPercentage;
			tempRoom.reservationPrice = price;
			
			rooms.at(roomNumberIndex) = tempRoom;

			return 0;
		}
		else {
			return 1;
		}
	}
	catch (exception e) {
		cout << "Error: " << e.what();
		return 1;
	}
}

// Shows the reserved rooms.
void showAllReservations(vector<Room> rooms) {

	// Initialize the variables.
	char c = ' ';

	system("cls");

	cout << "=====================\nReservations\n=====================\n\n";

	for (int i = 0; i < rooms.size(); i++) {

		if (rooms.at(i).reserved == true) {
			cout << "Room number: " << rooms.at(i).roomNum << endl
				<< "Reservation number: " << rooms.at(i).reservationNumber << endl
				<< "Reserved by: " << rooms.at(i).name << endl
				<< "Duration: " << rooms.at(i).numberOfNights << " nights" << endl
				<< "Price: " << rooms.at(i).reservationPrice <<"e" << endl
				<< "Discount: " << rooms.at(i).discount << "%\n\n";
		}
	}

	cout << "=====================\n\n"
		<< "Return to menu?\n\n";

	c = toupper(inputChecker<char>(c, ("Y")));
}

// Searches a reserved room
void searchReservation(vector<Room> rooms) {

	// Initialize the variables.
	int userInput = 0;
	int reservationNum = 0;
	string name = "";
	char c = ' ';
	vector<int> roomIndex(0);

	// Clears the console.
	system("cls");

	// Asks the user to select the search method.
	cout << "=====================\nSearch reservation\n=====================\n\n"
		<<"Search with name (1) or (2) reservation number? ";

	userInput = inputChecker<int>(1, 2);

	if (userInput == 1) {
		name = inputChecker<string>();		// Search with name.

		for (char& c : name) {
			c = tolower(c);
		}
				
	}
	else {
		cout << "\nEnter the reservation number: ";
		reservationNum = inputChecker<int>(10000, 99999);	// Search with number.
	}

	for (int i = 0; i < rooms.size(); i++) {

		if (rooms.at(i).name == name || rooms.at(i).reservationNumber == reservationNum && rooms.at(i).reservationNumber != 0) {
			
			roomIndex.push_back(rooms.at(i).roomNum - 1);
		
		}		
	}

	if (roomIndex.size() > 0) {

		cout << "\nReservation found!\n\n";

		for (int i : roomIndex) {

			cout << "Room number: " << rooms.at(i).roomNum << endl
				<< "Reservation number: " << rooms.at(i).reservationNumber << endl
				<< "Reserved by: " << rooms.at(i).name << endl
				<< "Duration: " << rooms.at(i).numberOfNights << " nights" << endl
				<< "Price: " << rooms.at(i).reservationPrice << "e" << endl
				<< "Discount: " << rooms.at(i).discount << "%\n\n";	
		}
	}
	else {
		cout << "\nNo reservations found!\n\n";
	}

	cout << "=====================\n\n"
		<< "Return to menu?\n\n";

	do {
		c = toupper(inputChecker<char>(c, "(Y)"));

	} while (c != 'Y');
}

// Deletes the reservation from the vector.
void deleteReservation(vector<Room> &rooms) {

	system("cls");

	cout << "=====================\nDelete reservation\n=====================\n\n";

	// Initialize the variables.
	Room emptyRoom;
	int reservationNum = 0;

	cout << "Enter the reservation number to delete: ";

	 reservationNum = inputChecker<int>(10000, 99999);

	for (int i = 0; i < rooms.size(); i++) {

		if (rooms.at(i).reservationNumber == reservationNum) {
			rooms.at(i) = emptyRoom;
		}
	}
}

// Prints the menu to the console.
void printMenu(int reserved) {

	// Clears the the console.
	system("cls");

	cout << "=====================\n"
		<< "Hotel reservation\n"
		<< "=====================\n\n"
		<< "Available rooms: " << reserved << endl
		<< "\n(1) Make a new reservation.\n"
		<< "(2) Show the all reservations.\n"
		<< "(3) Search a reservation.\n"
		<< "(4) Delete a reservation.\n"
		<< "(-1) Close the application.\n\n"
		<< "=====================\n\n"
		<< "Enter a number to select an action (1-4) or (-1) to close the application: ";
}
