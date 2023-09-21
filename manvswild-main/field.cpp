#include "field.h"
#include "tiggers.h"
#include "traps.h"
#include "lions.h"
#include "trees.h"
#include "rocks.h"
#include "normalPlayer.h"


#include <fstream>

#define FIELDSNAME_LOCATION "config/fieldsname.txt"
#define FIELDS_LOCATION "fields/"

using std::string;
using std::cout;
using std::cin;

/**
 * Set all game elements quantities
 */
void field::setGameVariables() {
    int nbOfOneElement {0};

    for(const auto& elementName : d_gameElementString) {
                cout << "Combien de " << elementName << " souhaitez-vous placer ?\n";
                cout << " \x10 ";
                cin >> nbOfOneElement;
                d_nbElements.push_back(nbOfOneElement);
    }
}

/**
 * Search the type of the aimed gameElement
 * @param x - Position x of the search element in the grid
 * @param y - Position y of the search element in the grid
 * @return char - gameElement type
 */
char field::getElementType(int x, int y) const{
        if (d_field[x][y] != nullptr)
            return d_field[x][y]->getElementName();
        else
            return '\0';
};

/**
 * Search if there is a normal player in the grid
 * @return bool - true if normal player is in the grid / false if not
 */
bool field::isNormalPlayer(){
    for (int i=0; i<MAP_SIZE; i++){
        for (int j=0; j<MAP_SIZE; j++){
            if (getElementType(i,j) == 'P'){
                return true;
            }
        }
    }
    return false;
}

bool field::isWildcats(){
    for (int i=0; i<MAP_SIZE; i++){
        for (int j=0; j<MAP_SIZE; j++){
            if (getElementType(i,j) == 'L' || getElementType(i,j) == 'T' ){
                return true;
            }
        }
    }
    return false;
}


/**
 * Search the normal player in the grid
 * @return std::unique_ptr<players> - dynamic pointer of the player
 */
std::unique_ptr<players> field::getNormalPlayer(){
        std::unique_ptr<players> p;
        for (int i=0; i<MAP_SIZE; i++){
            for (int j=0; j<MAP_SIZE; j++){
                if (getElementType(i,j) == 'P'){
                    p = std::make_unique<normalPlayer>('P',i,j);
                    return p;
                }
            }
        }
        return p;
}


std::vector<std::unique_ptr<wildcats>> field::getTiggers()
{
        std::vector<std::unique_ptr<wildcats>> t;
        for (int i=0; i<MAP_SIZE; i++){
            for (int j=0; j<MAP_SIZE; j++){
                if (getElementType(i,j) == 'T')
                    t.push_back(std::make_unique<tiggers>('T',i,j));

                }
            }

        return t;
}
std::vector<std::unique_ptr<wildcats>> field::getLions()
{
        std::vector<std::unique_ptr<wildcats>> l;
        for (int i=0; i<MAP_SIZE; i++){
            for (int j=0; j<MAP_SIZE; j++){
                if (getElementType(i,j) == 'L')
                    l.push_back(std::make_unique<lions>('L',i,j));

                }
            }

        return l;
}


/**
 * Set the normal player in the grid
 * @param x - Current position x of the normal player
 * @param y - Current position y of the normal player
 * @param xA - Future position x of the normal player
 * @param yD - Future position y of the normal player
 */
void field::setNormalPlayerInField(int x, int y, int xA, int yA){
    if (getElementType(xA,yA) == 'H'){
        d_field[x][y] = nullptr;
    }
    else{
        d_field[x][y] = nullptr;
        d_field[xA][yA] = std::make_unique<normalPlayer>('P',xA,yA);
    }
}

void field::setTiggerInField(int x, int y, int xA, int yA)
{
    if (getElementType(xA,yA) == 'H'){
        d_field[x][y] = nullptr;
    }
    else{
        if(getElementType(xA,yA == 'P'))
        {
            d_field[xA][yA] = nullptr;
        }
        d_field[x][y] = nullptr;
        d_field[xA][yA] = std::make_unique<tiggers>('T',xA,yA);
    }
}

void field::setLionInField(int x, int y, int xA, int yA)
{
    if (getElementType(xA,yA) == 'H'){
        d_field[x][y] = nullptr;
    }
    else{
        if(getElementType(xA,yA == 'P'))
        {
            d_field[xA][yA] = nullptr;
        }


        d_field[x][y] = nullptr;
        d_field[xA][yA] = std::make_unique<lions>('L',xA,yA);
    }
}

/**
 * Create a field
 * @param fieldName - name of the field file
 */
