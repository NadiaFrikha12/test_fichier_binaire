#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char* applyModOperations(const char* binaryStr) {
    // Calculer la longueur de la chaîne binaire
    size_t binaryLength = strlen(binaryStr);
    
    // Allouer de la mémoire pour une nouvelle chaîne de caractères
    char* modifieBinary = (char*)malloc((binaryLength + 1) * sizeof(char));
    if (modifieBinary == NULL) {
        return NULL; // En cas d'échec de l'allocation mémoire, retourner NULL
    }
    
    modifieBinary[0] = '\0'; // Initialiser la chaîne de caractères modifiée comme une chaîne vide
    
    // Parcourir chaque caractère de la chaîne binaire
    for (size_t i = 0; i < binaryLength; i++) {
        // Appliquer des opérations de modification en fonction de la position dans la chaîne
        if (i % 2 == 0) {
            // Si l'indice est pair, effectuer un XOR avec 1
            modifieBinary[i] = (binaryStr[i] == '0') ? '1' : '0';
        } else {
            // Sinon, effectuer un AND avec 1
            modifieBinary[i] = (binaryStr[i] == '0') ? '0' : '1';
        }
    }
    
    modifieBinary[binaryLength] = '\0'; // Ajouter un caractère nul à la fin de la chaîne modifiée
    
    return modifieBinary; // Renvoyer la chaîne de caractères modifiée
}


char* binaryToText(const char* binary) {
	// Calculer la longueur de la chaîne binaire
    size_t binaryLength = strlen(binary);
    
    // Allouer de la mémoire pour la chaîne de texte
    char* textBuilder = (char*)malloc((binaryLength / 8 + 1) * sizeof(char)); // +1 pour le caractère nul
    if (textBuilder == NULL) {
        return NULL; // Si l'allocation échoue, renvoyer NULL
    }
    
    textBuilder[0] = '\0'; // Ajouter un caractère nul pour initialiser la chaîne
    
    // Boucle pour traiter la chaîne binaire par tranches de 8 bits
    for (size_t i = 0; i < binaryLength; i += 8) {
        // Prendre les 8 bits suivants
        char binaryChar[9]; // 8 bits + 1 pour le caractère nul
        strncpy(binaryChar, &binary[i], 8); // Copier 8 caractères à partir de la position i
        binaryChar[8] = '\0'; // Terminer la chaîne avec un caractère nul
        
        // Convertir le binaire en valeur ASCII
        int asciiValue = strtol(binaryChar, NULL, 2); // strtol convertit une chaîne binaire en décimal
        
        // Ajouter le caractère ASCII à la chaîne de texte
        size_t textLength = strlen(textBuilder);
        textBuilder[textLength] = (char)asciiValue; // Ajouter le caractère ASCII
        textBuilder[textLength + 1] = '\0'; // Ajouter un caractère nul à la fin de la chaîne de texte
    }
    
    return textBuilder; // Retourner la chaîne de texte convertie
}


char* readFile(const char* filename, long* file_size){
	FILE* fp;
	char* tampon; 
	size_t result;
	
	//ouvrir le fichier binaire en mode read binaire
	fp= fopen(filename,"rb");
	if(fp == NULL){
		printf("le fichier n'a pas pu etre ouvert");
		exit(-1);
	}
	
	//determination de la taille du fichier
	fseek(fp,0,SEEK_END); //se déplacer à la fin du fichier
	*file_size = ftell(fp); //la position actuelle dans le fichier, ce qui correspond à la taille totale du fichier
	rewind(fp); //réinitialiser la position du curseur 
	
	//allouer la memoire pour le tampon
	tampon=(char*)malloc((*file_size +1)*sizeof(char)); //+1 pour le dernier caractere null
	if(tampon == NULL){
		printf("erreur de l'allocation");
		fclose(fp); //fermer le fichier avant de quitter
		exit(-1);
	}
	
	//lire le contenu du fichier dans un tampon
	result = fread(tampon,1,*file_size,fp);
	if(result != *file_size){
		printf("erreur de la lecture");
		free(tampon);
		fclose(fp);
		exit(-1);
	}
	
	// Ajouter un caractère nul à la fin pour marquer la fin de la chaîne
    tampon[*file_size] = '\0';

    // Fermer le fichier
    fclose(fp);

    return tampon;
	
}

int main(){
	char* buffer;
    long file_size;
    char nom[20];

    // Lire le contenu du fichier "prepa.bin"
    buffer = readFile("prepa.bin", &file_size);

    // Appliquer les opérations de modification à la chaîne binaire lue
    char* originalBinary = applyModOperations(buffer);
	//convertir le binaire en text
    char* originalText = binaryToText(originalBinary);
    printf("%s",originalText);

    // Libérer la mémoire allouée
    if (buffer != NULL ){free(buffer);}
    if (originalBinary != NULL ){free(originalBinary);}
    
    return 0;
    
    
}
