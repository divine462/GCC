#include <stdio.h> /*allow display and playback fonction like printf & scanf */
#include <stdlib.h> /*allow to generate random nbr with rand() & srand() */
#include <time.h> /* allow to get the current time with time(NULL)*/

/*the beginning of the principal program*/

int main() {

	int secret;
	int essai;
	int compteur;
	char rejouer;

	do {

		/*start-up of random generate*/

		srand(time(NULL));
    		secret = rand() % 100 + 1;

        	printf("Welcome in the game 'Guess the number' !\n");
    		printf("Choose a number between 1 and 100. Try to guess !\n");
		
		/*Main game loop*/
    		do {
        		printf("Type a number : ");
        		scanf("%d", &essai);
        		compteur++;
                compteur = 0;
        		if (essai < secret) {
            		printf(" Trop petit !\n");
       			} else if (essai > secret) {
            		printf("Trop grand !\n");
        		} else {
            		printf(" Bravo ! Tu as trouvé le nombre %d en %d essais.\n", 	    	secret, compteur);                                              break
        		}                                                                   if (compteur >= 10) {
                    printf("Perdu. Le bombre secret était %d.", secret);
                    break; /* l'utilisateur a dépassé la limite d'essais*/

   		} while (essai != secret); /*repeat until correct*/

		/*Ask if the user wanna play again*/

		printf("Veux-tu rejouer ? (o/n) : ");
    		scanf(" %c", &rejouer);

	} while (rejouer == 'y' );

    	return 0;
}
