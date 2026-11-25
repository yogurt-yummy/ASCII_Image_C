#define STB_IMAGE_IMPLEMENTATION // As I learnt , #define STB_IMAGE_IMPLEMENTATION is used to also include the implementation of the header file which is stb_image in our case. And Also it is written before including the header file beacuase it tells the header file to include its implementation . If we include it after #include "stb_image.h" we wont be able to activate the implementation section
#include "stb_image.h"           // Including the header file we downloaded
#include <stdio.h>               // Including the standard input output library so that we could use functions like printf , scanf and more
#include <ncurses.h>             // I am including this library(external) to use getch() especially . (just wanted to make someting like navigation through a sort of story) btw it takes over the terminal to use its own function , dont know why but it sound scary

int calculate_brightness(int, int, int);   // This is function decleration and I am writing this to declare that this to tell me program that this funciton exists.
int calculate_symbol_index(int);           // This is another function decleration
int greet_01(void);                        // I am declaring this funciton for instruction / greeting
int greet_02(void);                        // I am declaring this function for instruction / greeting
int check_image_validity(unsigned char *); // I am declaring this function for check if the image exist or not , or if its valid type or not

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

    printw("Hello!\n"); // This is abit annoying but the ncurses library uses printw function instead of printf , I tried using initilizing and endinf the its use only in getch , but the terminal output was getting abit weird and was recommended to use it this way.
    printw("\n");
    printw("Press ESC to exit the program.\n");
    printw("Press ENTER to continue...");

    refresh();

    int user_key = getch();

    clear(); // clearing the screen

    refresh(); // refreshing the terminal

    endwin(); // endwin is a function from ncurses which just resets the terminal to its normal state

    printf("You Pressed %d .\n", user_key);

    return user_key;
}

// Another function to continue the instruction
int greet_02(void)
{

    initscr();

    printw("I will tell you how to use this Image to ASCII converter. Ready ?\n\n");

    printw("Press backspace to go back...\n");
    printw("Press enter to continue...");

    refresh();

    int user_key = getch();

    endwin();

    return user_key;
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

int main()
{
    char image_name[] = "image.jpeg";
    int original_width;
    int original_height;
    int original_channel;
    int required_channel = 3;
    int user_key_returned;

    const char ascii_symbols[] = " .:-=+*#%&"; // These are the symbols in sequence , which we will be ploting , by using the brightness value

    // while (user_key_returned != 27)
    // {
    //     user_key_returned = greet_01();
    //     if (user_key_returned == 10)
    //     {
    //         user_key_returned = greet_02();
    //     }
    //     else if (user_key_returned == 27)
    //     {
    //         break;
    //     }
    //     break;
    // }

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

    // Now we calculate select the pixel position form the image
    int pixel_index;
    int original_row;
    int original_column;

    // for (original_row = 0; original_row < original_height; original_row++) // Let me explain why we used < and not <= , this one was abit confusing to me but i got it now , so the width and heiht returned by the stbi_load function is the number of pixels , so they start from one , but while reading those pixels , we get array where indexing starts from 0 , thats why we use < and not <= . This applies to the loop below as well , i.e. original_column < original_width .
    // {
    //     for (original_column = 0; original_column < original_width; original_column++)
    //     {
    //         pixel_index = ((original_row * original_width) + original_column) * required_channel; // Here lemme explain the formula myself , so , here , row * width takes us to the current row and adding column will take us to the current position , and we multiple with required channel , which is 3 here represent the red , green and blue value of the particular pixl . so we are reading those 3 value of each pixel.

    //         // printf("%d\t",pixel_index); If you try to print pixel index like i did , you will see that the difference in each index is 3 . and this is beacuase we take the pixel and skip 3 values of it as it would give rgb value of the same pixel

    //         unsigned char red_value = image[pixel_index]; // we use unsigned char here because the rgb value of the pixel is exactly ranging from 0 to 255 , and the unsigned char stores exactly upto 255 . So , its like made for this.
    //         unsigned char green_value = image[pixel_index + 1];
    //         unsigned char blue_value = image[pixel_index + 2];

    //         int brightness_returned = calculate_brightness(red_value, green_value, blue_value); // This is function call. I am using the function I decleared earlier
    //         // printf("Brightness : %d \n",brightness_returned); I printed it only for checking

    //         int symbol_index_value = calculate_symbol_index(brightness_returned);

    //         // printf("Symbol_index_value = %d\n",symbol_index_value);

    //         printf("%c", ascii_symbols[symbol_index_value]);
    //     }
    //     printf("\n");
    // }
    printf("\nProgram as reached its end.\n");
    return 0;
}