void field::createField(const string& fieldName){

    setGameVariables();

    // Initiliaze the field with only nullptr
    d_field.resize(MAP_SIZE); // Set number of lines in the field
    for(auto& elem : d_field) {
        elem.resize(MAP_SIZE); // Set number of columns for a line in the field
        for(auto& e : elem)
            e = nullptr;
    }

    int selectedElement {-1};
    int row {-1};
    int column {-1};
    bool allElementsPlaced {false};

    while(!allElementsPlaced) {
        showMap();

        cout << "\nQue souhaitez vous placer : ";

        for(unsigned index = 0; index < d_gameElementString.size(); index++) {
            // Can't use \t here because sometimes it's doesn't apply
            cout << "    " << index << ") " << d_gameElementString[index] << " [restants : " << d_nbElements[index] << "]";
        }

        do {
            cout << "\nVeuillez entrer un numero correct";
            cout << "\n\x10"; // Affiche une flèche pour entrer son choix
            cin >> selectedElement;
        } while(selectedElement < 0 || selectedElement >= d_gameElement.size());

        do {
            cout << "Ou souhaitez vous le placer ?\n";
            cout << "Ligne : ";
            cin >> row;
            cout << "Colonne : ";
            cin >> column;
        } while (row < 0 || row >= MAP_SIZE || column < 0 || column >= MAP_SIZE);


        if(d_field[row][column] == nullptr) {

            if(d_nbElements[selectedElement] > 0) {

                addElementOnField(selectedElement, row, column);

                d_nbElements[selectedElement] -= 1; // Remove 1 quantity from the number of the selected game element

                if(allGameElementsPlaced())
                    allElementsPlaced = true;

            } else {
                cout << "Tous les " << d_gameElementString[selectedElement] << "s sont deja mis\n";
            }
        } else {
            cout << "\nCette case est deja prise \n";
        }
    }

    cout << "Terrain cree avec succes\n";
    cout << "Enregistrement du terrain...\n";

    if(writeInFile(fieldName)) {
        cout << "Terrain enregistre\n";
        addFieldName(fieldName);
    }
}

/**
 * This method shows the field
 */
void field::showMap() const {

    int ligne {0};

    cout << "\n | ";
    for(int colonne = 0; colonne < MAP_SIZE; colonne++)
        cout << colonne << " ";

    cout << "\n";

    for(const auto& elements : d_field) {
        cout << ligne << "| ";
        // Change this loop with a for(int i = 0; i < elements.size(); i++)
        for(const auto& element : elements) {
            // use std::left and setw(i * 10)
            if(element != nullptr) {
                // cout elements[i]
                cout << element->getElementName() << " ";
            }
            else {
                cout << ". ";
            }
        }
        ++ligne;
        cout << "\n";
    }

    cout << "\n";
}

/**
 * This method import a field
 * @param fieldName - the name of the file
 */
void field::importMap(const string& fieldName) {
    std::ifstream mapFile (FIELDS_LOCATION + fieldName);
    char elementType;

    d_field.clear(); // clear the field to make sure nothing is already load on it

    std::vector<std::unique_ptr<gameElement>> fieldLine;

    if(!mapFile.is_open()) {
        std::cerr << "Erreur, impossible de charger la carte a cet emplacement\n";
    } else {
        for(int i = 0; i < MAP_SIZE; i++) {
            for(int j = 0; j < MAP_SIZE; j++) {
                mapFile >> elementType;

                switch(elementType) {

                    case 'T':
                        fieldLine.push_back(std::make_unique<tiggers>(elementType,i,j));
                        break;

                    case 'L':
                        fieldLine.push_back(std::make_unique<lions>(elementType,i,j));
                        break;

                    case 'R':
                        fieldLine.push_back(std::make_unique<rocks>(elementType,i,j));
                        break;

                    case 'W':
                        fieldLine.push_back(std::make_unique<trees>(elementType,i,j));
                        break;

                    case 'P':
                        fieldLine.push_back(std::make_unique<normalPlayer>(elementType,i,j));
                        break;

                    case 'H':
                        fieldLine.push_back(std::make_unique<traps>(elementType,i,j));
                        break;

                    default:
                        fieldLine.push_back(nullptr);
                        break;

                }

            }
            d_field.push_back(std::move(fieldLine));
            fieldLine.clear();
        }
    }

    mapFile.close();
    showMap();
}

/**
 * This method select a field
 */
void field::selectField() {
            std::string fieldName;
            showFieldsName();

            do {
                cout << "Quel terrain choississez-vous ?\n \x10 ";
                cin >> fieldName;
                d_fieldName = fieldName;
            } while(!existingField(fieldName));

            importMap(fieldName);
}

/**
 *  Return the name of the selected field
 * @return string - field name
 */
std::string field::getFieldName() const {
    return d_fieldName;
}

/**
 * This method permit to edit a field
 * @param fieldName - the name of the file
 */
