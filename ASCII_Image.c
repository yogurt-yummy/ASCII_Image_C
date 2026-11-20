#define STB_IMAGE_IMPLEMENTATION // As I learnt , #define STB_IMAGE_IMPLEMENTATION is used to also include the implementation of the header file which is stb_image in our case. And Also it is written before including the header file beacuase it tells the header file to include its implementation . If we include it after #include "stb_image.h" we wont be able to activate the implementation section
#include "stb_image.h"           // Including the header file we downloaded
#include <stdio.h>               // Including the standard input output library so that we could use functions like printf , scanf and more

int main()
{
    char image_name[] = "image.jpeg";
    int original_width;
    int original_height;
    int original_channel;
    int required_channel = 3;

    unsigned char *image = stbi_load(image_name, &original_width, &original_height, &original_channel, required_channel); // stbi_load is a function provided by stb_image header file . Also i m trying to match the syntax with similar sort of varible name so that i could memoize it

    // Now we check if the image is actually loaded or not
    // If the image is not loaded for some reason , then stbi_load function will return NULL
    if (image == NULL)
    {
        printf("Error loading the image.%s\n", stbi_failure_reason()); // I leant that stbi_failure_reason() function tells us the reason of error
    }
    else
    {
        printf("Image loaded successfully.\n");
    }

    // Now we calculate select the pixel position form the image
    int pixel_index;
    int original_row;
    int original_column;

    for (original_row = 0; original_row < original_height; original_row++) // Let me explain why we used < and not <= , this one was abit confusing to me but i got it now , so the width and heiht returned by the stbi_load function is the number of pixels , so they start from one , but while reading those pixels , we get array where indexing starts from 0 , thats why we use < and not <= . This applies to the loop below as well , i.e. original_column < original_width .
    {
        for (original_column = 0; original_column < original_width; original_column++)
        {
            pixel_index = ((original_row * original_width) + original_column) * required_channel; // Here lemme explain the formula myself , so , here , row * width takes us to the current row and adding column will take us to the current position , and we multiple with required channel , which is 3 here represent the red , green and blue value of the particular pixl . so we are reading those 3 value of each pixel.
        }
    }
    printf("Origina_row = %d.\n",original_row);
    printf("Original_column = %d.\n",original_column);
    printf("Width = %d.\n",original_width);
    printf("Height = %d.\n",original_height);
    return 0;
}