#define STB_IMAGE_IMPLEMENTATION // As I learnt , #define STB_IMAGE_IMPLEMENTATION is used to also include the implementation of the header file which is stb_image in our case. And Also it is written before including the header file beacuase it tells the header file to include its implementation . If we include it after #include "stb_image.h" we wont be able to activate the implementation section
#include "stb_image.h"           // Including the header file we downloaded
#include <stdio.h>               // Including the standard input output library so that we could use functions like printf , scanf and more
#include <ncurses.h>             // I am including this library(external) to use getch() especially . (just wanted to make someting like navigation through a sort of story) btw it takes over the terminal to use its own function , dont know why but it sound scary
#include <dirent.h> // I am including this library as read the current directory and also scan the images file in the directory (it might make the user experience better and i also might learn something new.)
#include <string.h> // I am including this library because I have to work with strings especially in displaying the images name.

int calculate_brightness(int, int, int);                                  // This is function decleration and I am writing this to declare that this to tell me program that this funciton exists.
int calculate_symbol_index(int);                                          // This is another function decleration
int greet_01(void);                                                       // I am declaring this funciton for instruction / greeting
int greet_02(void);                                                       // I am declaring this function for instruction / greeting
int greet_03(void);                                                       // I am declaring this function for instructions
int check_image_validity(unsigned char *);                                // I am declaring this function for check if the image exist or not , or if its valid type or not
void per_pixel_mapping(int, int, int, unsigned char *, const char arr[]); // I am declaring this function for converting image to ascii using certain method of conversion called per_pixel_mapping
int choose_image(void);                                                   // I am declaring this function to make a choose image sort of screen

// The below is function definition . Here I write the actual code of the function , like what it does and stuff
int calculate_brightness(int red_value, int green_value, int blue_value)
{
    int brightness = ((30 * red_value) + (59 * green_value) + (11 * blue_value)) / 100; // This is the formula I leanrt to calculate the brightness
    return brightness;
}

// I am making this function to calculate the index value with the help of which , we will be deciding which symbol to use at any particular brightness
int calculate_symbol_index(int brightness)
{
    int symbol_index_value = (brightness * 10) / 256; // This formula ensures that the brightness value stayes int he range of 0 to 9 , as we have use only 10 chars ranging from index 0 to 9
    return symbol_index_value;
}

// I am making this function to instruct use on how to use my program (this one function especially is only for prinitng hello though)
int greet_01(void)
{

    initscr(); // initscr function modifies the terminal making it ready for getch (and maybe other fucntions which the ncurses library might provide) through external library

    clear();

    printw("Hello!\n"); // This is abit annoying but the ncurses library uses printw function instead of printf , I tried using initilizing and endinf the its use only in getch , but the terminal output was getting abit weird and was recommended to use it this way.
    printw("\n");
    printw("Press ESC to exit the program.\n");
    printw("Press ENTER to continue...");

    refresh();

    int user_key = getch();

    clear(); // clearing the screen

    refresh(); // refreshing the terminal

    endwin(); // endwin is a function from ncurses which just resets the terminal to its normal state

    // printf("You Pressed %d .\n", user_key);

    return user_key;
}

// Another function to continue the instruction
int greet_02(void)
{

    initscr();

    clear();

    printw("I will tell you how to use this Image to ASCII converter. Ready ?\n\n");

    printw("Press BACKSPACE to go back...\n");
    printw("Press ENTER to continue...");

    refresh();

    int user_key = getch();

    endwin();

    return user_key;
}

// Another function to continue the instruction
int greet_03(void)
{

    char image_names[500][100]; // I guess accepting 500 images should be enough and i dont think images name will be any higher then 200 characters (hopefully)
    initscr();

    clear();

    printw("Ok, so first you will have to choose which image you want to convert to ASCII : \n");
    printw("There will be few samples , but you can always put it inside the Images folder and compile this porgram to convert that image to ASCII art : ");

    printw("\n");

    printw("Choose any images :\n");

    // First we open the directory
    DIR *directory = opendir("./Images");

    // Then we check if the directory is successfully opened or not
    if(directory == NULL){
        printw("Error opening directory.\n");
        return 1;
    }else{
        printw("Opened Directory Successfully.\n");
    }

    // dirent is a pre-made structure provided by the dirent library
    struct dirent *entries;

    // Now we put the values in entries from the directory
    while((entries = readdir(directory)) != NULL){ // It checks the directory untill it reaches end (readdir returns NULL when it reaches the end)
        int i = 0;
        char *extension = strrchr((entries->d_name),'.'); // strrchr here search the last . and stores it in extension variable
        if((strcmp(extension,".jpg") == 0) || (strcmp(extension,".jpeg")) || (strcmp(extension,".png")) || (strcmp(extension,".tga")) || (strcmp(extension,".bmp")) || (strcmp(extension,".psd")) || (strcmp(extension,".gif")) || (strcmp(extension,".hdr")) || (strcmp(extension, ".pic")) || (strcmp(extension, ".ppm")) || (strcmp(extension,".pgm"))){
            strcpy(image_names[i],entries->d_name);
        }
    }

    printw("\n");

    printw("Press BACKSPACE to go back...\n");
    printw("Press ENTER to continue...");

    refresh();

    int user_key = getch();

    endwin();

    return user_key;
}