void field::editField(const std::string& fieldName) {
    int row {-1};
    int column {-1};
    int modify {-1};
    int choice {-1};
    int selectedElement {-1};

        // 1 = change an element on the field | 2 = leave
        while(modify != 2) {
            cout << "1) Modifier une case du terrain\t 2) Quitter\n";
            cout << " \x10 ";
            cin >> modify;

            if(modify == 1) {

                do {
                    cout << "Quel case souhaitez-vous modifier?\n";
                    cout << "Ligne : ";
                    cin >> row;
                    cout << "Colonne : ";
                    cin >> column;
                } while (row < 0 || row >= MAP_SIZE || column < 0 || column >= MAP_SIZE);

                if(d_field[row][column] == nullptr) {
                    cout << "Souhaitez-vous ajouter un element ?\n";
                    cout << "1) Oui\t 2) Non\n";
                    cout << " \x10 ";
                    cin >> choice;

                    if(choice == 1) {
                        cout << "\nQue souhaitez vous placer : ";

                        for(int index = 0; index < d_gameElementString.size(); index++) {
                            // Can't use \t here because sometimes it's doesn't apply
                            cout << "    " << index << ") " << d_gameElementString[index] << "\t";
                        }

                        do {
                            cout << "\nVeuillez entrer un numero correct";
                            cout << "\n\x10"; // Affiche une flèche pour entrer son choix
                            cin >> selectedElement;
                        } while(selectedElement < 0 || selectedElement >= d_gameElement.size());

                        addElementOnField(selectedElement,row,column);

                    }

                } else {
                    cout << "Souhaitez-vous supprimer cet element ?\n";
                    cout << "1) Oui\t 2) Non\n";
                    cout << " \x10 ";
                    cin >> choice;

                    if(choice == 1) {
                        d_field[row][column] = nullptr;
                    }
                }
            }

            showMap();
        }

        // Save the edited file
        writeInFile(fieldName);

}

/**
 * add an element on the field
 * @param selectedElement
 * @param row index of the line on the field
 * @param column index of  the column on the field
 */
void field::addElementOnField(int selectedElement, int row, int column) {

    switch(selectedElement) {

        case 0 :
            d_field[row][column] = std::make_unique<normalPlayer>('P',row,column);
            break;

        case 1 :
            d_field[row][column] = std::make_unique<trees>('W',row,column);
            break;

        case 2 :
            d_field[row][column] = std::make_unique<rocks>('R',row,column);
            break;

        case 3 :
            d_field[row][column] = std::make_unique<lions>('L',row,column);
            break;

        case 4 :
            d_field[row][column] = std::make_unique<tiggers>('T',row,column);
            break;

        case 5 :
            d_field[row][column] = std::make_unique<traps>('H',row,column);
            break;

        default:
            break;

    }
}

/* ############################ PRIVATE METHODS ############################ */

/**
 * Check if the player placed all the game elements
 * @param fieldName the field file name
 * @return true if the file already exists
 */
bool field::existingField(const string& fieldName) {
    for(const auto& field : d_fieldsName) {
        if(fieldName == field)
            return true;
    }

    cout << "/!\\ Veuillez ecrire un nom de terrain existant /!\\ \n\n";
    return false;
}

/**
 * Show all the field file names
 */
void field::showFieldsName() {
        getFieldsName();

        for(const auto& field : d_fieldsName) {
            cout << field << "\n";
        }
        cout << "\n";
}

/**
 * This method write a field content in a file
 * @param fieldName the name of the file
 * @return true if successfully written otherwise false
 */
bool field::writeInFile(const string& fieldName) {

    std::ofstream newField (FIELDS_LOCATION + fieldName);

    if(!newField.is_open()) {
        std::cerr << "Erreur, impossible de creer le fichier de votre terrain\n";
        return false;
    } else {
        for(const auto& elements : d_field) {
            for(const auto& element : elements) {
                if(element == nullptr) {
                    newField << '.';
                } else {
                    newField << element->getElementName();
                }
            }
            newField << "\n";
        }

        newField.close();
        return true;
    }
}

/**
 * Add the given field name to the file storing all the fields names
 * @param fieldName name of the field file
 */
void field::addFieldName(const string& fieldName) {
    std::ofstream namesFile (FIELDSNAME_LOCATION, std::fstream::app);

    if(!namesFile.is_open()) {
        std::cerr << "Erreur, impossible d'ouvrir le fichier contenant les noms des terrains\n";
    } else {
        namesFile << "\n" << fieldName;
    }

    namesFile.close();
}

/**
 * Retrieve all the field file names
 */
void field::getFieldsName() {
    std::ifstream fieldsNameFile (FIELDSNAME_LOCATION); // Open the file
    d_fieldsName.clear(); // Clearing all old values

    if(!fieldsNameFile.is_open()) {
        std::cerr << "Erreur, impossible d'ouvrir le fichier contenant le nom des terrains de jeu\n";
    } else {
        string fieldName; // Variable that stores step by step each field name

        while(std::getline(fieldsNameFile, fieldName)) {
            d_fieldsName.push_back(fieldName);
        }

        fieldsNameFile.close();
    }
}

/**
 * Check if the player placed all the game elements
 * @return true if all elements have been placed
 */
bool field::allGameElementsPlaced() const {

    bool check {true};

    for(const auto& nbEachElement : d_nbElements) {
        // Check if at least 1 game element isn't placed
        if(nbEachElement > 0)
            check = false;
    }

    return check;
}
