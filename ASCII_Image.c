#define STB_IMAGE_IMPLEMENTATION // As I learnt , #define STB_IMAGE_IMPLEMENTATION is used to also include the implementation of the header file which is stb_image in our case. And Also it is written before including the header file beacuase it tells the header file to include its implementation . If we include it after #include "stb_image.h" we wont be able to activate the implementation section
#include "stb_image.h"           // Including the header file we downloaded
#include <stdio.h>               // Including the standard input output library so that we could use functions like printf , scanf and more

int main()
{
    char image_name[] = "imagee.jpeg";
    int width;
    int height;
    int original_channel;
    int required_channel = 3;

    unsigned char *image = stbi_load(image_name,&width,&height,&original_channel,required_channel); // stbi_load is a function provided by stb_image header file . Also i m trying to match the syntax with similar sort of varible name so that i could memoize it

    // Now we check if the image is actually loaded or not
    // If the image is not loaded for some reason , then stbi_load function will return NULL
    if(image == NULL){
        printf("Error loading the image.%s\n",stbi_failure_reason()); // I leant that stbi_failure_reason() function tells us the reason of error
    }else{
        printf("Image loaded successfully.\n");
    }
    return 0;
}