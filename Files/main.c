#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define Wrong_Arguments (-1)
#define Cannot_open_text (-2)
#define Cannot_open_dict (-3)

/*Reads and returns a word from a given file.*/
char* get_word_from_file(FILE *fp){

    /*The buffer to store the word.*/
    char word[255];
    int ch, i=0;

    /*Go over the chars in the file till a non spacing word is found (or the end of the file).*/
    while(EOF!=(ch=fgetc(fp)) && !(isalpha(ch) || !(isspace(ch))))
        continue;

    if(ch == EOF)
        return NULL;
    do{
        /*Builds the word's string*/
        word[i++] = (char)tolower(ch);
    }while(EOF!=(ch=fgetc(fp)) && (isalpha(ch) || !(isspace(ch))));

    /*Ends the string with the '\0' char, and returns the string.*/
    word[i]='\0';
    return strdup(word);
}

int main(int argc, char* argv[]){
    /*Checks if the arguments are valid*/
    if(argc != 3){
        printf("Usage: replace text_file dict_file");
        return Wrong_Arguments;
    }

    /*The pointer to the file for reading and replacing.*/
    FILE* fpr = fopen(argv[1], "r+");

    /*The file of the dictionary*/
    FILE* fpd = fopen(argv[2], "r+");

    /*The temporary file for writing the replaced text.*/
    FILE* fpt = fopen("temp.bamb", "w+");

    /*If one of the files was not opened => return an error message.*/
    if(fpr== NULL){
        printf("Cannot open the text file");
        return Cannot_open_text;
    }

    if(fpd== NULL){
        printf("Cannot open the dictionary file");
        return Cannot_open_dict;
    }

    /*The pointers for the words of the dictionary*/
    char* word1;
    char* word2;
    char* original_word;

    /*A variable for checking if the word has already been replaced.*/
    int bool = 0;

    /*Goes over the words in the given file.*/
    while (NULL != (original_word = get_word_from_file(fpr))){

        /*Goes over the words in the dictionary file.*/
        while ((NULL != (word1 = get_word_from_file(fpd))) && (NULL != (word2 = get_word_from_file(fpd)))) {
            /*If the word is the first loaded word => write the second word(and the opposite as well.)*/
            if (strcmp(word1, original_word) == 0) {
                fprintf(fpt, "%s ", word2);
                bool = 1;
                break;
            }
            if (strcmp(word2, original_word) == 0) {
                fprintf(fpt, "%s ", word1);
                bool = 1;
                break;
            }
        }
        /*Sets the file pointer to the start of the file.*/
        rewind(fpd);

        /*If the word was not replaced => write the original word*/
        if(bool == 0){
            fprintf(fpt, "%s ", original_word);
            bool = 0;
        }
    }

    int c;
    /*Sets the file pointers to the start.*/
    rewind(fpr);
    rewind(fpt);

    /*Copies the temp file to the input file.*/
    while (EOF != (c = fgetc(fpt))){
        fputc(c, fpr);
    }

    /*Closes the files.*/
    fclose(fpd);
    fclose(fpr);
    fclose(fpt);

    /*Deletes the temporary file.*/
    remove("temp.bamb");
    return 0;
}
