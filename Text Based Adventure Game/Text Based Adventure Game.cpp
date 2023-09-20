#include <iostream>
#include <string>
#include <map>
#include <vector>

// Define a struct for items
struct Item {
    std::string name;
    std::string description;
    bool canPickup;

    Item(const std::string& n, const std::string& desc, bool pickup)
        : name(n), description(desc), canPickup(pickup) {}
};

// Define a struct for rooms
struct Room {
    std::string name;
    std::string description;
    std::map<std::string, Item> items;
    std::map<std::string, Room*> exits;

    Room(const std::string& n, const std::string& desc)
        : name(n), description(desc) {}
};

// Function to display available actions
void showActions() {
    std::cout << "Available actions: " << std::endl;
    std::cout << "1. Look around (look)" << std::endl;
    std::cout << "2. Go to a different room (go <room_name>)" << std::endl;
    std::cout << "3. Pick up an item (take <item_name>)" << std::endl;
    std::cout << "4. Inventory (inventory)" << std::endl;
    std::cout << "5. Quit the game (quit)" << std::endl;
}

int main() {
    // Create rooms
    Room livingRoom("Living Room", "You are in the living room. There is a couch and a table.");
    Room kitchen("Kitchen", "You are in the kitchen. You see a knife on the counter.");
    Room bedroom("Bedroom", "You are in the bedroom. There is a bed and a closet.");

    // Define exits between rooms
    livingRoom.exits["kitchen"] = &kitchen;
    livingRoom.exits["bedroom"] = &bedroom;
    kitchen.exits["livingroom"] = &livingRoom;
    bedroom.exits["livingroom"] = &livingRoom;

    // Create items
    Item knife("knife", "A sharp kitchen knife.", true);
    kitchen.items["knife"] = knife;

    // Player inventory
    std::vector<Item> inventory;

    // Current room
    Room* currentRoom = &livingRoom;

    std::string command;
    bool quit = false;

    std::cout << "Welcome to the Adventure Game!" << std::endl;

    while (!quit) {
        std::cout << std::endl << "You are in the " << currentRoom->name << "." << std::endl;
        std::cout << currentRoom->description << std::endl;

        showActions();

        std::cout << "> ";
        std::cin >> command;

        if (command == "look") {
            // Display items in the current room
            std::cout << "Items in the room: ";
            for (const auto& pair : currentRoom->items) {
                std::cout << pair.first << " ";
            }
            std::cout << std::endl;
        }
        else if (command == "quit") {
            quit = true;
            std::cout << "Thanks for playing!" << std::endl;
        }
        else if (command == "inventory") {
            // Display the player's inventory
            std::cout << "Inventory: ";
            for (const Item& item : inventory) {
                std::cout << item.name << " ";
            }
            std::cout << std::endl;
        }
        else if (command == "go") {
            // Change the current room
            std::string roomName;
            std::cin >> roomName;
            auto exit = currentRoom->exits.find(roomName);
            if (exit != currentRoom->exits.end()) {
                currentRoom = exit->second;
            }
            else {
                std::cout << "Cannot go to that room." << std::endl;
            }
        }
        else if (command == "take") {
            // Pick up an item from the room
            std::string itemName;
            std::cin >> itemName;
            auto item = currentRoom->items.find(itemName);
            if (item != currentRoom->items.end() && item->second.canPickup) {
                inventory.push_back(item->second);
                currentRoom->items.erase(item);
                std::cout << "You picked up the " << itemName << "." << std::endl;
            }
            else {
                std::cout << "Cannot pick up that item." << std::endl;
            }
        }
        else {
            std::cout << "Invalid command. Try again." << std::endl;
        }
    }

    return 0;
}