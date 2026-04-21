#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_ID 20
#define MAX_NOM 80
#define MAX_ADRESSE 80
#define MAX_VILLE 80
#define MAX_ETAT 20
#define MAX_PLACES_DISPO 10
#define MAX_CAPACITE_MAX 10
#define MAX_DATE_MAJ 20
#define MAX_AFF_PANNEAUX 10
#define MAX_PLAQUE 10
#define TARIF_HORAIRE 2.50


typedef struct {
    char id[MAX_ID];
    char nom[MAX_NOM];
    char adresse[MAX_ADRESSE];
    char ville[MAX_VILLE];
    char etat[MAX_ETAT];
    int places_dispo[MAX_PLACES_DISPO];
    int capacite[MAX_CAPACITE_MAX];
    char date_maj[MAX_DATE_MAJ];
    char aff[MAX_AFF_PANNEAUX];
} Parking;





typedef struct {
    char id_parking[MAX_ID];
    char plaque[MAX_PLAQUE];
    time_t heure_entree;
} Utilisateur;


typedef struct {
    char plaque[MAX_PLAQUE];
    float montant_paye;
    time_t heure_entree;
    time_t heure_sortie;
} SuiviClient;



int lesparkings(Parking parkings[],int nbparkings)
{

FILE *f = fopen("parking-metropole.csv","r");
if (f == NULL) {
    printf("Erreur ouverture fichier\n");
    return 0;}




fscanf (f, "%*[^\n]");
while (1){
      int ok=  fscanf (f, "%79[^;];%79[^;];%79[^;];%79[^;];%79[^;];%d;%d;%79[^;];%79[^\n]\n",
parkings[nbparkings].id,
parkings[nbparkings].nom,
parkings[nbparkings].adresse,
parkings[nbparkings].ville,
parkings[nbparkings].etat,
&parkings[nbparkings].places_dispo,
&parkings[nbparkings].capacite,
parkings[nbparkings].date_maj,
parkings[nbparkings].aff
);

if(ok!=9)
    break;
nbparkings++;
}

return nbparkings;

}




int Utilisateur_parking(Utilisateur utilisateurs[], int nbutilisateurs) {
    FILE *f = fopen("utilisateurs_parkings.csv", "r");
    if (f == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier utilisateur_parkings.csv\n");
        return nbutilisateurs;
    }
    fscanf(f, "%*[^\n]\n");
    while (1) {
        int ok = fscanf(f, "%79[^;];%79[^;];%ld\n",
utilisateurs[nbutilisateurs].id_parking,
utilisateurs[nbutilisateurs].plaque,
(long *)&utilisateurs[nbutilisateurs].heure_entree);

if (ok != 3)
    break;
nbutilisateurs++;
    }
    return nbutilisateurs;
}


void afficherparking(Parking parkings[], int nbparkings) {
    char id[20];
    printf("Entrez l'ID du parking : ");
    scanf("%s", id);

    for (int i = 0; i < nbparkings; i++) {
        if (strcmp(parkings[i].id, id) == 0) {
            printf("\n Informations Parking \n");
            printf("ID: %s\n", parkings[i].id);
            printf("Nom: %s\n", parkings[i].nom);
            printf("Adresse: %s\n", parkings[i].adresse);
            printf("Ville: %s\n", parkings[i].ville);
            printf("Etat: %s\n", parkings[i].etat);
            printf("Places Dispo: %d\n", parkings[i].places_dispo[0]);
            printf("Capacite: %d\n", parkings[i].capacite[0]);
            printf("MAJ: %s\n", parkings[i].date_maj);
            printf("Affichage: %s\n", parkings[i].aff);
            break;
        }

}
}






void afficherparkings(Parking parkings[], int nbparkings){
for (int i = 0; i < nbparkings; i++) {
    printf(" Parking num %d \n", i + 1);
    printf("ID: %s\n", parkings[i].id);
    printf("Nom: %s\n", parkings[i].nom);
    printf("Adresse: %s\n", parkings[i].adresse);
    printf("Ville: %s\n", parkings[i].ville);
    printf("Etat: %s\n", parkings[i].etat);
    printf("Places Dispo: %d\n", parkings[i].places_dispo[0]);
    printf("Capacite: %d\n", parkings[i].capacite[0]);
    printf("MAJ: %s\n", parkings[i].date_maj);
    printf("Affichage: %s\n\n", parkings[i].aff);
}
}


void afficherutilisateurs(Utilisateur utilisateurs[], int nbutilisateurs) {
    for (int i = 0; i < nbutilisateurs; i++) {
        printf(" id parking : %s \n", utilisateurs[i].id_parking);
        printf(" Plaque immat  : %s \n", utilisateurs[i].plaque);
        printf(" Heure entree : %s", ctime(&utilisateurs[i].heure_entree));
    }
}

