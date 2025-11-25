#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <windows.h> 
#include <conio.h> 

#define MAX_ORDER 200
#define PASSWORD "1234567"
#define MAX_PASS_LEN 32      
#define MENU_FILE "cafeteria_menu.txt" 
#define BREAKFAST_N 7
#define BRUNCH_N 8
#define LUNCH_N 10
#define PIZZA_N 3
#define BURGER_N 3
#define CLUB_N 2
#define DRINKS_N 4
#define SAMOSA_N 3
#define MAX_SALES 100
#define DISCOUNT_THRESHOLD 20.0f
#define DISCOUNT_RATE 0.10f 
#define GST_RATE 0.15f      
#define COLOR_DEFAULT 7
#define COLOR_GREEN 10
#define COLOR_CYAN 11
#define COLOR_RED 12
#define COLOR_MAGENTA 13
#define COLOR_YELLOW 14
#define COLOR_WHITE 15

typedef struct {
    char name[50];
    float price;
    float price_s;
    float price_m;
    float price_l;
    int stock;
    int has_size; 
} MenuItem;

typedef struct {
    char name[80]; 
    char size[10]; 
    float unit_price;
    int quantity;
    float total_price;
} OrderItem;

typedef struct {
    char customerName[80];
    float subtotal;
    float discountApplied;
    float gstApplied; 
    float finalTotal;
    time_t timestamp;
} SaleRecord;

OrderItem orders[MAX_ORDER];
int orderCount = 0;
SaleRecord salesHistory[MAX_SALES];
int saleCount = 0;
int hasOrderedDrink = 0; 

const char *funnyGreetings[] = {
    "Welcome! Our food is so good, even the chef is hungry.",
    "Please place your order before the chef sleeps... again.",
    "Warning: Our food cause extreme happiness!",
    "Today's special: Whatever the chef accidentally cook.",
    "We sell happiness by the plate. ",
    " skip diet order everything."
};
#define GREETINGS_N 6
const char *takingOrderJokes[] = {
    "Processing your order... just wait and then enjoyy ",
    "Loading deliciousness... Too yummy!",
    "Adding calories... I mean food... to your plate.",
    "Our food is 100% best ",
    "If food is life, then welcome to your new home!",
    "We're not responsible for food coma  after this meal. Enjoy!",
    "Item confirmed. Prepare your stomach to be over load.",
    "Checking inventory... Yep, we still have amazing food."
};
#define TAKING_ORDERS_N 8

const char *pizzaFunLines[] = {
    "Pizza solves 99% of problems. The other 1% requires more pizza.",
    "Life is short. Eat the  pizza.",
   // "Small pizza? Medium? Large? Choose wisely - your happiness depends on it!",
    "In crust we trust.",
    "A balanced diet means a slice in each hand."
};
#define PIZZA_FUN_N 5

const char *drinksFunLines[] = {
    "Cold drink coming... don't shake the screen!",
    " wait and pop the drink .",
    "Juice selected - vitamin happiness added.",
    "Need caffeine? We speak fluent coffee.",
    "enjoy yourr drinkk yehhhh."
};
#define DRINKS_FUN_N 5

const char *billJokes[] = {
    "Your bill is ready! Your wallet might cry, but your stomach will celebrate.",
    "Money doesn't buy happiness... but it buys food, and that's basically the same.",
    "Bill printed! Please pay before the chef starts eating your order.",
    "empty you wallet sir you just loved food "
};
#define BILL_JOKES_N 5

MenuItem breakfast[BREAKFAST_N] = {
    {"Pancake", 2.50f, 0,0,0, 20, 0},
    {"Omelette", 3.00f, 0,0,0, 20, 0},
    {"Paratha", 2.00f, 0,0,0, 20, 0},
    {"Coffee", 0, 3.00f, 4.50f, 6.00f, 30, 1}, 
    {"Tea", 0, 2.00f, 3.00f, 4.00f, 30, 1},
    {"Bread & Jam", 1.50f, 0,0,0, 25, 0},
    {"French Toast", 2.50f, 0,0,0, 15, 0}
};

MenuItem samosaMenu[SAMOSA_N] = {
    {"Aloo Samosa", 1.50f,0,0,0, 40, 0},
    {"Macaroni Samosa",2.00f,0,0,0, 25, 0},
    {"Paneer Samosa",2.50f,0,0,0, 20, 0}
};

MenuItem drinks[DRINKS_N] = {
    {"Coffee",0,2.50f,4.00f,5.50f, 50, 1},
    {"Tea",0,1.50f,2.50f,3.50f, 50, 1},
    {"Cold Drink",0,3.00f,4.50f,6.00f, 60, 1},
    {"Juice",0,3.50f,5.00f,7.00f, 40, 1}
};

MenuItem brunch[BRUNCH_N] = {
    {"Samosa",0,0,0,0, 0, 0}, 
    {"Chaat",3.00f,0,0,0, 20, 0},
    {"Gol Gappay",2.50f,0,0,0, 30, 0},
    {"Brownies",2.00f,0,0,0, 25, 0},
    {"Slice of Club Sandwich",3.50f,0,0,0, 20, 0},
    {"Macaroni",4.00f,0,0,0, 15, 0},
    {"Drinks",0,0,0,0, 0, 0}, 
    {"Cake Slice",2.50f,0,0,0, 15, 0}
};

MenuItem pizzaMenu[PIZZA_N] = {
    {"Veg Pizza",0,10.00f,15.00f,20.00f, 10, 1},
    {"Chicken Pizza",0,12.00f,18.00f,25.00f, 8, 1},
    {"BBQ Pizza",0,14.00f,20.00f,28.00f, 6, 1}
};
MenuItem burgerMenu[BURGER_N] = {
    {"Zinger Burger",6.00f,0,0,0, 20, 0},
    {"Mayo Burger",5.50f,0,0,0, 20, 0},
    {"Cheese Burger",6.50f,0,0,0, 15, 0}
};

