#pragma once
// Include the all needed header files.
#include "json.hpp"
#include <vector>
#include <random>
#include <fstream>
#include <string>


// Standard namespace.
using namespace std;

using json = nlohmann::json;

// Initialize the room struct.
struct Room
{
	int roomNum = 0;
	int roomType = 0;
	double cost = 0.0;

	string name = " ";
	int reservationNumber = 0, 
		numberOfNights = 0,
		discount = 0;
	double reservationPrice = 0.0;
	bool reserved = false;
	
};

// Reads the previous session from the file,
// or generates an even amount of rooms in range of 40-300.
void setupRooms(vector<Room>& rooms) {

	// Initialize the variables.
	string line;
	ifstream roomsFile("Rooms.json");

	// Generate rooms if the file doesn't exist.
	if (roomsFile.fail()) {

		// Initialize the variables.
		Room tempRoom;
		int random = 0;

		// Initialize the random number generator.
		random_device rnd;
		mt19937 gen(rnd());
		uniform_int_distribution<> roomDist(19, 149);
		//uniform_int_distribution<> costDist(79, 99);


		// Generate an even number between 40 and 300.
		// (e.g., 2 * (19 + 1) = 40 or 2 * (20 + 1) = 42 etc.).
		random = 2 * (roomDist(gen) + 1);

		// 
		for (int i = 0; i < random; i++) {
			
			// 2 - 3p 
			//roomCost = (double)(costDist(gen)) + 0.99;			

			// Rooms for one person.
			if ( i < (random / 2)) {
				tempRoom = { i + 1, 1, 100};	// Room number, room sizes, prize			
			}
			// Rooms for two persons.
			else {
				tempRoom = { i + 1, 2, 150};	// Room number, room size, prize	
			}

			// Adds the room to the rooms vector.
			rooms.push_back(tempRoom);
		}
	}

	// Read the reservations from the file.
	else {
		try {
			json j(json::parse(roomsFile));

			Room tempRoom;

			for (json i : j) {

				tempRoom = { i["roomNum"],
					i["roomType"],
					i["cost"],
					i["name"],
					i["reservationNumber"],
					i["numberOfNights"],
					i["discount"],
					i["reservationPrice"],
					i["reserved"] };

				rooms.push_back(tempRoom);
			}					
		}
		catch (exception e) {
			cout << "Error: " << e.what();
		}		
	}
}

void from_json(const json& j, Room& room) {
	j.at("roomNum").get_to(room.roomNum);
}

// 
bool isRoomReserved(vector<Room>& rooms, int roomIndex) {

	bool isRoomReserved = false;

	isRoomReserved = rooms[roomIndex].reserved;

	return isRoomReserved;
}

// 
void saveReservationsToFile(vector<Room> rooms) {

	// 
	json j;
	ofstream roomsFile;
	vector<json> jsonRoom;

	try {

		roomsFile.open("rooms.json");

		if (roomsFile.is_open()) {

			for (int i = 0; i < rooms.size(); i++) {

				j = json{ {"roomNum", rooms.at(i).roomNum},
					{"roomType", rooms.at(i).roomType},
					{"cost", rooms.at(i).cost},
					{"name", rooms.at(i).name},
					{"reservationNumber", rooms.at(i).reservationNumber},
					{"numberOfNights", rooms.at(i).numberOfNights},
					{"discount", rooms.at(i).discount},
					{"reservationPrice", rooms.at(i).reservationPrice},
					{"reserved", rooms.at(i).reserved} };
				
				jsonRoom.push_back(j);

			}
				roomsFile << setw(4) << jsonRoom << endl;
		}

		roomsFile.close();
	}
	catch (exception e) {
		cout << "Error: " << e.what();
	}	
}

// Calculates the reservation prize.
double calculateReservationPrice(int nights, int price, int discount) {

	double calculatedPrice = 0.0;

	if (discount == 0) {
		calculatedPrice = nights * price;
	}
	else {
		// (e.g., -20%) price * 100 - 20 => price * 0.8   
		calculatedPrice = ((double)nights * (double)price) * (1.0 - discount / 100.0);
	}
	return calculatedPrice;
}