void entreeparking(Parking parkings[], int nbparkings, Utilisateur utilisateurs[], int *nbutilisateurs)
{
    char id_rech[30];
    char plaque_rech[30];

    printf("ID du parking : ");
    scanf("%s", id_rech);

    printf("Plaque du vehicule : ");
    scanf("%s", plaque_rech);


    int index = -1;
    for (int i = 0; i < nbparkings; i++) {
        if (strcmp(parkings[i].id, id_rech) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Erreur : Parking introuvable.\n");
        return;
    }


    if (parkings[index].places_dispo[0] <= 0) {
        printf("Parking plein, impossible d'entrer.\n");
        return;
    }


    strcpy(utilisateurs[*nbutilisateurs].id_parking, id_rech);
    strcpy(utilisateurs[*nbutilisateurs].plaque, plaque_rech);
    utilisateurs[*nbutilisateurs].heure_entree = time(NULL);


    FILE *f = fopen("utilisateurs_parkings.csv", "a");
    if (f == NULL) {
        printf("Erreur : impossible d'ouvrir .csv\n");
        return;
    }

    fprintf(f, "%s;%s;%ld\n",
            id_rech,
            plaque_rech,
            (long)utilisateurs[*nbutilisateurs].heure_entree);

    fclose(f);

    (*nbutilisateurs)++;


    parkings[index].places_dispo[0]--;

    printf("\nVehicule enregistre avec succes !\n");
    printf("Heure d'entree : %s\n", ctime(&utilisateurs[*nbutilisateurs - 1].heure_entree));
}






void suiviClient(char plaque[], float montant, time_t entree, time_t sortie) {
    FILE *f = fopen("suivi.csv", "a");
 if (f != NULL) {
        char s_entree[20], s_sortie[20];
        struct tm tm_entree, tm_sortie;

        tm_entree = *localtime(&entree);
        strftime(s_entree, sizeof(s_entree), "%d/%m/%Y %H:%M:%S", &tm_entree);

        tm_sortie = *localtime(&sortie);
        strftime(s_sortie, sizeof(s_sortie), "%d/%m/%Y %H:%M:%S", &tm_sortie);

        fprintf(f, "%s;%.2f;%s;%s\n", plaque, montant, s_entree, s_sortie);
        fclose(f);
    }
}



void mettreAJourOccupation(Parking parkings[], int nbutilisateurs, char id[], int entree) {
    for (int i = 0; i < nbutilisateurs; i++) {
        if (strcmp(parkings[i].id, id) == 0) {
            if (entree == 1 && parkings[i].places_dispo[0] > 0) {
                parkings[i].places_dispo[0]--;
            }
            else if (entree == 0 && parkings[i].places_dispo[0] < parkings[i].capacite[0]) {
                parkings[i].places_dispo[0]++;
            }
            return;
        }
    }
}


void sortieparking(Parking parkings[], int nbparkings, Utilisateur utilisateurs[], int nbutilisateurs){
    char id_rech[30];
    char plaque_rech[30];
    int trouve = 0;

printf("Donnez l'id de votre parking:");
scanf("%s",id_rech);
printf("Donnez la plaque:");
scanf("%s",plaque_rech);


for(int i = 0; i<nbutilisateurs;i++){
    if (strcmp(utilisateurs[i].plaque,plaque_rech)==0 &&
        strcmp(utilisateurs[i].id_parking,id_rech)==0)
    {
        time_t heure_sortie = time(NULL);
        double sec = difftime(heure_sortie,utilisateurs[i].heure_entree);
        float duree = (float)sec/ 3600.0;
        float montant = duree*TARIF_HORAIRE;

        mettreAJourOccupation(parkings, nbparkings, id_rech, 0);

        suiviClient(plaque_rech, montant, utilisateurs[i].heure_entree, heure_sortie);

        trouve = 1;
        printf("payer: %.2f euros\n", montant);
        printf("vous etes dans le parkings depuis: %.1f heures\n",duree);

    }
    if(trouve =! 1)
        printf("\n erreur: vehicule introuvable\n");
}

}


int modeAdministrateur() {
    char codeSaisi[20];
    const char codeSecret[] = "1234";
    printf("\n--- Acces reserve ---\n");
    printf("Entrez le code secret : ");
    scanf("%s", codeSaisi);

    if (strcmp(codeSaisi, codeSecret) == 0) {
        printf("Acces autorise.\n");
        return 1;
    } else {
        printf("Code incorrect. Acces refuse.\n");
        return 0;
    }
}
void modifierDonneesParking(Parking parkings[], int nbutilisateurs) {
    char id_rech[30];
    int nouvelle_capa;

    printf("ID du parking a modifier : ");
    scanf("%s", id_rech);

    for (int i = 0; i < nbutilisateurs; i++) {

        if (strcmp(parkings[i].id, id_rech) == 0) {

            int ancienne_capa = parkings[i].capacite[0];
            int anciennes_places = parkings[i].places_dispo[0];

            printf("Parking : %s\n", parkings[i].nom);
            printf("Capacite actuelle : %d\n", ancienne_capa);
            printf("Places disponibles actuelles : %d\n", anciennes_places);

            printf("Nouvelle capacite : ");
            scanf("%d", &nouvelle_capa);


            parkings[i].capacite[0] = nouvelle_capa;

            int difference = nouvelle_capa - ancienne_capa;
            parkings[i].places_dispo[0] += difference;

            if (parkings[i].places_dispo[0] < 0)
                parkings[i].places_dispo[0] = 0;

            if (parkings[i].places_dispo[0] > nouvelle_capa)
                parkings[i].places_dispo[0] = nouvelle_capa;

            printf("\nModification enregistree !\n");
            printf("Nouvelle capacite : %d\n", parkings[i].capacite[0]);
            printf("Nouvelles places disponibles : %d\n", parkings[i].places_dispo[0]);

            return;
        }
    }


    printf("Erreur : Aucun parking trouve.\n");
}
int verifierPlacesDisponibles(Parking parkings[], int nbutilisateurs, char id_rech[]) {
    for (int i = 0; i < nbutilisateurs; i++) {

        if (strcmp(parkings[i].id, id_rech) == 0) {

            if (parkings[i].places_dispo[0] == 0) {
                return 1;
            } else {
                return 0;
            }
        }
    }
    return 1;
}

void sauvegarderEtatParking(Parking parkings[], int nbutilisateurs) {

    FILE *f = fopen("parking_maj.csv", "w");

    if (f == NULL) {
        printf("Erreur : Impossible de creer la copie de sauvegarde.\n");
        return;
    }

    for (int i = 0; i < nbutilisateurs; i++) {
        fprintf(f, "%s;%s;%s;%s;%d;%d;%s\n",
                parkings[i].id,
                parkings[i].nom,
                parkings[i].adresse,
                parkings[i].ville,
                parkings[i].capacite[0],
                parkings[i].places_dispo[0],
                parkings[i].etat);
    }

    fclose(f);
    printf("\n[SAUVEGARDE] Les donnees ont ete copiees dans 'parking_maj.csv'.\n");
}





int main()
{
    Parking parkings[100];
    Utilisateur utilisateurs[100];
    int nbparkings = 0;
    int n = lesparkings(parkings, nbparkings);
    int nbutilisateurs = 0;
    int m = Utilisateur_parking(utilisateurs, nbutilisateurs);

    int choix = -1;

    while (choix != 0) {
        printf("\n MENU GESTION PARKING \n");
        printf("1. Afficher un parking specifique\n");
        printf("2. Afficher tous les parkings\n");
        printf("3. Afficher tous les utilisateurs\n");
        printf("4. Entree d'un vehicule\n");
        printf("5. Sortie d'un vehicule\n");
        printf("6. Mode Administrateur\n");
        printf("7. Verification de la disponibilite\n");
        printf("0. Quitter\n");
        printf("Votre choix : ");

        scanf("%d", &choix);

        if (choix == 1) {
            afficherparking(parkings, n);
        }
        else if (choix == 2) {
            afficherparkings(parkings, n);
        }
        else if (choix == 3) {
            afficherutilisateurs(utilisateurs, m);
        }
        else if (choix == 4) {
            entreeparking(parkings, n, utilisateurs, &m);
            sauvegarderEtatParking(parkings,n);
        }
        else if (choix == 5) {
            sortieparking(parkings, n, utilisateurs, m);
            sauvegarderEtatParking(parkings,n);
        }
        else if (choix == 6) {
            if (modeAdministrateur()) {
                modifierDonneesParking(parkings,n);
                sauvegarderEtatParking(parkings,n);
            }
        }
        else if (choix == 7) {
            char id_rech[20];
            printf("ID parking:");
            scanf("%s",id_rech);
            if (verifierPlacesDisponibles(parkings,n, id_rech)== 1){
                printf("PLEIN\n");}
                else{printf("DISPONIBLE\n");}

        }
        else if (choix == 0) {
            printf("Sortie du menu !\n");
        }
        else {
            printf("Choix invalide, recommencez.\n");
        }
    }
    return 0;
}