MenuItem clubMenu[CLUB_N] = {
    {"Chicken Club",5.50f,0,0,0, 12, 0},
    {"Veg Club",4.50f,0,0,0, 12, 0}
};

MenuItem lunch[LUNCH_N] = {
    {"Pizza",0,0,0,0, 0, 0}, 
    {"Burgers",0,0,0,0, 0, 0}, 
    {"Club Sandwich",0,0,0,0, 0, 0}, 
    {"Haleem",4.00f,0,0,0, 15, 0},
    {"Karahi",5.00f,0,0,0, 12, 0},
    {"Tikka ",4.50f,0,0,0, 18, 0},
    {"Fajita roll ",5.00f,0,0,0, 15, 0},
    {"French Fries",2.00f,0,0,0, 30, 0},
    {"Dessert",3.00f,0,0,0, 20, 0},
    {"Drinks",0,0,0,0, 0, 0} 
};
void setColor(int color);
void clearScreen();
void printDateTime(char *buffer, size_t bufferSize);
void adminMenu();
void updatePrices();
void updateStock();
void viewTotalSales();
void customerMenu();
void placeOrder(MenuItem menu[], int menuSize, const char *category);
int selectSubmenu(MenuItem submenu[], int size, const char *submenuName);
void reduceStock(MenuItem *item, int qty);
void printBill(const char *customerName);
float getPriceForSize(MenuItem *item, const char *sizeLabel);
void printRandomJoke(const char *jokes[], int count);
void saveMenuToFile();
void loadMenuFromFile();
void initializeDummySales(); 
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void clearScreen() {
    system("cls");
}
void initializeDummySales() {
    time_t now = time(NULL);
    float taxableAmount;
    if (saleCount < MAX_SALES) {
        salesHistory[saleCount].subtotal = 15.00f;
        salesHistory[saleCount].discountApplied = 0.00f;
        taxableAmount = salesHistory[saleCount].subtotal - salesHistory[saleCount].discountApplied;
        salesHistory[saleCount].gstApplied = taxableAmount * GST_RATE; // 15.00 * 0.15 = 2.25
        salesHistory[saleCount].finalTotal = taxableAmount + salesHistory[saleCount].gstApplied; 
        strcpy(salesHistory[saleCount].customerName, "ali ");
        salesHistory[saleCount].timestamp = now - 7200; 
        saleCount++;
    }

    if (saleCount < MAX_SALES) {
        salesHistory[saleCount].subtotal = 40.00f;
        salesHistory[saleCount].discountApplied = salesHistory[saleCount].subtotal * DISCOUNT_RATE; // 40.00 * 0.10 = 4.00
        taxableAmount = salesHistory[saleCount].subtotal - salesHistory[saleCount].discountApplied; // 36.00
        salesHistory[saleCount].gstApplied = taxableAmount * GST_RATE; // 36.00 * 0.15 = 5.40
        salesHistory[saleCount].finalTotal = taxableAmount + salesHistory[saleCount].gstApplied; // 41.40
        strcpy(salesHistory[saleCount].customerName, "amna ");
        salesHistory[saleCount].timestamp = now - 3600; 
        saleCount++;
    }

    if (saleCount < MAX_SALES) {
        salesHistory[saleCount].subtotal = 10.00f;
        salesHistory[saleCount].discountApplied = 0.00f;
        taxableAmount = salesHistory[saleCount].subtotal - salesHistory[saleCount].discountApplied;
        salesHistory[saleCount].gstApplied = taxableAmount * GST_RATE; // 10.00 * 0.15 = 1.50
        salesHistory[saleCount].finalTotal = taxableAmount + salesHistory[saleCount].gstApplied; // 11.50
        strcpy(salesHistory[saleCount].customerName, "kamran ");
        salesHistory[saleCount].timestamp = now - 1800; // 
        saleCount++;
    }
}
void writeSectionToFile(FILE *fp, const char *title, MenuItem *array, int size) {
    fprintf(fp, "----------------------------------------\n");
    fprintf(fp, "%s\n", title);
    fprintf(fp, "----------------------------------------\n");
    int i = 0;
    while (i < size) {
        
        fprintf(fp, "%s|%.2f|%.2f|%.2f|%.2f|%d\n", 
            array[i].name, array[i].price, array[i].price_s, array[i].price_m, array[i].price_l, array[i].stock);
        i++;
    }
}
void readSectionFromFile(FILE *fp, MenuItem *array, int size) {
    char buffer[200];
    int i = 0;
    
    fgets(buffer, sizeof(buffer), fp); 
    fgets(buffer, sizeof(buffer), fp); 
    fgets(buffer, sizeof(buffer), fp); 

    while (i < size) {
        if (fgets(buffer, sizeof(buffer), fp) != NULL) {
            
            char *token;
            
            token = strtok(buffer, "|"); 
            
            token = strtok(NULL, "|");
            if(token) array[i].price = atof(token);

            
            token = strtok(NULL, "|");
            if(token) array[i].price_s = atof(token);

            
            token = strtok(NULL, "|");
            if(token) array[i].price_m = atof(token);
            
            token = strtok(NULL, "|");
            if(token) array[i].price_l = atof(token);

            token = strtok(NULL, "|");
            if(token) array[i].stock = atoi(token);
        }
        i++;
    }
}
void saveMenuToFile() {
    FILE *fp = fopen(MENU_FILE, "w");
    if (fp == NULL) {
        setColor(COLOR_RED);
        printf("Error saving menu to file!\n");
        setColor(COLOR_DEFAULT);
        return;
    }
    
    writeSectionToFile(fp, "BREAKFAST", breakfast, BREAKFAST_N);
    writeSectionToFile(fp, "BRUNCH", brunch, BRUNCH_N);
    writeSectionToFile(fp, "LUNCH", lunch, LUNCH_N);
    writeSectionToFile(fp, "PIZZA", pizzaMenu, PIZZA_N);
    writeSectionToFile(fp, "BURGER", burgerMenu, BURGER_N);
    writeSectionToFile(fp, "CLUB", clubMenu, CLUB_N);
    writeSectionToFile(fp, "DRINKS", drinks, DRINKS_N);
    writeSectionToFile(fp, "SAMOSA", samosaMenu, SAMOSA_N);

    fclose(fp);
    setColor(COLOR_GREEN);
    printf("\n[System]: Menu data saved to %s successfully.\n", MENU_FILE);
    setColor(COLOR_DEFAULT);
}
void loadMenuFromFile() {
    FILE *fp = fopen(MENU_FILE, "r"); 
    
    if (fp == NULL) {
        
        saveMenuToFile(); 
        return;
    }

    readSectionFromFile(fp, breakfast, BREAKFAST_N);
    readSectionFromFile(fp, brunch, BRUNCH_N);
    readSectionFromFile(fp, lunch, LUNCH_N);
    readSectionFromFile(fp, pizzaMenu, PIZZA_N);
    readSectionFromFile(fp, burgerMenu, BURGER_N);
    readSectionFromFile(fp, clubMenu, CLUB_N);
    readSectionFromFile(fp, drinks, DRINKS_N);
    readSectionFromFile(fp, samosaMenu, SAMOSA_N);
    fclose(fp);
}

