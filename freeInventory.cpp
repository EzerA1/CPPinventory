#include <iostream>
#include <string>
#include <vector>

namespace InventorySystem {
    class Item {
    private:
        std::string name;
        int quantity;
        double price;

    public:
        Item(const std::string& name, int quantity, double price) : name(name), quantity(quantity), price(price) {}

        std::string getName() const { return name; }
        int getQuantity() const { return quantity; }
        double getPrice() const { return price; }

        void setQuantity(int newQuantity) { quantity = newQuantity; }

        void display() const {
            std::cout << "Name: " << name << ", Quantity: " << quantity << ", Price: $" << price << std::endl;
        }
    };

    class Inventory {
    private:
        std::vector<Item> items;

    public:
        void addItem(const Item& item) {
            items.push_back(item);
        }

        void displayInventory() const {
            std::cout << "Inventory:" << std::endl;
            for (const auto& item : items) {
                item.display();
            }
        }

        Item* findItem(const std::string& name) {
            for (auto& item : items) {
                if (item.getName() == name) {
                    return &item;
                }
            }
            return nullptr;
        }
    };
}

int main() {
    InventorySystem::Inventory inventory;

    inventory.addItem(InventorySystem::Item("ItemZero", 10, 15.99));
    inventory.addItem(InventorySystem::Item("ItemOne", 20, 1.50));

    inventory.displayInventory();

    std::string itemName = "Pen";
    InventorySystem::Item* foundItem = inventory.findItem(itemName);
    if (foundItem != nullptr) {
        foundItem->setQuantity(25);
        std::cout << "Quantity of " << itemName << " updated." << std::endl;
    } else {
        std::cout << "Item not found in inventory." << std::endl;
    }

    std::cout << "Inventory after update:" << std::endl;
    inventory.displayInventory();

    return 0;
}
