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
        bool addItem(const Item& item) {
            for (const auto& existingItem : items) {
                if (existingItem.getName() == item.getName()) {
                    std::cout << "Error: Item '" << item.getName() << "' already exists in the inventory." << std::endl;
                    return false;
                }
            }
            items.push_back(item);
            std::cout << "Item '" << item.getName() << "' added to the inventory." << std::endl;
            return true;
        }

        void displayInventory() const {
            std::cout << "Inventory:" << std::endl;
            for (const auto& item : items) {
                item.display();
            }
        }
    };
}

int main() {
    InventorySystem::Inventory inventory;

    inventory.addItem(InventorySystem::Item("ItemZero", 10, 15.99));
    inventory.addItem(InventorySystem::Item("ItemOne", 20, 1.50));
    inventory.addItem(InventorySystem::Item("ItemZero", 5, 12.50)); // Duplicate item example ezra

    inventory.displayInventory();

    return 0;
}