int main(void) {
    char userType;
    char customerName[80];
    srand(time(NULL)); 
    loadMenuFromFile(); 
    initializeDummySales(); 
    clearScreen(); 
    setColor(COLOR_YELLOW);
    printf("  Welcome to Cafeteria Management System\n"); 
    setColor(COLOR_DEFAULT);
    while (1) {
        
        setColor(COLOR_CYAN);
        printf("\n---------- Main Menu ----------\n");
        setColor(COLOR_YELLOW);
        printf("Are you Admin (A) or Customer (C)? (E to Exit): ");
        setColor(COLOR_DEFAULT);
        scanf(" %c", &userType);
        
        if (userType == 'A' || userType == 'a') {
            clearScreen();
            adminMenu();
            clearScreen(); 
        } else if (userType == 'C' || userType == 'c') {
            clearScreen();
            hasOrderedDrink = 0; 
            printRandomJoke(funnyGreetings, GREETINGS_N); 
            
            setColor(COLOR_GREEN);
            printf("Enter Customer Name: ");
            setColor(COLOR_DEFAULT);
            scanf(" %[^\n]", customerName); 
            
            clearScreen(); 
            customerMenu();
            
            clearScreen(); 
            if (orderCount > 0) {
                 printBill(customerName);
            } else {
                 setColor(COLOR_RED);
                 printf("\nNo items ordered. Order cancelled.\n");
                 setColor(COLOR_DEFAULT);
            }
            printf("\n(Press Enter to continue to Main Menu...)");
            getchar(); 
            getchar();
            clearScreen(); 
        } else if (userType == 'E' || userType == 'e') {
            setColor(COLOR_CYAN);
            printf("Exiting...\n");
            setColor(COLOR_DEFAULT);
            break;
        } else {
            setColor(COLOR_RED);
            printf("Invalid choice. Try again.\n");
            setColor(COLOR_DEFAULT);
        }
    }
    return 0;
}
void printDateTime(char *buffer, size_t bufferSize) {
    time_t t = time(NULL);
    char *timeStr = ctime(&t);
    strncpy(buffer, timeStr, bufferSize - 1);
    buffer[bufferSize - 1] = '\0';
    if (buffer[strlen(buffer) - 1] == '\n') {
        buffer[strlen(buffer) - 1] = '\0';
    }
}

