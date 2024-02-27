#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char* applyModOperations(const char* binaryStr) {
    // Calculer la longueur de la cha�ne binaire
    size_t binaryLength = strlen(binaryStr);
    
    // Allouer de la m�moire pour une nouvelle cha�ne de caract�res
    char* modifieBinary = (char*)malloc((binaryLength + 1) * sizeof(char));
    if (modifieBinary == NULL) {
        return NULL; // En cas d'�chec de l'allocation m�moire, retourner NULL
    }
    
    modifieBinary[0] = '\0'; // Initialiser la cha�ne de caract�res modifi�e comme une cha�ne vide
    
    // Parcourir chaque caract�re de la cha�ne binaire
    for (size_t i = 0; i < binaryLength; i++) {
        // Appliquer des op�rations de modification en fonction de la position dans la cha�ne
        if (i % 2 == 0) {
            // Si l'indice est pair, effectuer un XOR avec 1
            modifieBinary[i] = (binaryStr[i] == '0') ? '1' : '0';
        } else {
            // Sinon, effectuer un AND avec 1
            modifieBinary[i] = (binaryStr[i] == '0') ? '0' : '1';
        }
    }
    
    modifieBinary[binaryLength] = '\0'; // Ajouter un caract�re nul � la fin de la cha�ne modifi�e
    
    return modifieBinary; // Renvoyer la cha�ne de caract�res modifi�e
}


char* binaryToText(const char* binary) {
	// Calculer la longueur de la cha�ne binaire
    size_t binaryLength = strlen(binary);
    
    // Allouer de la m�moire pour la cha�ne de texte
    char* textBuilder = (char*)malloc((binaryLength / 8 + 1) * sizeof(char)); // +1 pour le caract�re nul
    if (textBuilder == NULL) {
        return NULL; // Si l'allocation �choue, renvoyer NULL
    }
    
    textBuilder[0] = '\0'; // Ajouter un caract�re nul pour initialiser la cha�ne
    
    // Boucle pour traiter la cha�ne binaire par tranches de 8 bits
    for (size_t i = 0; i < binaryLength; i += 8) {
        // Prendre les 8 bits suivants
        char binaryChar[9]; // 8 bits + 1 pour le caract�re nul
        strncpy(binaryChar, &binary[i], 8); // Copier 8 caract�res � partir de la position i
        binaryChar[8] = '\0'; // Terminer la cha�ne avec un caract�re nul
        
        // Convertir le binaire en valeur ASCII
        int asciiValue = strtol(binaryChar, NULL, 2); // strtol convertit une cha�ne binaire en d�cimal
        
        // Ajouter le caract�re ASCII � la cha�ne de texte
        size_t textLength = strlen(textBuilder);
        textBuilder[textLength] = (char)asciiValue; // Ajouter le caract�re ASCII
        textBuilder[textLength + 1] = '\0'; // Ajouter un caract�re nul � la fin de la cha�ne de texte
    }
    
    return textBuilder; // Retourner la cha�ne de texte convertie
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
	fseek(fp,0,SEEK_END); //se d�placer � la fin du fichier
	*file_size = ftell(fp); //la position actuelle dans le fichier, ce qui correspond � la taille totale du fichier
	rewind(fp); //r�initialiser la position du curseur 
	
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
	
	// Ajouter un caract�re nul � la fin pour marquer la fin de la cha�ne
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

    // Appliquer les op�rations de modification � la cha�ne binaire lue
    char* originalBinary = applyModOperations(buffer);
	//convertir le binaire en text
    char* originalText = binaryToText(originalBinary);
    printf("%s",originalText);

    // Lib�rer la m�moire allou�e
    if (buffer != NULL ){free(buffer);}
    if (originalBinary != NULL ){free(originalBinary);}
    
    return 0;
    
    
}
