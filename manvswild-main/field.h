#ifndef FIELD_H
#define FIELD_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "gameElement.h"
#include "players.h"
#include "wildcats.h"
#include "tiggers.h"
#include "lions.h"
// Game parameters
#define MAP_SIZE 8
#define NB_PARAMETERS 5

/**
 *  Represent a field
 */
class field {
public:
    field() = default; // Default empty constructor used to load a field

    void showMap() const; // Show map content
    void createField(const std::string& mapName); // Create a map
    void importMap(const std::string& mapName); // import map from file

    char getElementType(int x, int y) const;

    bool isNormalPlayer();
    bool isWildcats();

    std::unique_ptr<players> getNormalPlayer();
    std::vector<std::unique_ptr<wildcats>> getTiggers();
    std::vector<std::unique_ptr<wildcats>> getLions();

    void setNormalPlayerInField(int x, int y, int xA, int yA);
    void setTiggerInField(int x, int y, int xA, int yA);
    void setLionInField(int x, int y, int xA, int yA);

    void selectField();
    void editField(const std::string& fieldName);
    void setGameVariables(); // Set game variables based on gameElement vector;
    std::string getFieldName() const;
private:
    // Private methods
    bool allGameElementsPlaced() const; // Check if the user placed all the game elements
    void addElementOnField(int selectedElement, int row, int column);

    // Private methods managing files
    void showFieldsName(); // show all map (fields) names
    bool existingField(const std::string& fieldName); // Check if the given field already exists
    bool writeInFile(const std::string& fieldName);
    void addFieldName(const std::string& fieldName); // Add fieldname into the file that's saving all field names
    void getFieldsName(); // Retrieve all map (fields) names

    // Variables
    std::vector<std::vector<std::unique_ptr<gameElement>>> d_field; // Represent the game grid, a 2D vector containing gameElement (n
    std::vector<std::string> d_fieldsName;

    // P : player, W : wood = tree, R : rock, H : hole = trap, L : lion, T : tigger
    std::vector<char> d_gameElement {'P','W','R','L','T','H'};
    std::vector<std::string> d_gameElementString {"joueur","arbre","rocher","lion","tigre","piege"};
    std::vector<int> d_nbElements; // Each box represent the number of 1 type of gameElement

    std::string d_fieldName;
};


#endif // FIELD_H