void printRandomJoke(const char *jokes[], int count) {
    if (count > 0) {
        int index = rand() % count;
        setColor(COLOR_MAGENTA);
        printf("\n[FUN FACT]: %s\n", jokes[index]);
        setColor(COLOR_DEFAULT);
    }
}
void adminMenu() {
    char pass[MAX_PASS_LEN];
    int choice;
    int i; 
    
    setColor(COLOR_YELLOW);
    printf("Enter Admin Password: ");
    setColor(COLOR_DEFAULT);
    
    i = 0;
    char c;
    
    while (i < MAX_PASS_LEN - 1) { 
        c = (char)_getch(); 

        if (c == '\r' || c == '\n') { 
            break;
        } else if (c == '\b') { 
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else if (c >= 32 && c <= 126) { 
            pass[i++] = c;
            printf("*"); 
        }
    }
    pass[i] = '\0'; 
    printf("\n"); 
    if (strcmp(pass, PASSWORD) != 0) {
        setColor(COLOR_RED);
        printf("Incorrect password!\n");
        setColor(COLOR_DEFAULT);
        printf("\n(Press Enter to continue...)\n");
        getchar(); 
        getchar();
        return;
    }
    while (1) {
        setColor(COLOR_CYAN);
        printf("\n---------- Admin Menu ----------\n");
        setColor(COLOR_DEFAULT);
        printf("1. Update Prices\n2. Update Stock\n3. View Total Sales (History)\n4. View Stock\n5. Exit Admin Menu\n");
        printf("Enter choice: ");
        scanf(" %d", &choice);
        
        if (choice == 1) {
            clearScreen();
            updatePrices();
            printf("\n(Press Enter to continue...)\n");
            getchar(); getchar();
            clearScreen();
        }
        else if (choice == 2) {
            clearScreen();
            updateStock();
            printf("\n(Press Enter to continue...)\n");
            getchar(); getchar();
            clearScreen();
        }
        else if (choice == 3) {
            clearScreen();
            viewTotalSales();
            printf("\n(Press Enter to continue...)\n");
            getchar(); getchar();
            clearScreen();
        }
        else if (choice == 4) {
            clearScreen(); 
            setColor(COLOR_WHITE);
            
            i = 0; 
            printf("\n------- Breakfast -------\n");
            while (i < BREAKFAST_N) { printf("%d. %-20s | Stock: %d\n", i+1, breakfast[i].name, breakfast[i].stock); i++; }
            
            i = 0; 
            printf("\n------- Brunch -------\n");
            while (i < BRUNCH_N) { printf("%d. %-20s | Stock: %d\n", i+1, brunch[i].name, brunch[i].stock); i++; }
            
            i = 0; 
            printf("\n------- Lunch -------\n");
            while (i < LUNCH_N) { printf("%d. %-20s | Stock: %d\n", i+1, lunch[i].name, lunch[i].stock); i++; }
            
            i = 0; 
            printf("\n------- Pizza Submenu -------\n");
            while (i < PIZZA_N) { printf("%d. %-20s | Stock: %d\n", i+1, pizzaMenu[i].name, pizzaMenu[i].stock); i++; }
            
            i = 0; 
            printf("\n------- Burger Submenu -------\n");
            while (i < BURGER_N) { printf("%d. %-20s | Stock: %d\n", i+1, burgerMenu[i].name, burgerMenu[i].stock); i++; }
            
            i = 0; 
            printf("\n------- Club Submenu -------\n");
            while (i < CLUB_N) { printf("%d. %-20s | Stock: %d\n", i+1, clubMenu[i].name, clubMenu[i].stock); i++; }
            
            i = 0; 
            printf("\n------- Drinks Submenu -------\n");
            while (i < DRINKS_N) { printf("%d. %-20s | Stock: %d\n", i+1, drinks[i].name, drinks[i].stock); i++; }
            
            i = 0; 
            printf("\n------- Samosa Submenu -------\n");
            while (i < SAMOSA_N) { printf("%d. %-20s | Stock: %d\n", i+1, samosaMenu[i].name, samosaMenu[i].stock); i++; }
            setColor(COLOR_DEFAULT);
            
            printf("\n(Press Enter to continue...)\n");
            getchar(); getchar();
            clearScreen();
        }
        else if (choice == 5) return;
        else {
            setColor(COLOR_RED);
            printf("Invalid choice!\n");
            setColor(COLOR_DEFAULT);
        }
    }
}

void updatePrices() {
    int cat, choice;
    int i, j;
    MenuItem *m;
    MenuItem *sm, *dm, *pm, *bm, *cm; 

    printf("\nSelect category to update prices:\n1. Breakfast\n2. Brunch\n3. Lunch\n4. Pizza Submenu\n5. Burger Submenu\n6. Club Submenu\n7. Drinks Submenu\n8. Samosa Submenu\n");
    printf("Enter choice: "); scanf(" %d", &cat);
    clearScreen();   
    if (cat == 1) {
        i = 0; while (i < BREAKFAST_N) { printf("%d. %s\n", i+1, breakfast[i].name); i++; }
        printf("Pick item number: "); scanf(" %d", &choice);
        if (choice<1||choice>BREAKFAST_N) { setColor(COLOR_RED); printf("Invalid item\n"); setColor(COLOR_DEFAULT); return; }
        m = &breakfast[choice-1];
        if (m->has_size) {
            printf("Enter new Small price: "); scanf(" %f", &m->price_s);
            printf("Enter new Medium price: "); scanf(" %f", &m->price_m);
            printf("Enter new Large price: "); scanf(" %f", &m->price_l);
        } else {
            printf("Enter new price: "); scanf(" %f", &m->price);
        }
        setColor(COLOR_GREEN); printf("Price updated.\n"); setColor(COLOR_DEFAULT);
    } else if (cat == 2) {
        i = 0; while (i < BRUNCH_N) { printf("%d. %s\n", i+1, brunch[i].name); i++; }
        printf("Pick item number: "); scanf(" %d", &choice);
        if (choice<1||choice>BRUNCH_N) { printf("Invalid item\n"); return; }
        m = &brunch[choice-1];
        if (strcmp(m->name, "Samosa") == 0) {
             j = 0; while (j < SAMOSA_N) { printf("%d. %s\n", j+1, samosaMenu[j].name); j++; }
             printf("Pick item: "); scanf(" %d", &choice); sm = &samosaMenu[choice-1];
             printf("New price: "); scanf(" %f", &sm->price);
        } else if (strcmp(m->name, "Drinks") == 0) {
             j = 0; while (j < DRINKS_N) { printf("%d. %s\n", j+1, drinks[j].name); j++; }
             printf("Pick item: "); scanf(" %d", &choice); dm = &drinks[choice-1];
             printf("S/M/L prices: "); scanf("%f %f %f", &dm->price_s, &dm->price_m, &dm->price_l);
        } else {
             printf("New price: "); scanf(" %f", &m->price);
        }
        setColor(COLOR_GREEN); printf("Price updated.\n"); setColor(COLOR_DEFAULT);
    } else if (cat == 3) {
        i = 0; while (i < LUNCH_N) { printf("%d. %s\n", i+1, lunch[i].name); i++; }
        printf("Pick item number: "); scanf(" %d", &choice);
        if (choice<1||choice>LUNCH_N) { printf("Invalid item\n"); return; }
        m = &lunch[choice-1];
        if (strcmp(m->name, "Pizza") == 0) {
            j = 0; while (j < PIZZA_N) { printf("%d. %s\n", j+1, pizzaMenu[j].name); j++; }
            printf("Pick item: "); scanf(" %d", &choice); pm = &pizzaMenu[choice-1];
            printf("S/M/L prices: "); scanf("%f %f %f", &pm->price_s, &pm->price_m, &pm->price_l);
        } else if (strcmp(m->name, "Burgers") == 0) {
            j = 0; while (j < BURGER_N) { printf("%d. %s\n", j+1, burgerMenu[j].name); j++; }
            printf("Pick item: "); scanf(" %d", &choice); bm = &burgerMenu[choice-1];
            printf("New price: "); scanf(" %f", &bm->price);
        } else if (strcmp(m->name, "Club Sandwich") == 0) {
            j = 0; while (j < CLUB_N) { printf("%d. %s\n", j+1, clubMenu[j].name); j++; }
            printf("Pick item: "); scanf(" %d", &choice); cm = &clubMenu[choice-1];
            printf("New price: "); scanf(" %f", &cm->price);
        } else if (strcmp(m->name, "Drinks") == 0) {
            j = 0; while (j < DRINKS_N) { printf("%d. %s\n", j+1, drinks[j].name); j++; }
            printf("Pick item: "); scanf(" %d", &choice); dm = &drinks[choice-1];
            printf("S/M/L prices: "); scanf("%f %f %f", &dm->price_s, &dm->price_m, &dm->price_l);
        } else {
            printf("New price: "); scanf(" %f", &m->price);
        }
        setColor(COLOR_GREEN); printf("Price updated.\n"); setColor(COLOR_DEFAULT);
    } else if (cat == 4) {
        i = 0; while (i < PIZZA_N) { printf("%d. %s\n", i+1, pizzaMenu[i].name); i++; }
        printf("Pick item: "); scanf(" %d", &choice); pm = &pizzaMenu[choice-1];
        printf("S/M/L prices: "); scanf("%f %f %f", &pm->price_s, &pm->price_m, &pm->price_l);
        setColor(COLOR_GREEN); printf("Price updated.\n"); setColor(COLOR_DEFAULT);
    } else if (cat == 5) {
        i = 0; while (i < BURGER_N) { printf("%d. %s\n", i+1, burgerMenu[i].name); i++; }
        printf("Pick item: "); scanf(" %d", &choice); bm = &burgerMenu[choice-1];
        printf("New price: "); scanf(" %f", &bm->price);
        setColor(COLOR_GREEN); printf("Price updated.\n"); setColor(COLOR_DEFAULT);
    } else if (cat == 6) {
        i = 0; while (i < CLUB_N) { printf("%d. %s\n", i+1, clubMenu[i].name); i++; }
        printf("Pick item: "); scanf(" %d", &choice); cm = &clubMenu[choice-1];
        printf("New price: "); scanf(" %f", &cm->price);
        setColor(COLOR_GREEN); printf("Price updated.\n"); setColor(COLOR_DEFAULT);
    } else if (cat == 7) {
        i = 0; while (i < DRINKS_N) { printf("%d. %s\n", i+1, drinks[i].name); i++; }
        printf("Pick item: "); scanf(" %d", &choice); dm = &drinks[choice-1];
        printf("S/M/L prices: "); scanf("%f %f %f", &dm->price_s, &dm->price_m, &dm->price_l);
        setColor(COLOR_GREEN); printf("Price updated.\n"); setColor(COLOR_DEFAULT);
    } else if (cat == 8) {
        i = 0; while (i < SAMOSA_N) { printf("%d. %s\n", i+1, samosaMenu[i].name); i++; }
        printf("Pick item: "); scanf(" %d", &choice); sm = &samosaMenu[choice-1];
        printf("New price: "); scanf(" %f", &sm->price);
        setColor(COLOR_GREEN); printf("Price updated.\n"); setColor(COLOR_DEFAULT);
    } else {
        setColor(COLOR_RED); printf("Invalid category.\n"); setColor(COLOR_DEFAULT);
    }
    saveMenuToFile();
}

void updateStock() {
    int cat, choice, newStock;
    int i, j;

    printf("\nSelect category to update stock:\n1. Breakfast\n2. Brunch\n3. Lunch\n4. Pizza Submenu\n5. Burger Submenu\n6. Club Submenu\n7. Drinks Submenu\n8. Samosa Submenu\n");
    printf("Enter choice: "); scanf(" %d", &cat);
    
    clearScreen(); 
    
    if (cat == 1) {
        i = 0; while (i < BREAKFAST_N) { printf("%d. %s (Stock:%d)\n", i+1, breakfast[i].name, breakfast[i].stock); i++; }
        printf("Pick item: "); scanf(" %d", &choice);
        if (choice<1||choice>BREAKFAST_N) return;
        printf("New stock: "); scanf(" %d", &newStock);
        breakfast[choice-1].stock = newStock;
    } else if (cat == 2) {
        i = 0; while (i < BRUNCH_N) { printf("%d. %s (Stock:%d)\n", i+1, brunch[i].name, brunch[i].stock); i++; }
        printf("Pick item: "); scanf(" %d", &choice);
        if (strcmp(brunch[choice-1].name, "Samosa") == 0) {
             j = 0; while (j < SAMOSA_N) { printf("%d. %s (Stock:%d)\n", j+1, samosaMenu[j].name, samosaMenu[j].stock); j++; }
             scanf(" %d", &choice); printf("Stock: "); scanf("%d", &newStock); samosaMenu[choice-1].stock = newStock;
        } else if (strcmp(brunch[choice-1].name, "Drinks") == 0) {
             j = 0; while (j < DRINKS_N) { printf("%d. %s (Stock:%d)\n", j+1, drinks[j].name, drinks[j].stock); j++; }
             scanf(" %d", &choice); printf("Stock: "); scanf("%d", &newStock); drinks[choice-1].stock = newStock;
        } else {
             printf("Stock: "); scanf(" %d", &newStock); brunch[choice-1].stock = newStock;
        }
    } else if (cat == 3) {
        i = 0; while (i < LUNCH_N) { printf("%d. %s (Stock:%d)\n", i+1, lunch[i].name, lunch[i].stock); i++; }
        printf("Pick item: "); scanf(" %d", &choice);
        if (strcmp(lunch[choice-1].name, "Pizza") == 0) {
            j = 0; while (j < PIZZA_N) { printf("%d. %s (Stock:%d)\n", j+1, pizzaMenu[j].name, pizzaMenu[j].stock); j++; }
            scanf(" %d", &choice); printf("Stock: "); scanf("%d", &newStock); pizzaMenu[choice-1].stock = newStock;
        } else if (strcmp(lunch[choice-1].name, "Burgers") == 0) {
            j = 0; while (j < BURGER_N) { printf("%d. %s (Stock:%d)\n", j+1, burgerMenu[j].name, burgerMenu[j].stock); j++; }
            scanf(" %d", &choice); printf("Stock: "); scanf("%d", &newStock); burgerMenu[choice-1].stock = newStock;
        } else if (strcmp(lunch[choice-1].name, "Club Sandwich") == 0) {
            j = 0; while (j < CLUB_N) { printf("%d. %s (Stock:%d)\n", j+1, clubMenu[j].name, clubMenu[j].stock); j++; }
            scanf(" %d", &choice); printf("Stock: "); scanf("%d", &newStock); clubMenu[choice-1].stock = newStock;
        } else if (strcmp(lunch[choice-1].name, "Drinks") == 0) {
            j = 0; while (j < DRINKS_N) { printf("%d. %s (Stock:%d)\n", j+1, drinks[j].name, drinks[j].stock); j++; }
            scanf(" %d", &choice); printf("Stock: "); scanf("%d", &newStock); drinks[choice-1].stock = newStock;
        } else {
            printf("Stock: "); scanf(" %d", &newStock); lunch[choice-1].stock = newStock;
        }
    } else if (cat == 4) {
        i = 0; while (i < PIZZA_N) { printf("%d. %s (Stock:%d)\n", i+1, pizzaMenu[i].name, pizzaMenu[i].stock); i++; }
        printf("Pick item: "); scanf(" %d", &choice);
        printf("New stock: "); scanf(" %d", &newStock); pizzaMenu[choice-1].stock = newStock;
    } else if (cat == 5) {
        i = 0; while (i < BURGER_N) { printf("%d. %s (Stock:%d)\n", i+1, burgerMenu[i].name, burgerMenu[i].stock); i++; }
        printf("Pick item: "); scanf(" %d", &choice);
        printf("New stock: "); scanf(" %d", &newStock); burgerMenu[choice-1].stock = newStock;
    } else if (cat == 6) {
        i = 0; while (i < CLUB_N) { printf("%d. %s (Stock:%d)\n", i+1, clubMenu[i].name, clubMenu[i].stock); i++; }
        printf("Pick item: "); scanf(" %d", &choice);
        printf("New stock: "); scanf(" %d", &newStock); clubMenu[choice-1].stock = newStock;
    } else if (cat == 7) {
        i = 0; while (i < DRINKS_N) { printf("%d. %s (Stock:%d)\n", i+1, drinks[i].name, drinks[i].stock); i++; }
        printf("Pick item: "); scanf(" %d", &choice);
        printf("New stock: "); scanf(" %d", &newStock); drinks[choice-1].stock = newStock;
    } else if (cat == 8) {
        i = 0; while (i < SAMOSA_N) { printf("%d. %s (Stock:%d)\n", i+1, samosaMenu[i].name, samosaMenu[i].stock); i++; }
        printf("Pick item: "); scanf(" %d", &choice);
        printf("New stock: "); scanf(" %d", &newStock); samosaMenu[choice-1].stock = newStock;
    } else {
        printf("Invalid category.\n");
    }
    
    setColor(COLOR_GREEN);
    printf("Stock updated.\n");
    setColor(COLOR_DEFAULT);
    
    saveMenuToFile();
}

void viewTotalSales() {
    int i; 
    
    setColor(COLOR_CYAN);
    printf("\n---------- Sales History ----------\n");
    setColor(COLOR_DEFAULT);
    
    if (saleCount == 0) {
        printf("No sales recorded yet.\n");
        return;
    }
    float totalOverall = 0.0f;
    for (i = 0; i < saleCount; i++) { 
        char timeBuffer[30];
        struct tm *tm_info = localtime(&salesHistory[i].timestamp);
        strftime(timeBuffer, 30, "%Y-%m-%d %H:%M:%S", tm_info);

        printf("Sale #%d (Customer: %s)\n", i + 1, salesHistory[i].customerName);
        printf("  Time: %s\n", timeBuffer);
        printf("  Subtotal: $%.2f\n", salesHistory[i].subtotal);
        if (salesHistory[i].discountApplied > 0)
            printf("  Discount Applied: -$%.2f\n", salesHistory[i].discountApplied);
        printf("  GST Applied (15%%): $%.2f\n", salesHistory[i].gstApplied);
        setColor(COLOR_YELLOW);
        printf("  Final Total: $%.2f\n", salesHistory[i].finalTotal);
        setColor(COLOR_DEFAULT);
        printf("-----------------------------------\n");
        totalOverall += salesHistory[i].finalTotal;
    }
    setColor(COLOR_GREEN);
    printf("\nOVERALL TOTAL SALES (All Time): $%.2f\n", totalOverall);
    setColor(COLOR_DEFAULT);
}

void customerMenu() {
    int choice;
    while (1) {
        setColor(COLOR_CYAN);
        printf("\n---------- Customer Menu ----------\n");
        setColor(COLOR_DEFAULT);
        printf("1. Breakfast\n2. Brunch\n3. Lunch\n4. Finish Order\n");
        printf("-----------------------------------\n");
        setColor(COLOR_YELLOW);
        printf("Enter choice: "); 
        setColor(COLOR_DEFAULT);
        scanf(" %d", &choice);
        
        if (choice == 1) {
            clearScreen();
            placeOrder(breakfast, BREAKFAST_N, "Breakfast");
            printf("\n(Press Enter to return to Customer Menu...)\n");
            getchar(); getchar();
            clearScreen();
        }
        else if (choice == 2) {
            clearScreen();
            placeOrder(brunch, BRUNCH_N, "Brunch");
            printf("\n(Press Enter to return to Customer Menu...)\n");
            getchar(); getchar();
            clearScreen();
        }
        else if (choice == 3) {
            clearScreen();
            placeOrder(lunch, LUNCH_N, "Lunch");
            printf("\n(Press Enter to return to Customer Menu...)\n");
            getchar(); getchar();
            clearScreen();
        }
        else if (choice == 4) {
            if (orderCount > 0 && !hasOrderedDrink) {
                char resp;
                setColor(COLOR_MAGENTA);
                printf("\n[ Drink Reminder : You haven't ordered a drink yet.\n");
                printf("Would you like to add one? (Y/N): ");
                setColor(COLOR_DEFAULT);
                scanf(" %c", &resp);
                if (resp == 'Y' || resp == 'y') {
                    clearScreen();
                    placeOrder(drinks, DRINKS_N, "Drinks");
                    printf("\n(Press Enter to Finish Order...)\n");
                    getchar(); getchar();
                    clearScreen();
                }
            }
            return; 
        }
        else {
            setColor(COLOR_RED);
            printf("Invalid choice.\n");
            setColor(COLOR_DEFAULT);
        }
    }
}

void placeOrder(MenuItem menu[], int menuSize, const char *category) {
    int itemNo, qty;
    char sizeLabel[10];
    int i; 
    MenuItem *finalItem; 
    MenuItem *selected;
    char finalName[80];
    int isPizza = 0;
    int isDrink = 0;

    setColor(COLOR_CYAN);
    printf("\n---------- %s Menu ----------\n", category);
    setColor(COLOR_WHITE);
    
    i = 0; 
    while (i < menuSize) { 
        printf("%d. %s", i+1, menu[i].name); 
        if (menu[i].has_size) {
            printf(" (S:$%.2f M:$%.2f L:$%.2f)", menu[i].price_s, menu[i].price_m, menu[i].price_l);
        } else if (menu[i].price > 0) {
            printf(" (Price:$%.2f)", menu[i].price);
        }
        printf("\n");
        i++; 
    }
    
    setColor(COLOR_CYAN);
    printf("-----------------------------------\n");
    setColor(COLOR_YELLOW);
    printf("Enter item number to order: "); 
    setColor(COLOR_DEFAULT);
    scanf(" %d", &itemNo);
    if (itemNo < 1 || itemNo > menuSize) { 
        setColor(COLOR_RED); printf("Invalid item.\n"); setColor(COLOR_DEFAULT); return; 
    }

    selected = &menu[itemNo-1];
    finalItem = selected; 
    strcpy(finalName, selected->name);

    if (strcmp(category, "Drinks") == 0) { hasOrderedDrink = 1; isDrink = 1; }

    if (strcmp(selected->name, "Pizza") == 0) {
        int sub = selectSubmenu(pizzaMenu, PIZZA_N, "Pizza");
        if (sub == -1) return;
        finalItem = &pizzaMenu[sub]; strcpy(finalName, pizzaMenu[sub].name); isPizza = 1;
    } else if (strcmp(selected->name, "Burgers") == 0) {
        int sub = selectSubmenu(burgerMenu, BURGER_N, "Burgers");
        if (sub == -1) return;
        finalItem = &burgerMenu[sub]; strcpy(finalName, burgerMenu[sub].name);
    } else if (strcmp(selected->name, "Club Sandwich") == 0) {
        int sub = selectSubmenu(clubMenu, CLUB_N, "Club Sandwich");
        if (sub == -1) return;
        finalItem = &clubMenu[sub]; strcpy(finalName, clubMenu[sub].name);
    } else if (strcmp(selected->name, "Drinks") == 0) {
        hasOrderedDrink = 1;
        int sub = selectSubmenu(drinks, DRINKS_N, "Drinks");
        if (sub == -1) return;
        finalItem = &drinks[sub]; strcpy(finalName, drinks[sub].name); isDrink = 1;
    } else if (strcmp(selected->name, "Samosa") == 0) {
        int sub = selectSubmenu(samosaMenu, SAMOSA_N, "Samosa");
        if (sub == -1) return;
        finalItem = &samosaMenu[sub]; strcpy(finalName, samosaMenu[sub].name);
    }
    
    if (strcmp(category, "Breakfast") == 0 && (strcmp(selected->name, "Coffee") == 0 || strcmp(selected->name, "Tea") == 0)) {
        hasOrderedDrink = 1; isDrink = 1;
    }

    printf("Enter quantity: "); scanf(" %d", &qty);
    if (qty <= 0) { setColor(COLOR_RED); printf("Quantity must be positive.\n"); setColor(COLOR_DEFAULT); return; }

    if (finalItem->has_size) {
        printf("Choose size (Small/Medium/Large): ");
        scanf(" %9s", sizeLabel);
        float unit = getPriceForSize(finalItem, sizeLabel);
        if (unit < 0.0f) { setColor(COLOR_RED); printf("Invalid size choice.\n"); setColor(COLOR_DEFAULT); return; }
        if (qty > finalItem->stock) { setColor(COLOR_RED); printf("Not available! Reduce quantity.\n"); setColor(COLOR_DEFAULT); return; }
        
        strcpy(orders[orderCount].name, finalName);
        strcpy(orders[orderCount].size, sizeLabel);
        orders[orderCount].unit_price = unit;
        orders[orderCount].quantity = qty;
        orders[orderCount].total_price = unit * qty;
        reduceStock(finalItem, qty);
        orderCount++;
    } else {
        if (qty > finalItem->stock) { setColor(COLOR_RED); printf("Not available! Reduce quantity.\n"); setColor(COLOR_DEFAULT); return; }
        strcpy(orders[orderCount].name, finalName);
        strcpy(orders[orderCount].size, "-");
        orders[orderCount].unit_price = finalItem->price;
        orders[orderCount].quantity = qty;
        orders[orderCount].total_price = finalItem->price * qty;
        reduceStock(finalItem, qty);
        orderCount++;
    }
    setColor(COLOR_GREEN);
    printf("Item added to order.\n");
    setColor(COLOR_DEFAULT);
    
    if (isPizza) printRandomJoke(pizzaFunLines, PIZZA_FUN_N);
    else if (isDrink) printRandomJoke(drinksFunLines, DRINKS_FUN_N);
    else printRandomJoke(takingOrderJokes, TAKING_ORDERS_N);
}
int selectSubmenu(MenuItem submenu[], int size, const char *submenuName) {
    int choice;
    int i = 0;  
    clearScreen();  
    setColor(COLOR_CYAN);
    printf("\n---------- %s Options ----------\n", submenuName);
    setColor(COLOR_WHITE);
    while (i < size) { 
        if (submenu[i].has_size) 
            printf("%d. %s (S:$%.2f M:$%.2f L:$%.2f)\n", i+1, submenu[i].name, submenu[i].price_s, submenu[i].price_m, submenu[i].price_l);
        else 
            printf("%d. %s - $%.2f\n", i+1, submenu[i].name, submenu[i].price); 
        i++; 
    }
    setColor(COLOR_CYAN);
    printf("-----------------------------------\n");
    setColor(COLOR_YELLOW);
    printf("Enter choice (or 0 to cancel): "); 
    setColor(COLOR_DEFAULT);
    scanf(" %d", &choice);
    
    clearScreen(); 
    
    if (choice == 0) return -1;
    if (choice < 1 || choice > size) { setColor(COLOR_RED); printf("Invalid choice.\n"); setColor(COLOR_DEFAULT); return -1; }
    return choice - 1;
}

void reduceStock(MenuItem *item, int qty) {
    if (item->stock >= qty) item->stock -= qty;
}

void printBill(const char *customerName) {
    float subtotal = 0.0f;
    float discount = 0.0f;
    float taxableAmount = 0.0f;
    float gst = 0.0f;
    float finalTotal = 0.0f;
    char timeBuffer[30];
    int i; 

    setColor(COLOR_CYAN);
    printf("\n---------------- CAFETERIA BILL ----------------\n");
    setColor(COLOR_DEFAULT);
    printf("Customer: %s\n", customerName);
    printf("Date & Time: "); 
    printDateTime(timeBuffer, sizeof(timeBuffer));
    printf("%s\n", timeBuffer);
    setColor(COLOR_CYAN);
    printf("\n%-30s %-8s %-5s %-10s\n", "Item", "Size", "Qty", "Price");
    printf("------------------------------------------------\n");
    setColor(COLOR_DEFAULT);
    i = 0; 
    while (i < orderCount) {
        printf("%-30s %-8s %-5d $%.2f\n", orders[i].name, orders[i].size, orders[i].quantity, orders[i].total_price);
        subtotal += orders[i].total_price;
        i++;
    }
    setColor(COLOR_CYAN);
    printf("------------------------------------------------\n");
    setColor(COLOR_DEFAULT);

    if (subtotal > DISCOUNT_THRESHOLD) {
        discount = subtotal * DISCOUNT_RATE;
        setColor(COLOR_GREEN);
        printf("\n*** Congratulations! 10% Discount Applied (Order > $%.2f) ***\n", DISCOUNT_THRESHOLD);
        setColor(COLOR_DEFAULT);
    } 
    
    taxableAmount = subtotal - discount;
    gst = taxableAmount * GST_RATE;
    finalTotal = taxableAmount + gst;
    
    printf("Subtotal:       $%.2f\n", subtotal);
    if (discount > 0.0f) {
        printf("Discount (10%%): -$%.2f\n", discount);
    }
    printf("GST (15%%):       $%.2f\n", gst);
    setColor(COLOR_CYAN);
    printf("--------------------------------\n");
    setColor(COLOR_YELLOW);
    printf("Total Payable:  $%.2f\n", finalTotal);
    setColor(COLOR_DEFAULT);
    printRandomJoke(billJokes, BILL_JOKES_N); 
    setColor(COLOR_GREEN);
    printf("\n      Thank You! Come Again!      \n");
    setColor(COLOR_CYAN);
    printf("------------------------------------------------\n");
    setColor(COLOR_DEFAULT);
    if (saleCount < MAX_SALES && orderCount > 0) {
        strcpy(salesHistory[saleCount].customerName, customerName);
        salesHistory[saleCount].subtotal = subtotal;
        salesHistory[saleCount].discountApplied = discount;
        salesHistory[saleCount].gstApplied = gst; 
        salesHistory[saleCount].finalTotal = finalTotal;
        time(&salesHistory[saleCount].timestamp);
        saleCount++;
    } else if (orderCount > 0) {
        setColor(COLOR_RED);
        printf("\n[ALERT: Sales history is full! Sale not recorded.]\n");
        setColor(COLOR_DEFAULT);
    }
    orderCount = 0; 
}
float getPriceForSize(MenuItem *item, const char *sizeLabel) {
    if (!item->has_size) return -1.0f;
    
    if (tolower((unsigned char)sizeLabel[0]) == 's') return item->price_s;
    if (tolower((unsigned char)sizeLabel[0]) == 'm') return item->price_m;
    if (tolower((unsigned char)sizeLabel[0]) == 'l') return item->price_l;
    return -1.0f;
}