// I am making the below function to make a choose image sort of screen. My plan is to show a list of images on the screen which user can navigate and choose using the arrow key.
int choose_image(void)
{

    int user_choosen_image_number;

    initscr();

    clear();

    printw("Choose any image from the directory : \n");

    endwin();

    return user_choosen_image_number;
}

// I am making this function to check the validity of the image choosen by the user
int check_image_validity(unsigned char *image)
{
    if (image == NULL)
    {
        printf("Error loading image . Reason : %s.\n", stbi_failure_reason());
        return 1;
    }
    else
    {
        printf("Image loaded successfully.\n");
        return 0;
    }
}

// I am making the function to convert the image to ascii art pixel by pixel , i learnt that this method is called per-pixel mapping

void per_pixel_mapping(int original_height, int original_width, int required_channel, unsigned char *image, const char ascii_symbols[])
{

    // Now we calculate select the pixel position form the image
    int pixel_index;
    int original_row;
    int original_column;

    for (original_row = 0; original_row < original_height; original_row++) // Let me explain why we used < and not <= , this one was abit confusing to me but i got it now , so the width and heiht returned by the stbi_load function is the number of pixels , so they start from one , but while reading those pixels , we get array where indexing starts from 0 , thats why we use < and not <= . This applies to the loop below as well , i.e. original_column < original_width .
    {
        for (original_column = 0; original_column < original_width; original_column++)
        {
            pixel_index = ((original_row * original_width) + original_column) * required_channel; // Here lemme explain the formula myself , so , here , row * width takes us to the current row and adding column will take us to the current position , and we multiple with required channel , which is 3 here represent the red , green and blue value of the particular pixl . so we are reading those 3 value of each pixel.

            // printf("%d\t",pixel_index); If you try to print pixel index like i did , you will see that the difference in each index is 3 . and this is beacuase we take the pixel and skip 3 values of it as it would give rgb value of the same pixel

            unsigned char red_value = image[pixel_index]; // we use unsigned char here because the rgb value of the pixel is exactly ranging from 0 to 255 , and the unsigned char stores exactly upto 255 . So , its like made for this.
            unsigned char green_value = image[pixel_index + 1];
            unsigned char blue_value = image[pixel_index + 2];

            int brightness_returned = calculate_brightness(red_value, green_value, blue_value); // This is function call. I am using the function I decleared earlier
            // printf("Brightness : %d \n",brightness_returned); I printed it only for checking

            int symbol_index_value = calculate_symbol_index(brightness_returned);

            // printf("Symbol_index_value = %d\n",symbol_index_value);

            printf("%c", ascii_symbols[symbol_index_value]);
        }
        printf("\n");
    }
}

int main()
{
    char image_name[] = "image.jpeg";
    int original_width;
    int original_height;
    int original_channel;
    int required_channel = 3;
    int user_key_returned;
    int current_function = 1;

    const char ascii_symbols[] = " .:-=+*#%&"; // These are the symbols in sequence , which we will be ploting , by using the brightness value

    while (1)
    {
        switch (current_function)
        {
        case 1:
        {
            user_key_returned = greet_01();

            if (user_key_returned == 10)
            {
                current_function++; // Going to to the next function
            }
            else if (user_key_returned == 127)
            {
                return 1; // Going back to the previous function
            }
            else if (user_key_returned == 27)
            {
                return 1; // For the force exit
            }
            break;
        }
        case 2:
        {
            user_key_returned = greet_02();

            if (user_key_returned == 10)
            {
                current_function++;
            }
            else if (user_key_returned == 127)
            {
                current_function--;
            }
            else if (user_key_returned == 27)
            {
                return 1;
            }
            break;
        }
        case 3:
        {
            user_key_returned = greet_03();

            if(user_key_returned == 1){
                return 1;
            }

            if (user_key_returned == 10)
            {
                choose_image();
            }
            else if (user_key_returned == 127)
            {
                current_function--;
            }
            else if (user_key_returned == 27)
            {
                return 1;
            }
            break;
        }
        }
    }

    unsigned char *image = stbi_load(image_name, &original_width, &original_height, &original_channel, required_channel); // stbi_load is a function provided by stb_image header file . Also i m trying to match the syntax with similar sort of varible name so that i could memoize it

    // Now we check if the image is actually loaded or not
    // If the image is not loaded for some reason , then stbi_load function will return NULL
    // I have made a function called check_image_validity function for this job, so i will just check and check its return value

    int image_validation_return_value = check_image_validity(image); // calling the function

    // I am writing the following check of the return value just to close the program instantly ,incase if the image provided by the user is invalid in someway.
    if (image_validation_return_value == 1)
    {
        return 1;
    }
    else
    {
    }
    per_pixel_mapping(original_height, original_width, required_channel, image, ascii_symbols);
    printf("\nProgram as reached its end.\n");
    return 0;
}