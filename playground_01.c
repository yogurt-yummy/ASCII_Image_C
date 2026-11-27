// // I am making this playground to learn and test direct.h library . So that i dont mess up the main code while checking . I will comment it later on

// // Currently I am trying to read the directory using dirent.h

// #include <stdio.h>
// #include <dirent.h>
// #include <string.h>

// int main(){

//     // DIR *directory = opendir("./Images"); // DIR is a special type of data type provided by dirent.h . * for pointer and opendir is a function provided by dirent.h whose job is to just open the directory. and "." here this dot means current directory.

//     // if(directory == NULL){
//     //     printf("Could not open directory.\n");
//     //     return 1;
//     // }else{
//     //     printf("Successfully opend the directory.\n");
//     // }
//     // struct dirent *entry; // dirent is the structure which is already provided by the dirent library


//     // closedir(directory);

//     // Revise
//     // char file_names[500][200];

//     // // 1st Open the directory
//     // DIR *directory = opendir("./Images");

//     // // 2nd Check if the directory was opened successfully or not
//     // if(directory == NULL){
//     //     printf("Error Opening Directory.\n");
//     //     return 1;
//     // }else{
//     //     printf("Directory opened successfully.\n");
//     // }
    
//     // // 3rd Read the directory entries
//     // struct dirent *entries; // Entries here means like each of the file in directory is an entry

//     // int i = 0;
    
//     // while((entries = readdir(directory)) != NULL){ // now , the directory is read and its informations are kept in entries
//     //     printf("%s\n",entries->d_name);
//     //     char *extension = strrchr(entries->d_name,'.');
//     //     if((extension != NULL) && (strcmp(extension,".jpeg") == 0)){
//     //         printf("Its an image.");
//     //         strcpy(file_names[i],entries->d_name);

//     //     }else if((extension != NULL) && (strcmp(extension,".jpeg") != 0)){
//     //         printf("Its not images");
//     //     }
//     // }
//     // printf("\nImage name is %s .\n",file_names[0]);

//     DIR *directory = opendir("./Images");

//     if(directory == NULL){
//         printf("Error opening directory.\n");
//         return 1;
//     }else{
//         printf("Opened directory successfully.\n");
//     }

//     struct dirent *entries;

//     while((entries = readdir(directory)) != NULL){
//         // printf("\nFile name = %s .\n",entries->d_name);
//         char *extension = strrchr(entries->d_name,'.');

//         if(strcmp(extension,".jpeg") == 0){
//             printf("Acceptable file type found -> %s.\n",entries->d_name);
//         }
//     }

    
//     return 0;
// }